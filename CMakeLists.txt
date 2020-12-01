cmake_minimum_required(VERSION 3.17)
project(Warzone)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Warzone
        Cards.cpp
        Cards.h
        GameEngine.h
        GameObservers.cpp
        GameObservers.h
        Map.cpp
        Map.h
        MapLoader.cpp
        MapLoader.h
        Orders.cpp
        Orders.h
        Player.cpp
        Player.h
        PlayerStrategies.cpp
        PlayerStrategies.h
        PlayerStrategiesDriver.cpp)
