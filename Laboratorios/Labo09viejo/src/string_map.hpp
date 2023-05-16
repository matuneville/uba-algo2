template <typename T>
string_map<T>::string_map(): _raiz(nullptr), _size(0){}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    if (_raiz != nullptr){
        destructorRecursivo(_raiz);
    }
    if (not d.empty()){
        copiaRecursivo(_raiz, d._raiz);
    }
    _size = d.size();
}

template <typename T>
void string_map<T>::copiaRecursivo(Nodo* &n, const Nodo* copy){
    if (copy != nullptr) {
        n = new Nodo(copy->definicion);
        for (int i = 0; i < 256; ++i) {
            copiaRecursivo(n->siguientes[i], copy->siguientes[i]);
        }
    }
    else
        n = nullptr;
}

template <typename T>
string_map<T>::~string_map(){
    if (_raiz != nullptr){
        destructorRecursivo(_raiz);
    }
}

template <typename T>
void string_map<T>::destructorRecursivo(Nodo* &n){
    if (n != nullptr) {
        for (int i = 0; i < 256; ++i) {
            destructorRecursivo(n->siguientes[i]);
        }
        delete n->definicion;
        n->definicion = nullptr;
        delete n;
        n = nullptr;
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if (_raiz != nullptr){
        Nodo *actual = _raiz;
        for (string::const_iterator it = clave.begin(); it < clave.end(); it++){
            actual = buscoNodo(actual->siguientes, *it);
            if (actual == nullptr)
                return 0;
        }
        return (actual->definicion != nullptr) ? 1 : 0;
    }
    else
        return 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo *actual = _raiz;
    for (string::const_iterator it = clave.begin(); it < clave.end(); it++)
        actual = buscoNodo(actual->siguientes, *it);
    return *(actual->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo *actual = _raiz;
    for (string::const_iterator it = clave.begin(); it < clave.end(); it++)
        actual = buscoNodo(actual->siguientes, *it);
    return *(actual->definicion);
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& claveValor){
    string::const_iterator it = (claveValor.first).begin();
    if (_raiz == nullptr)
        _raiz = new Nodo(nullptr);

    Nodo *actual = _raiz;
    for (; it < (claveValor.first).end(); it++){
        Nodo* busco = buscoNodo(actual->siguientes, *it);
        if(busco == nullptr){
            Nodo* nuevoNodo = new Nodo(nullptr);
            actual->siguientes[int(*it)] = nuevoNodo;
            actual = nuevoNodo;
        }
        else
            actual = busco;
    }
    T* def = new T(claveValor.second);
    actual->definicion = def;
    _size++;
}


/*template <typename T>
void string_map<T>::erase(const string& clave) {
    vector<Nodo*> aBorrar;
    Nodo* actual = _raiz;
    for (char letra : clave){
        Nodo* busco = buscoNodo(actual->siguientes, letra);
        aBorrar.push_back(busco);
        actual = busco;
    }
    // itero al reves
    typename vector<Nodo*>::reverse_iterator letraIt = aBorrar.rbegin();
    for (; letraIt != aBorrar.rend(); letraIt++){
        for (int i = aBorrar.size()-1; i != -1; i--){
        // si la letra apunta a otra letra que no sea la que le sigue, se corta y no se borra
            if ((*letraIt)->siguientes[i] != nullptr){
                if (letraIt == aBorrar.rbegin()) {
                    (*letraIt)->definicion == nullptr;
                    return;
                }
                else if ((*letraIt)->siguientes[i] != (*letraIt--))
                    return;
            }
        }
        delete (*letraIt)->definicion;
        (*letraIt)->definicion = nullptr;
        delete (*letraIt);
        (*letraIt) = nullptr;
    }
}*/
template <typename T>
void string_map<T>::erase(const string& clave) {
    vector<Nodo**> aBorrar;
    Nodo* actual = _raiz;
    for (char letra : clave){
        Nodo* busco = buscoNodo(actual->siguientes, letra);
        Nodo** pBusco = &busco;
        aBorrar.push_back(pBusco);
        actual = busco;
    }
    // itero al reves
    typename vector<Nodo**>::reverse_iterator letraIt = aBorrar.rbegin();
    for (; letraIt != aBorrar.rend(); letraIt++){
        for (int i = 0; i != 256; i++){
            // si la letra apunta a otra letra que no sea la que le sigue, se corta y no se borra
            if ((**letraIt)->siguientes[i] != nullptr){
                if (letraIt == aBorrar.rbegin()) {
                    (**letraIt)->definicion == nullptr;
                    return;
                }
                else if ((**letraIt)->siguientes[i] != (**letraIt--))
                    return;
            }
        }
        delete (**letraIt)->definicion;
        (**letraIt)->definicion = nullptr;
        delete (**letraIt);
        (**letraIt) = nullptr;
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return (_raiz == nullptr);
}

// ###### auxiliares ######
template<typename T>
typename string_map<T>::Nodo* string_map<T>::buscoNodo(const vector<Nodo*> &v, const char &c) const{
    for(int i = 0; i < 256; i++){
        if (char(i) == c)
            return v[i];
    }
    return nullptr;
}
