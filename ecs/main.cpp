#include <iostream>
#include "Registry.hpp"

class Position {
public:
    int x, y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
};

class Health {
public:
    int hp;
    Health(int hp = 100) : hp(hp) {}
};

int main() {
    try {
        // Crée une instance de Registry
        Registry registry;

        // Enregistre les composants Position et Health dans le registre
        registry.register_component<Position>();
        registry.register_component<Health>();

        // Crée une entité
        auto entity = registry.spawn_entity();

        // Ajoute des composants à l'entité
        registry.add_component(entity, Position(10, 20));
        registry.add_component(entity, Health(80));

        // Affiche les valeurs de l'entité
        auto &position = registry.get_components<Position>();
        auto &health = registry.get_components<Health>();
        std::cout << "Entity position: (" << position[entity.get_value()]->x << ", " << position[entity.get_value()]->y << ")\n";
        std::cout << "Entity health: " << health[entity.get_value()]->hp << std::endl;

        // Supprime le composant Health de l'entité
        registry.remove_component<Health>(entity);
        std::cout << "Health component removed." << std::endl;
        auto &health2 = registry.get_components<Health>();

        // Affiche après suppression
        try {
            std::cout << "Entity health after removal: " << health2[entity.get_value()]->hp << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "No health component left for this entity.\n";
        }

        // Tue l'entité et supprime tous ses composants
        registry.kill_entity(entity);
        std::cout << "Entity killed and all components removed." << std::endl;

        // Test si l'entité a bien été ajoutée à _available_entities
        auto available_entities = registry.get_available_entities(); // Ajoute une fonction pour récupérer _available_entities
        if (std::find(available_entities.begin(), available_entities.end(), entity.get_value()) != available_entities.end()) {
            std::cout << "Entity has been successfully added to available entities.\n";
        } else {
            std::cout << "Entity is NOT in available entities.\n";
        }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
