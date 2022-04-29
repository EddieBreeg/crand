cmake_minimum_required(VERSION 3.9)
project(rand VERSION 0.1.0)

if(NOT ${CMAKE_BUILD_TYPE})
set(${CMAKE_BUILD_TYPE} Debug)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

add_library(crand 
    src/sys_rng.c
)
add_library(cpprand 
    src/sys_rng.cpp
)

# windows version requires bcrypt to compile
if(WIN32)
set(BCRYPT_BIN_DIR 
    "C:\\Program Files (x86)\\Windows Kits\\10\\Cryptographic Provider Development Kit\\Lib\\x64"
    CACHE STRING
    "The location of the bcrypt binary files"
)
message(BCRYPT_BIN_DIR="${BCRYPT_BIN_DIR}")
link_directories(${BCRYPT_BIN_DIR})
target_link_libraries(crand bcrypt_provider)
endif(WIN32)

add_executable(test test.c)
add_executable(cpptest test.cpp)
target_link_libraries(test crand)
target_link_libraries(cpptest cpprand)