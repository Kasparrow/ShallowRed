#pragma once

#include <vector>
#include <algorithm>
#include <limits>

enum NodeType { MIN, MAX };

class Node
{
  public:
                        Node            ();
                        Node            (double value, NodeType t);
                        ~Node           ();
    void                add_child       (Node* n);
    void                remove_child    (Node* n);
    double              get_min_child   ();
    double              get_max_childs  ();
    void                set_value       (double v);
    double              get_value       ();
    bool                is_leaf         ();
    void                set_type        (NodeType t);
    NodeType            get_type        ();
    std::vector<Node*>  get_childs      ();
    

  private:
    double              _value;
    std::vector<Node*>  _childs;
    NodeType            _type;
};

