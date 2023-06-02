# Guía práctica 5: Sorting

## Ejercicio 5

Básicamente hago un counting sort y luego lo ordeno por cantidad de occurrences.  
Esto lleva a una complejidad de O(n max(arr)). Es poco eficiente en caso de que el máximo elemento sea muy grande.

```c
typedef unsigned int uint;

// voy a usar funciones no definidas pero son faciles 

void sortingFrecuencia(uint arr[], uint size){

    uint maxElem = max(arr);    // O(n)
    
    uint aparicionesArr[maxElem + 1];

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


## Ejercicio 12

Lo que hay que hacer es un counting sort con los elementos que están entre 20 y 40, y los que quedan por fuera los meto en otro arreglo. El primer counting me llevaria a un O(n) pues el maximo elemento está acotado (hay 20 posibles diferentes), y en el otro arreglo sé que su largo puede ser como mucho √n, por lo que meterle un sorting no complicaría nada pues en el peor caso es un sorting cuadrático, y da una complejidad O(√n² = n). Luego junto ambos arreglos y queda una complejidad final linea, O(n).

```c
typedef unsigned int uint;

```