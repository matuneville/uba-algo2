#include <vector>
#include "algobot.h"

using namespace std;

// Ejercicio 1
vector<int> quitar_repetidos(vector<int> s) {
    set<int> resultSet;

    for (int i : s)
        resultSet.insert(i);

    vector<int> resultVector{};

    for (int i : resultSet)
        resultVector.push_back(i);

    return resultVector;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    return quitar_repetidos(s);
}

// Ejercicio 3
bool mismos_elementos(vector<int> a, vector<int> b) {
    set<int> setA, setB;

    for (int i : a)
        setA.insert(i);
    for (int i : b)
        setB.insert(i);

    return setA == setB;
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    return mismos_elementos(a,b);
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map<int, int> output;
    for (int i : s)
        output[i] += 1;
    return output;
}

// Ejercicio 6 - uso contar_apariciones
vector<int> filtrar_repetidos(vector<int> s) {
    map<int, int> apariciones = contar_apariciones(s);
    vector<int> output;


    for (pair<int, int> i : apariciones){
        if (i.second == 1)
            output.push_back(i.first);
    }

    /* Esto me pide C++ 17 :(

    for (auto [key, value] : apariciones){
        if (value == 1)
            output.push_back(key);
    }*/

    return output;
}

// Ejercicio 7
set<int> interseccion(set<int> a, set<int> b) {
    set<int> result;

    for (int i : a){
        if (b.count(i) == 1)
            result.insert(i);
    }

    return result;
}

// Ejercicio 8
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    // la cifra menos significativa la tomo como (mod 10)
    map<int, set<int>> result;

    for (int i : s){
        int key = i % 10;
        result[key].insert(i);
    }

    return result;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    vector<char> result;
    map<char, char> trad;

    for (pair<char, char> i : tr){
        trad.insert(i);
    }

    for (char c : str){
        if (trad.count(c) > 0)
            result.push_back(trad[c]);
        else
            result.push_back(c);
    }

    return result;
}

// Ejercicio 10
bool integrantes_repetidos(vector<Mail> s) {
    for (Mail m0 : s){
        for (Mail m1 : s){
            if (m0.libretas() != m1.libretas()){
                for (LU lu : m0.libretas()){
                    if (m1.libretas().count(lu)) // 0 = falso, >1 = verdadero
                        return true;
                }
            }
        }
    }
    return false;
}

// Ejercicio 11
map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
    map<set<LU>, Mail> entregas;

    for (int i = s.size()-1; i != -1; i--){
        Mail email = s[i];
        if (not(entregas.count(email.libretas())) && email.adjunto()){
            entregas[email.libretas()] = email;
        }
    }

    return entregas;
}