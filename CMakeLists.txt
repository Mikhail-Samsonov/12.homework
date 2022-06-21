cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PATCH_VERSION 0.0.${PATCH_VERSION})
project(mapreduce VERSION ${PATCH_VERSION})

set(HEADERS
        src/thread_pool/ThreadPool.h
        src/split/ISplit.h
        src/split/Split.h
        src/map/Map.h
        src/map/IMap.h
        src/reduce/Reduce.h
        src/controller/Controller.h
        )

set(SOURCES
        src/thread_pool/ThreadPool.cpp
        src/split/Split.cpp
        src/map/Map.cpp
        src/reduce/Reduce.cpp
        src/controller/Controller.cpp
        )

add_executable(mapreduce
        main.cpp
        ${SOURCES}
        ${HEADERS}
        )

target_include_directories(mapreduce PRIVATE "${CMAKE_SOURCE_DIR}/src/map")
target_include_directories(mapreduce PRIVATE "${CMAKE_SOURCE_DIR}/src/split")
target_include_directories(mapreduce PRIVATE "${CMAKE_SOURCE_DIR}/src/thread_pool")
target_include_directories(mapreduce PRIVATE "${CMAKE_SOURCE_DIR}/src/reduce")
target_include_directories(mapreduce PRIVATE "${CMAKE_SOURCE_DIR}/src/controller")

target_link_libraries(mapreduce pthread)

set_target_properties(mapreduce PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

#set_target_properties(mapreduce PROPERTIES COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
#set_target_properties(mapreduce PROPERTIES LINK_FLAGS "-fsanitize=address -fno-omit-frame-pointer")

enable_testing()
add_subdirectory(test)


set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT mesamsonov@mail.ru)

include(CPack)