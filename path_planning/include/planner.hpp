#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "astar.hpp"
#include "dijkstra.hpp"

typedef std::vector<std::pair<int, int>> vpii;

namespace planner {
    class SearchBasedPlanner {
    public:
        SearchBasedPlanner(pii start = {}, pii goal = {}, vvi grid = {{}}, std::string planner_type = "dijkstra") :
                           start_(start), goal_(goal), grid_(grid), planner_type_(planner_type) {}

        std::pair<vpii, int> get_path();

    private:
        pii start_;
        pii goal_;
        vvi grid_;
        std::string planner_type_;
        vpii path_;

        bool isValidStartOrGoal();
    };
} // namespace planner

bool planner::SearchBasedPlanner::isValidStartOrGoal() {
    if (this->grid_[this->start_.first][this->start_.second] == 1 || 
        this->grid_[this->goal_.first][this->goal_.second] == 1) {
        return false;
    }
    return true;
}

std::pair<vpii, int> planner::SearchBasedPlanner::get_path() {
    if (!isValidStartOrGoal()) {
        std::cout << "The start or goal is invalid." << std::endl;
        std::cout << "Start (" << this->start_.first << "," << this->start_.second << ") = ";
        std::cout << this->grid_[this->start_.first][this->start_.second] << std::endl;
        std::cout << "Goal (" << this->goal_.first << "," << this->goal_.second << ") = ";
        std::cout << this->grid_[this->goal_.first][this->goal_.second] << std::endl;
        return {};
    }
    else {
        std::cout << "The start or goal is valid." << std::endl;
    }

    if (this->planner_type_ == "dijkstra") {
        Dijkstra dijkstra(this->start_, this->goal_);
        return dijkstra.plan(this->grid_);
    }
    else if (this->planner_type_ == "a-star") {
        AStar astar(this->start_, this->goal_);
        return astar.plan(this->grid_);
    }
    return {};
}