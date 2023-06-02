# Módulo colaDePrioridadMax


## Interfaz

### Parámetros formales


### Operaciones básicas

```
PRÓXIMO(in c: colaDePrioridadMax) ➔ res: tupla(nat, iterador(persona))
    Pre ≡ {longitud(c.heap) > 0}
	Post ≡ {res = prim(c.heap)}
	Complejidad ≡ O(1)
	Aliasing ≡ Devuelve la tupla por referencia
	Descripcion ≡ Devuelve el elemento de mayor prioridad
```

```
MODIFICAR(inout c: colaDePrioridadMax, in p: persona, in gasto: int)
    Pre ≡ {c = c0}
	Post ≡ {c.heap[significado(p,c.indicePersona)] > c.heap.prim([significado(p,c.indicePersona)]) }
	Complejidad ≡ O(log n), siendo n el largo del heap
	Aliasing ≡ Modifica la cola pasada por referencia
	Descripcion ≡ Modifica un elemento de la cola de prioridad
```

```
CONSTRUIR(inout c: colaDePrioridadMax, in ca: conjLineal(persona))
    Pre ≡ {true}
    Post ≡ {la cola creada tiene en su heap y el diccLog a las personas dadas}
    Complejidad ≡ O(A²)
    Aliasing ≡ Modifica la cola pasada por referencia
    Descripcion ≡ Crea la cola de prioridad con las personas dadas
```

## Representación

Es en esencia un maximum heap respecto al primer elemento de la tupla del vector llamado heap, y un minimum heap respecto al segundo elemento. O sea, si tenemos 3 elementos en el techo del heap con el mismo elemento, se ordenarán con prioridad del más minimo elemento del tipo β. Además, tiene una estructura logarítmica para poder acceder a los elementos del heap de manera logarítmica, en vez de hacerlo con complejidad lineal. 
Si una persona está en el diccionario de colaDePrioridadMax entonces existe una tupla en el vector de colaDePrioridadMax que tiene el iterador que apunta a esa persona y su significado, más aún, está en la posición del vector que indica el significado del diccionario. Además el largo del vector es igual a la cantidad de elementos del conjunto de claves del diccionario.

### Estructura

Se representa con `cola`,  
donde `cola` es:

```
tupla<
	  heap: vector<tupla(gasto: nat, itPer: iterador(persona))>,
	  indicePersona: diccLog(persona, indice: nat)
	 >
```

### Invariante de representación:

```
Rep: cola ➔ bool
Rep(c) ≡
    (∀a: persona) a ∈ claves(π₂(colaDePrioridadMax)) ➔ (∃ t: tupla(nat, tupla(persona, nat))) está(t, π₁(colaDePrioridadMax))
    ∧ a = π₁(π₂(t))  ∧ obtener(a, π₂(colaDePrioridadMax)) = π₂(π₂(t)) ∧ personaEnLaPosicion(π₁(colaDePrioridadMax), a, π₂(π₂(t)))
	∧ long(π₁(colaDePrioridadMax)) = #claves(π₂(colaDePrioridadMax)) ∧
    (∀i: nat)(0 ≤ i <  (longitud(c) / 2) - 1  ➔ valorDePosicion(c.heap, i).gasto ≥ valorDePosicion(c.heap, 2*i+1).gasto  ∧
    ((2*i + 2) < longitud(h)) ➔ valorDePosicion(c.heap, i).gasto ≥ valorDePosicion(c.heap, 2*i+2).gasto) ∧ 
    (∀t: tupla(nat, tupla(persona, nat)))(está(t, colaDePrioridadMax.heap) ∧ π₁(t) = valorDePosicion(c.heap, i).gasto 
    ➔ π₁(π₂(t)) < π₁(valorDePosicion(c.heap, i).itPer))
```

Predicados y funciones auxiliares:

```
personaEnLaPosicion: vector(tupla(nat, tupla(perona, indice))) x persona x indice ➔ bool
personaEnLaPosicion(c, a, i) ≡ π₁(π₂(valorDePosicion(c, i))) = a

valorDePosicion: vector(nat) x indice ➔ nat
valorDePosicion(v, i) ≡ if (i = 0) then prim(v)
                        else valorDePosicion(fin(v), i-1)
                        fi
```

### Función de abstracción:

```
Abs: c ➔ TAD Cola de Prioridad

Abs(c)≡ cola: colaPrior / 
        vacia?(cola) ⇔ (vacio?(c.heap) ∧ vacia?(claves(c.indicePersona))) ∧L
        (¬vacia?(cola) ➔ proximo(cola) = c.heap[0] ∧ 
        desencolar(cola) = tupla<fin(c.heap), borrar(π_1(π_2(c.heap[0])),c.indicePersona)>)
```

## Algoritmos

```c
iCONSTRUIR(inout c: colaDePrioridadMax, in ca: conjLineal(persona)) {

// armo el diccLog con todas las personas e indice 0 (momentaneo)
    it = crearIt(ca);
	while(haySiguiente(it)) { // O(A)
		definir(c.indicePersona, siguiente(it), 0); // O(log A)
		it = siguiente(it);
    }

    // ahora creo un iterador del dicc
    it = crearIt(c.indicePersona);
    // hago un ciclo en el diccionario para pushear a todas las personas al heap y le asigno el indice
    que le corresponde
    while(haySiguiente(it)) { // O(A)
        agregarAtras(c.heap, <0, siguiente(it)>); // O(A)
        siguienteSignificado(it) = longitud(c.heap) - 1; // O(1)
    }
}
```

```c
iPROXIMO(in c: colaDePrioridad) ➔ res = tupla(nat, iterador(persona)) {
	return c.heap[0];
}
```

```c
iMODIFICAR(inout c: colaDePrioridadMax, in a: persona, in gasto: int){
	indice = significado(c.indicePersona, a);		// O(log A)
    c.heap[indice].gastoTotal += gasto;		// O(1) acceder al elemento

    if( gasto > 0) { 
        if(indice mod 2 == 0) {
            indicePadre = indice/2 - 1;
    } else { 
        indicePadre = indice/2;
    }
    while (indicePadre >= 0){
        if(c.heap[indice].gastoTotal > c.heap[indicePadre].gastoTotal OR 
        (c.heap[indice].gastoTotal == c.heap[indicePadre].gastoTotal AND siguienteClave(c.heap[indice].itPer)  < siguienteClave(c.heap[indicePadre].itPer))) {
            
            swap(c.heap, indice, indicePadre);

            siguienteSignificado(c.heap[indice].itPer) = indicePadre;
            siguienteSignificado(c.heap[indicePadre].itPer) = indice;

            indice = indicePadre;

            if(indice mod 2 == 0)
                indicePadre = indice/2 - 1;		// esto lleva al ciclo a un O(log A)
            else						// seria un log de base 2
                indicePadre = indice/2;
            }
        }
    }
    // si es negativo el gasto
    else { 
        // veo cuántos hijos tiene
        // si tiene dos hijos
        if(2*indice+2 < longitud(c.heap)) { 
            indiceHijoIzq = 2*indice+2;
            indiceHijoDer = 2*indice+1;
            while(indiceHijoDer >= longitud(c.heap)) {
                // veo cual es el hijo mayor
                if (c.heap[indiceHijoIzq] > c.heap[indiceHijoDer]){
                    indiceHijoMayor =  indiceHijoIzq;
                } else {
                    indiceHijoMayor = indiceHijoDer;
                }
                // hago swap con hijo mayor
                if (c.heap[indice].gastoTotal < c.heap[indiceHijoMayor].gastoTotal OR 
                (c.heap[indice].gastoTotal == c.heap[indiceHijoMayor].gastoTotal AND
                siguienteClave(c.heap[indice].itPer)  > siguienteClave(c.heap[indiceH ijoMayor].itPer))) { 
                    swap(c.heap, indice, indiceHijoMayor);
                    siguienteSignificado(c.heap[indice].itPer) = indiceHijoMayor;
                    siguienteSignificado(c.heap[indiceHijoMayor].itPer) = indice;
                    indice = indiceHijoMayor;
                    indiceHijoIzq = 2*indice+2;
                    indiceHijoDer = 2*indice+1;
                } else { 
                    return;	
                }
            }
    }
        // veo si tiene 1 hijo. Si es asi a lo sumo solo hariamos 1 swap
        if(2*indice+1 < longitud(c.heap)) {
            indiceHijoIzq = 2*indice+1;

            if (c.heap[indice].gastoTotal < c.heap[indiceHijoIzq].gastoTotal OR 
            (c.heap[indice].gastoTotal == c.heap[indiceHijoIzq].gastoTotal AND
            siguienteClave(c.heap[indice].itPer)  > siguienteClave(c.heap[indiceHijoIzq].itPer))) {
                swap(c.heap, indice, indiceHijoIzq);
                siguienteSignificado(c.heap[indice].itPer) = indiceHijoIzq;
                siguienteSignificado(c.heap[indiceHijoIzq].itPer) = indice;
            } else {
                return;
            }
        }
    }
}
```