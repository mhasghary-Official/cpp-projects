# 2048 Game - C++ Implementation

![](https://img.shields.io/badge/C++-11-blue)
![](https://img.shields.io/badge/platform-linux%20%7C%20macos-lightgrey)
![](https://img.shields.io/badge/license-MIT-green)

A terminal-based implementation of the popular 2048 puzzle game written in C++.

**🎮 About the Game**

2048 is a sliding block puzzle game where the goal is to combine tiles with the same numbers to create a tile with the number 2048. This implementation features a clean terminal interface and smooth gameplay.

**✨ Features**

· 🎯 Classic 2048 gameplay - Faithful to the original game mechanics
· ⌨️ Keyboard controls - Intuitive WASD controls for movement
· 🏆 Score tracking - Real-time score display
· 🎨 Clean terminal interface - Color-free, cross-platform compatible display
· ⚡ Efficient algorithms - Optimized tile movement and merging
· 🏁 Win/lose detection - Automatic game state detection

**🛠️ Installation & Build**

*Prerequisites*

· C++11 compatible compiler (GCC, Clang, etc.)
· Linux or macOS terminal
· CMake (optional)

*Build Instructions*

```bash
# Clone the repository
git clone https://github.com/yourusername/2048-cpp.git
cd 2048-cpp

# Compile directly
g++ -std=c++11 2048.cpp -o 2048

# Or with CMake
mkdir build && cd build
cmake ..
make
```

**🎯 How to Play**

Controls

· W ➡️ Move Up
· A ➡️ Move Left
· S ➡️ Move Down
· D ➡️ Move Right
· Q ➡️ Quit Game

**Game Rules**

1. Tiles slide in the chosen direction until they hit the wall or another tile
2. When two tiles with the same number collide, they merge into their sum
3. After each move, a new tile (2 or 4) appears in a random empty space
4. The game is won when you create a 2048 tile
5. The game ends when no more moves are possible

**🏗️ Project Structure**

```
2048.cpp
├── Game2048 Class
│   ├── Board state (4x4 grid)
│   ├── Score tracking
│   ├── Game state management
│   └── Movement algorithms
├── Terminal Input Handling
│   └── getch() function for single-character input
└── Main Game Loop
    └── Input processing and display updates
```

**🚀 Usage**

```bash
# Run the game
./2048

# Example output:
Score: 0
=========================
    .    .    .    .
    .    .   2    .
    .    .    .    .
    .    .    .   4
=========================
Controls: W (Up), S (Down), A (Left), D (Right), Q (Quit)
```

**🔧 Technical Details**

Key Algorithms

· Tile Movement: Efficient row processing with merge detection
· Board Rotation: 90-degree rotation for unified movement logic
· Game Over Detection: Comprehensive move possibility checking
· Random Tile Generation: Weighted probability (90% 2, 10% 4)

Code Highlights

```cpp
// Unified movement using board rotation
void moveUp() {
    rotateBoard();
    moveLeft();
    rotateBoard(); rotateBoard(); rotateBoard();
}

// Efficient merge algorithm
for (int j = 0; j < (int)temp.size() - 1; j++) {
    if (temp[j] == temp[j + 1]) {
        temp[j] *= 2;
        score += temp[j];
        if (temp[j] == 2048) won = true;
        temp.erase(temp.begin() + j + 1);
    }
}
```

**🤝 Contributing**

Contributions are welcome! Here's how you can help:

1. Fork the project
2. Create a feature branch (git checkout -b feature/AmazingFeature)
3. Commit your changes (git commit -m 'Add some AmazingFeature')
4. Push to the branch (git push origin feature/AmazingFeature)
5. Open a Pull Request

**Development Ideas**

· Add color support for terminals
· Implement undo functionality
· Add high score tracking
· Create different board sizes
· Add animations and effects

**📝 Code Style**

This project follows standard C++ best practices:

· Clear variable naming
· Modular class design
· Memory-efficient algorithms
· Comprehensive error handling

**🐛 Known Issues**

· Terminal clearing uses ANSI escape codes (Linux/macOS only)
· No color support in current version
· Limited to 4x4 grid size

**📄 License**

This project is licensed under the gpl 3 License - see the LICENSE file for details.

**🙏 Acknowledgments**

· Original 2048 game by Gabriele Cirulli
· C++ standard library for efficient data structures
· Terminal input handling inspired by Unix systems programming

---

Enjoy playing! 🎉 If you reach 2048, you're among the elite players!
