#include "ThreadPool.h"

void ThreadPool::start(std::size_t num_threads)
{
	for (auto i = 0u; i < num_threads; ++i) {
		m_threads.emplace_back(
				[=] {
				  while (true) {
					  Task task;
					  {
						  std::unique_lock<std::mutex> lock(m_event_mutex);

						  m_event_var.wait(lock, [=] { return m_stopping || !m_tasks.empty(); });

						  if (m_stopping && m_tasks.empty())
							  break;

						  task = std::move(m_tasks.front());
						  m_tasks.pop();
					  }

					  task();
				  }
				}
		);
	}
}

void ThreadPool::stop()
{
	{
		std::unique_lock<std::mutex> lock(m_event_mutex);
		m_stopping = true;
	}

	m_event_var.notify_all();

	for (auto& thread: m_threads)
		thread.join();
}