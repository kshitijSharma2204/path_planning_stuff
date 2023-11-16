#pragma once

#include <memory>
#include <cmath>

// Coordinate
class Coordinate {
public:
    Coordinate(int r=0, int c=0) : r_(r), c_(c) {}
    Coordinate operator+(const Coordinate& coord);
    bool operator==(const Coordinate& coord);
    bool operator!=(const Coordinate& coord);
    
    void set_row(int r);
    void set_col(int c);
    int get_row() const;
    int get_col() const;
private:
    int r_;
    int c_;
};

// Node
class Node {
public:
    Node(Coordinate point=Coordinate(0,0), Node* parent=nullptr, double g=0.0, double h=0.0, double f=0.0) :
         point_(point), parent_(parent), g_(g), h_(h), f_(f) {}

    void set_point(Coordinate point);
    void set_parent(Node* parent);
    void set_g(double g);
    void set_h(double h);
    void set_f(double f);

    Coordinate get_point() const;
    Node* get_parent() const;
    double get_g() const;
    double get_h() const;
    double get_f() const;
private:
    Coordinate point_;
    Node* parent_;
    double g_ = 0.0;
    double h_ = 0.0;
    double f_ = 0.0;
};

struct CompareNodes {
    bool operator()(Node* l, Node* r) const {
        return l->get_f() > r->get_f();
    }
};

// class Coordinate member functions
Coordinate Coordinate::operator+(const Coordinate& coord) {
    return Coordinate(this->r_ + coord.r_, this->c_ + coord.c_);
}

bool Coordinate::operator==(const Coordinate& coord) {
    return (this->r_ == coord.r_ && this->c_ == coord.c_); 
}

bool Coordinate::operator!=(const Coordinate& coord) {
    return (this->r_ != coord.r_ || this->c_ != coord.c_);
}

void Coordinate::set_row(int r) {
    this->r_ = r;
}

void Coordinate::set_col(int c) {
    this->c_ = c;
}

int Coordinate::get_row() const {
    return this->r_;
}

int Coordinate::get_col() const {
    return this->c_;
}

// class Node member functions
void Node::set_point(Coordinate point) {
    this->point_ = point;
}

void Node::set_parent(Node* parent) {
    this->parent_ = parent;
}

void Node::set_g(double g) {
    this->g_ = g;
}

void Node::set_h(double h) {
    this->h_ = h;
}
void Node::set_f(double f) {
    this->f_ = f;
}

Coordinate Node::get_point() const {
    return this->point_;
}

Node* Node::get_parent() const {
    return this->parent_;
}

double Node::get_g() const {
    return this->g_;
}

double Node::get_h() const {
    return this->h_;
}

double Node::get_f() const {
    return this->f_;
}