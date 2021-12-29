#ifndef TASK_12_MAP_H
#define TASK_12_MAP_H

#include "IMap.h"
#include "Split.h"
#include "ISplit.h"
#include <string>
#include <sstream>

namespace map {
	class Map : public IMap<std::string> {
	public:
		Map(std::string filename, std::size_t prefix_length);

		std::list<std::string> operator()(split::FileRange range) const override;
	private:
		[[nodiscard]] std::string do_read(split::FileRange range) const;

		std::size_t m_prefix_length;
	};
}

#endif //TASK_12_MAP_H
