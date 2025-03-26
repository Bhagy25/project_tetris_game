# Tetris Game

## Overview

This is a simple console-based Tetris game implemented in C++. It features colorful Tetrominoes, smooth movement, and sound effects. The game speeds up as you progress, making it more challenging.

## Features

- **7 Tetromino Shapes**: Includes classic I, O, T, S, Z, J, and L shapes.
- **Colorful Blocks**: Each Tetromino has a distinct color for better visibility.
- **Smooth Controls**: Move left, right, rotate, and drop Tetrominoes.
- **Gravity Mechanics**: Pieces fall at an increasing speed as the game progresses.
- **Line Clearing**: When a row is filled, it is removed, and the score increases.
- **Level Progression**: Speed increases after every 200 points.
- **Sound Effects**: Beeps for movement, rotation, line clearing, and game over.
- **Game Over Detection**: The game ends when new Tetrominoes can't spawn.

## Controls

- **Left Arrow (←)**: Move Tetromino left
- **Right Arrow (→)**: Move Tetromino right
- **Down Arrow (↓)**: Move Tetromino down
- **Up Arrow (↑)**: Rotate Tetromino
- **Spacebar**: Hard drop (instantly places the piece)

## Installation and Execution

1. **Compile the Code**:

   ```sh
   g++ tetris.cpp -o tetris.exe
   ```

   *(Ensure you have a C++ compiler installed, such as MinGW for Windows.)*

2. **Run the Executable**:

   ```sh
   ./tetris.exe
   ```

## Dependencies

- **C++ Standard Library**
- **Windows-specific Headers** (`conio.h`, `windows.h` for console manipulation and sound effects)

## Simple Changes

- Adjusted **falling speed** to improve gameplay balance.
- Improved **color visibility** for better differentiation of Tetrominoes.
- Enhanced **sound effects** for a more engaging experience.
- Optimized **screen rendering** to reduce flickering.
- Refined **scoring system** to make level progression smoother.

## Future Enhancements

- **Ghost Piece**: Shows where the Tetromino will land before dropping.
- **Hold Piece**: Allows swapping the current piece for later use.
- **Soft Drop Acceleration**: Increase the speed of the piece manually when pressing down.
- **Preview Queue**: Display upcoming Tetrominoes to plan better moves.
- **Pause Feature**: Add a key to pause and resume the game.



## Author

Developed as part of a learning project in C++ game development. Enjoy playing Tetris!

BHAGY SHETH-202401200

DHRUV SODVADIYA-202401207

RAMIT SHERASHIYA-202401198

PRINS SATAPARA-20240188
