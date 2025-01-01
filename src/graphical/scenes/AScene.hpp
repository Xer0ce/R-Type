/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AScene
*/

#pragma once

#include "../../ecs/EntitiesGestion.hpp"
#include "../../ecs/Registry.hpp"
#include "../Components/Control.hpp"
#include "../Components/Draw.hpp"
#include "../Components/Health.hpp"
#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"
#include "IScene.hpp"

class AScene : public IScene {
public:
  AScene();
  ~AScene();

  std::string getName() const override;

  void setWindow(Window *window) override;

  void setEcs(Registry ecs) override;

protected:
  std::string _name;
  Window *_window;
  Registry _ecs;
};
