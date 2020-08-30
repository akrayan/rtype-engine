cmake_minimum_required(VERSION 3.5)

project(EngineLib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")# -Wall -Wextra -Wno-unknown-pragmas")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SRC
  Application.cpp
  Client.cpp
  Room.cpp
  Collider.cpp
  EventNetwork.cpp
  GameManager.cpp
  GameObject.cpp
  IComponent.cpp
  RessourceManager.cpp
  Scene.cpp
  SceneLoader.cpp
  SpriteRenderer.cpp
  TransformObject.cpp
  SoundManager.cpp
  TextRenderer.cpp
  ../../network/UNetwork.cpp
  ../../network/NetworkManager.cpp
)

set(HDR
  Application.h
  BitArray.h
  Collider.h
  Engine.h
  EventNetwork.h
  GameManager.h
  GameObject.h
  IComponent.h
  RessourceManager.h
  Scene.h
  SceneLoader.h
  Script.h
  SpriteRenderer.h
  TransformObject.h
  SoundManager.h
  TextRenderer.h
  Client.h
  Room.h
  ../../network/UNetwork.hpp
  ../../network/NetworkManager.hpp
)

set(SRC_MAIN
  main.cpp
  )

find_package(Threads)


add_library(EngineLib SHARED
  ${SRC})

target_link_libraries(EngineLib ${CMAKE_THREAD_LIBS_INIT})

add_executable(r-type ${SRC_MAIN})

target_link_libraries(r-type EngineLib)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(r-type ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
