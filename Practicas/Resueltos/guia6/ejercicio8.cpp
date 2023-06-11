using namespace std;
#include <utility>
#include <vector>

typedef vector<vector<int>> matriz;

pair<int, int> buscarFalsoRecursivo(matriz m, int f1, int f2, int c1, int c2){
    if(f2-f1 == 1 and c2-c1 == 1)
        return make_pair(c1, f1); // solo llega a este caso si ESE elemento es Falso

    if(f2-f1 == 1){
        if (conjuncion(m, f1, f2, c1, (c2+c1)/2) == false)
            return buscarFalsoRecursivo(m, f1, f2, c1, (c2+c1)/2);
        else
            return buscarFalsoRecursivo(m, f1, f2, (c2+c1)/2, c2);
    }
    else{
        if (conjuncion(m, f1, (f2+f1)/2, c1, c2) == false)
            return buscarFalsoRecursivo(m, f1, (f2+f1)/2, c1, c2);
        else
            return buscarFalsoRecursivo(m, (f2+f1)/2, f2, c1, c2);
    }
}

pair<int, int> buscarFalso(matriz m){
    int size = m.size();
    return buscarFalsoRecursivo(m, 0, size, 0, size);
}