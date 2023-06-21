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