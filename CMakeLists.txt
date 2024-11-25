cmake_minimum_required(VERSION 3.10)

project(RType LANGUAGES CXX VERSION 1.0)


file(GLOB SOURCES_ECS "src/ecs/*.cpp")
add_executable(rtype_ecs ${SOURCES_ECS})

file(GLOB SOURCES_CLIENT "src/graphical/*.cpp")
add_executable(r-type_client ${SOURCES_CLIENT})

file(GLOB SOURCES_SERVER "src/server/*.cpp")
add_executable(r-type_server ${SOURCES_SERVER})
