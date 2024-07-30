#include <iostream>
#include <string.h>
using namespace std;

struct texto{
  int dia;
  int mes;
  string hms;
  int h,m,s;
  float horarioTotal;
  int ipnum, ipnum1, ipnum2, ipnum3; 
  string smes;
  string ip; //ip como string
  string puerto;
  string error;
  string todo;
};

struct nodo{
  struct texto x;
  struct nodo *sig ;
  struct nodo *prev;
};


int cambioMes(string _mes){
  if (_mes == "Jan")
    return 1;
  if (_mes == "Feb")
    return 2;
  if (_mes == "Mar")
    return 3;
  if (_mes == "Apr")
    return 4;
  if (_mes == "May")
    return 5;
  if (_mes == "Jun")
    return 6;
  if (_mes == "Jul")
    return 7;
  if (_mes == "Aug")
    return 8;
  if (_mes == "Sep")
    return 9;
  if (_mes == "Oct")
    return 10;
  if (_mes == "Nov")
    return 11;
  if (_mes == "Dic")
    return 12;
  return 0;
}

string backToNums(int cad){
  if (cad < 10)
    return "0" + to_string(cad); //para que se muestre como 01,02,...
  else
    return to_string(cad);
}//finbacktonums



struct nodo *split(struct nodo *head);

struct nodo *merge(struct nodo *first, struct nodo *second){
    // Si las listas están vacías
    if (!first)
        return second;
    if (!second)
        return first;


    // Comparaciones
    if (first->x.ipnum < second->x.ipnum){
        first->sig = merge(first->sig,second);
        first->sig->prev = first;
        first->prev = NULL;
        return first;
    }
//Apoyo/Referencia: https://www.geeksforgeeks.org/merge-sort-for-linked-list/
    if (first->x.ipnum == second->x.ipnum){ //si el ip es igual
        if(first->x.ipnum1 < second->x.ipnum1){
          first->sig = merge(first->sig,second);
          first->sig->prev = first;
          first->prev = NULL;
          return first;
        }
        if(first->x.ipnum1 == second->x.ipnum1){ //si el mes es igual
          if(first->x.ipnum2 < second->x.ipnum2){
            first->sig = merge(first->sig,second);
            first->sig->prev = first;
            first->prev = NULL;
            return first;
          }
          if(first->x.ipnum2 == second->x.ipnum2){ //ESTO ESTA DE MAS(?)
            if(first->x.ipnum3 < second->x.ipnum3){
              first->sig = merge(first->sig,second);
              first->sig->prev = first;
              first->prev = NULL;
              return first;
            }
            if(first->x.ipnum3 == second->x.ipnum3){
              if(first->x.mes < second->x.mes){
                first->sig = merge(first->sig,second);
                first->sig->prev = first;
                first->prev = NULL;
                return first;
              }
              if(first->x.mes == second->x.mes){
                if(first->x.dia < second->x.dia){
                  first->sig = merge(first->sig,second);
                  first->sig->prev = first;
                  first->prev = NULL;
                  return first;
                }
                if(first->x.dia == second->x.dia){
                  if(first->x.horarioTotal < second-> x.horarioTotal){
                    first->sig = merge(first->sig,second);
                    first->sig->prev = first;
                    first->prev = NULL;
                    return first;
                  }
                  if(first->x.horarioTotal == second->x.horarioTotal){
                    int res;
                    string s1, s2;
                    s1 = first->x.error;
                    s2 = second->x.error;
                    res = strcmp(s1.c_str(),s2.c_str());

                    if(res > 1){
                      first->sig = merge(first->sig,second);
                      first->sig->prev = first;
                      first->prev = NULL;
                      return first;
                  }
                  else{
                    second->sig = merge(first,second->sig);
                    second->sig->prev = second;
                    second->prev = NULL;
                    return second;
                  }
                  }
                  else{ //mes
                  second->sig = merge(first,second->sig);
                  second->sig->prev = second;
                  second->prev = NULL;
                  return second;
                }
                }
                else{ //mes
                  second->sig = merge(first,second->sig);
                  second->sig->prev = second;
                  second->prev = NULL;
                  return second;
                }
              }
              else{ //ipnum3
                second->sig = merge(first,second->sig);
                second->sig->prev = second;
                second->prev = NULL;
                return second;
              }
            }
            else{ //ipnum2
              second->sig = merge(first,second->sig);
              second->sig->prev = second;
              second->prev = NULL;
              return second;
            }

          }
          else{
            second->sig = merge(first,second->sig);
            second->sig->prev = second;
            second->prev = NULL;
            return second;
          }
        }
        else{
          second->sig = merge(first,second->sig);
          second->sig->prev = second;
          second->prev = NULL;
          return second;
        }
    }

    else{ //comparar ip
        second->sig = merge(first,second->sig);
        second->sig->prev = second;
        second->prev = NULL;
        return second;
    }

}

//Merge -- O(n log n)
struct nodo *mergeSort(struct nodo *head){
    if (!head || !head->sig)
        return head;
    nodo *second = split(head);

    head = mergeSort(head);
    second = mergeSort(second);

    return merge(head,second);
}
struct nodo *split(struct nodo *head)
{
    struct nodo *fast = head,*slow = head;
    while (fast->sig && fast->sig->sig)
    {
        fast = fast->sig->sig;
        slow = slow->sig;
    }
    struct nodo *temp = slow->sig;
    slow->sig = NULL;
    return temp;
}
