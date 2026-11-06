# Connect Four (C, console)

Human vs computer Connect Four on a 6x7 board.

- Board: 6x7 integer matrix (0 empty, 1 player, 2 computer) plus a per-column fill counter.
- Computer move: random column among those with free space.
- Player move: integer input validated by range and column capacity; entering 0 surrenders.
- The number of turns per player is chosen at start (1-21); the first player is random.
- Win check after every move: vertical, horizontal and both diagonals.
- If the turn limit is reached without a winner, an adjacency score decides the result (a tie is possible).
- ASCII-art messages live in `src/libreriaPersonal.h`.

## Build and run
The program uses `windows.h` and `system("cls")`, so it targets Windows:

```
gcc src/CuatroEnRayaFinal.c -o connect4
connect4
```

## Docs

Developed by Elías David Álvarez Martínez and José Pássera, 2022.
