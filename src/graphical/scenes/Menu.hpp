/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#pragma once

#include "AScene.hpp"

class Menu : public AScene {
public:
  Menu();
  ~Menu();

  void init() override;

  sceneType
  loop(eventType event,
       std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;


  void setMenu(std::string selectedButton);

  void initHostMenu(int responsiveWidth, int responsiveHeight, int posX, int posY);

  void initJoinMenu(int responsiveWidth, int responsiveHeight, int posX, int posY);

  void initSettingsMenu(int responsiveWidth, int responsiveHeight, int posX, int posY);

  void mouseHandler(float mouseX, float mouseY, eventType event);

  void buttonSystem(Boutton &boutton);

  void textSystem(Text &text);


private:
  std::string _selectedButton;
  std::string _menuTitle;
  float _windowWidth;
  float _windowHeight;
  std::string _nickname;
  int _gameMode;
  int _spaceshipId;
  int _bulletId;
};
