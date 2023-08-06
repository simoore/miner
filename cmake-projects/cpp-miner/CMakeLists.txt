cmake_minimum_required (VERSION 3.20)
project (CppMiner LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)

###############################################################################
# Third Party Dependancies
###############################################################################

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

###############################################################################
# Unit Tests
###############################################################################

add_library(CppMiner INTERFACE)
target_sources(CppMiner INTERFACE src/sha256.cpp)
target_include_directories(CppMiner INTERFACE include)

add_executable(UnitTests
    tests/main.cpp
    tests/test_sha256.cpp)
target_link_libraries(UnitTests CppMiner)
target_link_libraries(UnitTests gtest)
target_compile_options(UnitTests PRIVATE -g -Og)
target_link_options(UnitTests PRIVATE -static-libasan -static-libgcc -static-libstdc++)
