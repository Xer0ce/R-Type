/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameWindow
*/

#include "GameWindow.hpp"

GameWindow::GameWindow(WindowManager& manager, ConnectionManager &connectionManager) : windowManager(manager), connectionManager(connectionManager)
{

}

GameWindow::~GameWindow()
{
}

void GameWindow::initialize()
{
    connectionManager.initialize("127.0.0.1", 4243, "127.0.0.1", 4242);
    std::cout << "GameWindow initialized and test messages sent." << std::endl;
    Command command;

    command.type = CommandType::CONNECT;
    command.connect.Nickname = "PlayerMichou";
    connectionManager.sendCommand(command, "TCP");
}

void GameWindow::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            windowManager.stop();
        }
    }
}

void GameWindow::render(SDL_Renderer* renderer)
{
 // render game
}