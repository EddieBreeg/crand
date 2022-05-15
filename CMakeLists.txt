cmake_minimum_required(VERSION 3.9)
project(rand VERSION 2.0)

if(NOT ${CMAKE_BUILD_TYPE})
set(${CMAKE_BUILD_TYPE} Debug)
endif()

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

add_compile_definitions(
    CRAND_VERSION=1
    CRAND_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
    CRAND_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
    CRAND_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
)

add_library(crand 
    src/sys_rng.c
    src/xoshiro.c
    src/ctr.c
    src/aes/luts.c
    src/lfsr.c
    src/aes/aes.c
    src/chacha20/chacha20.c
    src/xorshift.c
    src/version.c
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
    src/version.c
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

add_executable(ctr tests/ctr.cpp)
add_executable(sys_rng tests/sys_rng.cpp)
add_executable(tests tests/tests.cpp)
add_executable(std_tests tests/std_test.cpp)

target_link_libraries(ctr cpprand crand)
target_link_libraries(sys_rng cpprand crand)
target_link_libraries(tests cpprand crand)
target_link_libraries(std_tests cpprand)

install(TARGETS crand cpprand DESTINATION lib)
install(DIRECTORY ./include/crand DESTINATION include)