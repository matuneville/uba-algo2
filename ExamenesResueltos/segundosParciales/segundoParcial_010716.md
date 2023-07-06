## Ejercicio Monasterio

```
  tupla<
        simios:             conjLineal(simio),

        arbolesInfo:        vector(tupla<
                                        lianasCon:      vector(bool),
                                        simiosPorFalta: diccMaxHeap(faltas, itDiccTrie)
                                        >),

        simiosInfo:         diccTrie(simio, tupla<
                                                 árbol: nat,
                                                 itFaltas: itDiccMaxHeap
                                                 >),
        >
```

Soluciones pedidas:
- Para `saltar(s, ad)` lo que hago es buscar al mono en _simiosInfo_, que me cuesta O(|s|), agarro su iterador para eliminarlo del heap de _simiosPorFalta_, para que el mono ya no esté en su arbol anterior, y esto cuesta O(log Sa0). Luego, lo agrego al heap del árbol ad accediendo a él en O(1), y agregarlo cuesta O(log Sad), también lo defino con iterador al mono de _simiosInfo_, que ya lo tenía en el significado cuando estaba en el arbol anterior; luego me quedo con el iterador que genera esta definición para luego acceder nuevamente al mono y guardar su nuevo iterador a heap. También me fijo si habia liana conectando ambos árboles, que cuesta O(1), y si no había, accedo al iterador nuevo del mono en su nuevo arbol y le sumo una falta, que, al modificar el heap, cuesta O(log Sad). La complejidad final es de O(|s| + log Sa0 + log Sad)
- Para `requisar(a)` lo que hago es acceder al árbol en O(1) en _arbolesInfo_ y eliminar al mono con más faltas del heap _simiosPorFalta_, que es el de arriba de todo, y la rotación de acomodo del heap luego de esta eliminación cuesta O(log Sa). Pero antes de borrarlo del heap, accedo a su iterador del significado, y elimino al mono de _simiosIndo_, que me cuesta O(1) por tener su acceso directo con el iterador. Por lo tanto, la complejidad final es de O(log Sa).
- Para `todosLosSimios` lo que hago es devolver el conjunto _simios_ que cuesta O(1).
- Para `#faltas(s)` lo que hago es buscar al mono en _simiosInfo_ y luego, accediendo al iterador, devolver su clave que es la cantidad de faltas, y cuesta O(1). Por lo tanto, la complejidad queda O(|s|).
- Para `hayLiana(a1, a2)` lo que hago es acceder al a1 en _arbolesInfo_, que cuesta O(1), y luego en _lianasCon_ me fijo si accediendo a ar, que cuesta O(1), es true o false. Por lo tanto la complejidad queda O(1).

Aclaración: me di cuenta ahora que el diccMaxHeap no puede ser un diccionario porque no admite claves repetidas, pero se puede hacer todo de igual forma pero con un conjMaxHeap, es decir, un conjunto de tupla<faltas, itDiccTrie> implementado sobre un maxHeap, siendo la prioridad la mayor cantidad de faltas. Es practicamente lo mismo pero no tengo ganas de cambiar todas las palabras de antes jeje.