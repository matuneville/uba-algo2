## Ejercicio 1

```
Exploracion se representa con
  tupla <
        roversActivos:      conjLog(rover),
        roversInactivos:    conjLog(rover),
        infoRovers:         diccLog(rover, tupla<
                                                activo?:        bool,
                                                movimientos:    lista(celda),
                                                itItinerario:   itDiccTrie
                                                >),
        itinerario:         diccTrie(direccion, nat)
        >
```

- Para desplegar un rover, lo agrego a _roversActivos_ en O(log r).Para desactivarlo, elimino al rover de _roversActivos_ y luego lo añado a _roversInactivos_, esto cuesta O(log r + log r) = O(log r). También hay que añadirlo a _infoRovers_, que cuesta O(log r), y definirlo con la siguiente info: <true, {(0,0)}, iterador a raíz de _itinerario_>.
- Cuando se mueve un rover, hay que acceder a él en _infoRovers_ y añadir la nueva celda al final en _movimientos_ que cuesta O(1) por ser una linked list, y, accediendo al iterador _itItinerario_, acceder a la siguiente dirección en el trie _itinerario_, o definir el siguiente Nodo si no está, y sumar +1 en su significado, para saber que un rover pasó por esa posición; tambien hay que generar un nuevo iterador a esta nueva clave-valor del trie para luego definirlo nuevamente en _itItinerario_ como su nueva última posición. Lo de acceder al iterador, buscar la nueva direccion en el trie y definir +1, está acotado porque se hace siempre de igual forma, y buscar la nueva dirección en el trie es O(1) porque hay una cantidad acotada de direcciones. Luego volver a definir el iterador cuesta nuevamente O(log r). Esto cuesta, en total O(log r + log r) = O(log r).
- Para saber dónde está un rover en concreto, se lo busca en _infoRovers_ en O(log r) y se devuelve el último elemento de la linked list _movimientos_, que cuesta O(1). La complejidad final es O(log r)
- Para saber cuántos rovers realizaron un determinado recorrido, hay que ir buscando cada dirección en el trie, que esto cuesta O(1), y, al llegar hasta la última dirección, devolver el natural de su significado, que será la cantidad de rovers que llegaron hasta esta posición. Como hay que hacer long(T) veces algo que cuesta O(1), la complejidad es de O(long(T)).
- Se devuelven _roversActivos_ o _roversInactivos_.
  
Algoritmo para _Mover_:

```cpp
iMOVER(inout exp: Exploracion, in r: rover, in d: dirección)

    nuevoMovimientos = (obtener(exp.infoRovers, r)).movimientos // O(log r), referencia modificable

    nuevaPosición = <0,0>
    if (d == 'N')
        nuevaPosición = <π1(ultimo(nuevoMovimientos)), π2(ultimo(nuevoMovimientos))+1> // O(1)
    else if (d == 'S')
        nuevaPosición = <π1(ultimo(nuevoMovimientos)), π2(ultimo(nuevoMovimientos))-1> // O(1)
    else if (d == 'E')
        nuevaPosición = <π1(ultimo(nuevoMovimientos))-1, π2(ultimo(nuevoMovimientos))> // O(1)
    else if (d == 'O')
        nuevaPosición = <π1(ultimo(nuevoMovimientos))+1, π2(ultimo(nuevoMovimientos))> // O(1)

    agregarAtras(nuevoMovimientos, nuevaPosición) // O(1), modifica la referencia a lista movimientos

    iterador = (obtener(exp.infoRovers, r)).itItinerario // O(log r), referencia modificable

    nodoTrie = siguiente(iterador) // O(1), referencia modificable
    
    if (not def?(nodoTrie, d))
        definir(nodoTrie, d, 1) // O(1)
    else
        significado(nodoTrie, d) ++ // O(1), referencia modificable
    
    nuevoIterador = crearIterador(claveValor(nodoTrie, d)) // O(1)

    iterador = nuevoIterador // O(1), modifica la referencia

```


## Ejercicio 2
Ya lo hice en otro parcial