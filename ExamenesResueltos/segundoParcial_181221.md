## Ejercicio 1

Lo que tengo que hacer es primero ordenarlo por la cantidad de regalos, pues es lo menos importante, y luego por zona horaria, que es lo más importante, con un algoritmo balanceado para respetar lo pedido (siempre se ordena primero por lo menos importante). Primero recorremos el arreglo y separamos en otros dos arreglos aquellas tuplas en las que un niño haya pedido más de 3n regalos, y otra en la que hayan pedido menos de 3n. Sabemos que el primer arreglo, el de niños que hayan pedido más de 3n regalos, tiene su largo acotado por 1000, por lo que lo podemos sortear con cualquier algoritmo pues su complejidad será de $O(1)$. Luego el otro arreglo, sabemos que su largo será como máximo de n, y tambien que todos los numeros correspondientes a la cantidad de regalos serán como mucho de 3n. Esto quiere decir que podemos usar un Bucket Sort usando un arreglo de largo 3n con listas en las que pushearemos las tuplas. Esta complejidad será de $O(n + 3n) = O(n)$.  
Una vez que ya tenemos estos dos arreglos por cantidad de regalos; al de cantidad de regalos menor a 3n le hacemos un append con aquel que sea de regalos mayores a 3n. Con esto, solo nos queda sortearlo según las zonas horarias. Sabemos que el primer elemento de la tupla corresponde a esto, y que la mayor zona horaria está acotada por z, por lo que podemos nuevamente hacer un Bucket Sort en el que juntemos en un arreglo de largo z aquellas listas de tuplas de mismo horario, manteniendo el orden por el que lo ordenamos previamente. Con esto tendremos una complejidad de $O(z + n)$. Finalmente la complejidad será de $O(z + n)$.  
_Disclaimer: me dio fiaca hacer este algoritmo pero es simple siguiente los pasos descriptos, asi que la siguiente resolución es dada por ChatGPT_

```cpp
typedef pair<int, int> Tupla;

vector<Tupla> OrdenEntregas(int z, vector<Tupla> pedidos) {
    vector<Tupla> masDe3N;
    vector<list<Tupla>> menosDe3N(3 * z + 1);

    // Separar las tuplas en dos arreglos
    for (const Tupla& pedido : pedidos) {
        if (pedido.second > 3 * pedidos.size()) {
            masDe3N.push_back(pedido);
        } else {
            menosDe3N[pedido.second].push_back(pedido);
        }
    }

    // Ordenar las tuplas en el arreglo masDe3N por cantidad de regalos (será O(1) pues su largo es siempre <= 1000)
    sortingMagicoIdealDeCualquierComplejidad(masDe3N);

    // Ordenar las tuplas en el arreglo menosDe3N por cantidad de regalos (usando Bucket Sort)
    vector<Tupla> ordenado;
    for (int i = 3 * z; i >= 0; i--) {
        for (const Tupla& pedido : menosDe3N[i]) {
            ordenado.push_back(pedido);
        }
    }
    // Combinar los arreglos
    ordenado.insert(ordenado.end(), masDe3N.begin(), masDe3N.end());

    // Ordenar las tuplas por zona horaria (usando Bucket Sort nuevamente)
    vector<list<Tupla>> buckets(z + 1);
    for (const Tupla& pedido : ordenado) {
        buckets[pedido.first].push_back(pedido);
    }

    vector<Tupla> resultado;
    for (int i = 1; i <= z; i++) {
        for (const Tupla& pedido : buckets[i]) {
            resultado.push_back(pedido);
        }
    }

    return resultado;
}
```

## Ejercicio 2

