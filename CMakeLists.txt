set(SOURCE src/main.c src/functions.h src/variables.h src/variables.c src/main_menu.c src/init_end.c src/game_logics.c src/user_works.c)
set(PROJECT_NAME Fop_project)

cmake_minimum_required(VERSION 3.21)
project(${PROJECT_NAME} C)
set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SOURCE "src/*.c" "src/*.h")
add_executable("${PROJECT_NAME}" "${SOURCE}")

include_directories("/usr/include/SDL2")
target_link_libraries(${PROJECT_NAME} m SDL2 SDL2_gfx SDL2_image SDL2_ttf)
