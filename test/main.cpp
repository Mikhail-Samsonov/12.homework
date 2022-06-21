#include "gtest/gtest.h"

char** my_argv;

int main(int argc, char** argv)
{
	my_argv = argv;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}