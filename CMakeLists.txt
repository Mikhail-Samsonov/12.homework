cmake_minimum_required(VERSION 3.19)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PATCH_VERSION 0.0.${PATCH_VERSION})
project(task_12 VERSION ${PATCH_VERSION})

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

add_executable(task_12
        main.cpp
        ${SOURCES}
        ${HEADERS}
        )

target_include_directories(task_12 PRIVATE "${CMAKE_SOURCE_DIR}/src/map")
target_include_directories(task_12 PRIVATE "${CMAKE_SOURCE_DIR}/src/split")
target_include_directories(task_12 PRIVATE "${CMAKE_SOURCE_DIR}/src/thread_pool")
target_include_directories(task_12 PRIVATE "${CMAKE_SOURCE_DIR}/src/reduce")
target_include_directories(task_12 PRIVATE "${CMAKE_SOURCE_DIR}/src/controller")

target_link_libraries(task_12 pthread)

set_target_properties(task_12 PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

#set_target_properties(task_12 PROPERTIES COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
#set_target_properties(task_12 PROPERTIES LINK_FLAGS "-fsanitize=address -fno-omit-frame-pointer")

if(MSVC)
    target_compile_options(task_12 PRIVATE
            /W4
            )
else()
    target_compile_options(task_12 PRIVATE
            -Werror -Wall -Wimplicit-fallthrough -pedantic-errors
            )
endif()

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT mesamsonov@mail.ru)

include(CPack)