# Módulo colaDePrioridadMax


## Interfaz


### Operaciones básicas

```
PRÓXIMO(in c: colaDePrioridadMax) ➔ res: nat)
    Pre ≡ {¬vacia?(c)}
    Post ≡ {res = proximo(c)}
    Complejidad ≡ O(1)
    Aliasing ≡ Devuelve el nat por referencia
    Descripcion ≡ Devuelve el elemento de mayor prioridad
```

```
MODIFICAR(inout c: colaDePrioridadMax, in p: persona, in gasto: int)
    Pre ≡ {la persona está en colaDePrioridadMax}
    Post ≡ {El tamaño de colaDePrioridadMax se mantiene igual. 
            El gasto que se modifica tiene que corresponder a la persona. 
            El resto de elementos de colaDePrioridadMax tienen que mantener el mismo valor}
    Complejidad ≡ O(log n), siendo n el largo del heap
    Aliasing ≡ Modifica la cola pasada por referencia
    Descripcion ≡ Modifica un elemento de la cola de prioridad
```

```
CONSTRUIR(in ca: conjLineal(persona)) ➔ res: colaDePrioridadMax
    Pre ≡ {true}
    Post ≡ {la cola creada tiene en su heap y el diccLog a las personas dadas}
    Complejidad ≡ O(A * log A)
    Aliasing ≡
    Descripcion ≡ Crea la cola de prioridad con las personas dadas
```

```
DEVOLVER_GASTO(in a: persona, in c: colaDePrioridadMax) ➔ res: nat
    Pre ≡ {la persona está en la cola}
    Post ≡ {el resultado es el gasto de esa persona}
    Complejidad ≡ O(log A)
    Aliasing ≡
    Descripcion ≡ Dado una persona, devuelve el gasto total de esa persona
```

## Representación

Es en esencia un maximum heap respecto al primer elemento de la tupla del vector llamado heap, y un minimum heap respecto al segundo elemento. O sea, si tenemos 3 elementos en el techo del heap con el mismo elemento, se ordenarán con prioridad del más minimo elemento del tipo β. Además, tiene una estructura logarítmica para poder acceder a los elementos del heap de manera logarítmica, en vez de hacerlo con complejidad lineal. 
Si una persona está en el diccionario de colaDePrioridadMax entonces existe una tupla en el vector de colaDePrioridadMax que tiene el iterador que apunta a esa persona y su significado, más aún, está en la posición del vector que indica el significado del diccionario. Además el largo del vector es igual a la cantidad de elementos del conjunto de claves del diccionario.

### Estructura

Se representa con `c`,  
donde `c` es:

```
tupla<
     heap: vector<tupla(gasto: nat, itPer: itDicc(nat))>,
     indicePersona: diccLog(persona, indice: nat)
     >
```

### Invariante de representación:

```
Rep: cola ➔ bool
Rep(c) ≡
    (∀a: persona) a ∈ claves(π₂(colaDePrioridadMax)) ➔L (∃ t: tupla(nat, tupla(persona, nat))) ∧L está(t, π₁(colaDePrioridadMax))
    ∧ a = π₁(π₂(t))  ∧ obtener(a, π₂(colaDePrioridadMax)) = π₂(π₂(t)) ∧ personaEnLaPosicion(π₁(colaDePrioridadMax), a, π₂(π₂(t)))
	∧ long(π₁(colaDePrioridadMax)) = #claves(π₂(colaDePrioridadMax)) ∧
    (∀i: nat)(0 ≤ i <  (longitud(c) / 2) - 1  ➔L valorDePosicion(c.heap, i).gasto ≥ valorDePosicion(c.heap, 2*i+1).gasto  ∧
    ((2*i + 2) < longitud(h)) ➔L valorDePosicion(c.heap, i).gasto ≥ valorDePosicion(c.heap, 2*i+2).gasto) ∧L 
    (∀t: tupla( nat(tupla(persona, nat))(está(t, colaDePrioridadMax.heap) ∧L π₂(π₁(t)) = valorDePosicion(c.heap, i).gasto 
    ➔L π₂(π₁(t)) < π₁(valorDePosicion(c.heap, 2*i+1).itPer) ∧L π₂(π₁(it)) < π₁(valorDePosicion(c.heap, 2*i+2).itPer))
```

Predicados y funciones auxiliares:

```
(∀v: vector(α)), (∀a: persona), (∀i: nat)

personaEnLaPosicion: vector(tupla(nat, tupla(perona, indice))) x persona x indice ➔ bool
personaEnLaPosicion(v, a, i) ≡ π₁(π₂(valorDePosicion(v, a, i))) = a

valorDePosicion: vector(nat) x indice ➔ nat                  {i < long(v)}
valorDePosicion(v, i) ≡ if (i = 0) then prim(v)
                        else valorDePosicion(fin(v), i-1)
                        fi
```

### Función de abstracción:

```
Abs: c ➔ TAD Cola de Prioridad

Abs(c)≡ cola: colaPrior / 
        vacia?(cola) ⇔ (vacio?(c.heap)) ∧
        (¬vacia?(cola) ➔L proximo(cola) = c.heap[0]) ∧ 
        desencolar(cola) = <fin(c.heap), borrar(π_1(π_2(c.heap[0])),c.indicePersona)>)
```

## Algoritmos

```c
iCONSTRUIR(in ca: conjLineal(persona)) {
    c = <heap: <>, indicePersona: vacio()>

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
        agregarAtras(c.heap, <0, siguiente(it)>); // O(1)
        siguienteSignificado(it) = longitud(c.heap) - 1; // O(1)
    }
    return c;
}
```

```c
iPROXIMO(in c: colaDePrioridad) -> res = tupla(nat, iterador(persona)) {
	return c.heap[0]; // O(1)
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
    while (indicePadre >= 0){ // O(log A)
        if(c.heap[indice].gastoTotal > c.heap[indicePadre].gastoTotal OR 
        (c.heap[indice].gastoTotal == c.heap[indicePadre].gastoTotal AND siguienteClave(c.heap[indice].itPer)  < siguienteClave(c.heap[indicePadre].itPer))) { // O(1)
            
            swap(c.heap, indice, indicePadre); // O(1)

            siguienteSignificado(c.heap[indice].itPer) = indicePadre; // O(1)
            siguienteSignificado(c.heap[indicePadre].itPer) = indice; // O(1)

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
        if(2*indice+2 < longitud(c.heap)) { // O(1)
            indiceHijoIzq = 2*indice+2;
            indiceHijoDer = 2*indice+1;
            while(indiceHijoDer < longitud(c.heap)) { // O(log A)
                // veo cual es el hijo mayor
                if (c.heap[indiceHijoIzq] > c.heap[indiceHijoDer]){ // O(1)
                    indiceHijoMayor =  indiceHijoIzq;
                } else {
                    indiceHijoMayor = indiceHijoDer;
                }
                // hago swap con hijo mayor
                if (c.heap[indice].gastoTotal < c.heap[indiceHijoMayor].gastoTotal OR 
                (c.heap[indice].gastoTotal == c.heap[indiceHijoMayor].gastoTotal AND
                siguienteClave(c.heap[indice].itPer)  > siguienteClave(c.heap[indiceH ijoMayor].itPer))) {  // O(1)
                    swap(c.heap, indice, indiceHijoMayor); // O(1)
                    siguienteSignificado(c.heap[indice].itPer) = indiceHijoMayor; // O(1)
                    siguienteSignificado(c.heap[indiceHijoMayor].itPer) = indice; // O(1)
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
            siguienteClave(c.heap[indice].itPer)  > siguienteClave(c.heap[indiceHijoIzq].itPer))) { // O(1)
                swap(c.heap, indice, indiceHijoIzq); // O(1)
                siguienteSignificado(c.heap[indice].itPer) = indiceHijoIzq; // O(1)
                siguienteSignificado(c.heap[indiceHijoIzq].itPer) = indice; // O(1)
            } else {
                return;
            }
        }
    }
}
```

```c
iDEVOLVER_GASTO(in a: persona, in c: colaDePrioridadMax) -> res: int {
    // busco el índice de esa persona para saber dónde está en el vector
    i = significado(c.indicePersona, a) // O(log A)
    return = c.heap[i].gasto; // O(1)
}
```
