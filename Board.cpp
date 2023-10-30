/* ----------------------- HEADER FILES AND NAMESPACES ----------------------- */
#include "Board.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

using std::logic_error;
using std::fill;
using std::vector;

/* ----------------------- PRIVATE METHODS ----------------------- */

bool Board::validateBoard() {
    double checkSquared = sqrt(this->N) - (int)sqrt(this->N);
    if (checkSquared != 0)
        return false;

    for (const auto& r: this->board)
        if ((int)r.size() != N)
            return false;
    
    return true;
}

bool Board::findEmptyPos(int& x, int& y) {

    for (y=0; y<this->N; ++y)
        for (x=0; x<this->N; ++x)
            if (this->board[y][x] == Board::EMPTY)
                return true;

    return false;
}

bool Board::safePos(int n, int x, int y) {
    int sqN = (int)sqrt(this->N);
    return this->board[y][x] == Board::EMPTY &&
            !this->row[y][n-1] &&
            !this->col[x][n-1] && 
            !this->box[sqN*(y/sqN) + (x/sqN)][n-1];
}

void Board::setTo(int n, int x, int y, bool setting) {
    int sqN = (int)sqrt(this->N);
    this->row[y][n-1] = this->col[x][n-1] = this->box[sqN*(y/sqN) + (x/sqN)][n-1] = setting;
}

void Board::delete_auxilliary() {
    for (int i=0; i<this->N; ++i) {
        delete[] this->row[i];
        delete[] this->col[i];
        delete[] this->box[i];
    }
    delete[] this->row;
    delete[] this->col;
    delete[] this->box;
}

/* ----------------------- PUBLIC METHODS ----------------------- */

const int Board::EMPTY = 0;

Board::Board(const vector<vector<int>>& board) {
    this->board = board;
    this->N = board.size();
    if (!validateBoard()) {
        throw logic_error("The given board is not a valid sudoku board.\n");
    }
    
    this->row = new bool* [this->N];
    this->col = new bool* [this->N];
    this->box = new bool* [this->N]; 

    for (int i=0; i<this->N; ++i) {
        this->row[i] = new bool[this->N];
        this->col[i] = new bool[this->N];
        this->box[i] = new bool[this->N];
        for (int j=0; j<this->N; ++j)
            this->row[i][j] = this->col[i][j] = this->box[i][j] = false;
    }

    int sqN = (int)sqrt(this->N);

    // Fill all the present number into the auxilliary spaces
    for (int i=0; i<this->N; ++i) {
        for (int j=0; j<this->N; ++j) {
            int n = this->board[i][j];            
            if (n == Board::EMPTY)
                continue;
        
            row[i][n-1] = col[j][n-1] = box[sqN*(i/sqN) + (j/sqN)][n-1] = true;
        }
    }
}

bool Board::solve() {
    
    int x, y;
    if (!findEmptyPos(x, y))
        return true;

    for (int n=1; n<=this->N; ++n) {
        if (safePos(n, x, y)) {
            this->board[y][x] = n;
            setTo(n, x, y, true);
            if (solve())
                return true;
            this->board[y][x] = Board::EMPTY;
            setTo(n, x, y, false);
        }
    }

    return false;
}

void Board::display() {
    for (const auto& r: this->board) {
        for (int n: r)
            std::cout << n << ' ';
        std::cout << '\n';
    }
}

Board::~Board() {
    delete_auxilliary();
}