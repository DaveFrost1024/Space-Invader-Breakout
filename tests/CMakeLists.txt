
# ./tests --reporter compact --success

add_executable(tests
    Test-Common.cpp
    Test-Dot.cpp)

# target_include_directories(tests PUBLIC
#     ${SDL2_INCLUDE_DIRS})

# target_link_libraries(tests
#     ${SDL2_LIBRARIES})

target_include_directories(tests PUBLIC
    ../include/
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(tests PUBLIC
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES})