#include "Map.h"

namespace map {
	std::list<std::string> Map::operator()(split::FileRange range) const
	{
		std::string scope = do_read(range);
		std::string line;
		std::istringstream stream{ scope };
		std::list<std::string> lst;
		while (std::getline(stream, line, '\n')) {
			if (m_prefix_length > line.size())
				throw std::runtime_error("unique prefix doesn't exists");

			lst.emplace_back(line.substr(0, m_prefix_length));
		}
		lst.sort();
		return lst;
	}

	std::string Map::do_read(split::FileRange range) const
	{
		std::ifstream stream{ filename() };
		stream.seekg(range.first);
		std::string str(range.second - range.first, '\0');
		stream.read(str.data(), range.second - range.first);
		return str;
	}

	Map::Map(std::string filename, std::size_t prefix_length)
			:IMap(std::move(filename)),
			 m_prefix_length{ prefix_length } { }
}