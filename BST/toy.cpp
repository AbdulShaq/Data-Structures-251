#include <iostream>
#include "bst.h"


int main(){
    int x;
    int h;

    bst<int> *t = new bst<int>();

    while( (std::cin >> x)) 
        t->insert(x);

    if(t->size() <= 20) {
      t->inorder();
      t->preorder();
    }

    h = t->height();
    std::cout << "\n#### Reported height of tree:   " << h << "\n";

    delete t;
    
    return 0;
}
