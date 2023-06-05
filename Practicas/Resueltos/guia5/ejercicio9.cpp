#include <string>
typedef unsigned int uint;
using namespace std;

struct Alumno {
    string nombre;
    char gen;   // M o F
    uint nota;  // [1, 10]
};

void sortGeneroYNota(Alumno arr[], uint size) {
    Alumno sortGen[size], sortNota[size];
    
    char generos[2] = {'F', 'M'};

    uint index = 0;
    for (uint j = 0; j < 2; j++) {  // O(1) acotado por los 2 generos
        char c = generos[j];
        for (uint nota = 1; nota < 11; nota++) { // O(1), acotado por las 10 notas posibles
            for (uint i = 0; i < size; i++) {   // O(n)
                if (sortGen[i].nota == nota and sortGen[i].gen == c) {
                    sortNota[index] = sortGen[i];
                    index++;
                }
            }
        }
    }
    // Actualizar el arreglo original
    for (uint i = 0; i < size; i++) {   // O(n)
        arr[i] = sortNota[i];
    }

    // Complejidad final O(3n) = O(n)
}


// punto b

void sortGeneroYNota_B(Alumno arr[], uint size, char generos[], uint cantGeneros) {
    Alumno sortGen[size], sortNota[size];

    uint index = 0;
    for (uint j = 0; j < cantGeneros; j++){ // O(1), acotado por cantGeneros
        char c = generos[j];
        for (uint nota = 1; nota < 11; nota++) { // O(1), acotado por las 10 notas posibles
            for (uint i = 0; i < size; i++) {   // O(n)
                if (sortGen[i].nota == nota and sortGen[i].gen == c) {
                    sortNota[index] = sortGen[i];
                    index++;
                }
            }
        }
    }

    // Actualizar el arreglo original
    for (uint i = 0; i < size; i++) {   // O(n)
        arr[i] = sortNota[i];
    }

    // Complejidad final O(3n) = O(n)
}