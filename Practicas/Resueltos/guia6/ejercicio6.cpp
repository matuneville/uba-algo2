#include <iostream>
using namespace std;

struct Nodo{
    int valor;
    Nodo* izq;
    Nodo* der;
};

int maxDistancia(Nodo* raiz){
    if(raiz->izq == nullptr and raiz->der == nullptr)
        return 1;
    
    else if(raiz->izq == nullptr)
        return 1+maxDistancia(raiz->der);
    
    else if(raiz->der == nullptr)
        return 1+maxDistancia(raiz->izq);

    else
        return max(1+maxDistancia(raiz->der), 1+maxDistancia(raiz->izq));
}

