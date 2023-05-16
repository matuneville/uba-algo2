template <typename T>
string_map<T>::string_map(): _raiz(nullptr), _size(0){}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
}

template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
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
    // COMPLETAR
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& claveValor){
    Nodo *actual = _raiz;
    string::const_iterator it = (claveValor.first).begin();
    if (_raiz == nullptr) {
        actual = Nodo(nullptr);
        it++;
    }
    for (; it < (claveValor.first).end(); it++){
        actual = buscoNodo(actual->siguientes, *it);
        if(actual == nullptr){
            Nodo* nuevoNodo = Nodo(nullptr);
            actual = nuevoNodo;
        }
    }
   actual->definicion = &claveValor.second;
    _size++;
}


template <typename T>
void string_map<T>::erase(const string& clave) {

}

template <typename T>
int string_map<T>::size() const{
    // COMPLETAR
}

template <typename T>
bool string_map<T>::empty() const{
    // COMPLETAR
}

// ###### auxiliares ######
template<typename T>
typename string_map<T>::Nodo* string_map<T>::buscoNodo(vector<Nodo*> &v, const char &c){
    for(int i = 0; i < 256; i++){
        if (char(i) == c)
            return v[i];
    }
    return nullptr;
}
