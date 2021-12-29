#ifndef TASK_12_IMAP_H
#define TASK_12_IMAP_H

#include "Split.h"

#include <string>
#include <list>
#include <stdexcept>

namespace map {
	template<typename T>
	class IMap {
	public:
		IMap(std::string filename)
				:m_filename{ std::move(filename) } { };

		virtual std::list<T> operator()(split::FileRange range) const = 0;

		virtual ~IMap() = default;
	protected:
		const std::string& filename() const
		{
			return m_filename;
		}
	private:
		std::string m_filename;
	};
}

#endif //TASK_12_IMAP_H
