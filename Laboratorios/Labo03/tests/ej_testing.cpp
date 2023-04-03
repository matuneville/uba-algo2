#include "gtest-1.8.1/gtest.h"
#include "../src/Libreta.h"
#include "../src/Truco.h"
#include <map>
#include <cmath>

using namespace std;

// Ejercicio 4
TEST(Aritmetica, suma) {
    int suma = 15 + 7;
    int esperado = 22;
    EXPECT_EQ(suma, esperado);
}

// Ejercicio 5
TEST(Aritmetica, potencia) {
    int potencia = pow(10, 2);
    int esperado = 100;
    EXPECT_EQ(potencia, esperado);
}

// Ejercicios 6
TEST(Aritmetica, potencia_general) {
    for(int i = -5; i <= 5; ++i) {
        EXPECT_EQ(pow(i, 2), i * i);
    }
}

// Ejercicios 7
TEST(Diccionario, obtener) {
    map<int, int> diccionario;
    diccionario[13] = 10;
    EXPECT_TRUE(diccionario[13] == 10);
}

// Ejercicios 8
TEST(Diccionario, definir) {
    map<int, int> diccionario;
    EXPECT_FALSE(diccionario.count(13));
    diccionario[13] = 10;
    EXPECT_TRUE(diccionario.count(13));
}

// Ejercicios 9
TEST(Truco, inicio) {
    Truco trucardo;
    EXPECT_EQ(trucardo.puntaje_j1(), 0);
    EXPECT_EQ(trucardo.puntaje_j2(), 0);
}

// Ejercicios 10
TEST(Truco, buenas) {
    Truco trucardo;
    EXPECT_EQ(trucardo.puntaje_j1(), 0);
    for (int i = 0; i < 15; ++i) {
        trucardo.sumar_punto(1);
    }
    EXPECT_FALSE(trucardo.buenas(1));
    trucardo.sumar_punto(1);
    EXPECT_TRUE(trucardo.buenas(1));
    trucardo.sumar_punto(1);
    trucardo.sumar_punto(1);
    EXPECT_TRUE(trucardo.buenas(1));
}