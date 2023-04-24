# Ejercicio 4

Se propone la siguiente estructura para representar el TAD arbol binario:  

ab se representa con puntero(estr)  
donde _estr_ es tupla(altura: nat, izq: puntero(estr), raiz : α, der : puntero(estr))

## Resolucion:

### Invariante de Representacion
Tiene que cumplir:
1. si hay izq y/o der, entonces hay raiz
2. si no hay raiz entonces no hay izq y der
```
Rep: estr ➔ bool
Rep(e) ≡ ((e.izq ≠ NULL ∨ e.der ≠ NULL) ⇒ *(e.raiz) ≠ NULL)  ∧
         (*(e.raiz) = NULL  ⇒  e.izq = NULL ∧ e.der = NULL)

```

### Funcion de abstraccion
Tengo que ver que:
1. Si e.raiz es NULL entonces ab es Nil
2. Raiz sea igual a e.raiz
3. izq sea igual a e.izq
4. der sea igual a e.der
```
Abs: estr e ➔ Arbol Binario
Abs(e) = ab : Arbol Binario / 
        (*(e.raiz) = NULL  ⇔  nil?(ab)) ∧
        (not(nil?(ab)) ⇒ *(e.izq) = izq(ab) ∧ *(e.der) = der(ab) ∧ e.raiz = raiz(ab))
        

```

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ```