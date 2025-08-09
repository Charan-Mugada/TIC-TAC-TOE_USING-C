# Tic Tac Toe Game in C

This is my Tic Tac Toe project written in C language.  
It has gone through 3 versions where I improved the code, game logic, and user experience step by step.

---

## Version 1: Basic two-player & dumb bot game

- Created a simple 3x3 board with numbered positions (1-9).  
- Players enter position to mark 'X' or 'O'.  
- Option to play with a friend or against a **dumb bot** that just picks the first available cell.  
- Win condition checks rows, columns, and diagonals.  
- Basic input validation to avoid overwriting cells.  
- Added replay option using recursive call to `main()`.

---

## Version 2: Smarter bot & improved input handling

- Bot improved to try these in order:  
  - Win if possible in the next move.  
  - Block opponent’s winning move.  
  - Take center if free.  
  - Take corners.  
  - Take sides last.  
- Added recursion in bot input to retry on invalid moves.  
- Better separation between human and bot input handling.  
- Still command-line based, no colors yet.

---

## Version 3: Colorful UI & enhanced user experience

- Added color to board display using ANSI escape codes:  
  - Green for 'X', red for 'O', yellow for free cells, and colored grid lines.  
- Colored prompts and error messages for better UX.  
- Same smart bot logic from version 2.  
- Clear colored messages for win, draw, and invalid input.  
- Replay feature kept with colored prompts.

---

## How to Run

1. Compile the code (e.g., `tic_tac_toe.c`):  
gcc tic_tac_toe.c -o tic_tac_toe
2. Run the program:  

3. Follow on-screen instructions to play.

---

## What I Learned

- Handling 2D arrays to represent the board.  
- Implementing game logic: checking wins, draws.  
- User input validation and retries.  
- Creating a simple AI bot with strategic moves.  
- Using recursion for replay functionality.  
- Adding colors to terminal output for better interaction.  
- Managing turn-based game flow.

---

Feel free to ask if you want me to help improve this project further!
