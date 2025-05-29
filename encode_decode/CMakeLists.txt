cmake_minimum_required(VERSION 3.16)

project(EncodeDecode CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(
    EncodeDecode_Lib
    ChannelCoding.cpp)

# add_executable(EncodeDecode_Test test.cpp)
# target_link_libraries(
#     EncodeDecode_Test PRIVATE EncodeDecode_Lib
# )
