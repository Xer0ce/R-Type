/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Infos
*/

#include "GlobalSystem.hpp"
#include "../../../graphical/LifeBar.hpp"

void display_infos(Registry *ecs)
{
    auto &controls = ecs->get_components<Control>();
    auto &positions = ecs->get_components<Position>();
    auto &health = ecs->get_components<Health>();
    auto &nicknames = ecs->get_components<Nickname>();
    auto &entities = ecs->get_components<EntityType>();
    
    for (std::size_t i = 0; i < entities.size(); ++i) {
        if (entities[i] == EntityType::Player && nicknames[i].has_value()) {
            nicknames[i]->rect.x = positions[i]->x;
            nicknames[i]->rect.y = positions[i]->y - 20;
        }
    }
}

