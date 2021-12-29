#include "Reduce.h"

namespace reduce {
	bool reduce(reduce_iterator begin, reduce_iterator end)
	{
		if (begin == end)
			return true;
		for (auto it = std::next(begin); it != end; ++it)
			if (*std::prev(it) == *it)
				return false;
		return true;
	}
}