project(Warzone)

set(CMAKE_CXX_STANDARD 17)

add_executable(Warzone_MapLoader MapLoaderDriver.cpp MapLoader.cpp Map.cpp GameObservers.cpp Player.cpp Orders.cpp Cards.cpp)