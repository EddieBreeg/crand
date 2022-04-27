cmake_minimum_required(VERSION 3.2)
project(rand VERSION 0.1.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
add_library(rand rand.c)

# windows version requires bcrypt to compile
if(WIN32)
link_directories(./lib)
target_link_libraries(rand bcrypt_provider)
endif(WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(test test.c)
target_link_libraries(test rand)