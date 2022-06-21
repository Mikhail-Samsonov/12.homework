cmake_minimum_required(VERSION 3.10)

project(test)


configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/googletest-download)

add_subdirectory(${CMAKE_BINARY_DIR}/test/googletest-src
        ${CMAKE_BINARY_DIR}/test/googletest-build)


file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE TESTS "${CMAKE_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM TESTS "${CMAKE_SOURCE_DIR}/test/main.cpp")

foreach (file ${TESTS})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${HEADERS}
            ${SOURCES}
            ${file}
            ${CMAKE_SOURCE_DIR}/test/main.cpp)
    target_link_libraries("${name}_tests" gtest_main pthread)

    target_include_directories("${name}_tests" PRIVATE "${CMAKE_SOURCE_DIR}/src/map")
    target_include_directories("${name}_tests" PRIVATE "${CMAKE_SOURCE_DIR}/src/split")
    target_include_directories("${name}_tests" PRIVATE "${CMAKE_SOURCE_DIR}/src/thread_pool")
    target_include_directories("${name}_tests" PRIVATE "${CMAKE_SOURCE_DIR}/src/reduce")
    target_include_directories("${name}_tests" PRIVATE "${CMAKE_SOURCE_DIR}/src/controller")

    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach ()