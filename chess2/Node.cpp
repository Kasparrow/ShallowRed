#include "Node.h"



Node::Node()
{
}


Node::~Node()
{
}


void Node::add_child(Node* n)
{
  _childs.push_back(n);
}

void Node::remove_child(Node* n)
{
  // - remove only the first occurence of n, may cause error
  std::vector<Node*>::iterator position = std::find(_childs.begin(), _childs.end(), n);
  
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