# Battleship (C++ Console Game)

A console-based Battleship-style game in C++ featuring a **10×10 grid**, **five ship types**, **random ship placement**, and a clean turn-based loop with input validation.

Built to practice **object-oriented design**, **state tracking**, and **randomized placement with constraints**.

---

## Gameplay

- Enter moves using a column letter **A–J** and a row number **1–10**
  - Examples: `B4`, `A10`
- Type `quit` to end the game (the full board is revealed before exit).
- The game displays:
  - `~` = unknown water
  - `O` = miss
  - `X` = hit

### Win / Lose Conditions
- ✅ **Win:** all ships have been hit at least once (counted as “destroyed” in this simplified version).
- ❌ **Lose:** **15 misses in a row** ends the game.

> Note: This implementation treats a ship as “destroyed” the first time it is hit (simplified rule set).

---

## Ships Included

- Frigate (size 2)
- Submarine (size 3)
- Destroyer (size 3)
- Battleship (size 4)
- Aircraft Carrier (size 5)

Ships are placed randomly (horizontal or vertical) with validation to prevent:
- overlap with other ships  
- going out of bounds

---

## Features

- 10×10 grid with coordinate input (`A–J`, `1–10`)
- Random ship placement with collision/bounds checking
- Hit / miss handling + prevention of duplicate attacks
- End-of-game reveal mode (shows all ships)
- Simple loss mechanic: 15 consecutive misses

---

## Build & Run

### Compile (g++)
```bash
g++ -std=c++17 -Wall -Wextra -pedantic "BattleshipGame.cpp" ChessBoard.cpp Ship.cpp -o battleship
