## Ejercicio 1

### Item A:

Estructura:
```
  tupla <
         votosPorAgrupacion:    vector(nat),
         candidatosConAgrup:    diccLog(candidato, conjLineal(itDicc)),
         mesasConInfo:          diccTrie(mesa, tupla < conjLineal(DNI),
                                                       vector(nat) >),
         votaronEn:             diccLog(DNI, tupla < cant,
                                                     itConj >),
         repetidos:             conjLineal(DNI)
        >
```

- _votosPorAgrupacion_ indica cuantos votos tiene cada agrupación política a través de un vector en el que cada indice lleva a una agrupacion distinta, pues estas se enumeran de 1 a G (y el vector es largo G), y en dicho indice están sus cantidades de votos
- _candidatosConAgrup_ indica para cada candidato a qué partidos pertenece, mediante un iterador que lleva al par clave-valor de _votosPorAgrupacion_
- _mesasConInfo_ indica en quienes votaron en esa mesa y los votos para cada partido
- _votaronEn_ indica en cuantas mesas distintas votaron las personas y lleva el iterador a repetidos si y solo si la cantidad es mayor a 1, es decir, si voto en distintas mesas
- _repetidos_ indica las personas repetidas en las votaciones

### Item B

`iVOTOS_PARA` se puede implementar buscando al candidato en _candidatosConAgrup_ en O(log K) y recorriendo su conjunto asociado en O(G), en el que cada iterador lleva a su par clave-valor de _votosPorAgrupacion_, para sumar sus votos. Esto da una complejidad de O(log K + G)

`iREPETIDOS` se implementa simplemente devolviendo su conjunto en O(n)

`REGISTAR` implica hacer varias cosas. Primero, se accede a la mesa en el Trie _mesasConInfo_, eso lleva O(M). Aqui se le registran las personas correspondientes y sus votos. Luego, hay que sumarle los votos a cada agrupacion recorriendo el multiconjunto y sumando a _votosPorAgrupacion_, y aqui habran tantos elementos como votantes afectados, por lo que su complejidad será de O(Va). Pero tambien tengo que eliminar la información previa en mi estructura (si había), por lo que al acceder al significado de la mesa en el trie, también recorro el vector y resto los votos a mi estructura; recorrer este vector será de O(G). Tambien, recorro el conjlineal de votantes previos y por cada uno lo busco en _votaronEn_, y si su cantidad en el significado es mayor o igual a 1, le resto 1. Esto tiene complejidad O(Va * log V).  
Por último, debo chequear si ya habian votado en otras mesas las personas afectadas en esta votación. Recorro linealmente el conjunto de votantes, y por cada uno lo busco en _votaronEn_; si la cantidad en el significado es 0, le sumo 1, y si es mayor o igual a 1, quiere decir que esa persona habia votado en otra mesa distina a la actual (por lo que hicimos antes de redefinir la cantidad de veces que voto la persona en las mesas), por lo que le sumo 1 a la cantidad y la añado a _repetidos_ si y solo si no estaba ya incluido, esto lo veo a través de su iterador, si es válido y me lleva a la persona, quiere decir que ya estaba definida y no la agrego, sino la añado. Todo esto se hace en O(Va * log V).  
La complejidad final es de O(M + G + Va * log V)

## Ejercicio 2
