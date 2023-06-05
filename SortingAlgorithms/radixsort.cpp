#include <vector>
#include <string>
#include <iostream>
using namespace std;
typedef unsigned int uint;

string convertToBase(int number, int base) {
    string result;

    while (number > 0) {
        int remainder = number % base;
        result = to_string(remainder) + result;
        number /= base;
    }

    return result;
}

void radixsort(vector<uint> arr, uint base){
    vector<string> baseN;
    vector<string> sorted;

    for(uint num : arr){
        baseN.push_back(convertToBase(num, base));
    } // esto llevará O(n*d), con d la cantidad de operaciones requeridas para pasar a base N cada numero
    
    uint cifraMasLarga = -1;
    for(string s : baseN){
        if(cifraMasLarga == -1 or s.length() > cifraMasLarga){
            cifraMasLarga = s.length();
        }
    }

    for(uint i = cifraMasLarga - 1; i <= 0; i++){ // O(cifraMasLarga)
        for(uint j = 0; j < base; j++){ // O(1)
            for(string s : baseN){   // O(n)
                if(s[i] == j)
                    sorted.push_back(s);
            }
        }
        baseN = sorted;
        sorted = {};
    }

    for(int i = 0; i < arr.size(); i++){
        arr[i] = stoi(sorted[i]);
    }
}

int main(){
    vector<uint> v = {5,23,80,54,77,7,10,9};
    radixsort(v, 9);
    for (uint n : v) cout << n << " ";
    return 0;
}