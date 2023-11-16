#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <unordered_set>

#include "node.hpp"

typedef std::pair<int, int> pii;
typedef std::vector<std::vector<int>> vvi;
typedef std::vector<std::vector<bool>> vvb;
typedef std::vector<std::pair<int, int>> vpii;


class AStar {
public:
    AStar(pii start, pii goal) : start_(start), goal_(goal) {}
    std::pair<vpii, int> plan(const vvi& grid);
    ~AStar();
private:
    pii start_;
    pii goal_;
    std::vector<Node*> all_nodes_;
    std::vector<Coordinate> dir_ = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
    
    void calculate_g(Node* node);
    void calculate_h(Node* node);
    void calculate_f(Node* node);
    bool isValid(Node* node, const vvi& grid);
    std::string toKey(const Coordinate& coord);
    void cleanUp();
};

AStar::~AStar() {
    cleanUp();
}

void AStar::cleanUp() {
    for (Node* node : this->all_nodes_) {
        delete node;
    }
    all_nodes_.clear();
}

void AStar::calculate_g(Node* node) {
    if (node->get_parent() == nullptr) {
        node->set_g(0.0);
    }
    else {
        int parent_r = node->get_parent()->get_point().get_row();
        int parent_c = node->get_parent()->get_point().get_col();
        int r = node->get_point().get_row();
        int c = node->get_point().get_col();
        double g = node->get_parent()->get_g() + std::sqrt(std::pow((r-parent_r),2) + std::pow(c-parent_c,2));
        node->set_g(g);
    }
}

void AStar::calculate_h(Node* node) {
    int goal_r = this->goal_.first;
    int goal_c = this->goal_.second;
    int r = node->get_point().get_row();
    int c = node->get_point().get_col();
    double h = std::sqrt(std::pow((goal_r-r),2) + std::pow(goal_c-c,2));
    node->set_h(h);
}

void AStar::calculate_f(Node* node) {
    calculate_g(node);
    calculate_h(node);
    node->set_f(node->get_g() + node->get_h());
}

bool AStar::isValid(Node* node, const vvi& grid) {
    int neighbor_r = node->get_point().get_row();
    int neighbor_c = node->get_point().get_col();
    int m = grid.size();
    int n = grid[0].size();

    if(neighbor_r < 0 || neighbor_r >= m || neighbor_c < 0 || neighbor_c >= n || grid[neighbor_r][neighbor_c] == 1) {
        return false;
    }

    return true;
}

std::string AStar::toKey(const Coordinate& coord) {
    return std::to_string(coord.get_row()) + "," + std::to_string(coord.get_col());
}

std::pair<vpii, int> AStar::plan(const vvi& grid) {
    vpii path;
    Node* start =  new Node(Coordinate(this->start_.first, this->start_.second));
    Node* goal = new Node(Coordinate(this->goal_.first, this->goal_.second));


    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
    std::unordered_map<std::string, Node*> open_list;
    std::unordered_set<std::string> closed_list;
    
    int steps = 0;
    bool found = false;

    this->all_nodes_.push_back(start);
    this->all_nodes_.push_back(goal);

    pq.push(start);
    open_list[toKey(start->get_point())] = start;

    while(!pq.empty()) {
        Node* current_node = pq.top();
        pq.pop();

        std::string current_key = toKey(current_node->get_point());
        if (closed_list.count(current_key)) {
            continue;
        }

        int r = current_node->get_point().get_row();
        int c = current_node->get_point().get_col();
        
        closed_list.insert(current_key);
        steps++;

        if(current_node->get_point() == goal->get_point()) {
            while(current_node->get_point() != start->get_point()) {
                int coord_r = current_node->get_point().get_row();
                int coord_c = current_node->get_point().get_col();
                path.push_back(std::make_pair(coord_r, coord_c));
                current_node = current_node->get_parent();
            }
            found = true;
            break;
        }

        for(auto& i : this->dir_) {
            Node* neighbor = new Node(i + current_node->get_point(), current_node);
            all_nodes_.push_back(neighbor);
            
            std::string neighbor_key = toKey(neighbor->get_point());
            if (closed_list.count(neighbor_key)) {
                continue;
            }
            if (!isValid(neighbor, grid)) {
                continue;
            }
            calculate_f(neighbor);

            if (!open_list.count(neighbor_key) || open_list[neighbor_key]->get_f() > neighbor->get_f()) {
                open_list[neighbor_key] = neighbor;
                pq.push(neighbor);
            }
        }
    }
    if (found) {
        std::cout << "Path found in " << steps << " steps." << std::endl;
    }
    else {
        return {};
    }
    std::reverse(path.begin(), path.end());
    return std::make_pair(path, steps);
}