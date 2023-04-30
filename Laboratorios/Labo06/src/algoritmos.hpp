#ifndef ALGO2_LABO_CLASE5_ALGORITMOS_H
#define ALGO2_LABO_CLASE5_ALGORITMOS_H
#include "algoritmos.cpp"
#include <utility>
#include <iterator>
#include <vector>

// Completar con las funciones del enunciado

// ej 1
template<class Contenedor>
typename Contenedor::value_type minimo(const Contenedor& c);

// ej 2
template<class Contenedor>
typename Contenedor::value_type promedio(const Contenedor& c);

// ej 3
template<class Iterator>
typename Iterator::value_type minimoIter(const Iterator& desde, const Iterator& hasta);

template<class Iterator>
typename Iterator::value_type promedioIter(const Iterator& desde, const Iterator& hasta);

// ej 4
template<class Contenedor>
void filtrar(Contenedor &c, const typename Contenedor::value_type& elem);

// ej 5
template<class Contenedor>
bool ordenado(Contenedor &c);

// ej 6
template<class Contenedor>
std::pair<Contenedor, Contenedor> split(const Contenedor & c,
                                        const typename Contenedor::value_type& elem);

// ej 7
template <class Contenedor>
void merge(const Contenedor& c1, const Contenedor & c2, Contenedor & res);

#endif //ALGO2_LABO_CLASE5_ALGORITMOS_H
