cmake_minimum_required (VERSION 3.19)

project ("exam_project")

set(CMAKE_CXX_STANDARD 17)

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
#target_link_libraries(exam_project PRIVATE nlohmann_json::nlohmann_json)
add_subdirectory(src)


project("Google_tests")
enable_testing()
include_directories(Google_tests PUBLIC ${MY_INCLUDE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(Google_tests/lib)
add_executable(Google_tests "Google_tests/invert_in_test.cpp" "Google_tests/search_serve_test.cpp" "src/invert_in.cpp" "src/search_serve.cpp")
set_target_properties(Google_tests PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
target_link_libraries(Google_tests gtest gtest_main)
target_link_libraries(exam_project PRIVATE nlohmann_json::nlohmann_json)