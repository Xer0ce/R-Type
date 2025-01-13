/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AScene
*/

#pragma once

#include "../../ecs/Registry.hpp"
#include "../../game/Components/Components.hpp"
#include "../../game/gestion/EntitiesGestion.hpp"
#include "../../game/systems/global/GlobalSystem.hpp"
#include "../../queue/Queue.hpp"
#include "IScene.hpp"

class AScene : public IScene {
public:
  AScene();
  ~AScene();

  std::string getName() const override;

  void setWindow(Window *window) override;

  void setEcs(Registry *ecs) override;

  void setQueue(Queue *queue) override;

  void setChoosingParams(ChoosingParams *params) override;

protected:
  std::string _name;
  Window *_window;
  Registry *_ecs;
  Queue *_queue;
  ChoosingParams *_params;
};
