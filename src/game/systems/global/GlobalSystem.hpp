/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GlobalSystem
*/

#pragma once

#include "../../Components/Components.hpp"
#include "../../../ecs/Registry.hpp"
#include "../../../queue/Queue.hpp"
#include "../../gestion/EntitiesGestion.hpp"
#include "../../../graphical/Utils.hpp"

void position_system_net(float deltaTime, Registry *ecs, Queue *queue);
void position_system_graphic(float deltaTime, Registry &ecs, Queue *queue);
void control_system(keyType key, Registry &ecs);
void shoot_system(keyType key, Registry &_ecs, Queue *_queue);
void collision_system(Registry *ecs, Queue *queue);