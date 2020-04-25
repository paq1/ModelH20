cmake_minimum_required(VERSION 3.15)
project(ModelH2O)

set(CMAKE_CXX_STANDARD 11)

# lib sfml
include_directories(C:/sfml/SFML-2.5.1/include)
link_directories(C:/sfml/SFML-2.5.1/lib)

add_executable(ModelH2O src/main.cpp src/SDD/type_atomiques.cpp src/SDD/type_atomiques.hpp src/SDD/viewer.cpp src/SDD/viewer.hpp)
target_link_libraries(ModelH2O -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)