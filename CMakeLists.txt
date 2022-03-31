cmake_minimum_required(VERSION 3.20)
project(Zombie)

set(CMAKE_CXX_STANDARD 14)

add_executable(Zombie cmake-build-debug/main.cpp cmake-build-debug/Organism.cpp cmake-build-debug/Organism.h cmake-build-debug/Human.cpp cmake-build-debug/Human.h cmake-build-debug/Zombie.cpp cmake-build-debug/Zombie.h cmake-build-debug/City.cpp cmake-build-debug/City.h)
