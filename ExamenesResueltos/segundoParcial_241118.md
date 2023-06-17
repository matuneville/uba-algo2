## Ejercicio 1

### Item A

`MultAr` se representa con: 
```
  tupla <
        vehiculosConInfo:   diccTrie(vehiculo, tupla<
                                                    localidad: itLoc,
                                                    multas: multiconjLineal(ItMulta: itMulticonj)
                                                    >),
        localidadConInfo:   diccTrie(localidad, tupla<
                                                     vehiculos: conjTrie(vehiculo),
                                                     camaras: conjLineal(camara),
                                                     multas: multiconj(multa)
                                                     >),
        camarasConInfo:     diccLog(camara, locIt: itDicc)
        >
```

Cómo se hacen los 4 puntos que pide:
1. Accedo en O(|l|) a la localidad en _localidadConInfo_ y alli tengo toda la info pedida
2. Busco en O(1) al vehiculo en _vehiculoConInfo_ y allí tengo lo pedido
3. Accedo al vehiculo en O(1) en _vehiculosConInfo_ e itero sobre _multas_ en O(m), accediendo a cada una de sus multas con el iterador dado y usando la operacion eliminarSiguiente para eliminar las multas en _localidadConInfo_, y tambien lo hago en las de _vehiculosConInfo_ en O(m)
4. Con O(log n) accedo a _camarasConInfo_ y el iterador me lleva a su respectiva localidad en O(1), allí agrego la multa en _multas_ en O(1) y tambien genero un iterador a esta multa agregada al multiconj llamado _itMulta_. Con el vehiculo dado accedo en O(1) a _vehiculoConInfo_ y allí agrego el iterador _itMulta_ a las multas del vehiculo en O(1). Tambien accedo a la localidad del vehiculo y la agrego, solo si la localidad en la que fue multado el vehiculo es distinta a la localidad a la que pertenece. Esto tambien es O(1)

### Item B

```c
iABONAR(MultAr mAr, vehiculo v){
    multasDeV = significado(mAr.vehiculosConInfo, v); // significado devuelve referencia

    itM = crearIt(multasDeV);
    while(haySiguiente(itM)){ // O(m)
        eliminarSiguiente(siguiente(itM)); // aca estoy borrando las multas de localidadConInfo
        eliminarSiguiente(itM); // y aca borro la multa de vehiculosConInfo, su iterador en realidad
        avanzar(itM);
    }
}   // complejidad final O(m)
```

## Ejercicio 2

```cpp
void sortFalabella(int vector<pair<string, float>> v){
    diccTrie<string, vector<float>> trie = {};
    // creo el diccionario en trie y pongo los precios en cada vector para cada nombre

    for(int i = 0; i < v.size(); i++){ // O(n)
        if(!definido(trie, v[i].first)){ // O(|k|), palabra acotada -> O(1)
            definir(trie, v[i].first, {v[i].second}); // O(1)
        }
        else
            significado(trie, v[i].first).push_back(v[i].second); // O(1)
    } // complex total O(n)

    vector<list<pair<string, float>>> buckets(n); // vector tamaño n
    // pues voy a poner las tuplas en buckets segun el largo de sus vectores, es decir
    // segun la cantidad de ventas, que, como mucho, esta acotada por n

    for(trie.begin() itDicc : trie.end()){ // O(n)
        itList = siguienteSignificado(itDicc).begin()
        while (siguienteSignificado(itDicc).size() > 0){ // agrego tuplas de nombre y venta
            buckets[siguienteSignificado(itDicc).size()].agregarAtras(<siguienteClave(itList), siguienteSignificado(itList)>);
            avanzar(itList);
        }
    }

    for(int i = 0; i < buckets.size(); i++){ // O(n)
        if(buckets[i].length > 0)
            radixSort_porVentaEnTuplas(buckets[i]); // lo ordena segun tupla.second
    }       // el radix es O(n) pues la cantidad de cifras de cada venta esta acotada

    v = vectorDeListas_a_vector(buckets); // O(n), reformo el vector y listo
    // el algoritmo lo hace linealmente de derecha a izquierda, para que sea decreciente segun cantidad de ventas
    // de cada persona, y si dos personas compraron lo mismo, por el radix van a estar mergeadas
}
```

## Ejercicio 3

```cpp
struct Nodo{
    bool valor;
    Nodo* izq;
    Nodo* der;
}

void cuentoTruesYFalses(Nodo* raiz, int& trues, int& falses){
    if(nil?(raiz->izq) and nil?(raiz->der))
        return true;    // caso base, es hoja
    else
        if(nil?(raiz->izq)){ 
            if(*(raiz->der) == true) // caso solo hijo derecho
                trues++;
            cuentoTruesYFalses(raiz->der, trues, falses);
        }
        else if(nil?(raiz->der)){
            if(*(raiz->izq) == false) // caso solo hijo izquierdo
                falses++;
            cuentoTruesYFalses(raiz->izq, trues, falses);
        }
        else{ // caso 2 hijos
            if(*(raiz->izq) == false)
                falses++;
            if(*(raiz->der) == true)
                trues++;
            cuentoTruesYFalses(raiz->der, trues, falses);
            cuentoTruesYFalses(raiz->izq, trues, falses);
        }
}

bool estaEquilibrado(Nodo* raiz){
    int falseEnIzq = 0;
    int trueEnDer = 0;

    if (nil?(raiz)) return true;
    else if(nil?(raiz->izq) and nil?(raiz->der)) return true;

    cuentoTruesYFalses(raiz->izq, trueEnDer, falseEnIzq);

    if(abs(falseEnIzq - trueEnDer) <= 1) return true;
    return false;
}
```

### Complejidad:
$T(n) = 2*T(n/2) + O(1)$  
$Sea\ a = 2,\ c = 2,\ f(n) = 1,\ \epsilon > 0, \text{cumple el Caso 1 del Teorema Maestro}$  
$f(n) = 1 \in O(n^{log_2(2)-\epsilon}) = O(n^{1-\epsilon}),\ si\ \epsilon = 1$  
$\rightarrow O(n^{1-\epsilon}) = O(n^{0}) = O(1),\ y\ f(n)=1 \in O(1)$  
$\therefore T(n) = Θ(n^{log_2 2}) = Θ(n^1) = Θ(n)$
