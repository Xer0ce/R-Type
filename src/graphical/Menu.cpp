#include "Menu.hpp"

void render_text(SDL_Renderer *renderer, TTF_Font *font,
                 const std::string &text, float x, float y, SDL_Color color) {
  SDL_Surface *surface =
      TTF_RenderText_Blended(font, text.c_str(), text.length(), color);
  if (!surface) {
    std::cerr << "Text rendering failed: " << SDL_GetError() << std::endl;
    return;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FRect dstRect = {x, y, static_cast<float>(surface->w),
                       static_cast<float>(surface->h)};
  SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
  SDL_DestroySurface(surface);
  SDL_DestroyTexture(texture);
}

bool is_mouse_over(int x, int y, int w, int h, int mouseX, int mouseY) {
  return mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h;
}

bool menu(SDL_Renderer *renderer, TTF_Font *font, SDL_Window *window,
          std::string &ipAddress, std::string &port) {
  bool inMenu = true;
  SDL_Event event;
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color green = {0, 255, 0, 255};
  SDL_Color black = {0, 0, 0, 255};
  SDL_Color blue = {0, 0, 255, 255};

  std::string inputText = "127.0.0.1";
  std::string inputPort = "4243";

  SDL_StartTextInput(window);
  float mouseX, mouseY;

  SDL_FRect ipButton = {100, 150, 400, 50};
  SDL_FRect portButton = {100, 250, 400, 50};
  SDL_FRect connectButton = {100, 350, 200, 50};

  while (inMenu) {
    SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        return false;
      }

      if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (is_mouse_over(ipButton.x, ipButton.y, ipButton.w, ipButton.h,
                          mouseX, mouseY)) {
        } else if (is_mouse_over(portButton.x, portButton.y, portButton.w,
                                 portButton.h, mouseX, mouseY)) {
        } else if (is_mouse_over(connectButton.x, connectButton.y,
                                 connectButton.w, connectButton.h, mouseX,
                                 mouseY)) {
          ipAddress = inputText;
          port = inputPort;
          inMenu = false;
        }
      } else if (event.type == SDL_EVENT_TEXT_INPUT) {
        if (is_mouse_over(ipButton.x, ipButton.y, ipButton.w, ipButton.h,
                          mouseX, mouseY)) {
          inputText += event.text.text;
        } else if (is_mouse_over(portButton.x, portButton.y, portButton.w,
                                 portButton.h, mouseX, mouseY)) {
          inputPort += event.text.text;
        }
      } else if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_BACKSPACE) {
          if (is_mouse_over(ipButton.x, ipButton.y, ipButton.w, ipButton.h,
                            mouseX, mouseY) &&
              !inputText.empty()) {
            inputText.pop_back();
          } else if (is_mouse_over(portButton.x, portButton.y, portButton.w,
                                   portButton.h, mouseX, mouseY) &&
                     !inputPort.empty()) {
            inputPort.pop_back();
          }
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderClear(renderer);

    render_text(renderer, font, "R-Type", 500, 50, white);

    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
    SDL_RenderFillRect(renderer, &ipButton);
    render_text(renderer, font, "Server IP: " + inputText, ipButton.x + 10,
                ipButton.y + 10, black);

    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
    SDL_RenderFillRect(renderer, &portButton);
    render_text(renderer, font, "Port: " + inputPort, portButton.x + 10,
                portButton.y + 10, black);

    SDL_SetRenderDrawColor(renderer,
                           is_mouse_over(connectButton.x, connectButton.y,
                                         connectButton.w, connectButton.h,
                                         mouseX, mouseY)
                               ? green.r
                               : blue.r,
                           green.g, green.b, green.a);
    SDL_RenderFillRect(renderer, &connectButton);
    render_text(renderer, font, "Connect", connectButton.x + 30,
                connectButton.y + 10, white);

    SDL_RenderPresent(renderer);
  }

  SDL_StopTextInput(window);
  return true;
}
