# Tic-Tac-Toe (Minimax AI with Bitsets)

This is a simple tic-tac-toe game, where you play as X, against an AI (O).
I made this game as a side project in order to learn the Minimax algorithm,
which I need for finishing my Chess Engine.

## How to play

- Enter moves by typing descriptive commands:
    - "topleft"
    - "center"
    - "right"...
- The AI will respond with the best possible move.

## Features

- Minimax AI
- Board representation using std::bitset
- Move validation and user input handling
- Terminal-based UI
- Win and draw detection

## How to compile

### On Linux or macOS:
```bash
g++ -std=c++17 main.cpp -o main
./main
```
### On Windows (using g++):
```bash
g++ -std=c++17 main.cpp -o main.exe
main.exe
```

## Possible updates

- Alpha-beta pruning algorithm
- GUI using SFML library