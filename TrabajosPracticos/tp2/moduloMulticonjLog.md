# Módulo multiConjLog

## Interfaz

### Parámetros formales


### Operaciones básicas

```
VACIO() ➔ res: multiConjLog(nat)
    Pre ≡  {true}
    Post ≡ {res = ∅}
    Complejidad ≡ O(1)
    Aliasing ≡ Devuelve un multiConjLog por referencia
    Descripción ≡ Crea un nuevo multiconjunto logarítmico de nat vacío 
```

```
VACIO?(in M:multiConj(nat)) ➔ res: bool
    Pre ≡ {true}
    Post ≡ {res = vacio?(M)}
    Complejidad ≡ O(1)
    Descripción ≡ Dado un multiconjLog de nat devuelve true si este está vacío. En caso contrario devuelve false. 
```

```
AGREGAR (inout M: multiConj(nat), in a: nat)
    Pre ≡ {true}
    Post ≡ {res = Ag(a, M)}
    Complejidad ≡ O(log(M)), siendo M el tamaño de claves-valores
    Aliasing ≡ Modifica el multiConjLog pasado por referencia
    Descripción ≡ Agrega el elemento al multiConjunto
```

```
BORRAR (inout M: multiConj(nat), in a: nat) 
    Pre ≡ {M = M0 ∧ a ∈ M}
    Post ≡ {M = M0 - {a}}
    Complejidad: O(log(M)), siendo M el tamaño de claves-valores
    Aliasing ≡ Modifica el multiConjLog pasado por referencia
    Descripción: Borra el elemento del multi conjunto. 
```

## Representación

### Estructura

Se representa con `m`,  
donde `m` es:

```
tupla<
	  cantApariciones: diccLog(nat, cant)
	 >
```

### Invariante de representación:

```
Rep: multiConjLog ➔ bool
Rep(m) ≡ ¬(∃k: nat)(def?(k, m) ∧ obtener(k, m) = 0)
```

### Función de abstracción:

```
Abs: multiConjLog ➔ TAD multiconj(nat)
Abs(m) ≡ mconj: multiconj(nat) /
    (∀k: nat)(def?(k, m) ➔ k ∈ mconj ∧ obtener(k, m) = #(k, mconj)) ∧
    (∀n: nat)(n ∈ mconj ➔ def?(n, m) ∧ #(n, mc) = obtener(n, m))  
```

## Algoritmos

```c
iVacio(in M: multiConjLog(nat)) -> res:multiConjLog(nat){
	res = ∅;
}
```

```c
iAgregar (in M : multiConj(nat), in a : nat){
	if (Definido?(M.cantApariciones, a)){
		definir(M.cantApariciones, a, significado(a,M.cantApariciones) + 1);
    }
    else {
		definir(M.cantApariciones, a, significado(a,M.cantApariciones));
    }
}
```

```c
iBorrar(inout M: multiConj(nat): in a :nat){
    if (significado(M.cantApariciones, a) > 1){
		definir(M.cantApariciones, a, significado(a,M.cantApariciones) - 1)
    }
    else {
		Borrar(M.cantApariciones, a)
    }
}

```

```c
iVACIO?(in M: multiConjLog(nat)) -> bool{
    return M = vacio();
}
```