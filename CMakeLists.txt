project(Warzone)

set(CMAKE_CXX_STANDARD 17)

add_executable(Warzone_GameEngine GameEngine.cpp MapLoader.cpp Map.cpp Player.cpp Orders.cpp Cards.cpp GameObservers.cpp PlayerStrategies.cpp)