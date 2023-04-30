#include <utility>
#include <iterator>
#include <vector>

template<class Contenedor>
typename Contenedor::value_type minimo(const Contenedor& c){
    typename Contenedor::const_iterator min = c.begin();
    // auto min = c.begin();
    for(typename Contenedor::const_iterator it = c.begin(); it != c.end(); it++)
        min = (*it < *min) ? it : min;
    return *min;
}

template<class Contenedor>
typename Contenedor::value_type promedio(const Contenedor& c){
    typename Contenedor::value_type res = 0;
    typename Contenedor::size_type size = 0;

    for(typename Contenedor::const_iterator it = c.begin(); it != c.end(); it++) {
        res += *it;
        size++;
    }
    return res / size;
}

template<class Iterator>
typename Iterator::value_type minimoIter(const Iterator& desde, const Iterator& hasta){
    Iterator min = desde;

    for(Iterator it = desde; it != hasta; it++)
        min = (*it < *min) ? it : min;

    return *min;
}

template<class Iterator>
typename Iterator::value_type promedioIter(const Iterator& desde, const Iterator& hasta){
    typename Iterator::value_type res = 0;
    int size = 0;

    for(Iterator it = desde; it != hasta; it++){
        res += *it;
        size++;
    }

    return res / size;
}

template<class Contenedor>
void filtrar(Contenedor &c, const typename Contenedor::value_type& elem){
    for(typename Contenedor::iterator it = c.begin(); it != c.end();)
        it = (*it == elem) ? c.erase(it) : ++it;
}

template<class Contenedor>
bool ordenado(Contenedor &c){
    typename Contenedor::const_iterator end = --c.end();
    bool res = true;
    for(typename Contenedor::const_iterator it = c.begin(); it != end; it++){
        typename Contenedor::const_iterator next = it;
        next++;
        if (*next < *it) res = false;
    }
    return res;
}

template<class Contenedor>
std::pair<Contenedor, Contenedor> split(const Contenedor & c,
                                        const typename Contenedor::value_type& elem){
    Contenedor menores, mayores;
    for(const typename Contenedor::value_type i : c){
        if(i < elem) menores.insert(menores.end(), i);
        else mayores.insert(mayores.end(), i);
    }

    return std::make_pair(menores, mayores);
}

template <class Contenedor>
void merge(const Contenedor& c1, const Contenedor & c2, Contenedor & res){
    typename Contenedor::const_iterator it1 = c1.begin(), it2 = c2.begin();

    while(it1 != c1.end() or it2 != c2.end()){
        if(it2 == c2.end()){
            res.insert(res.end(), *it1);
            it1++;
        }
        else if(it1 == c1.end()){
            res.insert(res.end(), *it2);
            it2++;
        }
        else if(*it1 < *it2) {
            res.insert(res.end(), *it1);
            it1++;
        }
        else {
            res.insert(res.end(), *it2);
            it2++;
        }
    }
}


