# Alquerque (C, GTK 3)

5x5 Alquerque with a GTK 3 interface (`play.glade`).

- 12 pieces per side; black and white.
- Modes: single player vs computer (choose color), computer vs computer, two players, or random mode; the starting side can be black, white or random; players can enter names.
- Moves are represented internally as `xy:xy` coordinate strings and checked in two stages: syntax, then semantics (ownership, empty target, direction allowed from that point, unit step or capture jump over an enemy piece).
- Diagonal moves are allowed only from points that lie on the diagonals; chained jumps are allowed only after a capture; mixing a unit step with a jump in one turn is invalid (see `docs/img/move-validation-rules.png`).
- The computer picks random coordinates until the move passes the same validation.

## Build and run
Requires GTK 3 development files. Run from this folder so `play.glade` and `Images/` are found:

```
gcc src/alquerque.c -o alquerque $(pkg-config --cflags --libs gtk+-3.0)
./alquerque
```

## Docs
`docs/flowchart.pdf`, `docs/gui-schematic.pdf` and the move-validation notes (Spanish).

Developed by Elías David Álvarez Martínez and José Pássera, 2022.
