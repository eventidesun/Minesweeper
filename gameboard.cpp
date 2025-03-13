#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include "gameboard.h"

// this is the constructor
GameBoard::GameBoard(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);
    initializeGame();
}

// this sets up the game and then sets everything up again when the game is retried to play by the player
void GameBoard::initializeGame() {
    QLayoutItem *item;

    srand(time(nullptr)); // using a random number generator to randomly place the 99 mines out of 16 times 30 mines

    revealedCells = 0;

    // need this to reset everything (all  the widgets being used)
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget(); // deletes the widgets being used
        delete item; // this deletes the layout item
    }

    // this resets all the rows and cells and makes a new board again
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cells[i][j] = new Cell(this); // goes through each row and column and adds new cells
            layout->addWidget(cells[i][j], i, j);

            // this is to reveal a cell (left clicking)
            connect(cells[i][j], &QPushButton::clicked, [=]() { 
                revealCell(i, j); 
            });

            // this is to mark/flag a cell if you think there is a mine hidden (right clicking)
            connect(cells[i][j], &Cell::rightClicked, this, [=]() { 
                toggleFlag(i, j);
            });
            

            // reset all the marked flags and their states
            cells[i][j]->setFlagged(false);
        }
    }

    // this is to randomly place the mines
    int minesPlaced = 0;
    while (minesPlaced < MINES) { // if the mines placed so far are less then 99, then continue until all 99 mines are placed
        int x = rand() % ROWS;
        int y = rand() % COLS;
        if (!cells[x][y]->getMine()) { // to not place more than one mine at a cell
            cells[x][y]->setMine(true);
            minesPlaced++;
        }
    }
}


// this is the function that reveals the cell that is clicked on (left clicking since right clicking is reserved for placing a flag/marking)
void GameBoard::revealCell(int row, int col) {

    // if a cell is already revealed then don't do anything
    if (cells[row][col]->getRevealed()) { 
        return;
    }

    // if a cell is flagged and a player left clicks on it, then it is removed 
    if (cells[row][col]->getFlagged()) {
        cells[row][col]->setFlagged(false);
    }

    cells[row][col]->setRevealed(true); // this reveals the cell 

    if (!cells[row][col]->getMine()) {
        revealedCells++;
    }

    // is the cell has a mine hidden
    if (cells[row][col]->getMine()) {
        cells[row][col]->setText("M"); // M for Mine
        cells[row][col]->setStyleSheet("background-color: red; color: black;");

        QMessageBox msgBox;
        msgBox.setWindowTitle("Game Over");
        msgBox.setText("You hit a mine and exploded!");

        QPushButton *retryButton = msgBox.addButton("Try Again", QMessageBox::AcceptRole);
        QPushButton *leaveButton = msgBox.addButton("Exit", QMessageBox::RejectRole);

        msgBox.exec();

        if (msgBox.clickedButton() == retryButton) {
            initializeGame(); // restart the game
        } else if (msgBox.clickedButton() == leaveButton) {
            QApplication::quit(); // exit
        }
        return;
    }

    if (revealedCells == (ROWS * COLS - MINES)) { // cleared all the cells except for the ones with mines
        QMessageBox msgBox;
        msgBox.setWindowTitle("You win!");
        msgBox.setText("You cleared all the safe cells!");

        QPushButton *retryButton = msgBox.addButton("Try Again", QMessageBox::AcceptRole);
        QPushButton *leaveButton = msgBox.addButton("Exit", QMessageBox::RejectRole);

        msgBox.exec();

        if (msgBox.clickedButton() == retryButton) {
            initializeGame(); // restart the game
        } else if (msgBox.clickedButton() == leaveButton) {
            QApplication::quit(); // exit
        }
        return;
    }

    int adjacentMines = countAdjacentMines(row, col);

    if (adjacentMines == 0) {
        cells[row][col]->setText(""); // shows nothing (hides the 0)
        cells[row][col]->setEnabled(false); // can't click on it anymore

        // This is to reveal the empty neighbouring cells if a cell that is clicked on is empty
        for (int i = -1; i <= 1; ++i) { // check the row above (-1), below (1), and current (0)
            for (int j = -1; j <= 1; ++j) { // check the column left (-1), right (1), and current (0)
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) { // to not go out of bounds
                    if (!cells[newRow][newCol]->getRevealed()) { // if the cell isn't revealed already, then reveal it now
                        revealCell(newRow, newCol);
                    }
                }
            }
        }
    } else {
        // else, just show the number of adjacent mines
        cells[row][col]->setText(QString::number(adjacentMines));
    }
}

// using a similar logic as above, this function is to check for mines in adjacent cells
int GameBoard::countAdjacentMines(int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                if (cells[newRow][newCol]->getMine()) count++; // checks and counts for adjacent mines
            }
        }
    }
    return count;
}

// toggles/marks a question mark on a cell when right clicked
void GameBoard::toggleFlag(int row, int col) {
    if (!cells[row][col]->getRevealed()) { // first checks if a cell is already revealed
        bool newFlagState = !cells[row][col]->getFlagged();
        cells[row][col]->setFlagged(newFlagState);
    }
}

// destructor
GameBoard::~GameBoard() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            delete cells[i][j]; // dynamically deletes each allocatyd cell
        }
    }
    delete layout; // dynamically deletes allocated layout
}

