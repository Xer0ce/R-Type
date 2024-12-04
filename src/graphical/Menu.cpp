/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** menu
*/

#include "Menu.hpp"

void render_text(SDL_Renderer *renderer, TTF_Font *font,
                 const std::string &text, int x, int y, SDL_Color color) {
  SDL_Surface *surface =
      TTF_RenderText_Blended(font, text.c_str(), text.size(), color);
  if (!surface) {
    std::cerr << "Text rendering failed: " << SDL_GetError() << std::endl;
    return;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FRect dstRectF = {static_cast<float>(x), static_cast<float>(y),
                        static_cast<float>(surface->w),
                        static_cast<float>(surface->h)};
  SDL_RenderTexture(renderer, texture, nullptr, &dstRectF);
  SDL_DestroySurface(surface);
  SDL_DestroyTexture(texture);
}
bool menu(SDL_Renderer *renderer, TTF_Font *font, SDL_Window *window,
          std::string &ipAddress, std::string &port) {
  bool inMenu = true;
  bool inPort = false;
  SDL_Event event;
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color green = {0, 255, 0, 255};
  SDL_Color black = {0, 0, 0, 255};
  SDL_Color blue = {0, 0, 255, 255};
  std::string inputText = "127.0.0.1";
  std::string inputPort = "12346";

  SDL_StartTextInput(window);
  while (inMenu) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        return false;
      }
      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_TAB) {
          inPort = !inPort;
        }
        if (event.key.key == SDLK_RETURN) {
          ipAddress = inputText;
          port = inputPort;
          inMenu = false;
        } else if (event.key.key == SDLK_BACKSPACE) {
          if (inPort) {
            if (!inputPort.empty())
              inputPort.pop_back();
          } else {
            if (!inputText.empty())
              inputText.pop_back();
          }
        }
      } else if (event.type == SDL_EVENT_TEXT_INPUT) {
        if (inPort) {
          inputPort += event.text.text;
        } else {
          inputText += event.text.text;
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderClear(renderer);

    render_text(renderer, font, "Enter Server IP:", 100, 100, white);
    render_text(renderer, font, inputText, 100, 150, green);
    render_text(renderer, font, "Enter Port:", 100, 200, white);
    render_text(renderer, font, inputPort, 100, 250, blue);
    render_text(renderer, font, "Press Enter to Connect", 100, 300, white);

    SDL_RenderPresent(renderer);
  }
  SDL_StopTextInput(window);
  return true;
}