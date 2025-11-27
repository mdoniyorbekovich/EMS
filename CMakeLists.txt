cmake_minimum_required(VERSION 3.23)
project(EmployeeManagementSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES
        src/*.cpp
        main.cpp
)

add_executable(ems ${SOURCES})
