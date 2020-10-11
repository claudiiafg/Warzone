cmake_minimum_required(VERSION 3.17.3)

# set the project name
project(Warzone)

set(CMAKE_CXX_STANDARD 17)

# add the executable
add_executable(Warzone_MapLoader MapLoaderDriver.cpp MapLoader.cpp)
add_executable(Warzone_Map MapDriver.cpp Map.cpp)
add_executable(Warzone_Player Player.cpp)
add_executable(Warzone_Card CardDriver.cpp Cards.cpp)

