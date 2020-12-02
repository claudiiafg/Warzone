cmake_minimum_required(VERSION 3.17)
project(Warzone)

set(CMAKE_CXX_STANDARD 14)

add_executable(WarzoneStrategies PlayerStrategiesDriver.cpp Cards.cpp GameObservers.cpp Map.cpp MapLoader.cpp Orders.cpp Player.cpp PlayerStrategies.cpp)
add_executable(Warzone_MapLoader MapLoaderDriver.cpp MapLoader.cpp Map.cpp GameObservers.cpp Player.cpp Orders.cpp Cards.cpp)


