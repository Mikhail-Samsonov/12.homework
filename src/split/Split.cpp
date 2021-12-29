#include "ISplit.h"
#include "Split.h"

namespace split {
	std::vector<FileRange> Split::split(std::size_t count) const
	{
		std::ifstream::pos_type filesize = std::ifstream(filename(), std::ios::in | std::ios::app).tellg();

		if (filesize == std::ifstream::pos_type(-1))
			throw std::runtime_error("Error while opening file");

		std::ifstream::pos_type step = filesize / count;
		std::ifstream::pos_type cur_pos;
		std::ifstream::pos_type prev_pos = { 0 };

		std::vector<FileRange> ranges(count);

		std::ifstream stream{ filename() };

		for (std::size_t i = 0; i < count; ++i) {
			cur_pos = (filesize - prev_pos) < step ? filesize : prev_pos + step;
			stream.seekg(cur_pos);
			while ((cur_pos < filesize) && (stream.peek() != '\n')) {
				cur_pos += 1;
				stream.seekg(cur_pos);
			}
			ranges[i].first = prev_pos;
			ranges[i].second = cur_pos;
			prev_pos = cur_pos;
			if (prev_pos != filesize)
				prev_pos += 1;
		}

		return ranges;
	}
}

