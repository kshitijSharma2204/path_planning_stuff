#include "graph.hpp"
#include "planner.hpp"
#include "saveResults.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << "<arg1>" << std::endl;
    }
    std::string rows = argv[1];
    std::string cols = argv[2];
    std::string obstacle_percent = argv[3];
    std::string start_x = argv[4];
    std::string start_y = argv[5];
    std::string goal_x = argv[6];
    std::string goal_y = argv[7];
    std::string planner1 = argv[8];
    // std::string planner2 = argv[9];
    
    std::cout << "Rows: " << rows << std::endl;
    std::cout << "Cols: " << cols << std::endl;
    std::cout << "Obstacle Percentage: " << obstacle_percent << std::endl;
    std::cout << "Start: " << start_x << ", " << start_y << std::endl;
    std::cout << "Goal: " << goal_x << ", " << goal_y << std::endl;
    std::cout << "Planner1: " << planner1 << std::endl;
    // std::cout << "Planner2: " << planner2 << std::endl;

    if (planner1 != "a-star" && planner1 != "dijkstra") {
        std::cerr << "Wrong Planner: Choose a-star or dijkstra" << std::endl;
        exit(1);
    }

    int r = std::stoi(rows);
    int c = std::stoi(cols);
    double obs_perc = std::stod(obstacle_percent);
    std::pair<int, int> strt = std::make_pair(std::stoi(start_x), std::stoi(start_y));
    std::pair<int, int> gl = std::make_pair(std::stoi(goal_x), std::stoi(goal_y));

    map::Grid g(r,c,obs_perc);
    std::vector<std::vector<int>> grid = g.get_grid();

    grid[0][0] = 0;
    grid[r-1][c-1] = 0;

    planner::SearchBasedPlanner plan1(strt, gl, grid, planner1);
    std::vector<std::pair<int, int>> path1 = plan1.get_path().first;
    int steps1 = plan1.get_path().second;
    
    if (path1.empty()) {
        std::cout << "Path not found." << std::endl;
    }
    else {
        // std::cout << "Grid" << std::endl;
        // g.displayGrid();
        std::cout << "\nPath: ";
        for (const auto& i : path1) {
            std::cout << "(" << i.first << "," << i.second << "), ";
        }
    }

    SaveAndLoad sl1;
    sl1.saveResultDetailsBinary(r,c,obs_perc,strt,gl,planner1,grid, path1, steps1);

    return 0;
}