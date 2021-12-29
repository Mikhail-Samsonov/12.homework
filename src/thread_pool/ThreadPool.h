#ifndef TASK_12_THREADPOOL_H
#define TASK_12_THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

class ThreadPool {
public:
	using Task = std::function<void()>;

	explicit ThreadPool(std::size_t num_threads)
	{
		start(num_threads);
	}

	~ThreadPool()
	{
		stop();
	}

	template<typename T>
	auto enqueue(T task) -> std::future<decltype(task())>;

private:
	std::vector<std::thread> m_threads;

	std::condition_variable m_event_var;

	std::mutex m_event_mutex;
	bool m_stopping = false;

	std::queue<Task> m_tasks;

	void start(std::size_t num_threads);

	void stop();
};

template<typename T>
auto ThreadPool::enqueue(T task) -> std::future<decltype(task())>
{
	auto wrapper = std::make_shared<std::packaged_task<decltype(task())() >>(std::move(task));
	{
		std::unique_lock<std::mutex> lock{ m_event_mutex };
		m_tasks.emplace([=] {
		  (*wrapper)();
		});
	}

	m_event_var.notify_one();
	return wrapper->get_future();
}

#endif //TASK_12_THREADPOOL_H
