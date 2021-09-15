
#include <iostream>
#include "Graph.h"


// program exercising the enum_paths function

int main(int argc, char *argv[]){
  graph g;

  if(argc != 3) {
    std::cout << "usage:  ./epaths <filename> <destination-vertex>\n";
    return 0;
  }
  else {
    if(!g.read_file(argv[1])){
      std::cout << "could not open file '" << argv[1] << "'\n";
      return 0;
    }
  }

  /*
  std::cout << "\nADJACENCY-LIST REPRESENTATION:\n\n";
  g.display();
  std::cout << "\nEND ADJACENCY LIST:\n\n";
  */

  vector<string> paths;

  if(!g.enum_paths(argv[2], paths)) {
    std::cout << "enum_paths failed  - cycle?\n" ;
    return 0;
  }
  else {
    std::cout << "\nINPUT PATHS ENDING AT " << argv[2] << " :\n\n";
    pvec(paths);
  }

  return 0;
}

