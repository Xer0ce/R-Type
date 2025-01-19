# R-type Engine

#### This is the user documentation about our engine.

#### For the developer documentation with all the precise about classes click [here](https://m0ugou-club.github.io/R-Type/doxygen/html/dir_ddca5f149c4ce13074f28b270e950ba9.html)

---

We've decided to go with the architecture of an ECS (Entity Component System) because it provides a modular, flexible, and highly efficient framework for managing game entities and their behaviors. This approach allows us to separate concerns effectively, enabling developers to manage entities, components, and systems independently while ensuring scalability for complex game logic.

In this documentation, we will break down the implementation of each part of the ECS, including:

- Entities: The core identifiers for game objects.
- Components: The data associated with entities.
- Systems: The logic that operates on components to bring the game to life.

We'll also include a detailed example of how to use our ECS in code, illustrating its practical application and how it simplifies game development workflows.

### Entities :

Entities is basicly represented by an id and that's all !
So an entity will juste appear like this :

```
+-----------------+
|     Entity      |
|-----------------|
|       ID        |
|    (size_t)     |
+-----------------+
```

### Components :

Before linking our Components with Entities, we need a way to manage them effectively.

To do this, we use Sparse Arrays, which are an optimized structure for storing components associated with Entities.

A Sparse Array functions like an enhanced version of a vector, specifically designed to store components for entities. Each type of component will have its own Sparse Array. The size of the array corresponds to the total number of entities, with each index in the array representing an entity ID.

If a particular entity does not require the component, the value at its index will be set to nullopt. This approach ensures efficient memory usage and fast access to components, even when not all entities share the same components.

There is a small schema illustrating how Sparse Arrays work :

In the following schema, we have three columns: **Entities**, **Component A**, and **Component B**. The rows represent the entities (0 to 3) and the components assigned to them.

```
+-----------------+  +-----------------+  +-----------------+
|     Entities    |  |   Component A   |  |   Component B   |
|-----------------|  |-----------------|  |-----------------|
|        0        |  |   Component A   |  |   Component B   |
|        1        |  |     nullopt     |  |     nullopt     |
|        2        |  |     nullopt     |  |   Component B   |
|        3        |  |   Component A   |  |     nullopt     |
+-----------------+  +-----------------+  +-----------------+
```

Now that we have the Sparse Array to manage components and entities separately,
we need a system that will manage the creation of components and link them with the respective entities.
This part is handled by the Registry.

The Registry acts as a central management system where components are created, stored, and linked to their respective entities.
It ensures that each component type is associated with the correct entity and manages the lifecycle of these components efficiently.
This system allows for quick access and modification of components tied to specific entities, and it serves as a bridge between the component creation process and the Sparse Array.

The Registry is the core of the engine. It will store all the components, all the entities, and everything related to the game you're creating.
Additionally, it can manage the lifecycle of all these elements.

### Systems

In an Entity-Component-System (ECS) architecture, **Systems** are the core logic that processes entities with specific components. Unlike components, which only store data, and entities, which are identifiers for objects in the game, systems contain the behavior and rules that act on the components.

Systems iterate over the entities that have the required components, perform operations on them, and update the game state accordingly. Each system is responsible for a specific aspect of the game, such as movement, physics, or rendering.

In fact, systems are not directly managed by the Registry; instead, they are defined and implemented by the developer. Systems are essentially functions or classes that allow the developer to create and control the game's behavior.

Below is a schema that illustrates how systems interact with and update the components of entities.

```
+---------------------+           +-------------------+           +---------------------+
|     Developer's     |           |     Systems       |           |     Components      |
|     Functions       |           |  (Game Logic)     |           |    (Entity Data)    |
|     (Movement,      |           |                   |           |  - Position         |
|     Physics,        |   ---->   |   - Movement      |   ---->   |  - Velocity         |
|     Rendering,      |           |   - Physics       |           |  - Health           |
|     AI, etc.)       |           |   - AI            |           |  - AI State         |
|                     |           +-------------------+           |  ...                |
+---------------------+                    |                      +---------------------+
                                           v
                                 +---------------------+
                                 |    Entities         |
                                 |  - Entity 0         |
                                 |  - Entity 1         |
                                 |  - Entity 2         |
                                 |  ...                |
                                 +---------------------+
```

### Code implementation

#### 1 : Creation of an Entity

This is how you can create an entity.

```c++
#include "Registry.hpp"

int main() {
    Registry registry;

    size_t entity = registry.create_entity();

    std::cout << "Entity created with ID: " << entity << std::endl;

    return 0;
}

```

#### 2 : Add Components to an Entity

To add components to an entity, you must first register the component type in the registry. This step ensures that the registry is aware of the component and can manage its instances correctly.

Once the component is registered, you can add it to any entity. Components are linked to entities via their unique identifiers, and this process is both flexible and efficient.

```c++
#include "Registry.hpp"

struct Velocity {
  float x, y;
  Velocity(float x = 0, float y = 0) : x(x), y(y) {}
};

struct Position {
  float x, y;
  float old_x, old_y;
  Position(int x = 0, int y = 0) : x(x), y(y) {}
};

int main() {
    Registry registry;

    registry.register_component<Position>();
    registry.register_component<Velocity>();
    size_t entity = registry.create_entity();

    registry.add_component<Position>(entity, {100, 200});

    registry.add_component<Velocity>(entity, {2, 3});

    std::cout << "Entity " << entity << " has components: Position and Velocity." << std::endl;

    return 0;
}

```

#### 3 : Components Access and Modification

After a component is associated with an entity, you can access and modify it directly. This is useful for updating entity states, such as changing positions, modifying velocities, or updating health values during gameplay.

Components can be accessed by their type and the entity ID, ensuring fast lookups and streamlined operations.

```c++
#include "Registry.hpp"

struct Position {
  float x, y;
  float old_x, old_y;
  Position(int x = 0, int y = 0) : x(x), y(y) {}
};

int main() {
    Registry registry;

    registry.register_component<Position>();

    size_t entity = registry.create_entity();

    registry.add_component<Position>(entity, {100, 200});

    std::cout << "Initial Pos: (" << position.x << ", " << position.y << ")" << std::endl;

    position.x += 10;
    position.y += 20;

    std::cout << "Updated Pos : (" << position.x << ", " << position.y << ")" << std::endl;

    return 0;
}

```

#### 4 : Systems and Entity Updates

Systems are where the game logic resides. They iterate over entities with specific components and apply the necessary updates. For example, a movement system might update the position of all entities that have both Position and Velocity components.

Systems operate independently of the registry, allowing you to define and execute game behavior in a modular way.

```c++
#include "Registry.hpp"

struct Velocity {
  float x, y;
  Velocity(float x = 0, float y = 0) : x(x), y(y) {}
};

struct Position {
  float x, y;
  float old_x, old_y;
  Position(int x = 0, int y = 0) : x(x), y(y) {}
};

void update_positions(Registry &registry) {
    auto &positions = registry.get_components<Position>();
    auto &velocities = registry.get_components<Velocity>();

    for (size_t i = 0; i < positions.size(); ++i) {
        if (positions[i].has_value() && velocities[i].has_value()) {
            positions[i]->x += velocities[i]->x;
            positions[i]->y += velocities[i]->y;
        }
    }
}

int main() {
    Registry registry;

    registry.register_component<Position>();

    size_t entity1 = registry.create_entity();
    registry.add_component<Position>(entity1, {0, 0});
    registry.add_component<Velocity>(entity1, {1, 1});

    size_t entity2 = registry.create_entity();
    registry.add_component<Position>(entity2, {10, 20});
    registry.add_component<Velocity>(entity2, {2, 3});

    update_positions(registry);

    auto &positions = registry.get_components<Position>();
    for (size_t i = 0; i < positions.size(); ++i) {
        if (positions[i].has_value()) {
            std::cout << "Entity " << i << " Position: (" << positions[i]->x << ", " << positions[i]->y << ")" << std::endl;
        }
    }

    return 0;
}

```

#### 5 : Entity and Component Deletion

Entities and their components can be removed when they are no longer needed. Deleting an entity will automatically clean up all its associated components. You can also delete specific components from an entity if required.

This ensures efficient memory usage and keeps the ECS clean and performant during runtime.

```c++
#include "Registry.hpp"

struct Position {
  float x, y;
  float old_x, old_y;
  Position(int x = 0, int y = 0) : x(x), y(y) {}
};

int main() {
    Registry registry;

    registry.register_component<Position>();

    size_t entity = registry.create_entity();

    registry.add_component<Position>(entity, {50, 100});

    registry.kill_entity(entity);

    registry.remove_component<Position>(entity);

    std::cout << "Entity and its components have been removed." << std::endl;

    return 0;
}

```

#### 6 : Example Workflow

Here’s an overview of a typical workflow:

    Register the necessary component types.
    Create entities using the registry.
    Add components to the entities.
    Use systems to define and execute the game logic.
    Access or modify components as needed during gameplay.
    Delete unused entities or components to maintain performance.
