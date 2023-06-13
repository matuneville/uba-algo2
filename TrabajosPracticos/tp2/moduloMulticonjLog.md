# Módulo multiConjLog

## Interfaz

### Parámetros formales


### Operaciones básicas

```
VACIO() ➔ res: multiConjLog(α)
    Pre ≡  {true}
    Post ≡ {res = ∅}
    Complejidad ≡ O(1)
    Aliasing ≡ Devuelve un multiConjLog por referencia
    Descripción ≡ Crea un nuevo multiconjunto logarítmico de α vacío 
```

```
VACIO?(in M:multiConj(α)) ➔ res: bool
    Pre ≡ {true}
    Post ≡ {res = vacio?(M)}
    Complejidad ≡ O(1)
    Descripción ≡ Dado un multiconjLog de α devuelve true si este está vacío. En caso contrario devuelve false. 
```

```
AGREGAR (inout M: multiConj(α), in a: α)
    Pre ≡ {true}
    Post ≡ {res = Ag(a, M)}
    Complejidad ≡ O(log(M)), siendo M el tamaño de claves-valores
    Aliasing ≡ 
    Descripción ≡ Agrega el elemento al multiConjunto
```

```
BORRAR (inout M: multiConj(α), in a: α) 
    Pre ≡ {M = M0 ∧ a ∈ M}
    Post ≡ {M = M0 - {a}}
    Complejidad: O(log(M)), siendo M el tamaño de claves-valores
    Aliasing ≡ Modifica el multiConjLog pasado por referencia
    Descripción: Borra el elemento del multiConjunto. 
```

## Representación

### Estructura

Se representa con `m`,  
donde `m` es:

```
cantApariciones: diccLog(α, cant)
```

### Invariante de representación:

```
Rep: multiConjLog ➔ bool
Rep(m) ≡ ¬(∃k: α)(def?(k, m) ∧ obtener(k, m) = 0)
```

### Función de abstracción:

```
Abs: multiConjLog ➔ TAD multiconj(α)
Abs(m) ≡ mconj: multiconj(α) /
    (∀k: α)(def?(k, m) ➔ k ∈ mconj ∧ obtener(k, m) = #(k, mconj)) ∧
    (∀n: α)(n ∈ mconj ➔ def?(n, m) ∧ #(n, mc) = obtener(n, m))  
```

## Algoritmos

```c
iVacio(in M: multiConjLog(α)) -> res:multiConjLog(α){
	res = {};
}
```

```c
iAgregar (inout M : multiConjLog(α), in a : α){
	if (Definido?(M.cantApariciones, a)){
		significado(a,M.cantApariciones) += 1;
    }
    else {
		definir(M.cantApariciones, a, 1);
    }
}
```

```c
iBorrar(inout M: multiConjLog(α): in a :α){
    if (significado(M.cantApariciones, a) > 1){
		significado(a,M.cantApariciones) -= 1;
    }
    else {
		borrar(M.cantApariciones, a)
    }
}

```

```c
iVACIO?(in M: multiConjLog(α)) -> bool{
    return vacio() == M.cantApariciones;
}
```
