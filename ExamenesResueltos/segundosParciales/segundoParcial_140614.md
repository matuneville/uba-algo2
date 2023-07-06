## Ejercicio 1

```
  tupla <
        usuarios
        >
```



## Ejercicio 2

```cpp
esRojiNegroAux (in a : ab(color)) -> res : <bool, nat>

    // CONQUER
    if (esHoja(a)) // debe ser hoja negra, y suma +1 nodo negro
        res = <esColorNegro(a), 1>
    
    else
    // DIVIDE
        auxIzq = <true, 0>
        if (not nil?(izq(a)))
            auxIzq = esRojiNegroAux(izq(a))

        auxDer = <true, 0>
        if (not nil?(der(a)))
            auxDer = esRojiNegroAux(der(a))

        hijosNegros = true
        if (esColorRojo(a)) // si es rojo debe tener 2 hijos y ambos negros
            hijosNegros = esColorNegro(izq(a)) and esColorNegro(der(a))
        
        cuentoNodoNegro = 0 // si es negro, sumo +1
        if (esColorNegro(a))
            cuentoNegro = 1

    // COMBINE
        if (nil?(izq(a)))
            res = <π1(auxIzq) and π1(auxDer) and π2(auxIzq) == π2(auxDer) and hijosNegros,
                   π2(auxDer) + cuentoNodoNegro>
        else
            res = <π1(auxIzq) and π1(auxDer) and π2(auxIzq) == π2(auxDer) and hijosNegros,
                   π2(auxIzq) + cuentoNodoNegro>


esRojiNegro (in a : ab(color)) -> res : bool
    res = π1(esRojiNegroAux(ab))
```

## Ejercicio 3

Primero hago un Radix Sort por nombre de canción, pues tiene caracteres normales, y así obtengo una complejidad de O(n * |t|). Luego vuelvo a hacer lo mismo pero con los nombres de los discos, obteniendo una complejidad de O(n * |d|). Luego hay que ordenarlo por nombre de banda, lo podemos hacer en un diccAvl juntando en una lista o arreglo sus diferentes discos y canciones, obteniendo una complejidad de O(n * log(b)). Finalmente hay que recorrer esta estructura adecuadamente para llevarlo nuevamente a un arreglo. Su complejidad final es de O(n*|t| + n*|d| + n*log b). Cada término de la suma es menor que O(n · log(b) · |d| · |t|). Es decir,
- O(n * |t|) ∈ O(n · log(b) · |d| · |t|)
- O(n * |d|) ∈ O(n · log(b) · |d| · |t|)
- O(n * log(b)) ∈ O(n · log(b) · |d| · |t|)