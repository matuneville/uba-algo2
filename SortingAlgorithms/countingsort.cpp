using namespace std;
typedef unsigned int uint;

void countingSort(uint arr[], uint size, uint max){

    uint count[max + 1] = {0}; // cuento las apariciones de cada numero en el índice del mismo numero

    for(uint n : arr){  // O(n)
        count[n]++;
    }

    uint index = 0;

    for(uint i = 0; i < max + 1; i++){ // O(max), acotado, O(1)
        while(count[i] > 0){    // O(n)
            arr[index] = count[i];
            index++;
            count[i]--;
        }
    }
}
        // Complejidad final O(n)