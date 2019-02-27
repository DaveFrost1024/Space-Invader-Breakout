cmake_minimum_required (VERSION 3.1...3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Space-Invader-Breakout)

# cmake -DRUN_TEST=ON ../
option(RUN_TEST "enable testing" OFF)

add_subdirectory(src)

target_include_directories(Space-Invader-Breakout PUBLIC
    ./media/)

if(RUN_TEST)
    message("Note: Tests are included")
    add_subdirectory(tests)
endif()
