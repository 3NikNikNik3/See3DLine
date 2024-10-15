cmake_minimum_required(VERSION 3.0)

project(See3DLine)

add_compile_definitions(INCLUDE_UP STRLEN)

#include_directories(../raylib)

add_library(raylib STATIC IMPORTED)
set_property(TARGET raylib PROPERTY IMPORTED_LOCATION ../../libraylib.a)
#include(raylib)

#add_library(raygui STATIC ../raygui.h)

add_library(my_lib STATIC cpp/Graphics.cpp cpp/Math.cpp cpp/ScreenLines.cpp cpp/ScreenSettings.cpp hpp/Graphics.hpp hpp/Math.hpp hpp/Screen.hpp hpp/ScreenLines.hpp hpp/ScreenSettings.hpp)

add_executable(See3DLine cpp/main.cpp)

#target_link_libraries(raygui raylib)

target_link_libraries(See3DLine raylib my_lib)
