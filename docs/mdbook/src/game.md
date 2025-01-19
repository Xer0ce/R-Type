# R-Type Game

## Game Rules and Mechanics

### Objective of the Game

The player pilots a spaceship and must survive waves of enemies while destroying them. Each destroyed enemy awards points, and the goal is to progress through increasingly difficult waves and achieve the highest score possible.
Controls

    Movement: Use the arrow keys or WASD keys to move your spaceship along the X (horizontal) and Y (vertical) axes.
    Shooting: Press Spacebar or Left Click to fire bullets at enemies.

### Enemies

The game features various types of enemies, each with unique attributes and behaviors:

    Pion: Standard enemy with balanced health and speed.
    Zinzolin: Fragile but fast.
    Balourd: High health but slow.
    Mini Boss: Tougher enemies with significantly more health and average speed.
    Boss: Extremely durable and very slow, presenting a major challenge.

### Enemy Behavior

Enemies move from right to left across the screen. If they reach the left edge, they reappear at the right. Enemies are controlled by different AI types:

    Aggressive: Moves horizontally but adjusts its vertical position to follow the player.
    Passive: Moves straight horizontally without reacting to the player.
    Balzy: Moves diagonally, alternating between up and down while advancing.
    Boss: Moves slowly up and down but does not advance horizontally.

### Enemy Attacks

Enemies can attack with different attributes:

    Damage Type:
        Poke: Low damage.
        Punch: Standard damage.
        Marmite: High damage.

    Attack Frequency:
        Slow: Fires every 2 seconds.
        High: Fires every 1 second.
        Turret: Fires every 0.5 seconds.

    Bullet Types:
        Missile: Normal-sized bullets.
        FelixBalls: Large bullets.
        Obus: Extra-large bullets.

If no specific attack attributes are defined for an enemy, default values are assigned.
Waves

The game offers multiple modes to suit different playstyles and challenges.

Endless Mode

The game progresses in waves, with enemies becoming more numerous and challenging as you advance:

    Classic Waves: These waves include 5 enemies of varying types and behaviors.
    Mini Boss Waves: Occur every 5th wave (e.g., wave 5, 15, 25, etc.) and include 5 regular enemies along with 1-2 Mini Bosses.
    Boss Waves: Occur every 10th wave (e.g., wave 10, 20, 30, etc.) and feature 5 regular enemies, 1-2 Mini Bosses, and a single Boss.

Each wave is loaded randomly from a set of predefined configurations, ensuring variety and unpredictability in gameplay.

Additionally, players have the ability to create their own custom wave configurations by defining the types of enemies, their behaviors, and attack properties in JSON format. This allows for endless possibilities and personalization of the game experience.

An example of a custom wave configuration in JSON format is provided below.

```json
{
    "enemies":
    [
        {
            "type": "Pion",
            "number": 1,
            "ia": "Passive",
            "frequency": "Slow",
            "damage": "Punch"
        },
        {
            "type": "Balourd",
            "number": 1,
            "ia": "Passive",
            "frequency": "Turret",
            "damage": "Poke"
        },
        {
            "type": "Zinzolin",
            "number": 1,
            "ia": "Passive",
            "damage": "Marmite"
        },
        {
            "type": "BigBoss",
            "number": 1,
            "ia": "Boss",
            "damage": "Marmite"
        }
    ]
}
```

All the files are located in the src/game/config/endless directory. You can modify the existing files to customize your game.

### Adventure Mode

The game also features an Adventure Mode, where players face a series of 10 progressively harder levels. Each level introduces more enemies, additional Mini Bosses, and eventually Boss fights. The maximum number of enemies per wave in this mode is 15.

Player Strategy

To succeed, players must:

    Master ship movement to avoid enemy fire.
    Prioritize eliminating high-damage or fast enemies.
    Adapt to different enemy behaviors and attack patterns.
    Survive waves while collecting points and progressing through the game.

### Duel Mode

In Duel Mode, you can engage in a 1v1 battle with your friend. Each player has the ability to use a special ability or spell every 10 seconds. The goal is simple: defeat your opponent by strategically using your abilities and attacks. The player who successfully destroys the other first wins the match. This mode focuses on fast-paced, strategic gameplay where timing and skillful use of your special abilities are key to victory.