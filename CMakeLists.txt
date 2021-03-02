cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

project(ha-param-tool-box)

add_subdirectory(external)

add_library(param-tool-box STATIC
    include/ha/param_tool_box/core/types.h
    include/ha/param_tool_box/convert/dezibel.h
    include/ha/param_tool_box/process/ramp_processor.h
    include/ha/param_tool_box/process/ramp.h
    source/ramp.cpp
    source/ramp_processor.cpp
)

target_include_directories(param-tool-box
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/source
)

target_compile_features(param-tool-box
    PUBLIC
        cxx_std_17
)

enable_testing()

add_executable(param-tool-box_test
    test/convert_test.cpp
    test/ramp_processor_test.cpp
)

target_link_libraries(param-tool-box_test
    PRIVATE
        param-tool-box
        gtest
        gtest_main
)