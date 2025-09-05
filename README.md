# ‼️This branch exists only to comply with the structure described in the exam guidelines.‼️

## V0.1

### What's new 🆕

- Set initial window settings
- Handle window resizing
- Configure tile-based window
- Create game state with its respective states
- Create player with animated textures/sprites
- Handle movements
- Manage the view/camera to follow the player

### Demo 🎥

![Demo_V0.1](/docs/v0.1.gif)

## v0.2

### What's new 🆕

- Create the tilemap using a vertex array
- Load the map from a CSV file
- Optimize the tilemap by rendering only the tiles visible in the current view

### Demo 🎥

![Demo_V0.2](/docs/v0.2.gif)

## v0.3

### What's new 🆕

- Create a simple map
- Add a hitbox to the player
- Implement solid objects and populate them on the map using a CSV file
- Implement collisions with solid tiles and objects

### Demo 🎥

![Demo_V0.3](/docs/v0.3.gif)

## v0.4

### What's new 🆕

- Add an abstract Entity class
- Create collectible (pickup) objects
- Implement an inventory system to store collected objects

### Demo 🎥

![Demo_V0.4](/docs/v0.4.gif)

## v0.5

### What's new 🆕

- Add coins, health, and experience for the player
- Implement a UI that displays the above (coins, health, experience) along with the inventory

### Demo 🎥

![Demo_V0.5](/docs/v0.5.gif)

## v0.6

### What's new 🆕

- Refactor game state transitions using polymorphism
- Load and manage all textures from a single texture atlas (previously, each asset had its own texture)
- Create dedicated Collision and Handler classes
- Remove pickable objects from the game
- Simplify the TileMap, UI, Entity, and Player classes

### Screenshot 📸

![Screenshot_V0.5](/docs/class_diagram_v0.5.png)

---

![Screenshot_V0.6](/docs/class_diagram_v0.6.png)

## 0.7

### What's new 🆕

- Create NPCs
- Implement depth-ordered drawing and optimize NPC rendering
- Handle collisions between the player and NPCs
- Implement dialogue interactions with NPCs

### Demo 🎥

![Demo_V0.7](/docs/v0.7.gif)

## 0.8

### What's new 🆕

- Create weapons with 5 upgrade levels
- Add weapon display and cooldown indicator to the UI
- Implement advanced dialogues with selectable options

### Demo 🎥

![Demo_V0.8](/docs/v0.8.gif)

## 0.9

### What's new 🆕

- Dynamic management of entities on the map
- Create monsters
- Handle collisions between monsters and player (monster collision triggered by player’s weapon hit)
- Add an “aiming reticle” for the player’s attack
- Manage monster spawning
- Implement simple chasing AI for monsters

### Demo 🎥

![Demo_V0.9](/docs/v0.9.gif)

## 1.0

### What's new 🆕

- Add 2 maps (main map and arena)
- New textures created by my lovely girlfriend
- Implement graphics and logic for the pause menu
- Instant map switching from the pause menu
- Death and healing system
- Graphical implementation of the start state
- Inventory system for weapons

### Demo 🎥

![Demo_V1.0](/docs/v1.0.gif)

# Survivops 🎮

[![CI](https://github.com/flaventu/survivops/actions/workflows/ci.yml/badge.svg)](https://github.com/flaventu/survivops/actions/workflows/ci.yml)
![Repo Size](https://img.shields.io/github/repo-size/flaventu/survivops)
[![SFML](https://img.shields.io/badge/SFML-3.0.1-green?logo=sfml)](https://www.sfml-dev.org/)

## Purpose 🥅

This is a project for the "[Fundamentals of computer graphics](https://corsi.unige.it/off.f/2024/ins/77856)" course offered by the Bachelor's degree in [Computer Science](https://corsi.unige.it/corsi/8759) at the [University of Genoa](https://unige.it/).

## Description ▶️

It is a simple low-level 2D single-player game where you can explore the world map, interact with NPCs, fight enemies, develop your character's skills and weapons.

## Why SurvivOps ❔

The title is a play on the words "survive" and "Ops", just like [Dev-Ops](https://azure.microsoft.com/it-it/resources/cloud-computing-dictionary/what-is-devops). The idea is to take the main pivots of the model, where you **build** your application, **test** it and finally **deploy** it multiple times to associate it to the functions of the game;

- 🔧 build: you can purchase or upgrade your weapons and improve your character's abilities.
- 🧪 test: there is a training area where you can simulate fight.
- ✈️ deploy: where you can finally fight real enemies and take on new challenges as you progress throught the game.

It's a run-based game, which means that instead of following a linear story, the game substantially never ends, allowing the player great freedom in their gameplay.

## Constraint 🛑

1. the project must start from **scratch** (i can only use the [cmake-sfml-project](https://github.com/SFML/cmake-sfml-project) template).
2. I cannot use **external libraries** except for [SFML](https://www.sfml-dev.org/) itself.
3. I'm limited to using only **basic primitives** (text, simple shapes, sprite and vertex array).

## Credits 🌟

- 👥 **Characters (Player, Npcs and Enemies)**:
  - [retro-rpg-character-pack](https://the-pixel-nook.itch.io/retro-rpg-character-pack) by *The Pixel Nook*
- 🗡️ **Weapons**:
  - [super-epic-fantasy-weapons-pack](https://babysamurai.itch.io/super-epic-fantasy-weapons-pack) by *Babysamurai*
- ➡️ **UI arrow**:
  - [caz-pixel-letters](https://cazwolf.itch.io/caz-pixel-letters) by *Caz*

## Requirements ✒️

- [![CMake](https://img.shields.io/badge/CMake-white?logo=cmake&logoColor=darkred)](https://cmake.org/)
  - **≥ 3.28**
- ![C++](https://img.shields.io/badge/C%2B%2B-white.svg?logo=c%2B%2B&logoColor=darkblue)
  - **17**
    - GCC ≥ 9 or Clang (Linux)
    - Apple Clang (macOS)
    - MSVC (Visual Studio 2022+) or MinGW (Windows)
- ![Git](https://img.shields.io/badge/Git-white?logo=git)
  - Needed to clone the project and download SFML via `FetchContent`
- ![SFML](https://img.shields.io/badge/SFML-white?logo=sfml)
  - Automatically downloaded and built using [`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html)

## Setup ⚙️

After cloning the project with Git, follow the setup instructions below depending on your operating system or development environment:

### 🐧 Linux / macOS

```bash
# Run these commands inside the project root

# Create and enter the build directory
mkdir build && cd build

# Generate build files with CMake
cmake ..

# Compile the project
cmake --build .

# Navigate to the output directory
cd bin

# Run the game
./SurvivOps
```

### 🪟 Windows

#### Visual Studio

1. Open **Visual Studio 2022** (or newer).
2. Click on “**Open a local folder**” and select the project root directory.
3. Visual Studio will automatically detect the `CMakeLists.txt` file and configure the project.
4. Press **F5** or click “**Start Debugging**” to build and run the game.

#### Terminal (PowerShell or CMD)

```powershell
# Run these commands inside the project root

# Create a build directory
mkdir build
cd build

# Configure (Visual Studio generator)
cmake .. -G "Visual Studio 17 2022"

# Build (Release config)
cmake --build . --config Release

# Navigate to the output directory
cd bin/Release

# Run the executable
./SurvivOps.exe
```

### 🧩 Visual Studio Code (Cross-platform)

You can easily configure, build, and run the project in Visual Studio Code using the [**CMake Tools**](https://code.visualstudio.com/docs/cpp/cmake-linux) extension.

1. After installing the extension, open the project folder in VS Code
2. Press `Ctrl+Shift+P` → **CMake: Configure**
3. Press `Ctrl+Shift+P` → **CMake: Build**
4. Press `Ctrl+Shift+P` → **CMake: Run Without Debugging**

> ℹ️ **Note**: All of these actions can also be performed by clicking the corresponding buttons in the blue **status bar** at the bottom of the VS Code window — there's no need to use the command palette if you prefer using the UI.

## How To Play 🕹️

- When the window opens, press `Enter` to **start playing**.
- Use `WASD` to **move** your character.
- The UI **displays**
  - 🪙 Current **coins**
  - 📈 **Player level** (with a progress bar)
  - 💓 **Health**
  - 🗡️ Current **Weapon** with its level
  - A small icon indicating your **current map**:
    - 🏠 **Main map**
    - ⚔️ **Arena**
- **Coins** and **EXP** can be collected by defeating enemies.

### ⏸️ Pause & Map Switching

- Press `Esc` to pause the game, you can press `Esc` **again** to **resume** the game.
- You can also **instantly switch maps** from the pause panel:
  - Press `F` to go to the **arena** (only available when you're on the main map).
  - Press `H` to go back to the **main map** (only available when you're in the arena).

### 🗣️ Interacting with NPCs

- To start a conversation with an NPC, get close and press `Enter`. A black panel at the top of the screen will appear to indicate **dialogue mode**.
- During dialogue, press `Enter` to continue through the text.
- When multiple dialogue **options** appear (each one marked with a "-"), use the `⇑` and `⇓` arrow keys to select one. By default, **no option is pre-selected** to prevent accidental choices from spamming the Enter key.

### 👊 Combat & Weapons

- Press `P` to use your weapon. When the weapon is **glowing**, it’s ready to use; otherwise, you must wait for its **cooldown**, which varies depending on the weapon.
- Weapons range from **level 1** to **5**.
  - 🟤 Bronze
  - 🟨 Gold
  - 🟪 Amethyst
  - 🔷 Diamond
  - ⚫ Obsidian
- Each weapon has a specific **attack range**, and its shot is represented by a **red dot** on the map.
- **Coins** can be invested to **upgrade weapons** by talking to specific **NPCs**.
- After **purchasing** a new weapon, it is added to your **inventory**.
- Press `C` to cycle through weapons in your inventory.

### 🪲 Arena System & Enemies

- In the arena, enemies **spawn every 5 seconds** on the map, with levels close to the **current player level**.
- There are **three enemy types**:
  - 👺 **Goblin**: Very fast, but low health and low damage.
  - 🛡️ **Knight**: Very slow, but high health and strong attacks.
  - 🧙‍♀️ **Witch**: Weak in all stats, but can randomly poison the player.
- Each enemy displays its **current health** and **level** above its head.
- After **1 minute** in the arena, both the **player and enemies regenerate 10% of their health**.

### 🧬 Status Effects

- When you **take damage**, your character briefly turns **red** for **0.5 seconds**, during which you are **invulnerable** to further hits.
- If you are **poisoned**, your character turns **green**, and you take **small damage every second for 5 seconds**.
- When you **level up**, your character flashes **blue** briefly, and your **attributes increase**.
- During combat, there's a small chance to **dodge incoming attacks** (this chance increases **with your level**).

### ☠️ Game Over & Respawn

- If your health reaches zero, a **Game Over screen** appears.
- Press `R` to respawn at the center of the **main map**.
- Upon respawn, you **lose all coins** collected so far, all other attributes (weapons, level, experience, etc.) **remain unchanged**.

---

Have fun! 💟
