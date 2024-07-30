/*Descripcion: Aplicacion que ordena un conjunto de datos en un archivo txt y busca e imprime en un rango de fechas los datos 
Autores: Jose Jezarel Sanchez Mijares A01735226 / Christian Flores Alberto A01734997
Fecha: 26/09/2021*/
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include<string>
using namespace std;

class Texto{
private:
    vector<string>texto2;
    vector<double>texto1;
    string oldarchivo,newarchivo;
    string dayb,monthb,dayf,monthf;

public:
    Texto();
    Texto(string,vector<string>& ,string,vector<double>&,string,string,string,string);
    void lectura();
    void escritura();
    void cambio();
    void burbuja();
    void busqSecuencial();
};

Texto::Texto(string _oldarchivo,vector<string> &_texto2,string _newarchivo,vector<double> &_texto1,string dia_inicio,string mes_inicio,string diaf,string mesf){
  texto2=_texto2;
  texto1=_texto1;
  oldarchivo=_oldarchivo;
  newarchivo=_newarchivo;
  dayb=dia_inicio;
  monthb=mes_inicio;
  dayf=diaf;
  monthf=mesf;
}
//Lee el archivo
void Texto::lectura(){
  int n=0;
  string texto;  
  ifstream archivo;
  archivo.open(oldarchivo,ios::in);
  if(archivo.fail()){
    cout<<"couldn't load file";
    exit(1);
    }
    while(!archivo.eof()){
        getline(archivo,texto);
        texto2.push_back(texto);
    }
   archivo.close();
}

//Cambia las variables
void Texto::cambio(){
  int i,n=texto2.size();
  string a,b,c,d,e;
  double aa,bb,cc,dd,ee,esp=0;
  double Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dic,total;
  for(i=0;i<n;i++){
    a=texto2[i].substr(0,3);
    b=texto2[i].substr(4,2);
    c=texto2[i].substr(7,2);
    d=texto2[i].substr(10,2);
    e=texto2[i].substr(13,2);
    istringstream(b)>>bb;
    istringstream(c)>>cc;
    istringstream(d)>>dd;
    istringstream(e)>>ee;
    double A31=383990.986,A30=37199.986, A28=34799.986;
    double dia=1200,hora=50,min=0.833,seg=0.013;
    
    if(a=="Jan"){
      Jan=0;
      total=(Jan)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }
    if(a=="Feb"){
      Feb=A31;
      total=(Feb)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }
    if(a=="Mar"){
      Mar=A28+A31;
      total=(Mar)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
      }
    if(a=="Apr"){
      Apr=((2*A31)+A28);
      total=(Apr)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }
    if(a=="May"){
      May=((2*A31)+A28+A30);
      total=(May)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }

    if(a=="Jun"){
      Jun=((3*A31)+A28+A30);
      total=(Jun)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }

    if(a=="Jul"){
      Jul=((3*A31)+A28+(2*A30));
      total=(Jul)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }
    if(a=="Aug"){
      Aug=((4*A31)+A28+(2*A30));
      total=(Aug)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }
    if(a=="Sep"){
      Sep= ((5*A31)+A28+(2*A30));
      total=(Sep)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }
    if(a=="Oct"){
      Oct=((5*A31)+A28+(3*A30));
      total=(Oct)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }
    if(a=="Nov"){
      Nov=((6*A31)+A28+(3*A30));
      total=(Nov)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }

    if(a=="Dic"){
      Dic=((6*A31)+A28+(4*A30));
      total=(Dic)+(bb*dia)+(cc*hora)+(dd*min)+(ee*seg);
      texto1.push_back(total);
    }
  }
}

//Metodo burbuja
void Texto::burbuja(){
  bool band=true;
  double a,b,aux,cont=0,cont1=0,cont2=0;
  string _aux;
    for (a=0;a<texto2.size()-1 && band;a++){
      band=false;
      for (b=0;b<texto2.size()-a-1;b++){ //O(n2)
      cont++;////
        if (texto1[b]>texto1[b+1]){
          _aux=texto2[b];
          texto2[b]=texto2[b+1];
          texto2[b+1]=_aux;
          aux=texto1[b];
          texto1[b]=texto1[b+1];
          texto1[b+1]=aux;
          band=true;
         }
      } 
   } 
}  

//Registra datos en archivo
void Texto::escritura(){
    ofstream archivo;
    int i,n=texto2.size();
    archivo.open(newarchivo,ios::out);
    if(archivo.fail()){
    cout<<"couldn't load file";
    exit(1);
    }
    for(i=0; i<n;i++)
        archivo<<texto2[i]<<endl;
    archivo.close();
}

//Busqueda Secuencial
void Texto::busqSecuencial(){
    int p=0,i,n1=0;
    
    //Meses inicio
    if (monthb=="1"||monthb=="01")
      monthb="Jan";
    if (monthb=="2"||monthb=="02")
      monthb="Feb";
    if (monthb=="3"||monthb=="03")
      monthb="Mar";
    if (monthb=="4"||monthb=="04")
      monthb="Apr";
    if (monthb=="5"||monthb=="05")
      monthb="May";
    if (monthb=="6"||monthb=="06")
      monthb="Jun";
    if (monthb=="7"||monthb=="07")
      monthb="Jul";
    if (monthb=="8"||monthb=="08")
      monthb="Aug";
    if (monthb=="9"||monthb=="09")
      monthb="Sep";   
    if (monthb=="10")
      monthb="Oct";
    if (monthb=="11")
      monthb="Nov";
    if (monthb=="12")
      monthb="Dic";
    //Meses final
    if (monthf=="1"||monthf=="01")
      monthf="Jan";
    if (monthf=="2"||monthf=="02")
      monthf="Feb";
    if (monthf=="3"||monthf=="03")
      monthf="Mar";   
    if (monthf=="4"||monthf=="04")
      monthf="Apr";
    if (monthf=="5"||monthf=="05")
      monthf="May";
    if (monthf=="6"||monthf=="06")
      monthf="Jun";
    if (monthf=="7"||monthf=="07")
      monthf="Jul";
    if (monthf=="8"||monthf=="08")
      monthf="Aug";
    if (monthf=="9"||monthf=="09")
      monthf="Sep";
    if (monthf=="10")
      monthf="Oct";   
    if (monthf=="11")
      monthf="Nov";
    if (monthf=="12")
      monthf="Dec";

    for(i=0;i<texto2.size();i++){
        p++;
        if (texto2[i].substr(4,2)==dayb && texto2[i].substr(0,3)==monthb)
            i=texto2.size();
    }
    if(p==texto2.size()){ 
      for(p=0;p<texto2.size();p++){
        cout<<texto2[p]<<endl;
        n1=p;
        if (texto2[p].substr(4,2)==dayf&& texto2[p].substr(0,3)==monthf)
            p=texto2.size();
        }
        if(n1==texto2.size())
          cout<<-1;
        }
    else{
      for(p=p-1;p<texto2.size();p++){
        cout<<texto2[p]<<endl;
        n1=p;
        if (texto2[p].substr(4,2)==dayf&& texto2[p].substr(0,3)==monthf)
            p=texto2.size();
      }
    }
}

int main() {
   
    string dia_inicio,dia_fin;
    string mesi,mesf;
    int mi,mf,di,df;
    getline(cin,mesi);
    getline(cin,dia_inicio);
    getline(cin,mesf);
    getline(cin,dia_fin);
    
    //Excepciones
    try{
      istringstream(mesi)>>mi;
      istringstream(mesf)>>mf;
      istringstream(dia_inicio)>>di;
      istringstream(dia_fin)>>df;
      if(mi>mf)
        throw "La fecha es incorrecta";
      if(mi==mf && di>df)
        throw "La fecha es incorrecta";
      if(mi>12 ||mi<1||mf>12 ||mf<1)
        throw "La fecha es incorrecta";
      if(di>31 ||di<1||df>31 ||df<1)
        throw "La fecha es incorrecta";
      if(di>28 && mi==2) 
        throw "La fecha es incorrecta";
      if(df>28 && mf==2)
        throw "La fecha es incorrecta";
      if(di==31&& mi==4)
        throw "La fecha es incorrecta";      
      if (di==31 && mi==6)       
        throw "La fecha es incorrecta";
      if (di==31 && mi==9)  
        throw "La fecha es incorrecta";      
      if (di==31 && mi==11)
        throw "La fecha es incorrecta";
      if (df==31 && mf==4)
        throw "La fecha es incorrecta";
      if (df==31 && mf==6)
        throw "La fecha es incorrecta";
      if (df==31 && mf==9)
        throw "La fecha es incorrecta";
      if (df==31 && mf==11)
        throw "La fecha es incorrecta";
          vector <string>texto;
      vector <double> texto2;
      Texto obj1=Texto("bitacora.txt",texto,"sorted.txt",texto2,dia_inicio,mesi,dia_fin,mesf); 
      obj1.lectura();
      obj1.cambio();
      obj1.burbuja();
      obj1.escritura();
      obj1.busqSecuencial();
      }
    catch(const char *e){
      cout<< "Error: "<<e<<endl;
    }
    return 0;
}