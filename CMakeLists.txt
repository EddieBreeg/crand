cmake_minimum_required(VERSION 3.2)
project(rand VERSION 0.1.0)

if(NOT ${CMAKE_BUILD_TYPE})
set(${CMAKE_BUILD_TYPE} Debug)
endif()
if($<CONFIG>)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}/$<CONFIG>)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)
    else()
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
endif()

include_directories(include)

add_library(rand src/sys_rng.c)
set(${CMAKE_Release_POSTFIX} "")

# windows version requires bcrypt to compile
if(WIN32)
set(BCRYPT_BIN_DIR 
    "C:\\Program Files (x86)\\Windows Kits\\10\\Cryptographic Provider Development Kit\\Lib\\x64"
    CACHE STRING
    "The location of the bcrypt binary files"
)
message(BCRYPT_BIN_DIR="${BCRYPT_BIN_DIR}")
link_directories(${BCRYPT_BIN_DIR})
target_link_libraries(rand bcrypt_provider)
endif(WIN32)



add_executable(test test.c)
target_link_libraries(test rand)