/*Descripcion: Aplicación en C++ que utiliza listas doblemente ligadas
Autores: Karla Sánchez Olivares A01730545/ Jose Jezarel Sanchez Mijares A01735226 / Christian Flores Alberto A01734997
Fecha: 18/10/2021*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include<string>
#include "ordenamerge.h"
using namespace std;


//Funcion empuja -- O(1)
void push(nodo *&lista, texto objt){
  nodo *nuevoNodo = new nodo();
  nuevoNodo -> x = objt;
  nuevoNodo -> prev = NULL;
  nuevoNodo->sig = lista;
  lista = nuevoNodo;
}

//Funcion imprime -- O(n)
void imprimeLista(nodo *&lista){
  while(lista !=NULL){
    cout<<lista->x.todo;
    cout << endl;
    lista = lista -> sig;
  }
}

//Funcion reverseLista -- O(n)
void reverseLista(nodo* &lista){
  struct nodo *a,*b,*c;
  a=NULL;
  b=NULL;
  c=lista;

  while (c!=NULL){
    a=c->sig;
    c->sig=b;
    b=c;
    c=a;
  }
  lista=b;
  return;
}

//Funcion ipCompleto -- O(1)
string ipCompleto(struct texto _temp){
  return to_string(_temp.ipnum) +"."+to_string(_temp.ipnum1)+"."+to_string(_temp.ipnum2)+"."+to_string(_temp.ipnum3)+":"+_temp.puerto;
}

//Funcion horarioCompleto -- O(1)
string horarioCompleto(struct texto _temp){
  return backToNums(_temp.h) +":"+backToNums(_temp.m)+":"+backToNums(_temp.s);
}

//Funcion separarIp -- O(n)
vector <int>separarIp(string inIp, vector<int> v){
  int mark,segnum;
  string segstring;
  for(int i = 0; i < inIp.length(); i++){
    mark = inIp.find('.');
    segstring = inIp.substr(0, mark);
    int newmark = mark+1;
    inIp = inIp.substr(newmark);
    v.push_back(stoi(segstring));
  }
  
  v.push_back(stoi(inIp));
  return v;
}
//Funcion mostrarDatos -- O(1)
string mostrarDatos(struct texto _temp){
  return  _temp.smes+ " " + backToNums(_temp.dia) + " "  + _temp.hms+ " "+ _temp.ip+" "+_temp.error;
}

//Para sacar el Horario completo
float horario(int hora, int min, int seg){
    float tiempo =(hora*10)+(min*(0.16))+(seg*(0.0027));
    return tiempo;
}


int main() {
  struct nodo* lista = NULL;
  struct nodo* lista2 = NULL;

  int n=0; //contador
  string texto, sip1, sip2;
  int ip1, cip1, cip2, cip3, cip4;
  int ip2, dip1, dip2, dip3, dip4;
  vector<int> vecip1, vecip2;
  //Entrada de ips como string
  cin >> sip1;
  cin >> sip2;
  ip1 = stof(sip1);
  ip2 = stof(sip2);

  int mark,segnum;
  string segstring;
  for(int i = 0; i < sip1.length(); i++){
    mark = sip1.find('.');
    segstring = sip1.substr(0, mark);
    int newmark = mark+1;
    sip1 = sip1.substr(newmark);
    vecip1.push_back(stoi(segstring));
  }
  vecip1.push_back(stoi(sip1));



  for(int i = 0; i < sip2.length(); i++){
    mark = sip2.find('.');
    segstring = sip2.substr(0, mark);
    int newmark = mark+1;
    sip2 = sip2.substr(newmark);
    vecip2.push_back(stoi(segstring));
  }
  vecip2.push_back(stoi(sip2));


//Rango de entrada-----------------------------------
  cip1 = vecip1[0];
  cip2 = vecip1[1];
  cip3 = vecip1[2];
  cip4 = vecip1[3];
  
  dip1 = vecip2[0];
  dip2 = vecip2[1];
  dip3 = vecip2[2];
  dip4 = vecip2[3];

  //solo para debuggear
  // cout << "Vector" << endl;
  // for(int i = 0; i < vecip1.size(); i++){
  //   cout << vecip1[i] << " ";
  // }
  // cout <<endl;
  // cout << "Vector" << endl;
  // for(int i = 0; i < vecip2.size(); i++){
  //   cout << vecip2[i] << " ";
  // }
  // cout <<endl;


  struct texto temp;
  string  _mes, _dia, _hms, _ip1, _ip2, _ip3, _ip4,_puerto;
  string _h,_m,_s;

  //Todo entra como string, uso de función c_str() para ingresar a los valores y convertirlos a números con atof
  ifstream archivo("bitacora.txt");
  while(getline(archivo, _mes, ' ')){
      vector<int> iptemp;
      temp.smes = _mes;
      temp.mes = cambioMes(_mes);
      getline(archivo, _dia, ' ');
      temp.dia = atof( _dia.c_str() );
      getline(archivo, _h, ':');
      temp.h = atoi( _h.c_str() );
      getline(archivo, _m, ':');
      temp.m=atoi( _m.c_str() );
      getline(archivo,_s,' ');
      temp.s = atoi(_s.c_str());
      temp.horarioTotal = horario(temp.h, temp.m,temp.s);
      temp.hms = horarioCompleto(temp);
      getline(archivo, _ip1,'.');
      temp.ipnum = atoi(_ip1.c_str());
      iptemp.push_back(temp.ipnum);
      getline(archivo, _ip2,'.');
      temp.ipnum1 = atoi(_ip2.c_str());
      iptemp.push_back(temp.ipnum1);
      getline(archivo, _ip3,'.');
      temp.ipnum2 = atoi(_ip3.c_str());
      iptemp.push_back(temp.ipnum2);
      getline(archivo, _ip4, ':');
      temp.ipnum3 = atoi(_ip4.c_str());
      iptemp.push_back(temp.ipnum3);
      getline(archivo, _puerto, ' ');
      temp.puerto = _puerto;
      getline(archivo, texto);
      temp.error = texto;

      temp.ip = ipCompleto(temp);
      //Formar atributo con todos los datos
      temp.todo = mostrarDatos(temp);
    //PUSH si esta dentro de los rangos--------------------------------
    if(temp.ipnum > cip1 && temp.ipnum < dip1){  //
          push(lista, temp);
          push(lista2, temp);
          n++;
    }
    if(temp.ipnum == cip1 || temp.ipnum == dip1){
      if(temp.ipnum == cip1){
        if(temp.ipnum1 > cip2){
          push(lista, temp);
          push(lista2, temp);
          n++;
        }
        if(temp.ipnum1 == cip2){
          if(temp.ipnum2 > cip3){
            push(lista, temp);
            push(lista2, temp);
            n++;
          }
          if(temp.ipnum2 == cip3){
            if(temp.ipnum3 >= cip4){
              push(lista, temp);
              push(lista2, temp);
              n++;
            }
          }
        }
      }

      //Limite inferior
      if(temp.ipnum == dip1){
        if(temp.ipnum1 < dip2){
          push(lista, temp);
          push(lista2, temp);
          n++;
        }
        if(temp.ipnum1 == dip2){
          if(temp.ipnum2 < dip3){
            push(lista, temp);
            push(lista2, temp);
            n++;
          }
          if(temp.ipnum2 == dip3){
            if(temp.ipnum3 <= dip4){
              push(lista, temp);
              push(lista2, temp);
              n++;
            }
          }
        }
      }
      
    }//

  }//fin while getlines

  archivo.close();
  //Ordenar listas
  lista=mergeSort(lista);
  lista2=mergeSort(lista2);

  //Lista Ascendente a Sorted Data
  ofstream archivo2;
    int i;
    archivo2.open("SortedData.txt",ios::out);
    if(archivo2.fail()){
    cout<<"couldn't load file";
    exit(1);
    }
    for(i=0; i<n;i++){ 
      archivo2<<lista -> x.todo<<endl;
      lista=lista->sig;
    }
    archivo2.close();

  //Lista Descendiente a la Consola
  reverseLista(lista2);
  imprimeLista(lista2);

  //Liberar lista ligada
	struct nodo* tempborrar;
	while(lista!=NULL){
		tempborrar=lista->sig;
		delete lista;
		lista=tempborrar;
	}
  return 0;
}

