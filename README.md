### Here, I will be adding my projects.
# 1.Sudoku_Solver_Project
```
This is a sudoku solver project, which is able to solve any level of sudoku game and can be used for different type of grids with some changes in the code.
```

# 2.🎮 Tic-Tac-Toe AI Tournament (C++)

This is a **command-line based Tic-Tac-Toe** game written in **C++**, featuring:
- A human vs AI gameplay mode
- **Minimax algorithm with Alpha-Beta pruning** for unbeatable AI
- Tournament modes like best-of-3, best-of-5, best-of-7, and best-of-10
- Score tracking and match logs saved to file

---

## 📌 Features

- ✅ Interactive CLI-based board and instructions  
- 🤖 AI player uses Minimax algorithm with Alpha-Beta pruning for smart moves  
- 🔁 Tournament formats: Best of 3/5/7/10 matches  
- 🧠 Tracks match wins for each player  
- 📜 Logs results to a file (`game_log.txt`) with date/time stamps  
- 💾 Clean, modular object-oriented code using C++ classes

---

## 🧠 How It Works

- The board is a 3x3 grid (standard Tic-Tac-Toe)
- You and the AI take turns placing your marks (`X` for human, `O` for AI)
- AI selects its best move using **Minimax + pruning** to simulate future moves
- Tournament keeps track of wins and displays a **live scoreboard**
- Results are logged automatically with timestamps

---

## 🔧 How to Run

1. **Compile the code** (use any C++ compiler):

   ```bash
   g++ -o tictactoe main.cpp
