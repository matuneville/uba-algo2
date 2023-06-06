# Guía práctica 6: Divide & Conquer

## Ejercicio 1

El algoritmo se llama a sí mismo una cantidad de veces logarítmica, y su complejidad dentro es de O(2 n/2) = O(n). Por lo tanto, su complejidad temporal final es de O(n log n), siendo asi menor estricta que O(n²).
```cpp
#include <iostream>
using namespace std;

int sumar(int arr[], int begin, int end);

bool masALaIzquierda(int arr[], int size){

    if(size == 1) return true;

    int sumaIzq = sumar(arr, 0, size/2);    // O(n/2)
    int sumaDer = sumar(arr, size/2, size); // O(n/2)

    if(sumaDer >= sumaIzq) return false;
    else{
        masALaIzquierda(arr, size/2);
    }
}   // complejidad final O(n log n)

int sumar(int arr[], int begin, int end){   // se realiza log n veces
    int output = 0;
    for(int i = begin; i < end; i++){
        output += arr[i];
    }
    return output;
}
```