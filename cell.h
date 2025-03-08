#ifndef CELL_H
#define CELL_H

#include <QPushButton>
#include <QMouseEvent>

// This Cell class is to represent a single cell/tile in the minesweeper grid
class Cell : public QPushButton {
    Q_OBJECT

private:
    bool isMine; // if a cell has a mine (true if it does)
    bool isRevealed; // revealing a cell (true if a cell is revealed)
    int adjacentMines; // the number of adjacent cells to a revealed cell that has mines
    bool isFlagged; // if a player has flagged a cell as a possible mine (true if a cell is flagged)

public:
    Cell(QWidget* parent = nullptr); // constructor

    // checking if a cell has a mine
    void setMine(bool mine);
    bool getMine() const;

    // checking if a cell has been revealed
    void setRevealed(bool revealed);
    bool getRevealed() const;

    // sets and gets the number of adjacent cells with mines
    void setAdjacentMines(int count);
    int getAdjacentMines() const;

    // checking if a cell is flagged by the player
    void setFlagged(bool value);
    bool getFlagged() const;

protected:
    // checks mouse events for left and right clicks
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void rightClicked(); // signal for right clicks specifically
};

#endif // CELL_H

