# ArcadeGames

A collection of classic arcade games built with C++ and [raylib](https://www.raylib.com/). Includes Tic-Tac-Toe (XO), Connect 4, Snake, and Pong — each playable via a GUI with player-vs-player and player-vs-AI modes.

🌐 **Play it online:** [https://kamolia00.github.io/ArcadeGames/](https://kamolia00.github.io/ArcadeGames/)

## Games

| Game | Modes |
|------|-------|
| **Tic-Tac-Toe (XO)** | PvP, AI (easy / hard) |
| **Connect 4** | PvP, AI (easy / hard) |
| **Snake** | Classic, Timed |
| **Pong** | PvP, vs AI |

## Requirements

- **C++14** or later
- **CMake** ≥ 4.2
- **MinGW-w64** (or another compatible compiler)
- **raylib 6.0** — download from [raylib releases](https://github.com/raysan5/raylib/releases) and extract to a known path

## Setup

1. **Clone the repository**
   ```bash
   git clone <repo-url>
   cd ArcadeGamesByKamolia
   ```

2. **Set the raylib path**
   Open `CMakeLists.txt` and update the `RAYLIB_DIR` variable to point to your local raylib installation:
   ```cmake
   set(RAYLIB_DIR "D:/raylib-6.0_win64_mingw-w64")
   ```

3. **Build**
   ```bash
   cmake -B cmake-build-debug -G "MinGW Makefiles"
   cmake --build cmake-build-debug --target ArcadeGames
   ```

4. **Run**
   ```bash
   ./cmake-build-debug/ArcadeGames.exe
   ```
   > Assets (images and sounds) are automatically copied to the build directory after a successful build.

## Project Structure

```
ArcadeGamesByKamolia/
├── main.cpp                  # Entry point — main menu and game launcher
├── CMakeLists.txt            # Build configuration
├── assets/
│   ├── Pictures/             # Game images (Connect 4, XO)
│   └── sounds/               # Sound effects and music
├── xo/                       # Tic-Tac-Toe game logic and menus
├── connect 4/                # Connect 4 game logic and menus
├── snake_game/
│   ├── snake/                # Snake entity and constants
│   └── main_game/            # Snake game loop and menus
├── pong/
│   ├── pong game/            # Pong game logic and ball physics
│   └── menus/                # Pong menus
└── player stuff/             # Shared player class and input validation
```

## Scripts & Build Targets

| Command | Description |
|---------|-------------|
| `cmake --build <build-dir> --target ArcadeGames` | Build the executable |

A post-build step copies `assets/` into the build directory automatically.

## Environment Variables

No environment variables are required. The raylib path is configured directly in `CMakeLists.txt`.

## Tests

<!-- TODO: No automated tests are currently configured. -->
No automated test suite is present. The project can be verified by building and running the executable manually.

## License

<!-- TODO: Add a project license. -->
Sound assets are provided under their own license — see [`assets/sounds/License.txt`](assets/sounds/License.txt) for details.
