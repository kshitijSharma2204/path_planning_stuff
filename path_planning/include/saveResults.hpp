#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class SaveAndLoad {
public:
    SaveAndLoad() {}
    void saveResultDetailsBinary(int r, int c, double obs_perc,
                           const std::pair<int, int>& start, const std::pair<int, int>& goal,
                           const std::string& planner, const std::vector<std::vector<int>>& grid,
                           const std::vector<std::pair<int, int>>& path, int steps) {

        std::string results_dir = "../Results/";

        if (!std::filesystem::exists(results_dir)) {
            std::filesystem::create_directory(results_dir);
        }

        int file_count = 0;
        for (const auto& entry : std::filesystem::directory_iterator(results_dir)) {
            file_count++;
        }

        std::string file_name = results_dir + "/" + planner + "_" + std::to_string(file_count+1) + ".bin";

        std::ofstream output_file(file_name, std::ios::binary);

        if (!output_file.is_open()) {
            std::cerr << "Error: Unable to open file for writing." << std::endl;
            return;
        }

        output_file.write(reinterpret_cast<const char*>(&r), sizeof(r));
        output_file.write(reinterpret_cast<const char*>(&c), sizeof(c));
        output_file.write(reinterpret_cast<const char*>(&obs_perc), sizeof(obs_perc));
        output_file.write(reinterpret_cast<const char*>(&start), sizeof(start));
        output_file.write(reinterpret_cast<const char*>(&goal), sizeof(goal));
        output_file.write(reinterpret_cast<const char*>(&steps), sizeof(steps));

        for (const auto& row : grid) {
            output_file.write(reinterpret_cast<const char*>(row.data()), row.size() * sizeof(int));
        }

        for (const auto& p : path) {
            output_file.write(reinterpret_cast<const char*>(&p), sizeof(p));
        }

        output_file.close();

        std::cout << "\nResult details saved to " << file_name << std::endl;
    }

    bool loadResultDetailsBinary(const std::string& file_path,
                           int& r, int& c, double& obs_perc,
                           std::pair<int, int>& start, std::pair<int, int>& goal,
                           int& steps, std::vector<std::vector<int>>& grid,
                           std::vector<std::pair<int, int>>& path) {

        std::ifstream input_file(file_path, std::ios::binary);

        if (!input_file.is_open()) {
            std::cerr << "Error: Unable to open file for reading." << std::endl;
            return false;
        }

        input_file.read(reinterpret_cast<char*>(&r), sizeof(r));
        input_file.read(reinterpret_cast<char*>(&c), sizeof(c));
        input_file.read(reinterpret_cast<char*>(&obs_perc), sizeof(obs_perc));
        input_file.read(reinterpret_cast<char*>(&start), sizeof(start));
        input_file.read(reinterpret_cast<char*>(&goal), sizeof(goal));
        input_file.read(reinterpret_cast<char*>(&steps), sizeof(steps));

        grid.resize(r, std::vector<int>(c));
        for (auto& row : grid) {
            input_file.read(reinterpret_cast<char*>(row.data()), c * sizeof(int));
        }

        while (input_file.peek() != EOF) {
            std::pair<int, int> p;
            input_file.read(reinterpret_cast<char*>(&p), sizeof(p));
            path.push_back(p);
        }

        input_file.close();
        return true;
    }
};