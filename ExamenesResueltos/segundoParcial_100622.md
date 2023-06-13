## Ejercicio 1

Una solución sería crear un diccionario implementado a través de un AVL Tree. Luego habría que recorrer el arreglo e ir insertando cada elemento en el diccAVL. Como esta estructura no permite elementos repetidos, su cantidad de nodos totales será constantemente $d$. Al recorrer el arreglo para formar el diccAVL, si no está el elemento, se inserta y se le pone de significado 1, lo que costaría $O(log\ d)$. En cambio si yá está, habría que buscarlo y sumarle +1, que también costaría $O(log\ d)$. Hasta aca ya tenemos una complejidad de $O(n\ log\ d)$. Luego para reformar el arreglo pero ordenado, puedo buscar el mínimo del diccAVL (costo $O(log\ d)$), y por cada aparición insertarlo nuevamente en el arreglo. Luego se elimina el mínimo y se vuelve a buscar el siguiente (costo $O(log\ d)$). Esto costará en total $O(n\ 2*log\ d)$, pues habrá que recorrer las $d$ claves, pero la cantidad de apariciones totales será $n$, que es su cota superior. Por lo tanto, la complejidad final del algoritmo será de $O(n\ log\ d + n\ 2*log\ d) = O(n\ log\ d)$.

```cpp
class diccAVL{};

void sortArrToAVL(int arr[], int size){

    diccAVL arbol = {};

    for(int i = 0; i < size; i++){ // O(n)
        if (not arbol.count(arr[i]))  // O(log d)
            arbol.insert(arr[i]);   // O(log d)

        else
            arbol.at(arr[i])++;  // O(log d)
            // le sumo una aparicion
    }

    int pos = 0;
    while(not arbol.empty()){ // O(n) contando cada aparicion
        int minimo = arbol.masALaIzquierda(); // O(log d)
        while(significado(arbol, minimo) > 0){
            arr[pos] = minimo;
            pos++;
            significado(arbol, minimo)--; // asumo que se modifica por referencia
        }
    }
}
```

## Ejercicio 2

Lo que haré es crear un vector en el que juntaré tuplas que digan donde inicia y termina cada edificio, que cuesta $O(n)$. También podría juntar los diferentes arreglos de edificios pero es innecesario si se cuenta con los índices de inicio y fin de cada uno. Esto también me sirve para contar el ancho de cada edificio. La máxima cantidad de tuplas (o diferentes edificios) que pueden aparecer es de n, si son todos de ancho = 1. En cambio si todo el arreglo es un edificio, será una sola tupla y su ancho será n. Por lo tanto, podemos crear otro arreglo de largo n para hacer un counting sort según el ancho de cada edificio. En realidad sería un bucket sort segun el ancho de edificios, para poder guardar las tuplas, y en caso de que sean de igual ancho se mantendrán en el orden en que ya venian en el arreglo. Esta complejidad será de $O(n)$.

```cpp
void sortEdificios(int arr[], int size, int tolerancia){
    vector<pair<int, int>> edificios;
    
    for(int i = 0; i < size; i++){  // O(n)
        int j = i+1;
        while(j < size and (abs(arr[i] - arr[i+1]) <= tolerancia)){
            j++;
        }
        pair<int, int> edificio = make_pair(i, j);
    }

    vector<list<pair<int, int>>> buckets (size); // inicializo vector de tamaño n

    for(int i = 0; i < size; i++){  // O(n)
        int ancho = edificios[i].second - edificios[i].first;
        buckets[ancho].push_back(edificios[i]); // pongo la tupla en el bucket
    }

    int sortedArr(size);

    int pos = 0;
    for(int i = 0; i < buckets.size(); i++){    // O(n)
        while(not buckets[i].empty()){
            for(int j = buckets[i].front.first; j < buckets[i].front.second; j++){
                sortedArr[pos] = arr[j];
                pos++;
            } // los elementos que asignara son en total n
            buckets[i].pop_front();
        }
    }
}
```

## Ejercicio 3

### Item A

Una forma sería ir partiendo en mitades en arreglos y ver si la suma del primer elemento del arreglo junto con el índice del final de esta mitad es igual al elemento que se encuentra en dicho índice. Ejemplo: con el arreglo arr = [6, 7, 8, 9, 10, 11, 12, 13], n = 8, arr[8/2 - 1] = 9, y 9 == arr[0] + (8/2 - 1) = 6 + 3 (para la mitad derecha sucede lo mismo). La recursión solo se hará hacia la mitad en que no coincida esto, por lo que si coincide en ambas mitades, k = 0, y no se hará ninguna recursión.  
Otro ejemplo sería arr = [6, 7, 8, 9, 10, 11, 13, 14], que en su mitad derecha, 14 != arr[8/2] + (8/2 - 1) = 10 + 3.

```cpp
void buscoHuecos(int arr[], int begin, int end, list<int> &huecos){
    if(end - begin == 2){
        huecos.push_back(arr[begin] + 1); // caso base tamaño 2
    }
    else{
        int mitad = (end + begin) / 2;
        if(arr[mitad] != arr[mitad - 1] + 1){   // hay hueco justo en el medio del arreglo
            // es un border case a tener en cuenta porque no lo detectaria con los dos if de abajo
            huecos.push_back(arr[mitad] - 1);
        }
        if(arr[begin] + mitad - 1 != arr[mitad - 1]){   // hay hueco en izquierda
            buscoHuecos(arr, begin, mitad, huecos);
        }
        if(arr[mitad] + mitad - 1 != arr[end - 1]){     // hay hueco en derecha
            buscoHueco(arr, mitad, end, huecos);
        }
    }
}

list<int> huecos(int arr[], int size){
    list<int> listaHuecos;
    if(size == 1) return listaHuecos; // vacia, no hay huecos

    buscoHuecos(arr[], 0, size, listaHuecos);
    return listaHuecos;
}
```

### Item B

Parte de Dividir:

```cpp
if(arr[begin] + mitad - 1 != arr[mitad - 1]){   // hay hueco en izquierda
    buscoHuecos(arr, begin, mitad, huecos);
}
if(arr[mitad] + mitad - 1 != arr[end - 1]){     // hay hueco en derecha
    buscoHueco(arr, mitad, end, huecos);
}
```

Parte de Conquistar:

```cpp
if(end - begin == 2){
    huecos.push_back(arr[begin] + 1); // caso base tamaño 2
}
else{
    int mitad = (end + begin) / 2;
    if(arr[mitad] != arr[mitad - 1] + 1){   // hay hueco justo en el medio del arreglo
        // es un border case a tener en cuenta porque no lo detectaria con los dos if de abajo
        huecos.push_back(arr[mitad] - 1);
    }
```

La parte de Unir los subproblemas sería también cuando se pushean los huecos, pero no hace falta _unir_ subproblemas pues la lista de huecos está pasada por referencia, por lo que se va modificando y uniendo las soluciones a medida que se ejecutan sus recursiones.


### Item C

Si k = 1, pueden pasar dos cosas: que el único hueco se encuentre en el medio, por lo que se encontrará y se añadirá a la lista de huecos, sin entrar en ninguna recursión o ciclo, por lo que su complejidad será de $\Theta(1) \in O(log\ n)$.  
En otro caso, se encontrará solo en un lado del arreglo, es decir, o en la izquierda o en la derecha, y se harán las recursiones dividiendo al arreglo entre 2 hasta que, o bien llegue al caso base, o tenga el hueco justo en el medio. Lo importante es que siempre se hará como máximo una recursion, nunca serán dos hacia cada lado del arreglo. Su complejidad por Teorema Maestro sería:  
$T(n) = 1*T(n/2)+O(1), \text{sea a = 1 (sería k), c = 2, f(n) = 1}$  
$f(n) = 1 \in \Theta(n^{log_c(a)}) = \Theta(n^{log_2(1)}) = \Theta(n^{0}) = \Theta(1)$  
$\Rightarrow T(n) \in \Theta(n^{log_c(a)}*log\ n) = \Theta(n^0*log\ n) = \Theta(log\ n)$  

Esta solución cumple con la complejidad pedida pues $\Theta(log\ n) \in O(k\ log\ n)$

### Item D

En caso de que k > 1, entonces en el peor caso sí se harán recursiones hacia ambos lados del arreglo, a diferencia del item anterior. Entonces en este caso se hará como peor caso tantas recursiones logarítmicas como huecos presentes haya en el arreglo, dando una complejidad de $O(k\ log\ n)$