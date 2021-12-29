#include <iostream>
#include "Controller.h"

int main(int argc, char* argv[])
{
	try {
		std::istringstream src(argv[1]);
		std::string src_str;
		src >> src_str;

		std::istringstream map_thread_num_str(argv[2]);
		std::size_t map_thread_num_size_t;
		map_thread_num_str >> map_thread_num_size_t;

		std::istringstream reduce_thread_num_str(argv[3]);
		std::size_t reduce_thread_num_size_t;
		reduce_thread_num_str >> reduce_thread_num_size_t;

		controller::Controller controller(map_thread_num_size_t, reduce_thread_num_size_t);
		std::size_t n = controller.do_work(src_str);
		std::cout << "minimum prefix is " << n << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
}
