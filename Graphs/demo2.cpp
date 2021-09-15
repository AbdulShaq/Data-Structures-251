
#include <iostream>
#include "Graph.h"


int main(int argc, char *argv[]){
  graph g;
  std::vector<graph::vertex_label> bfs_rpt;
  std::vector<graph::vertex_label> dfs_rpt;
  bool cycle_found;

  if(argc != 2) 
    std::cout << "usage:  demo2 <filename>\n";
  else {
    if(!g.read_file(argv[1]))
      std::cout << "could not open file '" << argv[1] << "'\n";
  }

  std::cout << "\nADJACENCY-LIST REPRESENTATION:\n\n";
  g.display();

  g.bfs(0, bfs_rpt);
  std::cout << "\nBFS REPORT:\n\n";
  g.disp_report(bfs_rpt);

  g.dfs(0, dfs_rpt, cycle_found);
  std::cout << "\nDFS from vertex '" << g.id2name(0) << "' complete\n\n";
  if(cycle_found) 
    std::cout << "   cycle found!\n";
  else
    std::cout << "   no cycle found\n";
  std::cout << "DFS REPORT:\n\n";
  g.disp_report(dfs_rpt);

  g.dfs("b", dfs_rpt, cycle_found);
  std::cout << "\nDFS from vertex 'b' complete\n\n";
  if(cycle_found) 
    std::cout << "   cycle found!\n";
  else
    std::cout << "   no cycle found\n";
  std::cout << "DFS REPORT:\n\n";
  g.disp_report(dfs_rpt);


  if(g.has_cycle())
    std::cout << "g.has_cycle():  true\n";
  else
    std::cout << "g.has_cycle():  false\n";


  return 0;
}

