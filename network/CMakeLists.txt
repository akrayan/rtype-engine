cmake_minimum_required(VERSION 3.9)
project(network)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++11 -pthread -ldl")

add_executable(Server
        INetwork.hpp
        NetworkManager.cpp
        NetworkManager.hpp
        server.cpp UNetwork.cpp UNetwork.hpp)

add_executable(Client
        client.cpp
        INetwork.hpp
        NetworkManager.cpp
        NetworkManager.hpp
        UNetwork.cpp UNetwork.hpp)
