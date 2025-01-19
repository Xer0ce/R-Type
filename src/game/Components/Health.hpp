/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Health
*/

#ifndef HEALTH_HPP
#define HEALTH_HPP

struct Health {
  int hp;
  Health(int hp = 100) : hp(hp) {}
};

struct MaxHealth {
  int hp;
  MaxHealth(int hp = 100) : hp(hp) {}
};

#endif // HEALTH_HPP
