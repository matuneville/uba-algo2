## Ejercicio 1

```
tupla <
        procesos:   diccTrie(proceso, itRecurso: itLog),
        recursos:   diccLog(recurso, tupla<itConjLineal, cola(proceso)>),
        bloqueados: conjTrie(proceso),
        usados:     conjLineal(recurso)
      >
```

## Ejercicio 2

La complejidad debe ser O(n*(|e1|+|e2|)).  
Primero armo un diccionario implementado sobre un Trie en el que guardaré como significado una tupla con la cantidad de puntos de cada equipo distinto y sus goles a favor. Eso tiene complejidad O(n*(|e1|+|e2|)). Luego puedo hacer un Bucket Sort en el que cada indice del arreglo será la cantidad de puntos, para poder ordenarlo segun este parámetro. La máxima cantidad de puntos que un equipo puede obtener es 3n en caso de que aparezca en los n partidos y haya ganado todos, por lo que el largo del arreglo para el bucket sort será de 3n. Pero no solo eso, sino que cada bucket tendrá otro arreglo para hacer otro Bucket Sort, pero esta vez segun puntos, que son K, por lo que está acotado. Esto tendrá una complejidad de O(n + 3n) = O(n). Luego queda recorrer adecuadamente el arreglo de los Bucket Sorts y reordenarlo

```cpp
tabla sortTablaFutbol(vector<tupla<string e1, string e2, goles g1, goles g2>> partidos, goles k){
    diccTrie<string, tupla<puntos, goles>> trieEquipos;

    for(tupla t : partidos){    // O(n * (|e1|+|e2|))
        if(t.e1 > t.e2){
            if(not trieEquipos.definido(t.e1)){
                trieEquipos.definir(t.e1, <3, t.g1>)
            } else{
                def = trieEquipos.significado(t.e1); // modifica la referencia al significado
                def.puntos += 3;
                def.goles += t.g1;
            }
        }
        else if(t.e1 < t.e2){
            if(not trieEquipos.definido(t.e2)){
                trieEquipos.definir(t.e2, <3, t.g1>)
            } else{
                def = trieEquipos.significado(t.e2); // modifica la referencia al significado
                def.puntos += 3;
                def.goles += t.g1;
            }
        }
        else{
            if(not trieEquipos.definido(t.e1)){
                trieEquipos.definir(t.e1, <3, t.g1>)
            } else{
                def = trieEquipos.significado(t.e1); // modifica la referencia al significado
                def.puntos += 1;
                def.goles += t.g1;
            }
            if(not trieEquipos.definido(t.e2)){
                trieEquipos.definir(t.e2, <3, t.g1>)
            } else{
                def = trieEquipos.significado(t.e2); // modifica la referencia al significado
                def.puntos += 1;
                def.goles += t.g1;
            }
        }
    }

    vector<vector<lista<tupla<equipo, puntos, goles>>>> buckets(buckets(k), 3n); // creo vector de tamaño 3n con vectores de largo k

    for(clave key : trieEquipos){ // O(n)
        equipo = key;
        puntos = trieEquipos.significado(key).puntos;
        goles = trieEquipos.significado(key).goles;
        buckets[puntos][goles].encolar(tupla<equipo, puntos, goles>);
    }


    vector<tupla<equipo, puntos>> tabla;
    for(buckets.end() itPunto; hasta buckets.begin()){
        for(itPunto.begin() itGoles; hasta itPunto.end()){ // en orden por puntos
            for(itGoles.begin() itLista; hasta itGoles.end()){ // en orden por goles
                tabla.push_back(tupla<(*itLista).equipo, (*itLista).puntos>);
                
            }
        }
    } // todo eso es O(n) porque solo hay n equipos por los que iterar

    return tabla;
}
```

## Ejercicio 3

```cpp
tupla<copaRaiz, copaMayor> mayorCopaRecursivo(Nodo* raiz){
    
    if(nil(raiz))
        return <0, 0>;

    else{
        recIzq = mayorCopaRecursivo(raiz->izq);
        recDer = mayorCopaRecursivo(raiz->der);

        copaRaiz = 1;
        if(raiz->valor == raiz->izq->valor and raiz->valor == raiz->der->valor)
            copaRaiz += min(recIzq.first, recDer.first);
        
        mayorCopa= max(recIzq.second, recDer.second, copaRaiz);

        return <copaRaiz, mayorCopa>;
    }    
}

int mayorCopa(Nodo* raiz){
    return(mayorCopaRecursivo(raiz)).second;
}
```