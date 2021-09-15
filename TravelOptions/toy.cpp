#include "TravelOptions.h"

#include <stdlib.h>
#include <iostream>

// using namespace std;

/*
 simple demo program exercising some of the TravelOptions functions.

to compile:  g++ -std=c++11 toy.cpp

 purpose:  just to make sure you have an idea of how to write 
             driver/tester programs (this is not itself a tester program
             per-se, just a pretty random sequence of calls..
*/


int main(int argc, char *argv[]){
  TravelOptions *options_p, *options_p2, *options_p3;

  std::vector<std::pair<double, double>>
	vec{ {1, 7}, {2, 8}, {2, 9}, 
		{3, 5}, {5, 8}, {5, 8}, 
		{5, 9}, {6, 12} };

  std::vector<std::pair<double, double>> *vec2;

  // remember:  from_vec is a static function (hence, TravelOptions:: form)
  options_p = TravelOptions::from_vec(vec);
  options_p2 = TravelOptions::from_vec(vec);

  options_p->display();
  std::cout << "size: " << options_p->size() << std::endl; 
 
  TravelOptions::Relationship r;
  r = TravelOptions::compare(10.0, 2.9, 9.0, 1.9);
  if(r == TravelOptions::better) 
     std::cout << "BETTER?  ARE YOU SURE?" << std::endl;
  if(r == TravelOptions::incomparable) 
     std::cout << "INCOMPARABLE?  ARE YOU SURE?" << std::endl;
  if(r == TravelOptions::equal) 
     std::cout << "EQUAL?  ARE YOU SURE?" << std::endl;
  if(r == TravelOptions::worse) 
     std::cout << "WORSE?  I THINK YOU ARE RIGHT!" << std::endl;


  vec2 = options_p->to_vec();

  std::cout << "CONTENTS OF EXPORTED VECTOR:\n";
  for(int i=0; i<vec2->size(); i++) {
     std::cout << (*vec2)[i].first << " ,  " << (*vec2)[i].second << std::endl;
  }

  std::cout << "\n";

  if(options_p->is_sorted() ) 
     std::cout << "SORTED!" << std::endl;
  else 
     std::cout << "NOT SORTED!" << std::endl;

  if( options_p->is_pareto() )
     std::cout << "PARETO!" << std::endl;
  else 
     std::cout << "NOT PARETO!" << std::endl;

  if(options_p->is_pareto_sorted())
     std::cout << "PARETO - SORTED!" << std::endl;
  else 
     std::cout << "NOT PARETO-SORTED" << std::endl;

  if(options_p->insert_sorted(22.0, 9.7))
     std::cout << "INSERT_SORTED WORKED!" << std::endl;

  if(options_p->insert_pareto_sorted(21.0, 9.7))
     std::cout << "INSERT_PARETO_SORTED WORKED!" << std::endl;

  options_p3= options_p->union_pareto_sorted(*options_p2);

  if(options_p3->prune_sorted())
     std::cout << "prune_sorted worked!" << std::endl;

  delete options_p3;

  options_p3 = options_p->join_plus_plus(*options_p2);

  delete options_p3;
  options_p3 = options_p->join_plus_max(*options_p2);
  

  options_p->clear();
  delete options_p;
  delete options_p2;
  delete options_p3;

  return 0;
}
