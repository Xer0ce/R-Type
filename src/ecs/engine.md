# R-type Engine

#### This is the user documentation about our engine.

#### For the developer documentation with all the precise about classes click [here]()

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