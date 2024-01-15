cmake_minimum_required(VERSION 3.3)
project(logging VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable("${PROJECT_NAME}"
    "${PROJECT_SOURCE_DIR}/src/format.cpp"
    "${PROJECT_SOURCE_DIR}/src/logging.cpp"
    "${PROJECT_SOURCE_DIR}/src/message.cpp"

    "${PROJECT_SOURCE_DIR}/main.cpp"
)

# Dependencies
add_subdirectory(lib/datetime)
target_link_libraries("${PROJECT_NAME}" PUBLIC datetime)

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_SOURCE_DIR}/include")
