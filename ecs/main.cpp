#include <iostream>
#include "Registry.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <vector>

class Health {
public:
    int hp;
    Health(int hp = 100) : hp(hp) {}
};

class Position {
public:
    float x, y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
};

class Velocity {
public:
    float x, y;
    Velocity(int x = 0, int y = 0) : x(x), y(y) {}
};

class Drawable {
public:
    sf::RectangleShape shape;

    Drawable(sf::Color col, sf::Vector2f size) {
        shape.setFillColor(col);
        shape.setSize(size);
    }
};

class Controllable {
public:
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;

    void reset() {
        moveUp = moveDown = moveLeft = moveRight = false;
    }
};


void position_system(Registry &registry, float deltaTime) {
    auto &positions = registry.get_components<Position>();
    auto &velocities = registry.get_components<Velocity>();

    for (std::size_t i = 0; i < positions.size(); ++i) {
        if (positions[i] && velocities[i]) {
            positions[i]->x += velocities[i]->x * deltaTime;
            positions[i]->y += velocities[i]->y * deltaTime;
        }
    }
}

void control_system(Registry &registry) {
    auto &controllables = registry.get_components<Controllable>();
    auto &velocities = registry.get_components<Velocity>();

    for (std::size_t i = 0; i < controllables.size(); ++i) {
        if (controllables[i] && velocities[i]) {
            velocities[i]->x = 0;
            velocities[i]->y = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                velocities[i]->y = -100;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                velocities[i]->y = 100;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                velocities[i]->x = -100;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                velocities[i]->x = 100;

            controllables[i]->reset();
        }
    }
}

void draw_system(Registry &registry, sf::RenderWindow &window) {
    auto &positions = registry.get_components<Position>();
    auto &drawables = registry.get_components<Drawable>();

    for (std::size_t i = 0; i < positions.size(); ++i) {
        if (positions[i] && drawables[i]) {
            drawables[i]->shape.setPosition(static_cast<float>(positions[i]->x), static_cast<float>(positions[i]->y));
            window.draw(drawables[i]->shape);
        }
    }
}

int main() {
    Registry registry;

    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS Draw System");
    sf::Clock clock;

    registry.register_component<Position>();
    registry.register_component<Velocity>();
    registry.register_component<Drawable>();
    registry.register_component<Controllable>();
    registry.register_component<Health>();

    auto entity = registry.spawn_entity();
    registry.add_component<Position>(entity, Position(100, 150));
    registry.add_component<Velocity>(entity, Velocity());
    registry.add_component<Health>(entity, Health());
    registry.add_component<Drawable>(entity, Drawable(sf::Color::Green, {50.f, 50.f}));
    registry.add_component<Controllable>(entity, Controllable());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        control_system(registry);
        position_system(registry, deltaTime);
        window.clear();
        draw_system(registry, window);
        window.display();
    }

    auto test = registry.get_components<Position>();
    //std::cout << test[entity.get_value()]->x << std::endl;
    std::cout << test[entity]->x << std::endl;

    return 0;
}
