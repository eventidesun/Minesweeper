#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QMessageBox>
#include "Cell.h"

const int ROWS = 16;
const int COLS = 30;
const int MINES = 99;

// this is the entire minesweeper grid/baord
class GameBoard : public QWidget {
    Q_OBJECT

private:
    Cell* cells[ROWS][COLS]; // apparently rows and cols have to be consts (i had an issue when i didn't make them consts)
    QGridLayout *layout;
    int revealedCells; // how many cells are revealed

public:
    explicit GameBoard(QWidget *parent = nullptr); // this is the constructor
    ~GameBoard(); // the destructor

protected:
    void revealCell(int row, int col);
    int countAdjacentMines(int row, int col);
    void initializeGame();
    void toggleFlag(int row, int col); // this is for marking an area that you think might have a mine
};

#endif // GAMEBOARD_H

