#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(SunTracking)

include_directories(include)

file(GLOB SOURCES "src/*.cxx")
file(GLOB HEADERS "include/*.hh")

add_executable(SunTracking main.cxx ${SOURCES} ${HEADERS})
