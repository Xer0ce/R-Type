#ifndef MENU_HPP
#define MENU_HPP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>

class Menu {
public:
  Menu(SDL_Renderer *renderer);
  ~Menu();

  int run();
  void render();

private:
  void handleInput();
  void renderTitle();
  void renderMenuItems();

  SDL_Renderer *renderer;
  SDL_Texture *backgroundTexture;
  TTF_Font *font;

  int selectedIndex;
  std::vector<std::string> menuOptions;

  bool running;

  SDL_Texture *loadTexture(const char *path);
  void renderText(const std::string &text, float x, float y, bool isSelected);
};

#endif
