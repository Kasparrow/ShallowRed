#pragma once

#include <vector>
#include <algorithm>
#include <limits>

class Node
{
  public:
    Node();
    ~Node();
    void add_child(Node* n);
    void remove_child(Node* n);
    double get_min_child();
    double get_max_childs();
    void set_value(double v);
    double get_value();

  private:
    double _value;
    std::vector<Node*> _childs;
};

