#include <vector>
#include <iostream>
using namespace std;

vector<int> mergeAndCount(vector<int> vecA, vector<int> vecB, int & contador){
    vector<int> merged;

    int iA = 0, iB = 0;
    while(iA < vecA.size() and iB < vecB.size()){ // O(n + n) = O(n)
        if(vecA[iA] < vecB[iB]){
            merged.push_back(vecA[iA]);
            iA++;
        }
        else{ // este es el caso en el que cuento las parejas en desorden
            merged.push_back(vecB[iB]);
            contador += vecA.size() - iA; // ACA LO IMPORTANTE PARA EL EJERCICIO
            iB++;
        }
    }
    while(iA < vecA.size()){
        merged.push_back(vecA[iA]);
        iA++;
    }
    while(iB < vecB.size()){
        merged.push_back(vecB[iB]);
        iB++;
    }
    return merged;
}

void contarDisparejasRecursiva(vector<int> &vec, int & contador){    // se hace O(log n) veces recursivamente

    if(vec.size() == 1) return;
    
    vector<int> vecPart1, vecPart2;

    int i = 0;
    for(; i < vec.size()/ 2; i++){      // O(n)
        vecPart1.push_back(vec[i]);
    }
    for(; i < vec.size(); i++){           // O(n)
        vecPart2.push_back(vec[i]);
    }

    contarDisparejasRecursiva(vecPart1, contador); // recursion doble aca con n/2
    contarDisparejasRecursiva(vecPart2, contador);


    vec = mergeAndCount(vecPart1, vecPart2, contador);    // O(n)
}

int contarDisparejas(vector<int> vec){
    int contador = 0;
    contarDisparejasRecursiva(vec, contador);

    return contador;
}

int main(){
    vector<int> v{4,2,5,10,13,9,8,11,12,0,6,7,1,3};
    // fua, lo probé con uno al azar y conté exactamente 50 jajajal el algoritmo funciona bien
    cout << contarDisparejas(v);
}