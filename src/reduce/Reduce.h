#ifndef TASK_12_REDUCE_H
#define TASK_12_REDUCE_H

#include <functional>
#include <string>
#include <vector>

namespace reduce
{

	using reduce_iterator = std::vector<std::string>::const_iterator;
	using reduce_t = std::function<bool (reduce_iterator begin, reduce_iterator end)>;

	//look for duplicates
	bool reduce(reduce_iterator begin, reduce_iterator end);

} // namespace reduce

#endif //TASK_12_REDUCE_H
