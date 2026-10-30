#ifndef menupp_h
#define menupp_h

#include <iostream>

using namespace std;


struct P {
    int id;  
    int te;  
    int pr;  
    int tr;  
};


struct Nd {
    P p;     
    Nd* nx;  
};


class Q {

    Nd* hd;  
    Nd* tl;  

public:
 Q();                             
    ~Q();                           
    Q(const Q& other);               // Constructor de copia
    Q& operator=(const Q& other);    // Operador de asignación
    
    int qtm();
    void sort(int op);
    void add(P x);                  
    P pop();                         
    bool emp();                      //Cola vacia?
};


class Sim {
private:
    Q qb; 

public:
    void cap();       
    void fifo();       //Algoritmo FIFO
    void sjf();       //Algoritmo SJF
    void rr();  //Algoritmo Round Robin
    void pri();       //Algoritmo Prioridad
};

#endif