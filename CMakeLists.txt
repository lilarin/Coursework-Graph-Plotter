cmake_minimum_required(VERSION 3.20)
project(Coursework)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(Coursework main.cpp textbox.h button.h shunting_yard.h utility.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ./SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics REQUIRED)

include_directories(./SFML/include)
target_link_libraries(Coursework sfml-system sfml-window sfml-graphics)
