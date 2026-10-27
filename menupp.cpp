#include "menupp.h"
#include <iostream>

using namespace std;

Q::Q() {
    hd = nullptr;
    tl = nullptr;
}

Q::~Q() {
    Nd* act = hd;
    while (act != nullptr) {
        Nd* sig = act->nx;
        delete act;
        act = sig;
    }
    hd = nullptr;
    tl = nullptr;
}


Q::Q(const Q& other) {
    hd = nullptr; tl = nullptr;
    Nd* act = other.hd;
    while (act != nullptr) {
        this->add(act->p);
        act = act->nx;
    }
}


Q& Q::operator=(const Q& other) {
    if (this == &other) return *this;

    Nd* act = hd;
    while (act != nullptr) {
        Nd* sig = act->nx;
        delete act;
        act = sig;
    }
    hd = nullptr; tl = nullptr;

    act = other.hd;
    while (act != nullptr) {
        this->add(act->p);
        act = act->nx;
    }
    return *this;
}

bool Q::emp() {
    return hd == nullptr;
}

void Q::add(P x) {
    Nd* nvo = new Nd;   
    nvo->p = x;         
    nvo->nx = nullptr; 

    if (emp()) {
        hd = nvo;       // Si esta va Si esta vaccia, head y tail apuntan al nuevo nodo
        tl = nvo;
    } else {
        tl->nx = nvo;  
        tl = nvo;       
    }
}

P Q::pop() {
    if (emp()) {
        cout << "Error: Cola vacia.\n";
        return {-1, 0, 0, 0}; 
    }
    
    Nd* aux = hd;      
    P val = aux->p;     
    
    hd = hd->nx;        
    if (hd == nullptr) {
        tl = nullptr;   
    }
    
    delete aux;         
    return val;        
}

void Sim::cap() {
    int n;
    cout << "¿Cuantos procesos deseas ingresar?: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        P p;
        p.id = i + 1;
        cout << "\nProceso ID " << p.id << endl;
        cout << "Tiempo de Ejecución : ";
        cin >> p.te;
        cout << "Prioridad (PR): ";
        cin >> p.pr;
        p.tr = 0;

        qb.add(p);
    }
}

void Sim::fifo() {
    cout << "\nEJECUCIÓN FIFO\n" << endl;
    Q aux = qb; 
    int t = 0;  
    int s = 0;  
    int n = 0;  

    while (!aux.emp()) {
        P p = aux.pop();
        t += p.te;
        p.tr = t;
        s += p.tr;
        n++;
        cout << "P" << p.id << " ejecuto en " << p.te 
             << " ms. \tTR: " << p.tr << " ms" << endl;
    }
    if(n > 0) cout << "TR Promedio: " << (float)s / n << " ms\n";
}

void Q::sort(int op) {
    // Si la cola está vacía o tiene un solo elemento, ya está ordenada :p
    if (hd == nullptr || hd->nx == nullptr) {
        return;
    }

    bool flag;
    Nd* act;
    Nd* ult = nullptr;

    do {
        flag = false;
        act = hd;

        // Recorremos la lista hasta llegar al nodo donde terminamos la pasada anterior
        while (act->nx != ult) {
            bool swapNeeded = false;

            // Condición para SJF: Ordenar de menor a mayor tiempo de ejecución
            if (op == 1) {
                if (act->p.te > act->nx->p.te) {
                    swapNeeded = true;
                }
            }
            // Condición para Prioridad: Asumiendo que un número menor = mayor prioridad
            else if (op == 2) {
                if (act->p.pr > act->nx->p.pr) {
                    swapNeeded = true;
                }
            }

            if (swapNeeded) {
                P temp = act->p;
                act->p = act->nx->p;
                act->nx->p = temp;
                
                flag = true;
            }

            act = act->nx;
        }
        // El último nodo evaluado es el mayor, ya no necesitamos revisarlo en la siguiente iteración
        ult = act; 
        
    } while (flag);
}

void Sim::sjf() {
    cout << "\nEJECUCIÓN SJF\n";
    Q aux = qb;   
    aux.sort(1);  

    int t = 0, s = 0, n = 0;

    
    while (!aux.emp()) {
        P p = aux.pop();
        t += p.te;
        p.tr = t;
        s += p.tr;
        n++;
        cout << "P" << p.id << " ejecuto en " << p.te 
             << " ms. \tTR: " << p.tr << " ms" << endl;
    }
    if(n > 0) cout << "TR Promedio: " << (float)s / n << " ms\n";
}

void Sim::rr(int qt) {
    cout << "\n--- EJECUCIÓN ROUND ROBIN\n";
    cout << "(Quantum=" << qt << ") ---\n";
    Q qx = qb; 
    int t = 0;
    int s = 0;
    int n = 0;

    while (!qx.emp()) {
        P c = qx.pop();

        if (c.te <= qt) {
            t += c.te;
            c.tr = t;
            s += c.tr;
            n++;
            cout << "[T:" << t << "] P" << c.id << " TERMINA. \t(TR: " << c.tr << ")\n";
        } else {
            t += qt;
            c.te -= qt;
            cout << "[T:" << t << "] P" << c.id << " pausado. \t(Resta: " << c.te << ")\n";
            qx.add(c);
        }
    }
    if(n > 0) cout << "TR Promedio: " << (float)s / n << " ms\n";
}

void Sim::pri() {
    
    if (qb.emp()) {
        cout << "Error: No hay procesos en la cola.\n";
        return;
    }

    cout << "\nEJECUCIÓN POR PRIORIDAD\n";
    
    Q aux = qb;   
    aux.sort(2);  

    int t = 0;   
    int s = 0;   
    int n = 0;    

   
    while (!aux.emp()) {
        P p = aux.pop();
        
        t += p.te;   
        p.tr = t;     
        s += p.tr;    
        n++;
        
        cout << "P" << p.id << " (PR: " << p.pr << ")\t ejecuto en " << p.te 
             << " ms. \tTR: " << p.tr << " ms" << endl;
    }
    
    if (n > 0) {
        cout << "TR Promedio: " << (float)s / n << " ms\n";
    }
}