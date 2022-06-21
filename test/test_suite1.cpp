#include "gtest/gtest.h"
#include <iostream>
#include "Controller.h"

extern char** my_argv;

TEST(suite1, name1)
{

	std::istringstream src(my_argv[1]);
	std::string src_str;
	src >> src_str;

	std::istringstream map_thread_num_str(my_argv[2]);
	std::size_t map_thread_num_size_t;
	map_thread_num_str >> map_thread_num_size_t;

	std::istringstream reduce_thread_num_str(my_argv[3]);
	std::size_t reduce_thread_num_size_t;
	reduce_thread_num_str >> reduce_thread_num_size_t;

	controller::Controller controller(map_thread_num_size_t, reduce_thread_num_size_t);
	std::size_t n = controller.do_work(src_str);

	ASSERT_EQ(n, 2);

}

