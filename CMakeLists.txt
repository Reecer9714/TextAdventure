#cmake version to be used
cmake_minimum_required( VERSION 3.0 )
set(CMAKE_CXX_STANDARD 20)

# project name
project( text_adventure )

# flags


# include
include_directories(src)

# files
file(GLOB SRC_FILES src/**/*.cpp)
add_executable( main src/main.cpp ${SRC_FILES} )

# data files
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# tests
include(GoogleTest)
file(GLOB TEST_FILES test/**/*.cpp)
add_executable( gtest test/test-main.cpp ${SRC_FILES} ${TEST_FILES} )
include_directories( gtest test)
gtest_discover_tests( gtest AUTO )

# tests flags
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(gtest PRIVATE Threads::Threads)