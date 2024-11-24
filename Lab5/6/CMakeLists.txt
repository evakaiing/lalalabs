cmake_minimum_required(VERSION 3.10)
project(VectorTest)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(VectorTest unit.cpp vector.hpp)
target_link_libraries(VectorTest ${GTEST_LIBRARIES} pthread)

add_custom_target(valgrind_check
    COMMAND valgrind --leak-check=full --error-exitcode=1 ./VectorTest
    DEPENDS VectorTest
    COMMENT "valgrind: "
)