cmake_minimum_required(VERSION 3.8)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

#set(SOURCE_FILES main.cpp)
#add_executable(Chess ${SOURCE_FILES})
add_custom_target(Chess COMMAND make -C ${Chess_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})