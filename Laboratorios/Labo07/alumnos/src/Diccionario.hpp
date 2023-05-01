using namespace std;

template<class Clave, class Valor>
class Diccionario{
private:
    struct Asociacion{
        Asociacion(Clave k, Valor v); // constructor key-value
        Clave _clave;
        Valor _valor;
    };
    vector<Asociacion> _asociaciones;
public:
    Diccionario(); // contructor diccionario vacio
    void definir(Clave k, Valor v);
    bool def(Clave k) const;
    Valor obtener(Clave k) const;
};

template<class Clave, class Valor>
Diccionario<Clave, Valor>::Asociacion::Asociacion(Clave k, Valor v): _clave(k), _valor(v){}

template<class Clave, class Valor>
Diccionario<Clave, Valor>::Diccionario(): _asociaciones({}){}

template<class Clave, class Valor>
void Diccionario<Clave, Valor>::definir(Clave k, Valor v) {
    for(Asociacion& elem : this->_asociaciones){ // con referencia para que lo modifique
        if (elem._clave == k){
            elem._valor = v;
            return;
        }
    }
    this->_asociaciones.push_back(Asociacion(k, v));
}

template<class Clave, class Valor>
bool Diccionario<Clave, Valor>::def(Clave k) const{
    for(const Asociacion elem : this->_asociaciones){
        if (elem._clave == k) return true;
    }
    return false;
}

template<class Clave, class Valor>
Valor Diccionario<Clave, Valor>::obtener(Clave k) const {
    for(const Asociacion elem : this->_asociaciones)
        if (elem._clave == k)
            return elem._valor;

    return NULL;
}
