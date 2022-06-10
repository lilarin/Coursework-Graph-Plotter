cmake_minimum_required(VERSION 3.20)
project(Coursework)

set(CMAKE_CXX_STANDARD 17)

add_executable(Coursework main.cpp textbox.h button.h shunting_yard.h utility.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(Coursework sfml-system sfml-window sfml-graphics sfml-audio)
