# Extensión del módulo Vector

## Otras operaciones

```
SWAP(inout v: vector(α), in i: nat, in j: nat)
    Pre ≡ {los dos índices deben estar en el rango del vector}
    Post ≡ {el elemento en la posición ‘i’ pasa a estar en la posición ‘j’ y viceversa. Los demás elementos se mantienen como estaban}
    Complejidad ≡ Θ(1)
    Aliasing ≡ 
    Descripcion ≡ Intercambia el elemento del indice ‘i’ con el del indice ‘j’
```

## Algoritmos

```c
iSWAP(inout v: vector(a), in i: nat, in j: nat) { 
	guardoValor = v[i];
	v[i] = v[j];
	v[j] = guardoValor;
}
```
