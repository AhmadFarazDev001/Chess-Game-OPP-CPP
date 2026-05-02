
# ♟️ Chess Engine (C++ / OOP)

![C++](https://img.shields.io/badge/C++-17-blue.svg?style=flat&logo=c%2B%2B)
![SFML](https://img.shields.io/badge/SFML-2.6-green.svg)
![License](https://img.shields.io/badge/Status-Completed-success.svg)
![University](https://img.shields.io/badge/FAST_NUCES-Semester_Project-darkred.svg)

A feature-rich, object-oriented Chess Engine built entirely from scratch in C++. This project features a dual-interface system, allowing players to experience the game through a sleek, modern **Graphical Interface (SFML)** or a beautifully colored **Raw Console / Terminal Interface**.

Developed as the final Semester Project for the **Object-Oriented Programming Lab (Spring 2026)** at FAST NUCES Faisalabad-Chiniot Campus.

---

## ✨ Features

* **Dual Interface:** Play via the modern SFML GUI or the classic ANSI-colored terminal.
* **Strict Move Validation:** Every piece mathematically follows exact chess rules, including path-clearing and collision detection.
* **Advanced Chess Rules:** * Check & Checkmate detection
  * Stalemate conditions
  * Insufficient Material draws (e.g., King & Knight vs. King)
  * Threefold Repetition draws (Tracked via position history maps)
* **Custom UI:** Floating dark-mode panels, high-contrast board rendering, and real-time error handling built with SFML.

---

## 🚀 How to Play & Test

### 1. Quick Play (Recommended for Testing)
If you want to test the game quickly without setting up a coding environment, please use our **Release Version**.
* Go to the `Releases` tab on GitHub (or open the provided `Release` folder).
* Download the single packaged `.exe` file.
* Double-click to play! No external libraries or DLLs are required.

### 2. Building from Source (Windows)
If you are trying to test using the console, you must configure the SFML library (v2.6+) depending upon your editor (e.g., Visual Studio, VS Code, CLion).
* Ensure you link the following libraries: `sfml-graphics`, `sfml-window`, `sfml-system`.
* Make sure your compiler has the `/utf-8` flag enabled so the console chess symbols render correctly.

**To compile and run via Windows Terminal (using MinGW/g++):**
```bash
# 1. Compile the source code
g++ -std=c++17 main.cpp Board.cpp Piece.cpp gameexecution.cpp SFMLEngine.cpp -o ChessGame.exe -lsfml-graphics -lsfml-window -lsfml-system

# 2. Run the game
.\ChessGame.exe
```

### 3. Building from Source (Mac / Linux)
Because our engine is built on standard C++ and SFML, it is 100% cross-platform. Here is the method to compile and play using the terminal:

**For macOS:**
```bash
# 1. Install SFML via Homebrew
brew install sfml

# 2. Compile the source code
clang++ -std=c++17 main.cpp Board.cpp Piece.cpp gameexecution.cpp SFMLEngine.cpp -o ChessGame -lsfml-graphics -lsfml-window -lsfml-system

# 3. Run the game
./ChessGame
```

**For Linux (Ubuntu/Debian):**
```bash
# 1. Install SFML
sudo apt-get install libsfml-dev

# 2. Compile the source code
g++ -std=c++17 main.cpp Board.cpp Piece.cpp gameexecution.cpp SFMLEngine.cpp -o ChessGame -lsfml-graphics -lsfml-window -lsfml-system

# 3. Run the game
./ChessGame
```

---

## 🧠 Object-Oriented Programming Concepts Applied

This project strictly adheres to core OOP principles:

* **Encapsulation:** The internal state of the board (`Piece* grid[8][8]`) and piece attributes (`hasmoved`, `color`) are kept `private` or `protected`. They are safely accessed and modified only through specific getter/setter functions.
* **Inheritance:** All specific chess pieces (`Pawn`, `Knight`, `Rook`, etc.) inherit from a single abstract base class called `Piece`.
* **Polymorphism:** The `Piece` base class defines a pure virtual function `virtual bool isValidMove(...) = 0;`. Each derived piece overrides this with its own unique mathematical movement logic, allowing the `Board` to evaluate moves dynamically.
* **Composition:** The `Board` class "has-a" relationship with the pieces, containing a 2D array of `Piece*` pointers to manage the physical game state.

---

## 👨‍💻 Credits & Authors

* **Ahmad Faraz** (Roll No: 25F-0510) 
* **Ubaid Ur Rehman** (Roll No: 25F-0570)

*Special thanks to our Lab Instructor and the open-source SFML community.*
