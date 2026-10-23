cmake_minimum_required(VERSION 3.16)
project(P2J LANGUAGES CXX)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
add_compile_options(-Wno-error=vla-cxx-extension)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

set(PCAPPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(PCAPPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(PCAPPP_BUILD_TUTORIALS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    pcapplusplus
    GIT_REPOSITORY https://github.com/seladb/PcapPlusPlus.git
    GIT_TAG v24.09
)
FetchContent_MakeAvailable(pcapplusplus)

add_executable(P2J
    src/main.cpp
    src/reader/reader.cpp
    src/writer/writer.cpp
)

target_include_directories(P2J PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/reader
    ${CMAKE_SOURCE_DIR}/include/writer
    ${pcapplusplus_SOURCE_DIR}/Pcap++/header
    ${pcapplusplus_SOURCE_DIR}/Packet++/header
    ${pcapplusplus_SOURCE_DIR}/Common++/header
)

target_link_libraries(P2J PRIVATE
    nlohmann_json::nlohmann_json
    Pcap++
)

enable_testing()
add_executable(p2j_tests
    tests/test_main.cpp
    src/writer/writer.cpp
)

target_include_directories(p2j_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/writer
)

target_link_libraries(p2j_tests PRIVATE
    nlohmann_json::nlohmann_json
    GTest::gtest_main
)

add_test(NAME p2j_tests COMMAND p2j_tests)