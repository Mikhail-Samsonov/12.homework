#ifndef TASK_12_CONTROLLER_H
#define TASK_12_CONTROLLER_H

#include "Map.h"
#include "Reduce.h"
#include "ISplit.h"
#include "Split.h"
#include "ThreadPool.h"

#include <string>
#include <vector>

namespace controller {
	class Controller {
	public:
		Controller(std::size_t map_threads, std::size_t reduce_threads);

		std::size_t do_work(const std::string& filename);

	private:
		std::vector<std::string> map(const std::vector<split::FileRange>& ranges, const map::Map& mapper,
				ThreadPool& map_workers);

		bool reduce(const std::vector<std::string>& ranges, const reduce::reduce_t& reducer,
				ThreadPool& reduce_workers);

		std::size_t m_map_threads;
		std::size_t m_reduce_threads;
	};
}

#endif //TASK_12_CONTROLLER_H
