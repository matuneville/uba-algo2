using namespace std;
#include "Diccionario.hpp"

template<class T>
class Multiconjunto{
private:
    Diccionario<T, int> _multiset;
public:
    Multiconjunto();
    void agregar(T x);
    int ocurrencias(T x);
};

template<class T>
Multiconjunto<T>::Multiconjunto(): _multiset(Diccionario<T, int>()) {}

template<class T>
void Multiconjunto<T>::agregar(T x) {
    if(this->_multiset.def(x))
        this->_multiset.definir(x, this->_multiset.obtener(x) + 1);
    else
        this->_multiset.definir(x, 1);
}

template<class T>
int Multiconjunto<T>::ocurrencias(T x) {
    if (not(this->_multiset.def(x))) return 0;
    else
        return (this->_multiset.obtener(x));
}