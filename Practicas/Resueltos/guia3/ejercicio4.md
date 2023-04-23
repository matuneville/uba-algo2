# Ejercicio 4

Se propone la siguiente estructura para representar el TAD arbol binario:  

ab se representa con puntero(estr)  
donde _estr_ es tupla(altura: nat, izq: puntero(estr), raiz : α, der : puntero(estr))

## Resolucion:

### Invariante de Representacion
Tiene que cumplir:
1. altura es el largo de la rama mas larga del arbol
2. si no hay raiz entonces no hay izq y der
```
Rep: estr ➔ bool
Rep(e) ≡ (*(e.raiz) = NULL  ⇒  e.izq = NULL ∧ e.der = NULL) ∧
         (e.altura = max(izq.altura, der.altura)) ∧

```

### Funcion de abstraccion
```
Abs: estr e ➔ Arbol Binario
Abs(e) = ab : Arbol Binario / 
        

```

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ```