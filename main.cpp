#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <utility> // For std::pair
#include <unordered_set>

class Solver {
public:
    Solver(int width, int height);
    void solve();
    void initializeBoard(const std::vector<std::vector<char>>& initialState);
    void displayBoard();

private:
    int width, height;
    std::vector<std::vector<char>> board; 
    std::vector<std::vector<bool>> revealed;
    std::unordered_set<std::pair<int, int>, hash_pair> toCheck;

    void revealAdjacent(int x, int y);
    bool isValid(int x, int y) const;
    std::vector<std::pair<int, int>> getNeighbors(int x, int y) const;
    void deduce();
    void updateBoard(int x, int y, char value);
    static inline std::hash<int> hash_int;
    struct hash_pair {
        inline std::size_t operator()(const std::pair<int, int> &v) const {
            return hash_int(v.first) ^ hash_int(v.second);
        }
    };
};

#endif // SOLVER_H

#include "Solver.h"
#include <iostream>

Solver::Solver(int width, int height) : width(width), height(height), board(height, std::vector<char>(width, '?')), revealed(height, std::vector<bool>(width, false)) {}

void Solver::initializeBoard(const std::vector<std::vector<char>>& initialState) {
    board = initialState;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            revealed[y][x] = (initialState[y][x] != '?');
            if (!revealed[y][x]) {
                toCheck.insert({x, y});
            }
        }
    }
}

void Solver::solve() {
    while (!toCheck.empty()) {
        auto it = toCheck.begin();
        int x = it->first, y = it->second;
        toCheck.erase(it); // Remove this cell from the set
        if (board[y][x] == 'E') {
            revealAdjacent(x, y);
        } else if (board[y][x] != '?') {
            deduce();
        }
    }
}

void Solver::revealAdjacent(int x, int y) {
    std::vector<std::pair<int, int>> neighbors = getNeighbors(x, y);
    for (auto &n : neighbors) {
        if (isValid(n.first, n.second) && !revealed[n.second][n.first]) {
            revealed[n.second][n.first] = true;
            char val = board[n.second][n.first];
            updateBoard(n.first, n.second, val);
            if (val == 'E') {
                toCheck.insert(n);
            }
        }
    }
}

bool Solver::isValid(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

std::vector<std::pair<int, int>> Solver::getNeighbors(int x, int y) const {
    std::vector<std::pair<int, int>> neighbors;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            if (isValid(x + dx, y + dy)) {
                neighbors.emplace_back(x + dx, y + dy);
            }
        }
    }
    return neighbors;
}

void Solver::updateBoard(int x, int y, char value) {
    board[y][x] = value;
    revealed[y][x] = true;
}

void Solver::deduce() {
    // Implement sophisticated deduction logic here
}

void Solver::displayBoard() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << board[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

#include "Solver.h"
#include <vector>

int main() {
    int width = 10;
    int height = 10;
    Solver solver(width, height);

    std::vector<std::vector<char>> initialState = {
        // Fill with initial state
    };

    solver.initializeBoard(initialState);
    solver.solve();
    solver.displayBoard();
    return 0;
}
