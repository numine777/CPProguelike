cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} src assets)

add_executable(WallsEngine src/main.cpp src/game.cpp src/textureManager.cpp src/map.cpp src/vector2D.cpp src/collision.cpp src/ECS/ecs.cpp src/assetManager.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(WallsEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL_TTF_LIBRARIES})
