#include "Controller.h"

#include <future>
#include <iterator>
#include <vector>
#include <list>

namespace controller
{
	Controller::Controller(std::size_t map_threads, std::size_t reduce_threads)
			: m_map_threads(map_threads), m_reduce_threads(reduce_threads)
	{
	}

	std::vector<std::string>
	Controller::map(const std::vector<split::FileRange>& range_vector, const map::Map& map_functor,
			ThreadPool& map_workers)
	{
		using map_result_t = std::future<std::list<std::string>>;
		using Iter = std::list<std::string>::iterator;

		std::vector<map_result_t> mapped(m_map_threads);
		for (std::size_t i = 0; i < m_map_threads; ++i)
		{
			auto map_job = [i, &range_vector, &map_functor]() -> std::list<std::string>
			{
				return map_functor(range_vector[i]);
			};
			mapped[i] = map_workers.enqueue(map_job);
		}

		std::list<std::string> list_merge;
		for (map_result_t& future_result: mapped)
			list_merge.merge(future_result.get());

		std::vector<std::string> map_result_vector(std::move_iterator<Iter>(list_merge.begin()),
				std::move_iterator<Iter>(list_merge.end()));
		return map_result_vector;
	}

	bool
	Controller::reduce(const std::vector<std::string>& map_result_vector, const reduce::reduce_t& reduce_functor,
			ThreadPool& reduce_workers)
	{
		using it = std::vector<std::string>::const_iterator;
		auto range_vector = std::vector<std::pair<it, it>>(m_reduce_threads);

		std::ptrdiff_t step = map_result_vector.size() / m_reduce_threads;
		it prev = map_result_vector.begin();
		it next;
		for (std::size_t i = 0; i < m_reduce_threads; ++i)
		{
			next = (map_result_vector.end() - prev < step ? map_result_vector.end() : prev + step);
			if (next == map_result_vector.end())
			{
				range_vector[i].first = prev;
				range_vector[i].second = next;
				prev = next;
				continue;
			}
			while ((std::next(next) != map_result_vector.end()) && (*std::next(next) == *next))
				++next;
			range_vector[i].first = prev;
			range_vector[i].second = std::next(next);
			prev = std::next(next);
		}

		std::vector<std::future<bool>> reducer(m_reduce_threads);
		for (std::size_t i = 0; i < m_reduce_threads; ++i)
		{
			auto reduce_job = [reduce_functor, i, &range_vector]() -> bool
			{
				return reduce_functor(range_vector[i].first, range_vector[i].second);
			};
			reducer[i] = reduce_workers.enqueue(reduce_job);
		}

		bool answer = true;
		for (std::future<bool>& future_result: reducer)
		{
			if (!future_result.get())
				answer = false;
		}
		return answer;
	}

	std::size_t Controller::do_work(const std::string& filename)
	{

		std::vector<split::FileRange> range_vector = split::Split{ filename }.split(m_map_threads);

		std::size_t prefix_length = 1;
		std::vector<std::string> map_result_vector;

		ThreadPool map_workers(m_map_threads);
		ThreadPool reduce_workers(m_reduce_threads);

		for (;; ++prefix_length)
		{
			{
				map::Map m(filename, prefix_length);
				map_result_vector = map(range_vector, m, map_workers);
			}
			if (reduce(map_result_vector, &reduce::reduce, reduce_workers))
				break;
		}

		return prefix_length;
	}

}