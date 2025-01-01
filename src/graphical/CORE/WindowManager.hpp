/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WindowManager
*/

#pragma once

#include "../SYSTEMS/ConnectionManager.hpp"
#include "../UTILS/Command.hpp"
#include <string>
#include <unordered_map>
#include <memory>
#include "IWindow.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

class WindowManager {
public:
    WindowManager(ConnectionManager &connectionManager);
    ~WindowManager();

    void addWindow(const std::string& name, std::unique_ptr<IWindow> window);
    void setActiveWindow(const std::string& name);
    void update();
    void render();
    SDL_Renderer* getRenderer();
    IWindow* getActiveWindow();
    void setBackground(const std::string& windowName, const std::string& imagePath);
    void renderBackground();
    void renderText(const std::string& text, int x, int y);
    void renderButton(const std::string& text, int x, int y, int w, int h, int r, int g, int b);
    void renderSquare(int r, int g, int b);
    void stop();
    bool isRunning() const;
    SDL_Renderer* getRenderer() const;

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    IWindow* activeWindow;
    TTF_Font* font;
    ConnectionManager &connectionManager;
    std::unordered_map<std::string, std::unique_ptr<IWindow>> windows;
    std::unordered_map<std::string, SDL_Texture*> windowTextures;
};