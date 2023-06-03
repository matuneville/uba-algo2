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

## Ejercicio 7

La idea está en ubicar cada elemento del arreglo en su debida posición del AVL, pero sin tener elementos repetidos en el árbol. Podríamos tomarlo como un diccionario AVL, que su key-value sea numero-apariciones. Recorrer el arreglo sería O(n) y ubicarlo en su debida posicion sería O(log d). Esto daría una complejidad de O(n * log d). En un caso en que el arreglo no tiene elementos repetidos, entonces d = n. Un posible algoritmo sería:

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
    for (uint i = 0; i < 2; i++) {  // O(1) acotado por los 2 generos
        char c = generos[i];
        for (uint j = 0; j < size; j++) {   // O(n)
            if (arr[j].gen == c) {
                sortGen[index] = arr[j];
                index++;
            }
        }
    }

    index = 0;
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
    for (uint i = 0; i < cantGeneros; i++) {  // O(1) acotado por cantGeneros
        char c = generos[i];
        for (uint j = 0; j < size; j++) {   // O(n)
            if (arr[j].gen == c) {
                sortGen[index] = arr[j];
                index++;
            }
        }
    }

    index = 0;
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

## Ejercicio 18

### a)
Es básicamente un counting sort con elemento máximo el largo del arreglo, dando como resultado una complejidad de O(n).

### b)

### c)

### d)