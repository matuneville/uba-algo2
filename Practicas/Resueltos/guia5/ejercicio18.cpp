#include <vector>
using namespace std;
typedef unsigned int uint;

void radixsort(vector<uint> arr){
    vector<uint> baseN;

    for(uint num : arr){
        baseN.push_back(convertToBase(num, arr.size()));
    } // esto llevará O(n*d), con d la cantidad de operaciones requeridas para pasar a base N cada numero

    // despues lo sigo

}