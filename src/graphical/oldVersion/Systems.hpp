/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Systems
*/

#pragma once
#include "../ecs/EntitiesGestion.hpp"
#include "../ecs/Registry.hpp"
#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Serialisation.hpp"
#include "TcpClient.hpp"
#include "UdpClient.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstring>
#include <map>
#include <sstream>
#include <vector>

void position_system(Registry &registry, float deltaTime, UdpClient &udp);

void control_system(Registry &registry, UdpClient &udp);

void draw_system(Registry &registry, SDL_Renderer *renderer);

void collision_system(Registry &registry, TcpClient &tcp);

void handleShoot(Registry &registry, SDL_Renderer *renderer,
                 float &shootCooldown, float deltaTime);