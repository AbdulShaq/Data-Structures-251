
#include <iostream>
#include "Graph.h"


int main(){
  graph g;

  g._add_edge("a b 2");
  g._add_edge("a c 2");
  g._add_edge("a d ");
  g._add_edge("b d ten");
  g._add_edge("a");
  /*
  g.add_edge("a", "b");
  g.add_edge("b", "a");

  g.add_edge("b", "c");
  g.add_edge("d", "a");
  g.add_edge("b", "d");
  g.add_edge("a", "b");
  */


  g.display();

  return 0;
}

