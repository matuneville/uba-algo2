# Ejercicio 2


Se propone la siguiente estructura para representar a los polinomios que tienen a lo sumo grado n (ver TAD
en Practica 1):

polinomio se representa con estr  
donde estr es tupla(grado: nat, coef : array[0 . . . n] de nat)

Se pide:
1. Definir el invariante de representacion y la funcion de abstraccion.  
2. Escribir la interface completa y el algoritmo para la funcion evaluar.

## Resolucion:

### Invariante de Representacion
Tiene que cumplir:
1. Que el grado sea igual al largo de coef-1
2. Que el coeficiente de mayor grado no sea 0
```
Rep: estr ➔ bool
Rep(e) ≡ e.grado = largo(e.coef) - 1  ∧  e.coef[grado] ≠ 0
```

### Funcion de abstraccion
```
Abs: estr e ➔ polinomio
Abs(e) = polinomio / 
        (∀n: nat)(Evaluar(polinomio, n) = evaluar(e.coef, n))
```

### Algoritmos
```cpp
int evaluar(array<int> a, int n){
    int i = 0, res = 0;
    while(i < a.size()){
        res += a[i] * pow(n, i);
    }
    return result;
}
```

simbolos × ➔ ∀ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ```