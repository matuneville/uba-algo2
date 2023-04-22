#include "Lista.h"
#include <cassert>

Lista::Lista() : prim(nullptr) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    // elimino todos los nodos
    Nodo* actual = this->prim;
    while (actual != nullptr){
        Nodo* sgte = actual->next;
        delete actual;
        actual = sgte;
    }
    this->prim = nullptr;
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // elimino todos los nodos
    Nodo* actual = this->prim;
    while (actual != nullptr){
        Nodo* sgte = actual->next;
        delete actual;
        actual = sgte;
    }
    this->prim = nullptr;

    Nodo* actualCopy = aCopiar.prim;
    while(actualCopy != nullptr) {
        agregarAtras(actualCopy->data);
        actualCopy = actualCopy->next;
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    if(this->prim == nullptr)
        this->prim = new Nodo(nullptr, elem, nullptr);
    else{
        this->prim = new Nodo(nullptr, elem, this->prim);
        (this->prim->next)->prev = this->prim;
    }
}

void Lista::agregarAtras(const int& elem) {
    Nodo* actual = this->prim;
    if(actual == nullptr)
        this->prim = new Nodo(actual, elem, nullptr);
    else {
        while (actual->next != nullptr) {
            actual = actual->next;
        }
        Nodo *nuevo = new Nodo(actual, elem, nullptr);
        actual->next = nuevo;
    }
}


void Lista::eliminar(Nat i) {
    Nodo* iesimo = this->prim;
    uint j = i;
    while(j != 0){
        iesimo = iesimo->next;
        j--;
    }
    if(i == 0) {
        if(longitud() == 1) this->prim = nullptr;
        else {
            (iesimo->next)->prev = iesimo->prev;
            this->prim = this->prim->next;
        }
    }
    else if(i == longitud()-1)
        (iesimo->prev)->next = iesimo->next;
    else{
        (iesimo->next)->prev = iesimo->prev;
        (iesimo->prev)->next = iesimo->next;
    }

    delete iesimo;
}

int Lista::longitud() const {
    int largo = 0;
    Nodo* actual = this->prim;
    while (actual != nullptr){
        actual = actual->next;
        largo++;
    }
    return largo;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* actual = this->prim;
    while(i != 0){
        actual = actual->next;
        i--;
    }
    return (actual->data);
}

int& Lista::iesimo(Nat i) {
    Nodo* actual = this->prim;
    while(i != 0){
        actual = actual->next;
        i--;
    }
    return (actual->data);
}

void Lista::mostrar(ostream& o) {
    // Completar
}
