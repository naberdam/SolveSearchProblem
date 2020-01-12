cmake_minimum_required(VERSION 3.15)
project(untitled2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(untitled2 main.cpp CacheManager.h ClientHandler.h FileCacheManager.h MySerialServer.h MyTestClientHandler.h Solver.h Server.h boot.h StringReverser.h Searcher.h Point.h Searchable.h State.h Matrix.cpp Matrix.h ISearchable.h)