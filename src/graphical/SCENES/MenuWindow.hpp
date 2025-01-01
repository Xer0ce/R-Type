/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MenuWindow
*/

#pragma once
#include "../CORE/IWindow.hpp"
#include "../CORE/WindowManager.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class MenuWindow : public IWindow {
public:
    MenuWindow(WindowManager& manager, ConnectionManager &connectionManager);
    ~MenuWindow();

    void initialize() override;
    void update() override;
    void render(SDL_Renderer* renderer) override;
private:
    WindowManager& windowManager;
    ConnectionManager &connectionManager;
};

