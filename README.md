# Minesweeper (C++ with QT)
### Author: Vaishnavi Gudimella

## Project Overview
This is a **Minesweeper game** built using **C++ and Qt** with the **VSCode** IDE. The game follows the classic Minesweeper rules, where the player must uncover all the safe cells without clicking on a mine.

## How to Play
1. **Left-click** on a cell to reveal it.
2. **Right-click** on a cell to flag it as a potential mine.
3. If you click on a **mine**, the game **ends** and you explode. 
4. If you **clear all non-mine spaces**, you **win** the game!
5. You can click **"Try Again"** to restart after winning or losing.
6. Click **"Exit"** to quit the game.

## Installation & Setup
### **Prerequisites**
- C++ compiler
- **Qt** (Ensure you have Qt5 installed)

#### **Using Terminal (Manual Compilation)**
1. Navigate to the project folder.
2. Run:
   ```sh to enter the bash terminal
   qmake
   make clean - to clear any files if wanted
   make
   ./Minesweeper - to run