/*
** EPITECH PROJECT, 2025
** RType
** File description:
** EnemySytems
*/
#ifndef ENEMYSYTEMS_HPP
#define ENEMYSYTEMS_HPP
#include "../../../ecs/Registry.hpp"
#include "../../Components/Components.hpp"
#include "../../gestion/EntitiesGestion.hpp"
#include <map>

void aggresive_ai(Registry *ecs);
void balzy_ai(Registry *ecs);
void boss_ai(Registry *ecs);
void passive_ai(Registry *ecs);

void call_enemy_ai(Registry *ecs, AiType type);
void enemy_system(Registry *ecs);

#endif // ENEMYSYTEMS_HPP
