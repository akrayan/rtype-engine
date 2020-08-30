cmake_minimum_required(VERSION 3.5)

project(EngineLib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")# -Wall -Wextra -Wno-unknown-pragmas")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SRC
  ../EngineLib/EngineLib/Application.cpp
  ../EngineLib/EngineLib/Client.cpp
  ../EngineLib/EngineLib/Room.cpp
  ../EngineLib/EngineLib/Collider.cpp
  ../EngineLib/EngineLib/EventNetwork.cpp
  ../EngineLib/EngineLib/GameManager.cpp
  ../EngineLib/EngineLib/GameObject.cpp
  ../EngineLib/EngineLib/IComponent.cpp
  ../EngineLib/EngineLib/RessourceManager.cpp
  ../EngineLib/EngineLib/Scene.cpp
  ../EngineLib/EngineLib/SceneLoader.cpp
  ../EngineLib/EngineLib/SpriteRenderer.cpp
  ../EngineLib/EngineLib/TransformObject.cpp
  ../EngineLib/EngineLib/SoundManager.cpp
  ../EngineLib/EngineLib/TextRenderer.cpp
  ../network/UNetwork.cpp
  ../network/NetworkManager.cpp
)

set(HDR
  ../EngineLib/EngineLib/Application.h
  ../EngineLib/EngineLib/BitArray.h
  ../EngineLib/EngineLib/Collider.h
  ../EngineLib/EngineLib/Engine.h
  ../EngineLib/EngineLib/EventNetwork.h
  ../EngineLib/EngineLib/GameManager.h
  ../EngineLib/EngineLib/GameObject.h
  ../EngineLib/EngineLib/IComponent.h
  ../EngineLib/EngineLib/RessourceManager.h
  ../EngineLib/EngineLib/Scene.h
  ../EngineLib/EngineLib/SceneLoader.h
  ../EngineLib/EngineLib/Script.h
  ../EngineLib/EngineLib/SpriteRenderer.h
  ../EngineLib/EngineLib/TransformObject.h
  ../EngineLib/EngineLib/SoundManager.h
  ../EngineLib/EngineLib/TextRenderer.h
  ../EngineLib/EngineLib/Client.h
  ../EngineLib/EngineLib/Room.h
  ../network/UNetwork.hpp
  ../network/NetworkManager.hpp
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
