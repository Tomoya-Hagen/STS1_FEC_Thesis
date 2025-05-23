cmake_minimum_required(VERSION 3.16)

project(TM_TC_Encode_Decode_Test CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    encode_decode.cpp
    test.cpp
    ../reed_solomon/ccsds.cpp
    ../reed_solomon/decode_rs.cpp
    ../reed_solomon/decode_rs_8.cpp
    ../reed_solomon/encode_rs.cpp
    ../reed_solomon/encode_rs_8.cpp
    ../reed_solomon/taltab.cpp)

# add_subdirectory(../reed_solomon ${CMAKE_CURRENT_BINARY_DIR}/reed_solomon_build)

add_executable(encode_decode_test ${SOURCES})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../reed_solomon
    ../bit_scrambling)
