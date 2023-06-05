#include <vector>
#include <iostream>
using namespace std;

vector<int> merge(vector<int> vecA, vector<int> vecB){
    vector<int> merged;

    int iA = 0, iB = 0;
    while(iA < vecA.size() and iB < vecB.size()){
        if(vecA[iA] < vecB[iB]){
            merged.push_back(vecA[iA]);
            iA++;
        }
        else{
            merged.push_back(vecB[iB]);
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

void mergesort(vector<int> &vec){    // se hace O(log n) veces recursivamente

    if(vec.size() == 1)
        return;
    
    vector<int> vecPart1, vecPart2;

    int i = 0;
    for(; i < vec.size()/ 2; i++){      // O(n)
        vecPart1.push_back(vec[i]);
    }
    for(; i < vec.size(); i++){           // O(n)
        vecPart2.push_back(vec[i]);
    }

    mergesort(vecPart1);
    mergesort(vecPart2);


    vec = merge(vecPart1, vecPart2);    // O(n)
}