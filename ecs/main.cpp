#include <iostream>
#include "Registry.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <vector>

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

// int main() {
    //try {
    //    // Crée une instance de Registry
    //    Registry registry;
//
    //    // Enregistre les composants Position et Health dans le registre
    //    registry.register_component<Position>();
    //    registry.register_component<Health>();
//
    //    // Crée une entité
    //    auto entity = registry.spawn_entity();
//
    //    // Ajoute des composants à l'entité
    //    registry.add_component(entity, Position(10, 20));
    //    registry.add_component(entity, Health(80));
//
    //    // Affiche les valeurs de l'entité
    //    auto &position = registry.get_components<Position>();
    //    auto &health = registry.get_components<Health>();
    //    std::cout << "Entity position: (" << position[entity.get_value()]->x << ", " << position[entity.get_value()]->y << ")\n";
    //    std::cout << "Entity health: " << health[entity.get_value()]->hp << std::endl;
//
    //    // Supprime le composant Health de l'entité
    //    registry.remove_component<Health>(entity);
    //    std::cout << "Health component removed." << std::endl;
    //    auto &health2 = registry.get_components<Health>();
//
    //    // Affiche après suppression
    //    try {
    //        std::cout << "Entity health after removal: " << health2[entity.get_value()]->hp << std::endl;
    //    } catch (const std::out_of_range&) {
    //        std::cout << "No health component left for this entity.\n";
    //    }
//
    //    // Tue l'entité et supprime tous ses composants
    //    registry.kill_entity(entity);
    //    std::cout << "Entity killed and all components removed." << std::endl;
//
    //    // Test si l'entité a bien été ajoutée à _available_entities
    //    auto available_entities = registry.get_available_entities(); // Ajoute une fonction pour récupérer _available_entities
    //    if (std::find(available_entities.begin(), available_entities.end(), entity.get_value()) != available_entities.end()) {
    //        std::cout << "Entity has been successfully added to available entities.\n";
    //    } else {
    //        std::cout << "Entity is NOT in available entities.\n";
    //    }
//
    //} catch (const std::exception &e) {
    //    std::cerr << "Error: " << e.what() << std::endl;
    //}

     //return 0;
//}

int main() {
    Registry registry;

    // Initialisation de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS Draw System");
    sf::Clock clock;

    // Enregistrement des composants dans le registre
    registry.register_component<Position>();
    registry.register_component<Velocity>();
    registry.register_component<Drawable>();
    registry.register_component<Controllable>();

    // Création d'une entité avec tous les composants nécessaires
    auto entity = registry.spawn_entity();
    registry.add_component<Position>(entity, Position(100, 150));
    registry.add_component<Velocity>(entity, Velocity());
    registry.add_component<Drawable>(entity, Drawable(sf::Color::Green, {50.f, 50.f}));
    registry.add_component<Controllable>(entity, Controllable());

    // Boucle principale
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

    return 0;
}
