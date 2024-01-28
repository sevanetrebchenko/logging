cmake_minimum_required(VERSION 3.3)
project(logging VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Pull latest changes from submodules
find_package(Git REQUIRED)
execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND_ERROR_IS_FATAL ANY)
message(STATUS "Updated project dependencies")

add_executable("${PROJECT_NAME}"
    "${PROJECT_SOURCE_DIR}/src/format.cpp"
    "${PROJECT_SOURCE_DIR}/src/logging.cpp"
    "${PROJECT_SOURCE_DIR}/src/message.cpp"

    "${PROJECT_SOURCE_DIR}/main.cpp")

# Dependencies
add_subdirectory(lib/datetime)
target_link_libraries("${PROJECT_NAME}" PRIVATE datetime)
add_subdirectory(lib/utils)
target_link_libraries("${PROJECT_NAME}" PRIVATE utils)

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_SOURCE_DIR}/include")
