#include "Board.hpp"

#include <iostream>
#include <fstream>
#include <exception>
#include <cmath>

int main(int argc, char** argv) {

    std::ifstream iStream("Input.txt");
    if (!iStream.is_open())
        throw std::runtime_error("File \"Input.txt\" is not found.\n");

    int n = 0;
    std::vector<int> nums;

    while (iStream >> n) 
        nums.push_back(n);

    int N = (int)sqrt(nums.size());

    std::vector<std::vector<int>> B = 
        std::vector<std::vector<int>>(N, std::vector<int>(N, 0));

    n=0;
    for (int i=0; i<N; ++i) 
        for (int j=0; j<N; ++j) 
            B[i][j] = nums[n++];
    
    Board* Sudoku;
    try {
        Sudoku = new Board(B);
        if (Sudoku->solve())
            Sudoku->display();
        delete Sudoku; 
    } catch(std::logic_error const& e) {
        std::cerr << e.what();
        exit(-1);
    }

    return 0;
}