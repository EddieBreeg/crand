cmake_minimum_required(VERSION 3.9)
project(rand VERSION 0.1.0)

if(NOT ${CMAKE_BUILD_TYPE})
set(${CMAKE_BUILD_TYPE} Debug)
endif()

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

add_library(crand 
    src/sys_rng.c
    src/xoshiro.c
    src/ctr.c
    src/aes/luts.c
    src/lfsr.c
    src/aes/aes.c
    src/chacha20/chacha20.c
)


add_library(cpprand 
    src/sys_rng.cpp
    src/lfsr.cpp
    src/ctr.cpp
    src/xorshift.cpp
    src/xoshiro.cpp
    src/aes/luts.c
    src/aes/aes.cpp
    src/chacha20/chacha20.cpp
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

add_executable(c_sys_rng tests/sys_rng.c)
add_executable(c_ctr tests/ctr.c)
add_executable(cpp_ctr tests/ctr.cpp)
add_executable(cpp_sys_rng tests/sys_rng.cpp)
add_executable(c_xoshiro tests/xoshiro.c)
add_executable(cpp_xoshiro tests/xoshiro.cpp)
add_executable(c_lfsr tests/lfsr.c)
add_executable(cpp_lfsr tests/lfsr.cpp)

target_link_libraries(c_sys_rng crand)
target_link_libraries(c_xoshiro crand)
target_link_libraries(cpp_xoshiro cpprand)
target_link_libraries(c_lfsr crand)
target_link_libraries(cpp_lfsr cpprand)
target_link_libraries(c_ctr crand)
target_link_libraries(cpp_ctr cpprand)
target_link_libraries(cpp_sys_rng cpprand)