cmake_minimum_required (VERSION 3.10)
project(missile_motion LANGUAGES CXX)

file(GLOB UTILS utils/*/*/*.cpp utils/*/*.cpp utils/*.cpp)
file(GLOB MM missile_motion/*/*.cpp)
file(GLOB GLBL global/*.cpp)
file(GLOB CORE core/*.cpp)

add_subdirectory(utils)

add_executable(run 
    main.cpp
    ${UTILS}
    ${MM}
    ${GLBL}
    ${CORE}
    )

target_include_directories(
    run 
    PUBLIC 
    utils
    ${CMAKE_CURRENT_SOURCE_DIR})