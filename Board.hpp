#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

/**
 * CLASS: Board
 * Representing a NxN sudoku board; and a built-in method to solve said board 
*/
class Board {
private:
    std::vector<std::vector<int>> board;

    bool** col; 
    bool** row;
    bool** box;

    int N;
    bool validateBoard();
    bool findEmptyPos(int& x, int& y);
    bool safePos(int n, int x, int y);
    void setTo(int n, int x, int y, bool setting);
    void delete_auxilliary();

public:
    static const int EMPTY;

    Board(const std::vector<std::vector<int>>& board);
    bool solve();
    void display();
    ~Board();
};

#endif