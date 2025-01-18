/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#pragma once

#include "../../game/LaunchServer.hpp"
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

  bool isHostGameReady();

  bool isJoinGameReady();

  void hideAllMenu();

  void unselectAllBoutton(int menuId);

  void unclickAllBoutton(Boutton &boutton, MenuType menuType);

  void unclickTypeBoutton(Boutton &boutton, std::string type);

  void initMenu();

  void initHostMenu();

  void initJoinMenu();

  void initSettingsMenu();

  sceneType mouseHandler(float mouseX, float mouseY, eventType event);

  sceneType buttonSystem(Boutton &boutton);

  void displayCameraFeed();

private:
  std::string _selectedButton;
  std::string _menuTitle;
  float _windowWidth;
  float _windowHeight;
  std::string _nickname;
  std::string _assetsPath;
  int _gameMode;
  int _spaceshipId;
  int _bulletId;
};
