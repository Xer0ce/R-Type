/*
** EPITECH PROJECT, 2024
** RType
** File description:
** TextInput
*/

#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include <string>
#include <functional>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

struct TextInput {
  SDL_Rect rect;                  // Zone où le texte sera affiché
  SDL_Texture *backgroundTexture; // Texture d'arrière-plan (optionnel)
  SDL_Color textColor;            // Couleur du texte
  std::string inputText;          // Texte actuel entré par l'utilisateur
  bool isFocused;                 // Indique si l'utilisateur interagit avec cette zone de texte

  // Constructeur
  TextInput(SDL_Rect r, SDL_Color color, SDL_Texture *bgTex = nullptr)
      : rect(r), backgroundTexture(bgTex), textColor(color), inputText("cacadoux"), isFocused(false) {}

  // Méthode pour ajouter du texte
  void addCharacter(char c) {
    if (isFocused) {
      inputText += c;
    }
  }

  // Méthode pour supprimer un caractère (backspace)
  void removeCharacter() {
    if (isFocused && !inputText.empty()) {
      inputText.pop_back();
    }
  }

  // Méthode pour dessiner le TextInput
  void render(SDL_Renderer *renderer, TTF_Font *font) {
    // Dessiner l'arrière-plan
    if (backgroundTexture) {
      SDL_RenderCopy(renderer, backgroundTexture, nullptr, &rect);
    } else {
      SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Gris clair par défaut
      SDL_RenderFillRect(renderer, &rect);
    }

    // Dessiner le texte
    if (!inputText.empty()) {
      SDL_Surface *textSurface = TTF_RenderText_Blended(font, inputText.c_str(), textColor);
      SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

      SDL_Rect textRect = {rect.x + 5, rect.y + (rect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
      SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

      SDL_DestroyTexture(textTexture);
      SDL_FreeSurface(textSurface);
    }

    // Dessiner une bordure si le champ est sélectionné
    if (isFocused) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Bordure bleue
      SDL_RenderDrawRect(renderer, &rect);
    }
  }
};

#endif // TEXTINPUT_HPP
