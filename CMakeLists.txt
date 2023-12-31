# 参考：
# https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html
#

cmake_minimum_required(VERSION 3.10)
project(cppboot)

# enable c++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# default build debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

option(CPPBOOT_BUILD_EXAMPLES "Build samples" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third_party)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -fPIC -Wall -O0 -g --coverage")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -fPIC -Wall  -O0 -g --coverage")

add_definitions(-DCPPBOOT_OPTION_HARDENED=0)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${THIRD_PARTY_DIR}/googletest-1.12.1/googlemock/include
    ${THIRD_PARTY_DIR}/googletest-1.12.1/googletest/include
    ${THIRD_PARTY_DIR}/asio-1.28.0/include
)

enable_testing()

add_subdirectory(${THIRD_PARTY_DIR}/googletest-1.12.1)
add_subdirectory(cppboot)
add_subdirectory(tests)

add_custom_target(lcov
    lcov -c 
    -t cppboot
    -o ${CMAKE_BINARY_DIR}/lcov.info
    -d ${PROJECT_SOURCE_DIR} 
    -b ${PROJECT_SOURCE_DIR} 
    COMMAND
    lcov 
    -r ${CMAKE_BINARY_DIR}/lcov.info
    -o ${CMAKE_BINARY_DIR}/lcov.info
    '*/third_party/*' 
    '/usr/include/*'
    '*/cppboot/base/internal/fmt/*'
    '*/cppboot/base/internal/json/*'
    '*/examples/*'
    '*/tests/*'
    '*/*_test.cc'
    '*/*.test.cc'
)

add_custom_target(lcov_html
    genhtml -o ${CMAKE_BINARY_DIR}/coverage ${CMAKE_BINARY_DIR}/lcov.info
)

if(CPPBOOT_BUILD_EXAMPLES)
    add_subdirectory(examples)
    add_subdirectory(${THIRD_PARTY_DIR}/asio-1.28.0/src/examples)
endif()