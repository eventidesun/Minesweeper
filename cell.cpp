#include "cell.h"

// the constructor
Cell::Cell(QWidget* parent) 
    : QPushButton(parent), isMine(false), isRevealed(false), adjacentMines(0), isFlagged(false) {
    setFixedSize(40, 40); // setting the size of each cell
}

// sets true or false depending on whether a cell has a mine or not
void Cell::setMine(bool mine) { 
    isMine = mine; 
}

// returns true or false if a cell does have a mine 
bool Cell::getMine() const {
    return isMine; 
}

// reveals a cell that the player clicked on and updates in accordingly
void Cell::setRevealed(bool revealed) { 
    isRevealed = revealed; 
    if (isRevealed) {
        setEnabled(false);
        if (getMine()) {
            setText("M"); // M is mine
        } else if (adjacentMines > 0) {
            setText(QString::number(adjacentMines)); // shows the number of adjacent mines
        } else {
            setText(""); // otherwise, it remains empty (there are also no mines around)
        }
    }
}

// returns the status of a revealed cell (if it is revealed or not)
bool Cell::getRevealed() const { 
    return isRevealed; 
}

// sets the number of adjacent mines to this cell
void Cell::setAdjacentMines(int count) { 
    adjacentMines = count; 
}

// returns the number of adjacent mines
int Cell::getAdjacentMines() const { 
    return adjacentMines; 
}

// toggles the flag state and updates the display
void Cell::setFlagged(bool value) {
    isFlagged = value;
    setText(isFlagged ? "?" : ""); // ? is the flagging symbol
}

// returns the status of the cell (if it is flagged or not)
bool Cell::getFlagged() const { 
    return isFlagged;
}

// handles the mouse clicks (the left and right clicks for revealing or flagging a cell)
void Cell::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {        
        if (!getRevealed()) {
            emit rightClicked();
        }
    } else {
        QPushButton::mousePressEvent(event); // Normal left-click
    }
}

