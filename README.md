<p align="center"><img src="docs/img/banner.svg" width="100%" alt="Board Games in C"></p>

<p align="center"><img src="https://img.shields.io/badge/C-gcc-00599c"> <img src="https://img.shields.io/badge/GTK-3%20%2B%20Glade-4a86cf"> <img src="https://img.shields.io/badge/Console-Windows-555555"></p>
<p align="center"><a href="#english">English</a> · <a href="#español">Español</a></p>

## English

### Overview
This repository contains two board games written in plain C. Each implements its rules from scratch (move validation, capture or four-in-a-row detection, end-of-game conditions) and includes a computer opponent. Connect Four runs in the Windows console; Alquerque has a GTK 3 interface built with Glade. In both games, the computer chooses randomly among moves that pass the same validation used for human players; there is no search or heuristic play.

### Projects
| Project | What it does | Interface | Build |
|---|---|---|---|
| [`connect-four/`](connect-four) | 6x7 Connect Four, human vs computer. Random first player, optional turn limit (1-21 turns each), surrender, tie-break by adjacent-piece score, ASCII-art messages | Console (uses `windows.h` and `system("cls")`) | `gcc CuatroEnRayaFinal.c -o connect4` (Windows) |
| [`alquerque/`](alquerque) | 5x5 Alquerque with 12 pieces per side: validated moves and captures (including chained jumps), single player vs computer, computer vs computer or two players, optional player names | GTK 3 window defined in `play.glade` | `gcc src/alquerque.c -o alquerque $(pkg-config --cflags --libs gtk+-3.0)`, run from the `alquerque/` folder |

### Highlights
- Rules implemented without game libraries: column-fill tracking and four-direction win check for Connect Four; diagonal, orthogonal and jump-capture validation with move-chain rules for Alquerque.
- Input handling: integer parsing with range filtering (Connect Four); syntax and semantic checks of `xy:xy` move strings (Alquerque).
- Alquerque separates game logic from the GTK event callbacks; the console logic was reused behind the GUI.
- Design notes and flow diagrams are included for Alquerque; a written report with data structures and algorithms is included for Connect Four.

### Repository layout
```
connect-four/   src/ (game and message library)
alquerque/      src/alquerque.c, play.glade, Images/, docs/ (flowchart, GUI schematic, move rules)
```

### Known limitations
- The computer opponents are random, not strategic.
- The Alquerque design notes record a crash when generating the computer move in an early GUI version; the final state of that issue was not re-verified here.
- No screenshots of the running programs are included.

### Team & credits
Developed by Elías David Álvarez Martínez and José Pássera at Universidad Católica "Nuestra Señora de la Asunción" (Paraguay), 2022. The Connect Four report is shared for reference.

### License
MIT.

---

## Español

### Descripción general
Este repositorio contiene dos juegos de tablero escritos en C. Cada uno implementa desde cero sus reglas (validación de jugadas, capturas o detección de cuatro en línea, condiciones de fin) e incluye un oponente controlado por la computadora. Cuatro en Raya corre en la consola de Windows; Alquerque tiene una interfaz GTK 3 creada con Glade. En ambos juegos, la computadora elige al azar entre jugadas que pasan la misma validación que las de una persona; no hay búsqueda ni heurística.

### Proyectos
| Proyecto | Qué hace | Interfaz | Compilación |
|---|---|---|---|
| [`connect-four/`](connect-four) | Cuatro en Raya 6x7 persona vs computadora. Primer jugador aleatorio, límite de turnos opcional (1-21 por jugador), rendición, desempate por puntaje de adyacencia | Consola (Windows) | `gcc CuatroEnRayaFinal.c -o connect4` |
| [`alquerque/`](alquerque) | Alquerque 5x5 con 12 fichas por bando: jugadas y capturas validadas (con saltos encadenados), un jugador vs computadora, computadora vs computadora o dos jugadores | Ventana GTK 3 (`play.glade`) | `gcc src/alquerque.c -o alquerque $(pkg-config --cflags --libs gtk+-3.0)`, ejecutar desde `alquerque/` |

### Limitaciones conocidas
Los oponentes son aleatorios. No se incluyen capturas de pantalla de los programas en ejecución.

### Equipo y créditos
Desarrollado por Elías David Álvarez Martínez y José Pássera en la Universidad Católica "Nuestra Señora de la Asunción" (Paraguay), 2022.

### Licencia
MIT.
