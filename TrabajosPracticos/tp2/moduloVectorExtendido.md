# Extensión del módulo Vector

## Otras operaciones

```
SWAP(inout v: vector(α), in i: nat, in j: nat)
    Pre ≡ {los dos índices deben estar en el rango del vector}
    Post ≡ {el elemento en la posición ‘i’ pasa a estar en la posición ‘j’ y viceversa. Los demás elementos se mantienen como estaban}
    Complejidad ≡ Θ(1)
    Aliasing ≡ Modifica el vector pasado por referencia
    Descripcion ≡ Intercambia el elemento del indice ‘i’ con el del indice ‘j’
```

```
ORDENAR_POR_MENOR_STOCK(inout v: vector(tupla(id: nat, stock: nat)))
    Pre ≡ {los ID no se repiten y el vector es no vacío}
    Post ≡ {los elementos quedan ordenados de menor a mayor stock. Se desempata por menor ID}
    Complejidad ≡ O(n²), n siendo el largo del vector
    Aliasing ≡ Modifica el vector pasado por referencia
    Descripcion ≡ Ordena los elementos de tal forma que el criterio principal es tener los stock de menor a mayor. En caso de que dos puestos tengan el mismo stock, se desempata por ID
```

## Algoritmos

```c
iSWAP(inout v: vector(α), in i: nat, in j: nat) { 
	guardoValor = v[i];
	v[i] = v[j];
	v[j] = guardoValor;
}
```

```c
iORDENAR_POR_MENOR_STOCK(inout v: vector(tupla(id: nat, stock: nat))) { 
	for(i = 0; i < longitud(v); i++) { // selection sort O(n2)
		indiceDelMinimo = i;
        for(j = 1; i < longitud(v); j++) { 
            if (v[j].stock < v[indiceDelMinimo].stock)
                indiceDelMinimo = j;
            if (v[j].stock == v[indiceDelMinimo].stock AND v[j].id < v[indiceDelMinimo].id)
                indiceDelMinimo = j;
        }
        swap(v, i, indiceDelMinimo); 
    }
}
```