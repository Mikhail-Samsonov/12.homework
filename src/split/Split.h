#ifndef TASK_12_SPLIT_H
#define TASK_12_SPLIT_H

#include "ISplit.h"

namespace split {

	class Split : public ISplit {
	public:
		using ISplit::ISplit;

		virtual std::vector<FileRange> split(std::size_t count) const;
		virtual ~Split() = default;
	private:
	};

}

#endif //TASK_12_SPLIT_H
