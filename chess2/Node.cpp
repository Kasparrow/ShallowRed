#include <algorithm>

#include "Node.h"

Node::Node() : _childs()
{
    _value = 0;
}

Node::Node(double value, NodeType t) : _childs()
{
    _value = value;
    _type = t;
}

Node::~Node()
{
    for (auto it : _childs)
        delete it;
}


void Node::add_child(Node* n)
{
    _childs.push_back(n);
}

void Node::remove_child(Node* n)
{
    // - remove only the first occurence of n, may cause error
    auto position = std::find(_childs.begin(), _childs.end(), n);
  
    if (position != _childs.end())
        _childs.erase(position);
}

double Node::get_min_child()
{
    double min = std::numeric_limits<double>::infinity();

    for (auto it : _childs)
        min = std::min(min, it->get_value());

    return min;
}

double Node::get_max_childs()
{
    double max = -std::numeric_limits<double>::infinity();

    for (auto it : _childs)
        max = std::max(max, it->get_value());

    return max;
}

void Node::set_value(double v)
{
    _value = v;
}

double Node::get_value()
{
    return _value;
}

bool Node::is_leaf()
{
    return _childs.size() == 0;
}

void Node::set_type(NodeType t)
{
    _type = t;
}

NodeType Node::get_type()
{
    return _type;
}

std::vector<Node*> Node::get_childs()
{
    return _childs;
}