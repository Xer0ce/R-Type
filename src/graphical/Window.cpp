/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#include "Window.hpp"
#include <iostream>

Window::Window() {}

Window::~Window() {}

void Window::init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    exit(84);
  }

  _window = SDL_CreateWindow("R-Type", 800, 600, 0);
  if (!_window) {
    std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    exit(84);
  }

  _renderer = SDL_CreateRenderer(_window, nullptr);
  if (!_renderer) {
    std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError()
              << std::endl;
    destroyWindow();
    exit(84);
  }
}

void Window::destroyWindow() {
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

void Window::delay(int time) {
  SDL_Delay(time);
}

bool Window::checkingCloseWindow() {
  while (SDL_PollEvent(&_event)) {
    if (_event.type == SDL_EVENT_QUIT) {
      return false;
    }
  }
  return true;
}

void Window::draw(SDL_Texture *texture, SDL_FRect rect) {
  SDL_RenderTexture(_renderer, texture, nullptr, &rect);
}

void Window::render() {
  SDL_RenderPresent(_renderer);
}

void Window::clear() {
  SDL_RenderClear(_renderer);
}

SDL_Texture *Window::loadTexture(const char *path) {
  return IMG_LoadTexture(_renderer, path);
}
