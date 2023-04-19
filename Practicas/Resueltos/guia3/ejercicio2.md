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
```
Rep: estr -> bool
Rep(e) = true <=>
            (e.grado = length(e.coef) - 1)  ∧  (e.coef[e.grado] != 0) 
```

### Funcion de abstraccion
```
Abs: estr e -> estr
(∀e: estr) Abs(e) = d: estr <=>
```

## Interface
### Operaciones
```
Evaluar (in p: polinomio, in n: nat) -> res: nat
Pre{true}
Post{res = evaluar(p,n)}
Complejidad: O(n)
Aliasing:
Descripcion: evalua p en n
```
### Algoritmos
```
Evaluar(in p: estr, in n: nat) -> res: nat
    res <- 0
    i <- 0
    while (i ≤ p.grado)
        res <- res + p.coef[i] * pow(n,i)
        i <- i + 1
    return res
```
simbolos × ➔ ∀ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ```