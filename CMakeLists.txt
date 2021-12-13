cmake_minimum_required(VERSION 3.21)
project(Snake_in_C C)

set(CMAKE_C_STANDARD 99)

add_executable(Snake_in_C main.c state_menu.c state_play.c state_settings.c gui.c constants.c list.c point.c)
