#include <vector>
typedef unsigned int uint;
using namespace std;

void sortingVeinteCuarenta(uint arr[], uint size){
    vector<uint> outtaRange1, outtaRange2;  // uso vector porque el largo esta entre 0 y raiz(n), es dinamico no fijo
    uint arrCount[41] = {0};  // para el counting sort de los elementos entre [20, 40], empiezan con 0
   
    for(uint i : arr){           // O(n)
        if(i < 20)
            outtaRange1.pushback(i);
        else if(i > 40)
            outtaRange2.pushback(i);
        else
            arrCount[i]++;    
    }
   
    sort(outtaRange1); // O(√n² = n)
    sort(outtaRange2); // O(√n² = n)

    uint index = 0;

    for(; index < outtaRange1.size(); index++){ // O(√n)
        arr[index] = outtaRange1[index];
    }

    for (int i = 20; i < 41; i++) { // O(1), acotado por 40. Hago un counting
        while (arrCount[i] > 0) {  // O(n) por index que crece hasta n - outtaRange2.size()
            arr[index] = i;
            index++;
            arrCount[i]--;
        }
    }

    for(uint n : outtaRange2){ // O(√n)
        arr[index] = n;
        index++;
    }
}
        // Complejidad final O(n)