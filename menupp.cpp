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
        hd = nvo;     
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

int Q::qtm() {
    if (emp()) return 1; 

    int s = 0; 
    int c = 0; 
    Nd* act = hd;
    
    while (act != nullptr) {
        s += act->p.te;
        c++;
        act = act->nx;
    }
    
    int q = s / c; 
    return (q > 0) ? q : 1; 
}

void Sim::fifo() {
    cout << "\nEJECUCIÓN FIFO\n" << endl;
    Q aux = qb; 
    int t = 0;  
    int s = 0;  
    int n = 0;  

    while (!aux.emp()) {

        P p = aux.pop();
        int ti = t;

        t += p.te;
        p.tr = t;
        s += p.tr;
        n++;
        
       cout << "TR" << p.id << ":" << " ejecuta " << p.te << "ms y termina \t(TR: " << p.tr << ")\n";
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

        while (act->nx != ult) {
            bool swapNeeded = false;

            //condicion para sjf ordenar de menor a mayor tiempo de ejecución
            if (op == 1) {
                if (act->p.te > act->nx->p.te) {
                    swapNeeded = true;
                }
            }
            //condición para Prioridad mayor = mayor prioridad
            else if (op == 2) {
                if (act->p.pr < act->nx->p.pr) {
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
        
        ult = act; 
        
    } while (flag);
}

void Sim::sjf() {
    cout << "\nEJECUCIÓN SJF\n" << endl;
    Q aux = qb;   
    aux.sort(1);  

    int t = 0, s = 0, n = 0;

    
    while (!aux.emp()) {
        
        P p = aux.pop();
        int ti = t;

        t += p.te;
        p.tr = t;
        s += p.tr;
        n++;

        cout << "TR" << p.id << ":"  << " ejecuta " << p.te << "ms y termina \t(TR: " << p.tr << ")\n";
    }
    if(n > 0) cout << "TR Promedio: " << (float)s / n << " ms\n";
}

void Sim::rr() {

    if (qb.emp()) return;

    Q qx = qb; 
    int qt = qx.qtm();

    cout << "\nEJECUCIÓN ROUND ROBIN\n" << endl;
    cout << "Quantum = " << qt << "\n" << endl;
    
    int t = 0;
    int s = 0;
    int n = 0;

    while (!qx.emp()) {

        P c = qx.pop();
        int ti = t;

        if (c.te <= qt) {
            t += c.te;
            c.tr = t;
            s += c.tr;
            n++;
                   cout << "TR" << c.id << ":" << " ejecuta " << c.te << "ms y termina \t(TR: " << c.tr << ")\n";

        } else {
            t += qt;
            c.te -= qt;
            // Imprime la pausa y el residuo
            cout << "TR" << c.id << ":" << " ejecuta " << qt << "ms y es pausado \t(Resta: " << c.te << ")\n";
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

    Q aux = qb;   
    int qt = aux.qtm();


    cout << "\nEJECUCIÓN POR PRIORIDAD\n" << endl;
    cout << "Quantum = " << qt << "\n" << endl;
    
    int t = 0;   
    int s = 0;   
    int n = 0;    

    aux.sort(2);

   
    while (!aux.emp()) {

        P p = aux.pop();
        int ti = t;
        
        if (p.te <= qt) {
        t += p.te;   
        p.tr = t;     
        s += p.tr;    
        n++;
        
       cout << "TR" << p.id << ":" << " (PR: " << p.pr << ") ejecuta " << p.te << "ms y termina \t(TR: " << p.tr << ")\n";
        }
        else {
            t += qt;
            p.te -= qt;
            cout << "TR" << p.id << ":" << " (PR: " << p.pr << ") ejecuta " << qt << "ms y es pausado \t(Resta: " << p.te << ")\n";

                 aux.add(p);

                 aux.sort(2);
        }
    }

    if (n > 0) {
        cout << "TR Promedio: " << (float)s / n << " ms\n";
    }
}