cmake_minimum_required(VERSION 3.15)

project(RType LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_CLIENT "Build the client executable" ON)
option(BUILD_SERVER "Build the server executable" ON)

add_subdirectory(external/SDL3)
add_subdirectory(external/SDL3_ttf)
add_subdirectory(external/SDL3_image)
add_subdirectory(external/SDL3_mixer)
add_subdirectory(external/json)

if(BUILD_CLIENT)
    file(GLOB SOURCES_CLIENT "src/graphical/*.cpp")
    file(GLOB SOURCES_CLIENT_COMMAND "src/graphical/commandSystem/*.cpp")

    file(GLOB SOURCES_CLIENT_SCENES "src/graphical/scenes/*.cpp")
    file(GLOB SOURCES_CLIENT_NETWORK "src/network/client/*.cpp")
    file(GLOB SOURCES_QUEUE "src/queue/*.cpp")

    file(GLOB SOURCES_ECS "src/ecs/*.cpp")
    file(GLOB SOURCES_GAME_GESTION "src/game/gestion/*.cpp")
    file(GLOB SOURCES_GAME_SYSTEMS "src/game/systems/enemy/*.cpp")
    file(GLOB SOURCES_GAME_SYSTEMS_GLOBAL "src/game/systems/global/*.cpp")

    add_executable(r-type_client ${SOURCES_GAME_SYSTEMS} ${SOURCES_CLIENT} ${SOURCES_CLIENT_COMMAND} ${SOURCES_ECS} ${SOURCES_CLIENT_SCENES} ${SOURCES_GAME_GESTION} ${SOURCES_CLIENT_NETWORK} ${SOURCES_QUEUE} ${SOURCES_GAME_SYSTEMS_GLOBAL})
    target_include_directories(r-type_client PRIVATE include/graphical)

    target_link_libraries(r-type_client PRIVATE SDL3::SDL3)
    target_link_libraries(r-type_client PRIVATE SDL3_ttf::SDL3_ttf)
    target_link_libraries(r-type_client PRIVATE SDL3_image::SDL3_image)
    target_link_libraries(r-type_client PRIVATE SDL3_mixer::SDL3_mixer)

    target_compile_definitions(r-type_client PRIVATE $<$<CONFIG:Debug>:DEBUG>)
endif()

if(BUILD_SERVER)
    file(GLOB SOURCES_SERVER "src/server/*.cpp")
    file(GLOB SOURCES_SERVER_COMMAND "src/server/commandSystem/*.cpp")
    file(GLOB SOURCES_NETWORK "src/network/server/*.cpp")
    file(GLOB SOURCES_NETWORK_TCP "src/network/server/tcp/*.cpp")
    file(GLOB SOURCES_NETWORK_UDP "src/network/server/udp/*.cpp")
    file(GLOB SOURCES_QUEUE "src/queue/*.cpp")
    file(GLOB SOURCES_CLIENT_SCENES "src/server/scenes/*.cpp")
    file(GLOB SOURCES_CLIENT_SCENES_UTILS "src/server/scenes/utils/*.cpp")
    file(GLOB SOURCES_ECS "src/ecs/*.cpp")
    file(GLOB SOURCES_GAME_GESTION "src/game/gestion/**.cpp")
    file(GLOB SOURCES_GAME_SYSTEMS "src/game/systems/enemy/*.cpp")
    file(GLOB SOURCES_GAME_SYSTEMS_GLOBAL "src/game/systems/global/*.cpp")

    add_executable(r-type_server
        ${SOURCES_SERVER}
        ${SOURCES_SERVER_COMMAND}
        ${SOURCES_NETWORK}
        ${SOURCES_NETWORK_TCP}
        ${SOURCES_NETWORK_UDP}
        ${SOURCES_ECS}
        ${SOURCES_GAME_GESTION}
        ${SOURCES_GAME_SYSTEMS}
        ${SOURCES_QUEUE}
        ${SOURCES_CLIENT_SCENES}
        ${SOURCES_CLIENT_SCENES_UTILS}
        ${SOURCES_GAME_SYSTEMS_GLOBAL}
        ${SOURCES_GRAPHICAL}
    )

    target_link_libraries(r-type_server PRIVATE SDL3::SDL3)
    target_link_libraries(r-type_server PRIVATE SDL3_ttf::SDL3_ttf)
    target_link_libraries(r-type_server PRIVATE SDL3_image::SDL3_image)
    target_link_libraries(r-type_server PRIVATE SDL3_mixer::SDL3_mixer)
    target_link_libraries(r-type_server PRIVATE nlohmann_json)
endif()


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in Debug mode")
else()
    message(STATUS "Building in Release mode")
endif()

add_compile_options(-Wall -Wextra -pedantic)