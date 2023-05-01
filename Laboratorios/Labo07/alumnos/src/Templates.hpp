
template<class T>
T cuadrado(T n){
    return n * n;
}

template<class Contenedor, class Elem>
bool contiene(Contenedor c, Elem elem){
    bool res = false;
    for(Elem i : c){
        if(i == elem) res = true;
    }
    return res;
}

template<class Contenedor>
bool esPrefijo(Contenedor a, Contenedor b){
    if (a.size() >= b.size())
        return false;

    typename Contenedor::iterator it_a = a.begin(), it_b = b.begin();
    while(it_a != a.end()){
        if (*it_a != *it_b) return false;
        it_b++;
        it_a++;
    }
    return true;
}

template<class Contenedor, class Elem>
Elem maximo(Contenedor c){
    typename Contenedor::iterator max = c.begin();
    for(typename Contenedor::iterator it = c.begin(); it != c.end(); it++){
        if(*it > *max) max = it;
    }
    return *max;
}