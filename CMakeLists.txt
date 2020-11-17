project(Warzone)

set(CMAKE_CXX_STANDARD 17)

add_executable(Warzone_MapLoader MapLoaderDriver.cpp MapLoader.cpp Map.cpp GameObservers.cpp)
add_executable(Warzone_Map MapDriver.cpp Map.cpp MapLoader.cpp GameObservers.cpp)
add_executable(Warzone_Player PlayerDriver.cpp Player.cpp Map.cpp Cards.cpp Orders.cpp GameObservers.cpp)
add_executable(Warzone_Order OrdersDriver.cpp Orders.cpp GameObservers.cpp)
add_executable(Warzone_Card CardDriver.cpp Cards.cpp GameObservers.cpp)
add_executable(Warzone_GameEngine GameEngine.cpp MapLoader.cpp Map.cpp Player.cpp Orders.cpp Cards.cpp GameObservers.cpp)
