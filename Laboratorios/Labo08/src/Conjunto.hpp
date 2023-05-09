
template <class T>
Conjunto<T>::Conjunto() {
    this->_raiz = NULL;
}

template <class T>
Conjunto<T>::~Conjunto() {
    destruirRecursivo(this->_raiz);
    this->_raiz = nullptr;
}

template <class T>
void Conjunto<T>::destruirRecursivo(Conjunto<T>::Nodo* nodo) {
    if (nodo != nullptr) {
        destruirRecursivo(nodo->der);
        destruirRecursivo(nodo->izq);
        delete nodo;
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {

    Nodo* actual = this->_raiz;
    if (actual == nullptr) return false;

    while(actual != nullptr){
        if (actual->valor == clave) return true;
        else
            actual = (clave < actual->valor) ?
                    actual->izq : actual->der;
    }

    return actual != nullptr;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {

    if (not pertenece(clave)) {

        Nodo *nuevoNodo = new Nodo(clave);
        Nodo* actual = this->_raiz;

        // caso arbol vacio
        if (actual == nullptr) {
            this->_raiz = nuevoNodo;
            return;
        }

        while (true) {
            // veo derecha
            if (actual->valor < clave) {
                if (actual->der == nullptr) {
                    actual->der = nuevoNodo;
                    break;
                }
                else {
                    actual = actual->der;
                }
            }
            // veo izquierda
            else {
                if (actual->izq == nullptr) {
                    actual->izq = nuevoNodo;
                    break;
                }
                else {
                    actual = actual->izq;
                }
            }
        }
    }
}


template <class T>
void Conjunto<T>::remover(const T& clave) {

    // caso eliminar raiz
    if (_raiz->valor == clave){
        if(_raiz->der == nullptr and _raiz->izq == nullptr) {
            delete _raiz;
            _raiz = nullptr;
        }
        else if(_raiz->der == nullptr){
            _raiz = _raiz->izq;
        }
        else if(_raiz->izq == nullptr){
            _raiz = _raiz->der;
        }
        else {
            Nodo* predecesor = _raiz->izq;
            while (predecesor->der != nullptr) {
                predecesor = predecesor->der;
            }
            predecesor->der = _raiz->der;
            _raiz = _raiz->izq;
        }
    }

    else{   // Busco al nodo a eliminar
        Nodo* actual = this->_raiz;
        bool estaEnDerecha = false;
        while(true){
            if(actual->der != nullptr and actual->der->valor == clave){
                estaEnDerecha = true;
                break;
            }
            else if(actual->izq != nullptr and actual->izq->valor == clave){
                break;
            }
            else if(actual->valor > clave){
                actual = actual->izq;
            }
            else{
                actual = actual->der;
            }
        }

        if(estaEnDerecha){
            // caso 0 hijos
            if(actual->der->der == nullptr and actual->der->izq == nullptr){
                delete actual->der;
                actual->der = nullptr;
            }
            // caso 1 hijos
            else if(actual->der->der == nullptr or actual->der->izq == nullptr){
                Nodo* temp = nullptr;
                if(actual->der->der == nullptr)
                    temp = actual->der->izq;
                else
                    temp = actual->der->der;
                delete actual->der;
                actual->der = temp;
            }
            // caso 2 hijos
            else{
                Nodo* sucesor = actual->der->der;
                while(sucesor->izq != nullptr){
                    sucesor = sucesor->izq;
                }
                sucesor->izq = actual->der->izq;
                Nodo* temp = actual->der->der;
                delete actual->der;
                actual->der = temp;
            }
        }
        else{
            // caso 0 hijos
            if(actual->izq->der == nullptr and actual->izq->izq == nullptr){
                delete actual->izq;
                actual->izq = nullptr;
            }
            // caso 1 hijos
            else if(actual->izq->der == nullptr or actual->izq->izq == nullptr){
                Nodo* temp = nullptr;
                if(actual->izq->der == nullptr)
                    temp = actual->izq->izq;
                else
                    temp = actual->izq->der;
                delete actual->izq;
                actual->izq = temp;
            }
            // caso 2 hijos
            else{
                Nodo* sucesor = actual->izq->izq;
                while(sucesor->der != nullptr){
                    sucesor = sucesor->der;
                }
                sucesor->der = actual->izq->der;
                Nodo* temp = actual->izq->izq;
                delete actual->izq;
                actual->izq = temp;
            }

        }
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* actual = this->_raiz, *sucesor = nullptr;

    while (actual != nullptr) {
        if (actual->valor > clave) {
            sucesor = actual;
            actual = actual->izq;
        }
        else {
            actual = actual->der;
        }
    }

    return (sucesor->valor);
}

// Asumo al menos 1 elemento
template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual = this->_raiz;
    while(actual->izq != nullptr){
        actual = actual->izq;
    }
    return actual->valor;
}

// Asumo al menos 1 elemento
template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual = this->_raiz;
    while(actual->der != nullptr){
        actual = actual->der;
    }
    return actual->valor;
}


template <class T>
unsigned int Conjunto<T>::cardinal() const {

    return cardinalAux(this->_raiz);
}

// AUXILIAR RECURSIVA PARA CARDINAL
template <class T>
unsigned int Conjunto<T>::cardinalAux(const Conjunto<T>::Nodo *n) const{
    if (n != nullptr)
        return 1 + cardinalAux(n->izq) + cardinalAux(n->der);

    else return 0;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

