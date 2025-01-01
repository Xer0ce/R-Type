/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AWindow
*/

#pragma once
#include "IWindow.hpp"

class AWindow : public IWindow {
protected:
    int width;
    int height;
    float volume;

public:
    AWindow(int w, int h, float v) : width(w), height(h), volume(v) {}
    virtual ~AWindow() = default;

    void setVolume(float v) { volume = v; }
    float getVolume() const { return volume; }
};
