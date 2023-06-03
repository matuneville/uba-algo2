typedef unsigned int uint;
using namespace std;

// supongamos que la clase mapAVL esta creada
class mapAVL{};

void sortArrToAVL(uint arr[], uint size){

    mapAVL arbol = {};

    for(uint i = 0; i < size; i++){ // O(n)
        if (not arbol.count(arr[i]))  // O(log d)
            arbol.insert(arr[i]);   // O(log d)

        else
            arbol.at(arr[i])++;  // O(log d)
            // le sumo una aparicion
    }
}
