/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MenuWindow
*/

#include "MenuWindow.hpp"

MenuWindow::MenuWindow(WindowManager& manager, ConnectionManager &connectionManager) : windowManager(manager), connectionManager(connectionManager)
{
}

MenuWindow::~MenuWindow()
{
}

void MenuWindow::initialize()
{
    // Pour initialiser la fenêtre
}

void MenuWindow::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            windowManager.stop();
        } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            int x = event.button.x;
            int y = event.button.y;

            if (x > 350 && x < 450 && y > 250 && y < 300) {
                windowManager.setActiveWindow("game");
            } else if (x > 350 && x < 450 && y > 320 && y < 370) {
                //Pour l'instant rien (rejoindre)
            } else if (x > 350 && x < 450 && y > 390 && y < 440) {
                // Pour l'instant rien (option)
            } else if (x > 350 && x < 450 && y > 460 && y < 510) {
                windowManager.stop();
            }
        }
    }
}

void MenuWindow::render(SDL_Renderer* renderer)
{
    windowManager.renderText("Michou’s Cosmic", 50, 50);
    windowManager.renderText("Vendetta", 50, 30);

    windowManager.renderButton("Héberger", 350, 250, 100, 50, 0, 0, 0);
    windowManager.renderButton("Rejoindre", 350, 320, 100, 50, 0, 0, 0);
    windowManager.renderButton("Option", 350, 390, 100, 50, 0, 0, 0);
    windowManager.renderButton("Quitter", 350, 460, 100, 50, 0, 0, 0);
}
