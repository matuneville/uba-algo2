# Módulo Lolla-Patuza

simbolos × ➔ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ `` α ¬

## Interfaz

### Parámetros formales


### Operaciones básicas

```
NUEVO_LOLLA (in dp: diccLog(ID, puesto), in ca: conjLineal(persona), in ci: conjLineal(item)) ➔ lolla
    Pre ≡ {vendenAlMismoPrecio(significados(dp)) ∧ NoVendieronAun(significados(dp)) ∧ ¬∅?(ca) ∧ ¬∅?(claves(dp))}
    Post ≡ {puestos(l) = significados(dp) ∧ personas(l) = ca}
    Complejidad ≡ O( )
    Aliasing ≡ Crea un nuevo objeto Lolla modificable
    Descripción ≡ Crea una nueva instancia de Lolla-Patuza
```

```
COMPRA (inout l: lolla, in a: persona, in id: nat, in i: item, in cant: nat) 
    Pre ≡ {l = l0 ∧ a ∈ personas(l) ∧ def?(p, puestos(l)) ∧L haySuficiente?(obtener(pi, puestos(l)), i, c)} 
    Post ≡ {l = vender(l0, id, a, i, cant)}
    Complejidad ≡ O(log A + log I + log P + log cant)
    Aliasing ≡ Modifica el Lolla pasado por referencia
    Descripción ≡ Modifica el historial de ventas de un puestos, el historial de compras de una persona, y el registro de todas las compras en el lolla

```

```
HACKEAR (inout l: lolla, in a : persona, in i : item)
    Pre ≡ {l = l0  ∧  ConsumioSinPromoEnAlgunPuesto(l0, a, i)}
    Post ≡ {l = hackear(l0, a, i)}
    Complejidad ≡ O(log A + log I + log P)
    Aliasing ≡ Modifica el Lolla pasado por referencia
    Descripción ≡ Hackea la compra del ítem dado al puesto
```

```
GASTO_TOTAL_DE (in l: lolla, in a: persona) ➔ res: nat
    Pre ≡  {a ∈ personas(l)}
    Post ≡ {res = gastoTotal(l, a)}
    Complejidad ≡ O(log A)
    Aliasing ≡ Devuelve un nat por copia
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
    Complejidad ≡ O(P² + I²)
    Aliasing ≡ Devuelve una copia al puesto 
    Descripción ≡ Devuelve el puesto que menor stock tiene del item dado
```

```
PERSONAS (in l: lolla) ⇒ res: conjLog(persona)
    Pre ≡  {true}
    Post ≡ {res = personas(l)}
    Complejidad ≡ O(1)
    Aliasing ≡ Devuelve una copia a conjunto
    Descripción ≡ Devuelve el conjunto de personas de la instancia Lolla
```

```
PUESTOS (in l: lolla) ⇒ res: conjLog(puesto)
    Pre ≡  {true}
    Post ≡ {res = puestos(l)}
    Complejidad ≡ O(1)
    Aliasing ≡ Devuelve una copia a conjunto
    Descripción ≡ Devuelve el conjunto de puestos de la instancia Lolla
```

## Representación

### Estructura

TAD Lolla-Patuza se representa con `lolla`,  
donde `lolla` es:
```
tupla<
      personas		    : conjLineal(persona),
      puestosPorID  	: diccLog(ID, puesto),
	  gastoTotal	    : colaDePrioridadMax,
      puestosHackeables : diccLog(persona, diccLog(item, diccLog(ID, puesto)))
     >
```

### Invariante de representación:
Hay que chequear que:

1. El conjunto de claves del diccionario de gastoTotal.indicePersona es igual al conjLineal de personas
2. Los ID de puestosHackeables tienen que pertenecer a las claves de puestosPorID, y cada puesto que le corresponde a cada ID de puestosHackeables también tiene que ser el significado en puestosPorID
3. El conjunto de claves de puestosHackeables tiene que ser igual al conjLineal de personas

```
Rep: lolla ➔ bool
Rep(l) ≡ (1) ∧ (2) ∧ (3)

(1) ≡ l.personas = claves(π₂(l.gastoTotal))

(2) ≡ (∀a: persona)(∀i: item)(∀id: nat)(a ∈ claves(l.puestosHackeables) ∧ i ∈ claves(significado(l.puestosHackeables, a)) ∧L
                id ∈ claves(obtener(obtener(l.puestosHackeables, a), i))) ➔ id ∈ claves(l.puestosPorID) ∧L
                obtener(id, obtener(i, obtener(l.puestosHackeables, a))) = obtener(id, l.puestosPorID)

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
iNUEVO_LOLLA(in dp: diccLog(ID, puesto), in ca: conjLineal(persona), in ci: conjLineal(item)) -> lolla { 
    personas = ca;  
    puestosPorID = dp;	       
	gastoTotal.heap	= < >;
    gastoTotal.indicePersona = vacio(); 
    puestosHackeables = vacío();  

    // armo gastoTotal
    construir(l.gastoTotal, ca); // O(A*log A)

    // defino a todas las personas en primer diccLog poniendo como significado un diccLog vacío
    it = crearIt(ca);
    while(haySiguiente(it)){ // O(A)
        definirRapido(l.puestosHackeables, siguiente(it), vacío()); // O(1)
        it = siguiente(it);	
    }

    // ahora para cada persona creo un diccLog de todos los items con significado un diccLog vacio
    itPersona = crearIt(l.puestosHackeables);
    itItem = crearIt(ci);
    while(haySiguiente(itPersona)) { // O(A)
        while(haySiguiente(itItem)) { // O(I)
            siguienteValor(itPersona) = definirRapido(siguienteValor(itPersona), itItem, vacío()); // O(1)
            itItem = siguiente(itItem); 
        }
        itPersona = siguiente(itPersona);
    }
}
```

```c
iCOMPRA (inout l: lolla, in a: persona, in ID: nat, in i: item, in cant: nat) {
	// busco el puesto
    p = significado(l.puestosPorID, ID);		// // O(log P)	

	// calculo cuánto es el gasto de la compra
	precioTotal = precio_total(p, i, cant);	
		
    // tengo que modificar gastoTotal (modificar heap  e indicePersona)
	modificar(l.gastoTotal, a, precioTotal);	

	descuento = descuento_de(p, i, cant);

    // modificamos puestosHackeables
    if(descuento == 0) {
        if(definido?(significado(significado(l.puestosHackeables, a), i), id)) {
            definir(significado(significado(l.puestosHackeables, a), i), id, puesto);
        }
    }
    // modifico el puesto
	registrar_compra(p,a,i,c);
}
```

```c
iHACKEAR(inout l: lolla, in a: persona, in i: item) {
    // busco el puesto
    puestoAHackearIt = crearIt(significado(significado(l.puestosHackeables, a), i));    // O(log A + log I)
    puestoHack = siguienteSignificado(puestoAHackearit);

    // modifico el puesto
    registrar_hackeo(puestoHack, a, i);

    // si deja de ser hackeable, lo quito
    if(!esHackeable?(puestoHack, a, i)) { 
            borrar(significado(significado(l.puestosHackeables, a), i), puestoHack);
    }
        
    modificar(l.gastoTotal, a, - gastoTotal); 	// se pasa como negativo para que lo reste
} 

```

```c
iGASTO_TOTAL_DE(in l: lolla, in a: persona) -> nat {
    indice = significado(a, l.gastoTotal.indicePersona); // O(log A)
    return l.gastoTotal.heap[indice].gasto;
}
```

```c
iMAYOR_GASTADOR(in l: lolla) → persona {
	siguienteClave(return l.gastoTotal.heap[0].itPer); // O(1)
}
```

```c

iMENOR_STOCK(in l: lolla, in i: item) -> ID {
	// armo vector de tuplas que tengan el id del puesto y el stock de ese ítem
	it = crearIt(l.puestosPorID);
	vectorIDxStock = vacío();
	while(haySiguiente(it)) { // O(P*P)
	    agregarAtras(vectorIDxStock, <id: siguienteClave(it), stock: stock_de(siguienteValor(it), i)>); // O(P)
	    it = siguiente(it); // O(1)
    }

    // ahora ordeno el vector cuyo criterio principal sea el menor stock y desempate con el menor id
	ordenar_por_menor_stock(vectorIDxStock); // O(I*I)
	
	// ahora la primera posición del vector es la que necesitamos
    return vectorIDxStock[0].id; // O(1);	
}
```

```c
iPERSONAS(in l : lolla) ⇒ conjLog(persona) {
	return l.personas;	// O(1)
}
```

```c
iPUESTOS(in l : lolla) ⇒ diccLog(ID, puesto) {
	return l.puestosPorID;	// O(1)
}
```