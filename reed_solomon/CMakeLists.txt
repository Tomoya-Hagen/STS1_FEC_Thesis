cmake_minimum_required(VERSION 3.16)

project(Reed_Solomon CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    test_rs.cpp
    ccsds.cpp
    decode_rs.cpp
    decode_rs_8.cpp
    encode_rs.cpp
    encode_rs_8.cpp
    taltab.cpp
)

add_executable(reed_solomon ${SOURCES})