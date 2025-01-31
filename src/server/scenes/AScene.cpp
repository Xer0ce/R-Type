/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AScene
*/

#include "AScene.hpp"

AScene::AScene() {}

AScene::~AScene() {}

std::string AScene::getName() const { return _name; }

void AScene::setEcs(Registry *ecs) { _ecs = ecs; }

void AScene::setQueue(Queue *queue) { _queue = queue; }

void AScene::setGamemode(int gamemode) { _gamemode = gamemode; }

void AScene::setLevel(std::string level) { _level = level; }