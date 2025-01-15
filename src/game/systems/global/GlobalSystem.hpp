/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GlobalSystem
*/

#pragma once

#include "../../../ecs/Registry.hpp"
#include "../../../graphical/Utils.hpp"
#include "../../../queue/Queue.hpp"
#include "../../Components/Components.hpp"
#include "../../gestion/EntitiesGestion.hpp"

void position_system_net(
    float deltaTime, Registry *ecs, Queue *queue,
    std::chrono::time_point<std::chrono::steady_clock> _next);
void position_system_graphic(float deltaTime, Registry &ecs, Queue *queue);
void control_system(std::vector<keyType> keys, Registry &ecs);
void shoot_system(std::vector<keyType> keys, Registry &_ecs, Queue *_queue,
                  std::chrono::time_point<std::chrono::steady_clock> next);
void collision_system(Registry *ecs, Queue *queue);
void display_infos(Registry *ecs);