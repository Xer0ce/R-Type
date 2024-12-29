/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Commands
*/

#pragma once

#include "../ecs/Registry.hpp"
#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstring>
#include <map>
#include <sstream>
#include <vector>
#include "../ecs/EntitiesGestion.hpp"

std::vector<std::string> my_strToWordArray(const std::string &str,
                                           char delimiter);

void connectCommand(std::string buffer, Registry &registry,
                    SDL_Renderer *renderer);

void moveEntity(std::string buffer, Registry &registry, SDL_Renderer *renderer);

void createEnemy(std::string buffer, Registry &registry,
                  SDL_Renderer *renderer);

void killEntity(std::string buffer, Registry &registry, SDL_Renderer *renderer);

void initCommandHandle(
    std::map<uint8_t,
             std::function<void(std::string, Registry &, SDL_Renderer *)>>
        &commandsHandle);