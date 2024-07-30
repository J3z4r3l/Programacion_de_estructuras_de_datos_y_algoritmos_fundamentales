/*Descripcion: Programa que almacena los datos en un grafo dirigido, se determina el grado de salida de cada nodo, despliega la red con mayor hosts registrados en la bitacora y despliega los hosts con mayor incidencia (IP completa sin puerto)
Autores: Karla Sánchez Olivares A01730545/ Jose Jezarel Sanchez Mijares A01735226 / Christian Flores Alberto A01734997
Fecha:07/11/2021*/
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h> //para new y delete
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

struct resumen{
  string red;
  string ipcompleta;
  int accesos; 
  int unicos;
  vector<string> ips;
};

void print(vector<pair<string, struct resumen>> ht){
  for(int i = 0; i < ht.size();i++){
    cout << i <<" "<<ht[i].first<< " "<<ht[i].second.accesos<<" "<< ht[i].second.unicos << endl;
  }
}

void ins(vector <pair<string, struct resumen>> &ht, int place, struct resumen temp, int cap){ 
  int cont = 0;
  if(ht[place].first == "none"){
    ht[place].first = temp.red;
    ht[place].second = temp;
  }
  else if( ht[place].first != "none" && ht[place].second.red != temp.red){
    for(int i = place; i < cap; ++i){
      if(ht[i].first == "none"){
        ht[i].first = temp.red;
        ht[i].second = temp;
        i = cap;
        cont++;
      }
    }
    if(cont == 0){
      for(int i = 0; i < place; ++i){
        if(ht[i].first == "none"){
          ht[i].first = temp.red;
          ht[i].second = temp;
          i = place;
          cont++;
        }
    }
  }
  if(cont == 0){
      cout << "La tabla está llena, imposible insertar";
    }
}
}

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

int ipSuprema(string _ipcompleta, int mod){ //Complejidad -- O(n)
  vector <int> partes;
  int i=0;
  string str = "";
 
  for(char &x : _ipcompleta){ 
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
  mark = _ipcompleta.find(':');
  partes[4] = stoi(_ipcompleta.substr(mark+1));
  int x = partes[0] + (partes[1] * 0.001) + (partes[2] * 0.000001) + (partes[3] * 0.00000001) + (partes[4] * 0.000000000001);

  return x % mod;
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

//Redes y hosts con más entradas
//int conmas = root->redes[0]->gradsal;
//string redr = "250.051";

//Redes con mayor grado de salida

/*
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
*/

vector <pair<string, struct resumen>> hashtable;
int _mod = entradas.size();

for(int i =0; i < entradas.size(); i++){
  struct resumen xtemp;
  xtemp.accesos = 0;
  xtemp.unicos = 0;
  hashtable.push_back(make_pair("none", xtemp));
}

//print(hashtable);
for(int i= 0; i < _mod; ++i){
  struct resumen temp;
  temp.red = entradas[i].red;

  for(int j = 0; j < root->redes.size(); j++){
    if(temp.red == root->redes[j]->redId){
      temp.accesos = root->redes[j]->gradsal;
      for(int k = 0; k < root->redes[j]->hosts.size(); k++){
        temp.ips.push_back(root->redes[j]->hosts[k]->hostId);
        
      }
    }
  }

  temp.unicos = temp.ips.size();
  ins(hashtable, ipSuprema(entradas[i].red, _mod), temp, _mod);
}

//print(hashtable);
int count = 0;
for(int i = 0; i< porbuscar.size(); i++){
  for(int j = 0; j < hashtable.size(); j++){
    if(count == 0 && porbuscar[i] == hashtable[j].first){
      cout << hashtable[j].first << endl <<hashtable[j].second.accesos << endl<< hashtable[j].second.unicos<< endl;

      for(int k = 0; k < hashtable[j].second.ips.size(); k++){
        cout << stof(hashtable[j].first) << "."<< stof(hashtable[j].second.ips[k]) << endl;
      }
      count++;
    }
  }
}

delete root;
};
