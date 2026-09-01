# Battleship (C++ Console Game)

A console Battleship-style game in C++: a 10x10 grid, five ships placed randomly with collision and
bounds checking, and a turn loop with coordinate input validation.

Built for CSIS-297 at Grossmont College to practice object-oriented design, state tracking, and
randomized placement under constraints.

## Gameplay

Enter a column letter (`A`-`J`) followed by a row number (`1`-`10`), for example `B4` or `A10`.
Type `quit` to end the game; the full board is revealed on exit.

| Symbol | Meaning |
|---|---|
| `~` | unknown water |
| `O` | miss |
| `X` | hit |

- **Win:** every ship has been hit at least once
- **Lose:** 15 consecutive misses

## Ships

| Ship | Size |
|---|---|
| Frigate | 2 |
| Submarine | 3 |
| Destroyer | 3 |
| Battleship | 4 |
| Aircraft Carrier | 5 |

Placement is random in either orientation, rejected and retried on overlap or out-of-bounds.

## Design

### Occupancy and shots are separate

The board keeps two grids rather than one:

```cpp
Ship* board[ROWS][COLS];   // non-owning: which ship covers a square, nullptr = open water
char  shots[ROWS][COLS];   // ' ' untouched, 'X' hit, 'O' miss
```

This split matters because **a single `Ship` object is aliased by every square it covers**.
`placeShip` writes `&ship` into each square the ship occupies, so those entries are all the same
object. Recording a shot by mutating the ship would mark every square that ship covers, and marking
a miss would mean allocating something to stand in for empty water.

Keeping shots in their own grid means the board array is never mutated after placement and owns
nothing, so there is no allocation during play and nothing to free.

### Ownership

Ships are owned by the caller and the board only aliases them, so `ChessBoard` has no destructor and
needs none. Valgrind and AddressSanitizer both report zero leaks and zero errors across a full game.

## What it does not do

- **A ship counts as destroyed the first time it is hit**, rather than when all its squares are hit.
  This is a deliberate simplification, not a bug, but it is not real Battleship scoring.
- **No second player and no AI.** One player firing at a randomly generated board.
- **No ship-sunk announcements**, since ships are not tracked square by square.
- **Board is not persisted.** Quitting ends the game.

## Build and run

Requires a C++17 compiler. No external dependencies.

```bash
git clone https://github.com/qedkymish/battleship-console-cpp.git
cd battleship-console-cpp
g++ -std=c++17 -Wall -Wextra -pedantic BattleshipGame.cpp ChessBoard.cpp Ship.cpp -o battleship
./battleship
```

Builds clean with GCC 11 and 13 under `-Wall -Wextra -pedantic`, and with MSVC.

## Sample

One shot at A1, revealed on quit:

```
    A  B  C  D  E  F  G  H  I  J
 1  X  O  O  ~  ~  ~  ~  D  ~  ~
 2  B  ~  ~  ~  ~  ~  ~  D  ~  ~
 3  B  ~  ~  ~  ~  ~  ~  D  ~  ~
 4  B  ~  ~  ~  ~  ~  ~  ~  ~  ~
 5  ~  A  F  F  ~  ~  ~  ~  ~  ~
 6  ~  A  ~  ~  ~  ~  ~  ~  ~  ~
 7  ~  A  ~  ~  ~  ~  ~  ~  ~  ~
 8  ~  A  ~  ~  ~  ~  ~  ~  ~  ~
 9  ~  A  ~  ~  ~  ~  ~  ~  ~  ~
10  ~  ~  ~  S  S  S  ~  ~  ~  O
```

A1 hit the Battleship. A2 through A4 are the rest of that ship, still unhit, and visible only
because the board was revealed on exit.

## Possible next steps

- Rename `ChessBoard` to `Board`. The class started life in a chess project and the name never
  followed it here.
- Track hits per ship so a ship sinks only when every square is hit, and announce it when it does
- Let the player place ships manually as an alternative to random placement
- Seed the RNG with something finer than `time(0)`, which gives an identical board to two games
  started in the same second
