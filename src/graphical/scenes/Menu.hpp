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


  void resetGameValues();

  bool isGameReady();

  void hideAllMenu();

  void unselectAllBoutton(int menuId);

  void unclickAllBoutton(Boutton &boutton, MenuType menuType);

  void unclickTypeBoutton(Boutton &boutton, std::string type);

  void initMenu(int responsiveWidth, int responsiveHeight, int posX, int posY);

  void initHostMenu(int responsiveWidth, int responsiveHeight, int posX, int posY);

  void initJoinMenu(int responsiveWidth, int responsiveHeight, int posX, int posY);

  void initSettingsMenu(int responsiveWidth, int responsiveHeight, int posX, int posY);

  void mouseHandler(float mouseX, float mouseY, eventType event);

  void buttonSystem(Boutton &boutton);

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
