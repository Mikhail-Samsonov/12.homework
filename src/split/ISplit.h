#ifndef TASK_12_ISPLIT_H
#define TASK_12_ISPLIT_H

#include <fstream>
#include <string>
#include <vector>

namespace split {

	using FileRange = std::pair<std::ifstream::pos_type, std::ifstream::pos_type>;

	class ISplit {
	public:
		ISplit(std::string filename)
				:m_filename{ std::move(filename) } { };
		virtual std::vector<FileRange> split(std::size_t count) const = 0;
		virtual ~ISplit() = default;
	protected:
		const std::string& filename() const
		{
			return m_filename;
		}
	private:
		std::string m_filename;
	};

}

#endif //TASK_12_ISPLIT_H
