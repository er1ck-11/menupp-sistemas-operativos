#include <iostream>
#include "menupp.h" 
using namespace std;

int main() {
    Sim s;     
    int op;    
    int qt;    

    do {
        cout << "\n--- PLANIFICADOR DE PROCESOS ---\n";
        cout << "1. Captura procesos\n";
        cout << "2. FIFO\n";
        cout << "3. SJF\n";
        cout << "4. Round Robin\n";
        cout << "5. Prioridad\n";
        cout << "6. Salir\n";
        cout << "Opción: ";
        cin >> op;

        switch(op) {
            case 1:
                s.cap();
                break;
            case 2:
                s.fifo();
                break;
            case 3:
                s.sjf();
                break;
            case 4:
                cout << "Ingresa el Quantum: ";
                cin >> qt;
                s.rr(qt);
                break;
            case 5:
                s.pri();
                break;
            case 6:
                cout << "Adios :)\n";
                break;
            default:
                cout << "Opción invalida.\n";
        }
    } while (op != 6);

    return 0;
}