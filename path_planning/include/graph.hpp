#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <unordered_set>

namespace map {
    class Grid {
    public:
        Grid(int rows = 0, int cols = 0, double percent_obstacles = 0.0) :
             rows_(rows), cols_(cols), percent_obstacles_(percent_obstacles) {
            this->generateGrid();
        }
        void displayGrid();
        std::vector<std::vector<int>> get_grid();
    private:
        int rows_;
        int cols_;
        double percent_obstacles_;
        std::vector<std::vector<int>> grid_;

        void generateGrid();
        int get_random_integer(int min, int max);
    };
} // namespace map

void map::Grid::generateGrid() {
    int num_obstacles = (this->percent_obstacles_ * 0.01) * (this->rows_ * this->cols_);
    this->grid_.resize(this->rows_, std::vector<int>(this->cols_, 0));
    std::unordered_set<std::string> st;
    int count = 0;
    while(count < num_obstacles) {
        int row = this->get_random_integer(0, this->rows_-1);
        int col = this->get_random_integer(0, this->cols_-1);
        std::string s = std::to_string(row) + "," + std::to_string(col);
        
        if (st.find(s) == st.end()) {
            this->grid_[row][col] = 1;
            st.insert(s);
            count++;
        }
    }
}

int map::Grid::get_random_integer(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(min, max);
    int random_integer = distribution(gen);
    return random_integer;
}

void map::Grid::displayGrid() {
    for (const auto& i : this->grid_) {
        for (const auto& j : i) {
            std::cout << j << "\t";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> map::Grid::get_grid() {
    return this->grid_;
}