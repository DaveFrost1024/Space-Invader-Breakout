# cmake_minimum_required (VERSION 3.1...3.13)

# if(${CMAKE_VERSION} VERSION_LESS 3.12)
#     cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
# endif()

# project(Space-Invader-Breakout)

add_executable(Space-Invader-Breakout
    main.cpp
    Setup.h
    Setup.cpp
    Common.h
    Common.cpp
    LTexture.h
    LTexture.cpp
    WindowController.h
    WindowController.cpp
    Gameplay.h
    Gameplay.cpp
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

target_include_directories(Space-Invader-Breakout PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(Space-Invader-Breakout PUBLIC
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES})
