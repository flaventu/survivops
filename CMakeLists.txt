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

# ASSETS COPYING
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/)
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(SurvivOps ${SOURCES})
target_compile_features(SurvivOps PRIVATE cxx_std_17)
target_include_directories(SurvivOps PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/states
    ${CMAKE_SOURCE_DIR}/include/entities
    ${CMAKE_SOURCE_DIR}/include/weapons
)
target_link_libraries(SurvivOps PRIVATE SFML::Graphics)

# DEBUGGING CONFIGURATIONS
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        target_compile_options(SurvivOps PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wunused -Werror -ggdb -O0)
        target_link_options(SurvivOps PRIVATE -ggdb)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(SurvivOps PRIVATE /W4 /WX /permissive- /Zi /Od /analyze)
        target_link_options(SurvivOps PRIVATE /DEBUG)
    endif()
endif()