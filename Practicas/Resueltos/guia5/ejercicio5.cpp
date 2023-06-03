// Algoritmo punto 5
#include <iostream>
using namespace std;
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