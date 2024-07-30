/*Descripcion: Programa que almacena los datos en un grafo dirigido, se determina el grado de salida de cada nodo, despliega la red con mayor hosts registrados en la bitacora y despliega los hosts con mayor incidencia (IP completa sin puerto)
Autores: Karla Sánchez Olivares A01730545/ Jose Jezarel Sanchez Mijares A01735226 / Christian Flores Alberto A01734997
Fecha:07/11/2021*/
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h> //para new y delete
#include <map>
#include <vector>
using namespace std;

struct grafo{
  vector <struct red*> redes;
};
struct red{
    string redId; //la red pues
    int gradsal;
    vector <struct host*> hosts;
};
struct host{
  string hostId;
  int gradsal;
};
struct texto{
  string fecha, puerto, error;
  string red, host;
  string todo;
};

//Función para unir la entrada - Comlpejidad O(1)
string muchoTexto(struct texto _temp){
  return _temp.fecha+" "+ _temp.red+"."+_temp.host+":"+_temp.puerto+" "+_temp.error;
}

//Función para imprimir un vector(for debugging) - Comlpejidad O(N)
void imprimir(vector<struct texto> &v){
  for(int i = 0; i < v.size(); i++){
    cout << v[i].red << endl;
  }
}

//Función para unir ips a sus host, hosts a sus redes y redes al grafo - Comlpejidad O(N^3)
void crearGrafo(struct grafo *Graph, vector<struct texto> ents){
  struct red *rtemp;
  int sizeRedes = 0;

  struct host *htemp;
  int sizeHosts = 0;
  

  for(int i = 0; i < ents.size(); ++i){
    string exiRed = "no", exiHost = "no";
    rtemp = new red();
    rtemp->gradsal = 1;
    rtemp->redId = ents[i].red;
    htemp = new host();
    htemp->gradsal = 1;
    htemp->hostId = ents[i].host;

    if(i == 0){
      rtemp->hosts.push_back(htemp);
      Graph->redes.push_back(rtemp);
      //cout << rtemp->redId<<endl;
    }
    else{
      sizeRedes = Graph->redes.size();
      //Si la red ya existe en el vector cambia la tag a "ya" y se repite el proceso con los hosts
      for(int j = 0; j < sizeRedes; j++){ //1
        if (Graph->redes[j]->redId == ents[i].red){
          exiRed = "ya";

          sizeHosts = Graph->redes[j] ->hosts.size();
          for(int w = 0; w < sizeHosts; ++w){
            if (Graph->redes[j]->hosts[w]->hostId == ents[i].host){
            exiHost = "ya";
            Graph->redes[j] -> hosts[w] -> gradsal+=1;
            }
            else if(w==sizeHosts-1 && exiHost=="no"){
              Graph->redes[j]->hosts.push_back(htemp);
              Graph->redes[j]->gradsal++;
            }
          }
          
        }
        //Si la red no existe en el vector se añade
        else if(j == sizeRedes -1 && exiRed == "no"){
          rtemp->hosts.push_back(htemp);
          Graph->redes.push_back(rtemp);
          //cout << rtemp->redId<<endl;
      }
    }
    //cout << rtemp->gradsal << " " << rtemp->redId<<endl;
  }
  }
}

int main() {

  int numb;
  string redzz;
  cin >> numb;

  vector <string> porbuscar;
  for(int i = 0; i < numb; ++i){
    cin >> redzz;
    porbuscar.push_back(redzz);
  }
  cout<<endl;


  struct grafo* root = NULL; //Creación del graph
  root = new grafo();
  struct texto temp; //objeto texto
  string  _mes,_dia, _hms, _ip1, _ip2, _ip3, _ip4,_puerto;
  string _todo;
  vector<struct texto> entradas;

  ifstream archivo("bitacora2.txt");
  while(getline(archivo, _mes, ' ')){
      getline(archivo, _dia, ' ');
      getline(archivo,_hms,' ');
      temp.fecha =_mes+" "+_dia+" "+_hms;
      getline(archivo, _ip1,'.');
      getline(archivo, _ip2,'.');
      temp.red = _ip1 +"."+ _ip2;
      getline(archivo, _ip3,'.');
      getline(archivo, _ip4, ':');
      temp.host = _ip3 + "."+_ip4;
      getline(archivo, _puerto, ' ');
      temp.puerto = _puerto;
      getline(archivo, _todo);
      temp.error = _todo;
      temp.todo = muchoTexto(temp);
      //cout << temp.todo<<endl; //<< " " << temp.red << " "<<temp.host << endl;
      entradas.push_back(temp);
    }

//imprimir(entradas);
crearGrafo(root, entradas);

/*
for(int i = 0; i < root->redes.size(); ++i){
  for(int j = 0; j < root->redes[i]->hosts.size(); ++j){
    cout << root->redes[i]->hosts[j]->hostId << endl;
  }
}
*/

//Redes y hosts con más entradas
//int conmas = root->redes[0]->gradsal;
//string redr = "250.051";

//Redes con mayor grado de salida

for(int i = 0; i < porbuscar.size();++i){
  for(int j = 0; j < root->redes.size(); ++j){
    if(root->redes[j]->redId == porbuscar[i]){
      cout << root->redes[j]->redId << endl;
      cout << root->redes[j]->gradsal << endl;
      for(int k = 0; k < root->redes[j]->hosts.size(); k++){
        cout << root->redes[j]->hosts[k]->hostId << endl;
      }
    }
  }
}

/*
for(int i = 0; i < root->redes.size();++i){
  if(root->redes[i]->gradsal == conmas){
    cout << root->redes[i]->redId<<endl;
  }
}
cout << endl;
conmas = root->redes[0]->hosts[0]->gradsal;
*/
//Hosts con mayor grado de salida
/*
for(int i = 0; i < root->redes.size(); ++i){
  for(int j = 0; j < root->redes[i]->hosts.size(); ++j){
    if(root->redes[i]->hosts[j]->gradsal > conmas){
    conmas = root->redes[i]->hosts[j]->gradsal;
    }
  }
}

for(int i = 0; i < root->redes.size(); ++i){
  for(int j = 0; j < root->redes[i]->hosts.size(); ++j){
    if(root->redes[i]->hosts[j]->gradsal == conmas){
    cout<< root->redes[i]->redId <<"."<< root->redes[i]->hosts[j]->hostId<<endl;
    }
  }
}
*/

delete root;
};

/*
         _nnnn_
        dGGGGMMb     ,"""""""""""""".
       @p~qp~~qMb    | Linux Rules! |
       M|()||()M|   _;..............'
       @,----.JM| -'
      JS^\__/  qKL
     dZP        qKRb
    dZP          qKKb
   fZP            SMMb
   HZM            MMMM
   FqM            MMMM
 __| ".        |\dS"qML
 |    `.       | `' \Zq
_)      \.___.,|     .'
\____   )MMMMMM|   .'
     `-'       `--' hjm

*/
