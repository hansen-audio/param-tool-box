cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

set(CMAKE_CXX_STANDARD 14)

project(ha-param-tool-box)

add_subdirectory(external)

add_library(param-tool-box STATIC  
    include/ha/ptb/paramrampprocessor.h
    include/ha/ptb/paramramp.h
    source/paramramp.cpp
    source/paramrampprocessor.cpp
)

target_include_directories(param-tool-box
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/source
)

enable_testing()

add_executable(param-tool-box_test
    test/paramrampprocessor_test.cpp
)

target_link_libraries(param-tool-box_test
    PRIVATE
        param-tool-box
        gtest
        gtest_main
)