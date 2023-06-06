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

int main(){ // lo testeo 
    int arr[8] = {8, 4, 7, 6, 5, 1, 3, 2};
    return masALaIzquierda(arr, 8);
}