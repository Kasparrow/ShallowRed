#include "ShallowRed.h"



ShallowRed::ShallowRed()
{

}


ShallowRed::~ShallowRed()
{

}


double ShallowRed::alphabeta(Node* n, double a, double b)
{
  if (n->is_leaf())
    return n->get_value();

  double  best = -std::numeric_limits<double>::infinity();
  double  v;

  for (auto it : n->get_childs())
  {
    v = -alphabeta(it, -b, -a);

    if (v < best)
      continue;

    best = v;

    if (best < a)
      continue;

    a = best;

    if (a >= b)
      return best;
  }

  return best;
}
