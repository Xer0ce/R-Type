/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AScene
*/

#pragma once

#include "../../game/gestion/EntitiesGestion.hpp"
#include "../../ecs/Registry.hpp"
#include "../../queue/Queue.hpp"
#include "../../game/Components/Components.hpp"
#include "IScene.hpp"

class AScene : public IScene {
public:
  AScene();
  ~AScene();

  std::string getName() const override;

  void setWindow(Window *window) override;

  void setEcs(Registry ecs) override;

  void setQueue(Queue *queue) override;

protected:
  std::string _name;
  Window *_window;
  Registry _ecs;
  Queue *_queue;
};
