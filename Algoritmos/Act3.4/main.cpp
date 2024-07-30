/*Descripcion: Programa que a traves de un BST despliega las 5 IP's mas altas 
Autores: Karla Sánchez Olivares A01730545/ Jose Jezarel Sanchez Mijares A01735226 / Christian Flores Alberto A01734997
Fecha:07/11/2021*/

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "auxilio.h"
using namespace std;

bstnode* create(texto objt,bstnode* padre){ //Complejidad -- O(1)
  bstnode* temp= new bstnode();
  temp -> x =objt;
  temp -> right = temp -> left = NULL;
  temp -> padre = padre;
  return temp;
}

void insert (bstnode* &root, bstnode* padre, texto objt){ //Complejidad -- O(log n) 
  if (root==NULL)
    root=create(objt,padre); //inicio
  else if (root->x.ipComp > objt.ipComp)  //si el nodo actual es mayor que el de ingreso, inserta a la izq
    insert(root->left,root,objt);
  else if (root->x.ipComp == objt.ipComp){
    return;
  }
  else  insert(root->right,NULL,objt);
}

//Separar la IP y condensarla 
double ipSuprema(struct texto _temp){ //Complejidad -- O(n)
  vector <int> partes;
  int i=0;
  string str = "";
 
  for(char &x : _temp.ip){ //SUSTITUI AUTO POR CHAR (AUTO DECIA QUE TIPO DE VARIABLE ES PERO AL MOMENTO DE COMPILAR SOOO ME IMAGINO LO HACIA AUTOMATICO HAHA, PERO EN POCAS PALABRAS ES SOLO TIPO DE VARIABLE)
        if(x == ':'){
            partes.push_back(stoi(str));
        } 
        if(x == '.'){
            partes.push_back(stoi(str));
            str = "";
            i++;
        }
        else{
            str = str + x;
        }
    }
  int mark;
  mark = _temp.ip.find(':');
  partes[4] = stoi(_temp.ip.substr(mark+1));
  return partes[0] + (partes[1] * 0.001) + (partes[2] * 0.000001) + (partes[3] * 0.00000001) + (partes[4] * 0.000000000001);
}

//INORDEN CONVEXO -- Complejidad O(n)
void inorden(bstnode* &root, vector<string> &vec){
  if (root != NULL){ 
    inorden(root->right, vec); 
    vec.push_back(root->x.todo); //vector
    inorden(root->left, vec);
    }
}

int main() {
  bstnode* root = NULL; //Creación del arbol
  struct texto temp; //objeto texto

  string _texto; //solo el contenedor

  ifstream archivo;
  archivo.open("bitacora.txt",ios::in);
  while(!archivo.eof()){
      getline(archivo, _texto);
      temp.todo = _texto;

      int mark;
      string segnum;
      segnum = _texto.substr(16);
      mark = segnum.find(' ');
      temp.ip = segnum.substr(0, mark);
      temp.ipComp = ipSuprema(temp);
      insert(root, NULL, temp);
  }

  vector <string> vect;
  inorden(root, vect);
  if (vect.size() < 5){
    cout << "No hay datos suficientes"<< endl;
  }
  else{
    for(int i = 0; i < 5; ++i){
      cout << vect[i] << endl;
    }
  }
};
