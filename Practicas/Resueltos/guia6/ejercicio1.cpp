#include <iostream>
using namespace std;

int sumar(int arr[], int begin, int end);

bool masALaIzquierda(int arr[], int begin, int end){

    if(end-begin == 1) return true;

    int sumaIzq = sumar(arr, begin, (end+begin)/2);    // O(n/2)
    int sumaDer = sumar(arr, (end+begin)/2, end); // O(n/2)

    if(sumaDer >= sumaIzq) return false;

    else
        return (masALaIzquierda(arr, begin, (end+begin)/2) and masALaIzquierda(arr, (end+begin)/2, end)); // O(log n + log n)

}   // complejidad final O(n log n)

int sumar(int arr[], int begin, int end){
    int output = 0;
    for(int i = begin; i < end; i++){
        output += arr[i];
    }
    return output;
}

int main(){ // lo testeo 
    int arr[8] = {9,0,5,3,7,1,3,2};
    if (masALaIzquierda(arr, 0, 8) == true) cout << "v";
    else cout<< "f";
    return 0;
}