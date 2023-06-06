# Guía práctica 5: Sorting

## Ejercicio 5

Básicamente hago un counting sort y luego lo ordeno por cantidad de occurrences.  
Esto lleva a una complejidad de O(n max(arr)). Es poco eficiente en caso de que el máximo elemento sea muy grande.

```cpp
typedef unsigned int uint;

// voy a usar funciones no definidas pero son faciles 

void sortingFrecuencia(uint arr[], uint size){

    uint maxElem = max(arr);    // O(n)
    
    uint aparicionesArr[maxElem + 1] = {0};

    for(uint i = 0; i < size; i++){
        aparicionesArr[i]++;
    }

    uint i = 0;

    while (i < size){   // O(n)
        uint apariciones, num;
        buscoMasAparecido(num, apariciones, aparicionesArr); // O( max(arr))
        // busca el numero mas aparecido y de mayor valor en caso de coincidir
        for(uint j = 0; j < apariciones; j++){  //O (max(arr))
            arr[i] = num;
            j++;
        }
        aparicionesArr[num] = 0;
    }
}       // Complejidad final: O(size * max(arr))
```

## Ejercicio 6

Mi idea es: primero pense en juntar en un arreglo de arreglos todas sus escaleras, pero no es necesario, sino que se puede juntar las tuplas de indices de inicio y fin de cada escalera. Eso se hace en O(n). Luego se le mete dos sortings, primero segun el minimo elemento, y luego, una vez ordenado por minimos elementos, segun el largo de las escaleras (es decir, tupla.second - tupla.first). Lo importante es que sea estable el algoritmo, como el Merge Sort, para que luego de estar ordenado por mínimo, mantenga este orden al reordenarlo por largo. Luego se junta en un arreglo solo y listo. Entonces queda O(n + 2m log m + n), siendo n el largo del arreglo y m la cantidad de escaleras. Pero m esta acotado por n, pues como mucho pueden haber n escaleras, por lo tanto la complejidad queda O(n log n).

```cpp
#include <vector>
using namespace std;

void sortEscaleras(int arr[], int size){
    vector<pair<int,int>> escaleras;

    int i = 1;
    while(i < size){    // O(n)
        int j = i;
        while(arr[j-1]-1 == arr[j]){
            j++;
        }
        pair<int,int> tupla = make_pair(i, j);
        escaleras.push_back(tupla);
        i++;
    }

    mergesort_v1(escaleras, arr);   // O(m log m), m la cantidad de escaleras
    // lo ordena segun el primer elemento de cada escalera, es decir, arr[t.first], siendo t cada tupla de escaleras;

    mergesort_v2(escaleras);   // O(m log m), m la cantidad de escaleras
    // lo ordena segun el largo de cada escalera, manteniendo el orden previo

    int sortedArr[size];

    int k = 0;
    for(pair<int,int> t : escaleras){
        int beginTupla = t.first; // la tupla de c++ no es modificable
        while(beginTupla <= t.second){
            sortedArr[k] = arr[t.first];
            k++;
            beginTupla++;
        }
    }   // este ciclo es O(n)

    for (int l = 0; l < size; l++){
        arr[l] = sortedArr[l];
    }   // O(n) para copiar el arreglo ordenado

}   // complejidad final O(n + m log m)
```

## Ejercicio 7

La idea está en ubicar cada elemento del arreglo en su debida posición del AVL, pero sin tener elementos repetidos en el árbol. Podríamos tomarlo como un diccionario AVL, que su key-value sea numero-apariciones. Recorrer el arreglo sería O(n) y ubicar cada elemento en su debida posicion sería O(log d). Esto daría una complejidad de O(n * log d). En un caso en que el arreglo no tiene elementos repetidos, entonces d = n. Un posible algoritmo sería:

```cpp
typedef unsigned int uint;
using namespace std;

// supongamos que la clase mapAVL esta creada
class mapAVL{};

void sortArrToAVL(uint arr[], uint size){

    mapAVL arbol = {};

    for(uint i = 0; i < size; i++){ // O(n)
        if (not arbol.count(arr[i]))  // O(log d)
            arbol.insert(arr[i]);   // O(log d)

        else
            arbol.at(arr[i])++;  // O(log d)
            // le sumo una aparicion
    }
}
```

## Ejercicio 9

### a)
```cpp
typedef unsigned int uint;
using namespace std;

struct Alumno {
    string nombre;
    char gen;   // M o F
    uint nota;  // [1, 10]
};

void sortGeneroYNota(Alumno arr[], uint size) {
    Alumno sortGen[size], sortNota[size];
    
    char generos[2] = {'F', 'M'};

    uint index = 0;
    for (uint j = 0; j < 2; j++) {  // O(1) acotado por los 2 generos
        char c = generos[j];
        for (uint nota = 1; nota < 11; nota++) { // O(1), acotado por las 10 notas posibles
            for (uint i = 0; i < size; i++) {   // O(n)
                if (sortGen[i].nota == nota and sortGen[i].gen == c) {
                    sortNota[index] = sortGen[i];
                    index++;
                }
            }
        }
    }
    // Actualizar el arreglo original
    for (uint i = 0; i < size; i++) {   // O(n)
        arr[i] = sortNota[i];
    }

    // Complejidad final O(3n) = O(n)
}
```

### b)
```cpp
typedef unsigned int uint;
using namespace std;

struct Alumno {
    string nombre;
    char gen;   // M o F
    uint nota;  // [1, 10]
};

void sortGeneroYNota_B(Alumno arr[], uint size, char generos[], uint cantGeneros) {
    Alumno sortGen[size], sortNota[size];

    uint index = 0;
    for (uint j = 0; j < cantGeneros; j++){ // O(1), acotado por cantGeneros
        char c = generos[j];
        for (uint nota = 1; nota < 11; nota++) { // O(1), acotado por las 10 notas posibles
            for (uint i = 0; i < size; i++) {   // O(n)
                if (sortGen[i].nota == nota and sortGen[i].gen == c) {
                    sortNota[index] = sortGen[i];
                    index++;
                }
            }
        }
    }

    // Actualizar el arreglo original
    for (uint i = 0; i < size; i++) {   // O(n)
        arr[i] = sortNota[i];
    }

    // Complejidad final O(3n) = O(n)
}
```

## Ejercicio 11

Básicamente hay que hacer un counting sort. Lo que hago es crear un arreglo de tamaño max(arr), es decir, que su largo va a estar acotado por el rango del arreglo dado (si este está acotado, sino entrará en juego su complejidad también, como en el 5).

```cpp
typedef unsigned int uint;

void countingSort(uint arr[], uint size, uint max){

    uint count[max + 1] = {0}; // cuento las apariciones de cada numero en el índice del mismo numero

    for(uint n : arr){  // O(n)
        count[n]++;
    }

    uint index = 0;

    for(uint i = 0; i < max + 1; i++){ // O(max), acotado, O(1)
        while(count[i] > 0){    // O(n)
            arr[index] = count[i];
            index++;
            count[i]--;
        }
    }
}
        // Complejidad final O(n)
```

## Ejercicio 12

Lo que hay que hacer es un counting sort con los elementos que están entre 20 y 40, y los que quedan por fuera los meto en otro arreglo. El primer counting me llevaria a un O(n) pues el maximo elemento está acotado (hay 20 posibles diferentes), y en el otro arreglo sé que su largo puede ser como mucho √n, por lo que meterle un sorting no complicaría nada pues en el peor caso es un sorting cuadrático, y da una complejidad O(√n² = n). Luego junto ambos arreglos y queda una complejidad final linea, O(n).

```cpp
typedef unsigned int uint;

void sortingVeinteCuarenta(uint arr[], uint size){
    vector<uint> outtaRange1, outtaRange2;  // uso vector porque el largo esta entre 0 y raiz(n), es dinamico no fijo
    uint arrCount[41] = {0};  // para el counting sort de los elementos entre [20, 40], empiezan con 0
   
    for(uint i : arr){           // O(n)
        if(i < 20)
            outtaRange1.pushback(i);
        else if(i > 40)
            outtaRange2.pushback(i);
        else
            arrCount[i]++;    
    }
   
    sort(outtaRange1); // O(√n² = n)
    sort(outtaRange2); // O(√n² = n)

    uint index = 0;

    for(; index < outtaRange1.size(); index++){ // O(√n)
        arr[index] = outtaRange1[index];
    }

    for (int i = 20; i < 41; i++) { // O(1), acotado por 40. Hago un counting
        while (arrCount[i] > 0) {  // O(n) por index que crece hasta n - outtaRange2.size()
            arr[index] = i;
            index++;
            arrCount[i]--;
        }
    }

    for(uint n : outtaRange2){ // O(√n)
        arr[index] = n;
        index++;
    }
}
        // Complejidad final O(n)
```

## Ejercicio 13

Lo que hay que hacer es ordenar primero las tuplas por su string en un Trie como diccionario. Ubicar cada palabra lleva O(l) ¿, y como se hace n veces lleva a una complejidad de O(nl). Luego lo ordeno respecto a sus números de cada string con algun algoritmo como Merge sort que sea estable para que mantenga el orden segun los stirngs, y que su complejidad sea de O(n log n). Luego, la complejidad final es de O(nl + n log n).  

## Ejercicio 16

Me fijo primero buscando el máximo elemento y el mínimo. Si max-min es mayor o igual que el tamaño del arreglo, entonces hay agujero. En el otro caso puede ser falso, pero tengo que chequear que no haya elementos repetidos. Ejemplo, [3, 1, 4, 2], cumple 4-1 < 4 y no tiene agujero, pero en el caso [3, 1, 1, 1], cumple 3-1 < 4 pero sí tiene agujero. Entonces como max-min < n, puedo hacer un counting sort con un arreglo de tamaño (max-min) pues está acotado por n. De todos modos, que tenga repetidos no quiere decir que sea falso, por lo que al hacer el counting, me fijo si en el arreglo en el que cuento apariciones hay algun elemento que no aparezca, es decir, que tenga 0 apariciones. En este caso sí hay agujero.

```c
typedef unsigned int uint;

bool tieneAgujero(uint arr[], uint size){
    uint maxElem = max(arr);    // O(n)
    uint minElem = min(arr);    // O(n)

    if (maxElem - minElem >= size) return true;

    else{ // puede tener repetidos
        uint countArr[max - min + 1];
        for(uint n : arr){              // O(n)
            countArr[n - minElem]++;
        }

        for(uint occurr : countArr){    // O(n)
            if (occurr == 0) return true;
        }
    }
    return false;
}                   // Complejidad final O(n)
```

## Ejercicio 18

a) Es básicamente un counting sort con elemento máximo el largo del arreglo, dando como resultado una complejidad de O(n).  

b) Para expresar un numero menor a n² en base n se requieren dos cifras. Es decir, un numero de dos cifras en base n puede expresar como máximo el numero n²-1. Entonces la idea es pasar los numeros del arreglo a base n y luego hacer un Radix Sort para los 2 dígitos. Pasar cada número a base n requiere 2 operaciones pues estará escrito en 2 cifras que está acotado. Luego la complejidad final será de O(n).  

c) Mismo concepto que antes pero para numeros acotados por k. Entonces la complejidad en vez de O(2n) será de O(k*n).  