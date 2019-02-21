cmake_minimum_required (VERSION 3.1...3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(sdlProject1)

add_executable(sdlProject1
    main.cpp
    common.h
    common.cpp
    LTexture.h
    LTexture.cpp
    Paddle.h
    Paddle.cpp
    Dot.h
    Dot.cpp
    Obstacle.h
    Obstacle.cpp
    Projectile.h
    Projectile.cpp)

find_package(PkgConfig)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2TTF REQUIRED SDL2_ttf)

target_include_directories(sdlProject1 PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(sdlProject1
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES})
