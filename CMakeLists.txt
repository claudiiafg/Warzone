cmake_minimum_required(VERSION 3.17.3)

project(Warzone)

set(CMAKE_CXX_STANDARD 17)
FIND_PACKAGE(Boost REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(Warzone_MapLoader MapLoaderDriver.cpp MapLoader.cpp Map.cpp)
add_executable(Warzone_Map MapDriver.cpp Map.cpp MapLoader.cpp)
add_executable(Warzone_Player PlayerDriver.cpp Player.cpp Map.cpp Cards.cpp Orders.cpp)
add_executable(Warzone_Order OrdersDriver.cpp Orders.cpp)
add_executable(Warzone_Card CardDriver.cpp Cards.cpp)
add_executable(Warzone_GameEngine GameEngine.cpp MapLoader.cpp Map.cpp Player.cpp Orders.cpp Cards.cpp)

target_link_libraries(Warzone_GameEngine ${Boost_FILESYSTEM_LIBRARY})