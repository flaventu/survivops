cmake_minimum_required(VERSION 3.28)
project(survivops LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(SurvivOps ${SOURCES})
target_compile_features(SurvivOps PRIVATE cxx_std_17)
target_include_directories(SurvivOps PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/State
)
target_link_libraries(SurvivOps PRIVATE SFML::Graphics)
