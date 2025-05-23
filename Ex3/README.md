# COUP Game
## Game Overview

Coup is a bluffing and deduction game. Each player controls roles and uses them to perform actions such as gaining coins, eliminating other players, and blocking attacks. The goal is to be the last surviving player. Posibble actions for all players are - gather, tax, arrest, bribe, sanction and coup. Some of the actions can be blocked by other players.

This project include core game logics, all six unique roles, each with its own powers and restrictions, a modular class-based architecture, a Doctest test suite, a Makefile for easy building and testing and a main to run the game in GUI (SFML) form.

## Class Descriptions
### 🔹 Game:
Manages the entire game lifecycle.
Tracks all players.
Handles turn logic, game start, elimination, and winner detection.
Can assign roles randomly or accept manually created players.
Responsible for skipping eliminated players and resetting flags.

### 🔹 Player (Base class):

Base class representing a player.
Stores name, role, coin count, alive status, and flags (arrested, anotherTurn..).
Provides common actions like coins(), gather(), tax(), and more.
Base for all specific roles.

### 🔹 Role Classes (Inherit from Player)

Each of the following extends Player with role-specific behavior:

- `Governor`: The Governor tax action gives him 3 coins instead of 2. He can also undo other's players tax actions.

- `Baron`: The Baron can invest 3 coins and get 6 in return. Also, if he get sanctioned he gets 1 coin as a compensation.

- `General`: The General can undo the coup action, that cost him 5 coins. Also, if he get arrested he get his coin back.

- `Merchant`:  The Merchant earns extra coin for each turn he start with at least 3 coins and whe get arrested he pays 2 coins to the game instead of 1 to the player that arrested him.

- `Judge`: The Judge can undo the Bribe action and if another player sanction him, he have to pat another coin to the game.

- `Spy`: The Spy can reveal another player's coin count and block arrest actions. Inherits from Player and defines the Spy's unique actions. 

Each role has:

- A constructor setting the role name

- One or more custom methods to support its unique gameplay ability.

## File Descriptions
| File / Folder          | Purpose                                             |
| ---------------------- | --------------------------------------------------- |
| `src/Game.*`           | Game logic: player management, turn control, winner |
| `src/Player.*`         | Player functionality                       |
| `src/*.cpp`      | Each role’s unique logic                            |
| `src/*.hpp`      | Each role’s declerations                          |
| `Tests/tests.cpp`  | Game unit tests                               |
| `Tests/doctest.h`  | Decleration so the doctext can be used                             |
| `GUI/`    | SFML-based window and button UI system for the game              |
| `makefile`             | Automates build & test commands                     |
| `GUI/main.cpp`             | Entry point to start the game and running the GUI   |
| `GUI/AmericanCaptain-MdEY.otf`             | The font used in the GUI   |
| `GUI/background_image.png`             | The background image used in the GUI   |

## Tests
Testing is done with Doctest. They includes Core logics like turn passing, player removal, and winner logic. Each role’s behavior tested in isolation and integration. Tests are all in a single TEST_CASE per class, with SUBCASEs separating functionality.

## Makefile
The Makefile provides the following targets:
| Target       | Description                   |
| ------------ | ----------------------------- |
| `make Main`       | Builds the main game binary   |
| `make test`  | Compiles and runs all tests   |
| `make valgrind`   | Run the main with valgrind for memory leak detection |
| `make clean` | Cleans all compiled files     |

## How To Run
Ensure you're in the project root directory (Ex3) and have `clang++` and `valgrind` installed.

### Build Main Program With The GUI
```bash
make Main
```
#### Than run the Main Program:
```bash
./Main
```

### Memory Check with Valgrind
```bash
make valgrind
```

### Test running
```bash
make test
```
### Clean Build Files
```bash
make clean
```
