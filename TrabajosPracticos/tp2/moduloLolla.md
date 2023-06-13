# Módulo Lolla-Patuza

## Interfaz

### Parámetros formales


### Operaciones básicas

```
NUEVO_LOLLA (in dp: diccLog(ID, puesto), in ca: conjLineal(persona)) ➔ lolla
    Pre ≡ {vendenAlMismoPrecio(significados(dp)) ∧ NoVendieronAun(significados(dp)) ∧ ¬∅?(ca) ∧ ¬∅?(claves(dp))}
    Post ≡ {puestos(l) = significados(dp) ∧ personas(l) = ca}
    Complejidad ≡ O(A²)
    Aliasing ≡ Crea un nuevo objeto Lolla modificable
    Descripción ≡ Crea una nueva instancia de Lolla-Patuza
```

```
COMPRA (inout l: lolla, in a: persona, in id: nat, in i: item, in cant: nat) 
    Pre ≡ {l = l0 ∧ a ∈ personas(l) ∧ def?(p, puestos(l)) ∧L haySuficiente?(obtener(pi, puestos(l)), i, c)} 
    Post ≡ {l = vender(l0, id, a, i, cant)}
    Complejidad ≡ O(log A + log I + log P + log cant)
    Aliasing ≡ 
    Descripción ≡ Modifica el historial de ventas de un puestos, el historial de compras de una persona, y el registro de todas las compras en el lolla

```

```
HACKEAR (inout l: lolla, in a : persona, in i : item)
    Pre ≡ {l = l0  ∧  ConsumioSinPromoEnAlgunPuesto(l0, a, i)}
    Post ≡ {l = hackear(l0, a, i)}
    Complejidad ≡ O(log A + log I + log P)
    Aliasing ≡ 
    Descripción ≡ Hackea la compra del ítem dado al puesto
```

```
GASTO_TOTAL_DE (in l: lolla, in a: persona) ➔ res: nat
    Pre ≡  {a ∈ personas(l)}
    Post ≡ {res = gastoTotal(l, a)}
    Complejidad ≡ O(log A)
    Aliasing ≡ 
    Descripción ≡ Devuelve el gasto total de esa persona en el lolla
```

```
MAYOR_GASTADOR (in l: lolla) ➔ res: persona
    Pre ≡  {true}
    Post ≡ {res = masGasto(l)}
    Complejidad ≡ O(1)
    Aliasing ≡ Devuelve una persona por referencia
    Descripción ≡ Devuelve a la persona que más gasto
```

```
MENOR_STOCK (in l: lolla, in i: item) ➔ res: puesto
    Pre ≡  {(∃p: puesto)(p ∈ puestos(l) ∧ i ∈ menu(p) )}
    Post ≡ {res = menorStock(l, i)}
    Complejidad ≡ O(P * log I)
    Aliasing ≡ 
    Descripción ≡ Devuelve el puesto que menor stock tiene del item dado
```

```
PERSONAS (in l: lolla) ⇒ res: conjLog(persona)
    Pre ≡  {true}
    Post ≡ {res = personas(l)}
    Complejidad ≡ O(1)
    Aliasing ≡ Devuelve una referencia a conjunto
    Descripción ≡ Devuelve el conjunto de personas de la instancia Lolla
```

```
PUESTOS (in l: lolla) ⇒ res: conjLog(puesto)
    Pre ≡  {true}
    Post ≡ {res = puestos(l)}
    Complejidad ≡ O(1)
    Aliasing ≡ Devuelve una referencia a conjunto
    Descripción ≡ Devuelve el conjunto de puestos de la instancia Lolla
```

## Representación

### Estructura

TAD Lolla-Patuza se representa con `l`,  
donde `l` es:
```
tupla<
      personas          : conjLineal(persona),
      puestosPorID      : diccLog(ID, puesto),
      gastoTotal        : colaDePrioridadMax,
      puestosHackeables : diccLog(persona, diccLog(item, diccLog(ID, puesto)))
     >
```

### Invariante de representación:
Hay que chequear que:

1. El tamaño de la colaDePrioridadMax tiene que ser igual a la cantidad de personas
2. Los ID de puestosHackeables tienen que pertenecer a las claves de puestosPorID, y cada puesto que le corresponde a cada ID de puestosHackeables también tiene que ser el significado en puestosPorID. Además los items pertenecen al menú de ese puesto
3. El conjunto de claves de puestosHackeables tiene que ser igual al conjLineal de personas

```
Rep: lolla ➔ bool
Rep(l) ≡ (1) ∧ (2) ∧ (3)

(1) ≡ #l.personas = tamaño(l.gastoTotal))

(2) ≡ (∀a: persona)(∀i: item)(∀id: nat)(a ∈ claves(l.puestosHackeables) ∧ i ∈ claves(significado(l.puestosHackeables, a)) ∧L
                id ∈ claves(obtener(obtener(l.puestosHackeables, a), i))) ➔L id ∈ claves(l.puestosPorID) ∧L
                obtener(id, obtener(i, obtener(l.puestosHackeables, a))) = obtener(id, l.puestosPorID) ∧L i ∈ menu(obtener(id, l.puestosPorID)

(3) ≡ claves(l.puestosHackeables) = l.personas
```

### Función de abstracción:

```
Abs: estr ➔ TAD Lolla Patuza
Abs(l) ≡ lp : lolla /
    puestos(lp) = l.puestosPorID  ∧
	personas(lp) = l.personas
```

## Algoritmos

```c
iNUEVO_LOLLA(in dp: diccLog(ID, puesto), in ca: conjLineal(persona)) -> lolla { 
    personas = ca;  
    puestosPorID = dp;	       
    gastoTotal.heap	= < >;
    gastoTotal.indicePersona = vacio(); 
    puestosHackeables = vacio();  

    // armo gastoTotal
    construir(l.gastoTotal, ca); // O(A* log A)

    // defino a todas las personas en primer diccLog poniendo como significado un diccLog vacío
    it = crearIt(ca);
    while(haySiguiente(it)){ // O(A)
        definir(l.puestosHackeables, siguiente(it), vacio()); // O(log A)
        it = siguiente(it);	
    }
}
```

```c
iCOMPRA (inout l: lolla, in a: persona, in ID: nat, in i: item, in cant: nat) {
    // busco el puesto
    p = significado(l.puestosPorID, ID);		// O(log P)	

    // calculo cuánto es el gasto de la compra
    precioTotal = precio_total(p, i, cant);	// O(log I)
		
    // tengo que modificar gastoTotal (modificar heap  e indicePersona)
    modificar(l.gastoTotal, a, precioTotal);	// O(log A)
	
    descuento = descuento_de(p, i, cant) // O(log I)
    diccPer = significado(l.puestosHackeables, a) // O(log P)
    
    // modificamos puestosHackeables
    if(descuento == 0) {
        if(definido?significado(diccPer, i){ // O(log I)
            diccItem = significado(diccPer, i);
            if(!definido?(significado(diccItem, i), id) { // O(log P)
                definir(significado(diccItem, i), id, p); // O(log P)
            }
        }
        else { 
            definir(diccPer, i, vacio()); // O(log I)
            diccItem = significado(diccPer, i); // O(log I)
            definir(significado(diccDeItem, i), id, p);  // O(log P)
        }
    }
    // modifico el puesto
    registrar_compra(p,a,i,c); // O(log A + log I + log cant)
}
```

```c
iHACKEAR(inout l: lolla, in a: persona, in i: item) {
    // busco el puesto
    diccPerItem = significado(significado(l.puestosHackeables, a), i)  // O(log A + log I)
    puestoAHackearIt = crearIt(diccPerItem);   // O(1)
    puestoHack = siguienteSignificado(puestoAHackearit); // O(1)

    // modifico el puesto
    registrar_hackeo(puestoHack, a, i); // O(log A + log I) 

    // si deja de ser hackeable, lo quito
    if(!esHackeable?(puestoHack, a, i)) { // O(log A + log I)
        borrar(diccPerItem, puestoHack); // O(log P)
    }

    // modificamos la cola de prioridad
    modificar(l.gastoTotal, a, - gastoTotal); 	// O(log A) (el gasto se pasa como negativo para que lo reste)
} 

```

```c
iGASTO_TOTAL_DE(in l: lolla, in a: persona) -> nat {
    return devolver_gasto(a, l.gastoTotal); // O(log A)
}
```

```c
iMAYOR_GASTADOR(in l: lolla) -> persona {
    proximo(l.gastoTotal) // O(1)
}
```

```c
MENOR_STOCK(in l: lolla, in i: item) -> ID {
    // creo iterador que recorra el diccionario de puestos
    it = crearIt(l.puestosPorID); // O(1)
    // asigno al primero como el menor
    menor = stock(siguienteSignificado(it),i); // O(log I)
    menorID = siguienteClave; // O(1)
    // recorro todos los puestos y si hay uno con menor stock se actualiza
    while(haySiguiente(it)) { // O(P * log I)
    	id = siguienteClave(it)
    	puesto = siguienteSignificado(it)
        if(stock(puesto, i) < menor){ // O(log I)
    	    menor = stock(puesto, i); // O(log I)
    	    menorID = id;
        }
        // aquí desempato por menor id en el caso que sean iguales
        else if(stock(puesto, i) == menor){ // O(log I)
            if(id < menorID){ 
            menor = stock(puesto, i); // O(log I)
            menorID = id; 
            }
        }
    avanzar(it); // O(1)
    }
return menorID;
}
```

```c
iPERSONAS(in l : lolla) -> conjLog(persona) {
    return l.personas;	// O(1)
}
```

```c
iPUESTOS(in l : lolla) -> diccLog(ID, puesto) {
    return l.puestosPorID;	// O(1)
}
```
