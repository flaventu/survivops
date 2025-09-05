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

function(build_version ver)
    file(COPY ${CMAKE_SOURCE_DIR}/${ver}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin/${ver})
    file(GLOB_RECURSE SOURCES ${ver}/src/*.cpp)

    add_executable(SurvivOps_${ver} ${SOURCES})
    target_compile_features(SurvivOps_${ver} PRIVATE cxx_std_17)

    # Common include directories
    target_include_directories(SurvivOps_${ver} PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
    )

    # Additional include directories based on version
    if(ver STREQUAL "v1.0" OR ver STREQUAL "v0.9" OR ver STREQUAL "v0.8" OR ver STREQUAL "v0.7" OR ver STREQUAL "v0.6")
        target_include_directories(SurvivOps_${ver} PRIVATE 
            ${CMAKE_SOURCE_DIR}/include/states
            ${CMAKE_SOURCE_DIR}/include/entities
        )
    endif()

    if(ver STREQUAL "v1.0" OR ver STREQUAL "v0.9" OR ver STREQUAL "v0.8")
        target_include_directories(SurvivOps_${ver} PRIVATE
            ${CMAKE_SOURCE_DIR}/include/weapons
        )
    endif()

    target_link_libraries(SurvivOps_${ver} PRIVATE SFML::Graphics)

    set_target_properties(SurvivOps_${ver} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${ver}
    )
endfunction()

# List of versions to build
set(versions
    v1.0
    v0.9
    v0.8
    v0.7
    v0.6
    v0.5
    v0.4
    v0.3
    v0.2
    v0.1
)

foreach(ver IN LISTS versions)
    build_version(${ver})
endforeach()
