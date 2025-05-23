cmake_minimum_required(VERSION 3.16)

project(TM_TC_Encode_Decode_Test CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    ChannelCoding.cpp
    test.cpp
    ../reed_solomon/Ccsds.cpp
    ../reed_solomon/DecodeRS.cpp
    ../reed_solomon/DecodeRS8.cpp
    ../reed_solomon/EncodeRS.cpp
    ../reed_solomon/EncodeRS8.cpp
    ../reed_solomon/TalTab.cpp)

# add_subdirectory(../reed_solomon ${CMAKE_CURRENT_BINARY_DIR}/reed_solomon_build)

add_executable(encode_decode_test ${SOURCES})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../reed_solomon
    ../bit_scrambling)
