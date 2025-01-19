# R-Type Architecture

The architecture of R-Type is built around several key components that manage threads, scenes, communication, and graphical rendering.

---

## 1. **Core File and Thread Management**

The architecture is centered around a core file, typically named `Server.cpp` or `Game.cpp`, which runs three threads:

- **TCP Thread**: Manages network connections via TCP.
- **UDP Thread**: Manages network connections via UDP.
- **Game Loop Thread**: Handles the game logic continuously.

---

## 2. **Client/Server Interfaces**

For both the client and the server, we use the `IClient` and `IServer` interfaces. These interfaces are implemented in the following files:

- `TCP.cpp`
- `UDP.cpp`

These implementations manage network communications via TCP and UDP.
<img src="https://iili.io/2PiL4V4.png" alt="Client/Server Architecture Illustration" width="450"/>

---

## 3. **Scene System**

The architecture also features a basic scene system. The scene structure is organized as follows:

1. **`IScene` Interface**
2. **Abstract Class `AScene`**
3. **Concrete Implementations**:
   - Endless
   - History
   - OneVsOne
   - Menu
   - Lobby

The core file contains an instance of each scene, and an enum specifies which scene should be played. Each scene is mapped to an enum value in a `std::map`. Each scene implements an overridden `loop` method that returns a `sceneType` enum to determine if the scene should change.

<img src="https://iili.io/2PipPIt.png" alt="Client/Server Architecture Illustration" width="600"/>

---

## 4. **Graphical Core (SDL3)**

The graphical core of the project contains an instance of the `Window` class, which interacts with the SDL3 graphics library through various methods.

---

## 5. **ECS (Entity-Component-System)**

The architecture also includes an instance of the ECS system, specifically the `Registry`, which efficiently manages most of the game entities.

---

## 6. **Thread Communication via Queue**

The code includes an instance of `Queue` (in `Queue.hpp`), allowing communication between the three threads. This enables the game loop thread to send messages to the server through the TCP or UDP queues, facilitating bidirectional communication between all threads.

<img src="https://iili.io/2PsJYaj.png" alt="Client/Server Architecture Illustration" width="300"/>

---

## Conclusion

The architecture of R-Type is based on a modular and optimized system for managing network connections, game scenes, graphical rendering, and entities. Each component is designed to work seamlessly and efficiently, providing an optimal gaming experience.

