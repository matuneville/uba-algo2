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