cmake_minimum_required(VERSION 3.15.0)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 609281088cfefc76f9d0ce82e1ff6c30cc3591e5
)

FetchContent_MakeAvailable(googletest)