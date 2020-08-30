cmake_minimum_required(VERSION 3.5)

project(r-type)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unknown-pragmas")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SRC
  main.cpp 
  Interface.cpp 
  Menu.cpp 
  Room.cpp 
  Animation.cpp 
  Game.cpp 
  ../network/NetworkManager.cpp 
  ../network/UNetwork.cpp 
)

set(HDR
  Animation.hh 
  Game.hh 
  Interface.hh 
  Menu.hh 
  Room.hh 
  ../../network/UNetwork.hpp 
  ../../network/NetworkManager.hpp 
)

find_package(Threads)

add_executable(r-type ${SRC})

target_link_libraries(r-type ${CMAKE_THREAD_LIBS_INIT})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(r-type ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
