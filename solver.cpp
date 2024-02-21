#include "Solver.h"
#include <iostream>

// Existing Solver methods...

void Solver::initializeBoard(const std::vector<std::vector<char>>& initialState) {
    board = initialState; // Assume initialState is correctly sized and filled
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            revealed[y][x] = (initialState[y][x] != '?');
        }
    }
}

void Solver::updateBoard(int x, int y, char value) {
    if (isValid(x, y)) {
        board[y][x] = value;
        revealed[y][x] = true; // Mark this cell as revealed
    }
}

void Solver::displayBoard() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (revealed[y][x]) {
                std::cout << board[y][x] << " ";
            } else {
                std::cout << "? "; // Unrevealed cells are marked with ?
            }
        }
        std::cout << std::endl;
    }
}
