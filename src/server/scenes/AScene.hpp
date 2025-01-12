/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AScene
*/

#pragma once

#include "../../ecs/EntitiesGestion.hpp"
#include "../../ecs/Registry.hpp"
#include "../../graphical/Components/Control.hpp"
#include "../../graphical/Components/Draw.hpp"
#include "../../graphical/Components/Health.hpp"
#include "../../graphical/Components/Nickname.hpp"
#include "../../graphical/Components/Position.hpp"
#include "../../graphical/Components/Velocity.hpp"
#include "IScene.hpp"

class AScene : public IScene {
public:
  AScene();
  ~AScene();

  std::string getName() const override;

  void setEcs(Registry *ecs) override;

  void setQueue(Queue *queue) override;

protected:
  std::string _name;
  Registry *_ecs;
  Queue *_queue;
};
