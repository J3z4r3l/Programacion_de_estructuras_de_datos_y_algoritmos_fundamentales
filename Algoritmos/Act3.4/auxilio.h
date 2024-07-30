#include <iostream>
#include <string.h>
using namespace std;

struct texto{
  string ip; //ip como string
  double ipComp; //para comparación y ordenamiento
  string todo;
};

struct bstnode { 
  struct texto x;
  bstnode *left;
  bstnode *right; 
  bstnode *padre;
}; 
