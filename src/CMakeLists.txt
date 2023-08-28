cmake_minimum_required (VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)


# Добавьте источник в исполняемый файл этого проекта.
add_executable (exam_project "exam_project.cpp" "converter_js.cpp" "${MY_INCLUDE_DIR}/converter_js.h" 
"${MY_INCLUDE_DIR}/invert_in.h" "invert_in.cpp"
"${MY_INCLUDE_DIR}/search_serve.h" "search_serve.cpp"
"${MY_INCLUDE_DIR}/const_var.h")
target_include_directories(exam_project PUBLIC ${MY_INCLUDE_DIR})
#add_subdirectory(nlohmann_json)
target_link_libraries(exam_project PRIVATE nlohmann_json::nlohmann_json)


