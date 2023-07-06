# Módulo Puesto de Comida

## Interfaz

### Parámetros formales

### Operaciones básicas

```
NUEVO_PUESTO(in m: diccLog(item, nat), in s: diccLog(item, nat), in d: diccLog(item, diccLog(cant, nat)) ➔ res = puesto
    Pre ≡  {claves(m) = claves(s) ∧ claves(d) ⊆ claves(m)}
    Post ≡ {res = crearPuesto(m, s, d)}
    Complejidad ≡ O(I * descuentos * cantParaDescuento), donde descuentos es la cantidad de descuentos que hay disponibles, y cantParaDescuento es la mayor cantidad que se puede comprar de un item para obtener su mayor descuento
    Aliasing ≡ Crea un puesto por referencia y modificable
    Descripción ≡ Crea una nueva instancia de Puesto de Comida
```

```
STOCK(in p: puesto, in i: item) ➔ res: nat 
    Pre ≡ {true}
    Post ≡ {res = stock(p,i)}
    Complejidad ≡ O(log I)
    Aliasing ≡
    Descripción ≡ Devuelve el stock que queda del item
```

```
DESCUENTO_DE(in p: puesto, in i: item, in cant: cantidad) ➔ res: porcentaje 
    Pre ≡  {i ∈ menu(p)}
    Post ≡ {res = descuento(p,i,cant) ∧ 0 < res < 100}
    Complejidad ≡ O(log I)
    Aliasing ≡
    Descripción ≡ Devuelve qué descuento corresponde dado un ítem y una cantidad
```

```
GASTO_DE(in p: puesto, in a: persona) ➔ res: nat 
    Pre ≡  {true}
    Post ≡ {res = gastosDe(p, a)}
    Complejidad ≡ O(log A)
    Aliasing ≡ 
    Descripción ≡ Devuelve cuánto gastó una persona en el puesto

```

### Otras operaciones
```
REGISTRAR_COMPRA(inout p: puesto, in a: persona, in i: item, in cant: nat)
    Pre ≡  {el ítem existe en el menú y hay stock del mismo en el puesto}
    Post ≡ {la compra se registra en ventas del puesto, las demás ventas quedan iguales}
    Complejidad ≡ O(log A + log I + log cant)
    Aliasing ≡
    Descripción ≡ Registra la compra de ese item y cantidad en el puesto
```

```
REGISTRAR_HACKEO(inout p: puesto, in a: persona, in i: item)
    Pre ≡  {la persona ya compró ese item sin descuento en ese puesto}
    Post ≡ {se asegura de que el puesto recupera +1 en el stock del item, que la compra en la persona pierda -1 en alguna cantidad comprada sin descuento del item, y que en el gasto de pierda el precio del item dado}
    Complejidad ≡ O(log A + log I)
    Aliasing ≡ Modifica el puesto pasado por referencia
    Descripción ≡ Dado un pueto, una persona y un ítem, se realiza el hackeo correspondiente
```

```
PRECIO_TOTAL(in p: puesto, in i: item, in cant: nat) ➔ res: nat 
    Pre ≡  {el item tiene que estar en el menu}
    Post ≡ {el nat que devuelve tiene que ser el precio con el descuento correspondiente aplicado }
    Complejidad ≡ O(log I)
    Descripción ≡ Dado un ítem y una cantidad, calcula su precio total.
```

```
ES_HACKEABLE?(in p: puesto, in a: persona, in i:item) ➔ res: bool
    Pre ≡  {la persona compró en algún momento ese ítem sin descuento}
    Post ≡ {el resultado da true si no existen compras sin descuento asociadas a ese item y a esa persona}
    Complejidad ≡ O(log A + log I)
    Descripción ≡ Dado un puesto, una perona y un ítem, chequea si el puesto sigue siendo hackeable.
```

## Representación

### Estructura

TAD Puesto de Comida se representa con `p`,  
donde `p` es:
```
tupla<
      menu                      : diccLog(item, precio),
      stock                     : diccLog(item, cantidad),
      gastoDe 	                : diccLog(persona, nat),
      descuentos               	: diccLog(item, vector(porcentaje)),
      comprasPorPersonaConDesc  : diccLog(persona, diccLog(item, multiconjLog(cantidad))),
      comprasPorPersonaSinDesc  : diccLog(persona, diccLog(item, multiconjLog(cantidad)))
     >
```

### Invariante de representación

Hay que chequear que:
1. El conjunto de claves de stock es igual al conjunto de claves de menu
2. El conjunto de claves de descuentos es igual al conjunto de claves de menu
3. La union del conjunto de claves de comprasPorPersonaConDesc y de comprasPorPersonaSinDesc es igual al conjunto de claves de gastoDe
4. La cantidad de items en comprasPorPersonaConDesc tiene que ser válida para aplicar el descuento
5. La cantidad de items en comprasPorPersonaSinDesc no tiene que ser válida para aplicar el descuento
6. Los items de comprasPorPersonaConDesc y comprasPorPersonaSinDesc tienen que estar en menú
7. Para cada vector de descuentos, el indice 0 tiene que valer 0 y en adelante cada valor tiene que ser mayor o igual que su anterior valor. El tamaño del vector será igual a la cantidad máxima que tiene descuento. El tamaño mínimo del vector será 1 (con el valor 0).
8. El gasto de una persona en gastoDe tiene que corresponder con la cantidad de items que compró por el precio y el descuento

```
Rep: puesto ➔ bool
Rep(p) ≡ (1) ∧ (2) ∧ (3) ∧ (4) ∧ (5) ∧ (6) ∧ (7) ∧ (8)

(1) ≡ claves(p.stock) = claves(p.menu) ∧

(2) ≡ claves(p.descuentos) ⊆ claves(p.menu) ∧

(3) ≡ claves(p.comprasPorPersonaConDesc) U claves(p.comprasPorPersonaSinDesc) = claves(p.gastoDe) ∧L

(4) ≡ (∀a: persona)(∀i: item)(∀c: cantidad)(a ∈ claves(p.comprasPorPersonaConDesc) ∧L 
i ∈ claves(obtener(a, p.comprasPorPersonaConDesc)) ∧L 
c ∈ obtener(i, obtener(a, p.comprasPorPersonaConDesc))  ➔L 
(c > longitud(obtener(i, p.descuentos)) ∨L obtener(i, p.descuentos)[c] ≠ 0) ∧L

(5) ≡ (∀a: persona)(∀i: item)(∀c: cantidad)(a ∈ claves(p.comprasPorPersonaSinDesc) ∧L
 i ∈ claves(obtener(a, p.comprasPorPersonaSinDesc)) ∧L 
c ∈ obtener(i, obtener(a, p.comprasPorPersonaSinDesc))  ➔L 
(c > longitud(obtener(i, p.descuentos)) ➔L longitud(obtener(i, p.descuentos)) = 1) ∨L obtener(i, p.descuentos)[c] = 0) ∧

(6) ≡ (∀a: persona)(a ∈ claves(p.comprasPorPersonaConDesc) ➔L claves(obtener(a, p.comprasPorPersonaConDesc)) ⊂ claves(p.stock)) ∧L
(∀ a :persona)(a ∈ claves(p.comprasPorPersonaSinDesc) ➔L 
claves(obtener(a, p.comprasPorPersonaSinDesc)) ⊂ claves(p.stock))  ∧L

(7) ≡ (∀i: item)(∀ j: indice)(i ∈ claves(p.descuentos) ∧L  0 ≤ j < long(obtener(i, p.descuentos)) - 1  ➔L  
obtener(i, p.descuentos)[0] = 0 ∧L obtener(i, p.descuentos)[j] ≤ obtener(i, p.descuentos)[j+1])  ∧L

(8) ≡ (∀a: persona)(Definido?(p.gastoDe, a) ➔L
 obtener(a, p.gastoDe) = gastoTotalSinDesc(p,obtener(a, p.compraPorPersonaSinDesc)) +
gastoTotalConDesc(p,obtener(a,p.compraPorPersonaConDesc)))
```

Predicados o funciones auxiliares utilizadas:
```
(∀dp: dicc(item,multiconj(cant))), (∀cp: multiconj(cant))

gastoTotalSinDesc: puesto x dicc(item,multiconj(cant)) ➔ nat
gastoTotalSinDesc(p,dp) ≡ if vacio?(claves(dp)) then 0 
                          else 
                                gasto(obtener(dameUno(claves(dp)),dp), obtener(dameUno(claves(dp)),p.menu)) + 
	                                gastoTotalSinDesc(p,borrar(dameUno(claves(dp)),dp))
                          fi

gasto: multiconj(cant) x precio ➔ nat 
gasto(cp,precio) ≡ if vacio?(claves(dp)) then 0
                   else precio * dameUno(cp) + gasto(sinUno(cp),precio)
                   fi

gastoTotalConDesc: puesto x dicc(item,multiconj(cant)) ➔ nat
gastoTotalConDesc(p,dp) ≡ if vacio?(claves(dp)) then 0
                          else gastoDesc(obtener(dameUno(claves(dp)),dp),obtener(dameUno(claves(dp)),p.menu),
                               obtener(dameUno(claves(dp)),p.descuentos)) + gastoTotalConDesc(p,borrar(dameUno(claves(dp)),dp))
                          fi

gastoDesc: multiconj(cant) x precio x vector(porcentaje) ➔ nat
gastoDesc(cp,precio,desc) ≡ if vacio?(cp) then 0 
                            else
		                        dameUno(cp) * (precio*desc[dameUno(cp)]/100) + gastoDesc(sinUno(cp),precio,desc)
                            fi
```

### Función de abstracción
```
Abs: estr ➔ TAD Puesto de Comida
Abs(p)≡ p: puesto /
        menu(p) = claves(p.menu) ∧ 
        (∀ i:item)(∀ c: nat)(def?(i,p.menu) ∧ def?(i,p.stock) ∧ def?(c,p.descuentos) ∧ 
        precio(p,i) = obtener(i,p.menu) ∧ stock(p,i) = obtener(i,p.stock))
        ∧
        descuento(p,i,c) = valorDePosicion(obtener(i, p.descuentos),c)
        ∧
        (∀a: persona)(def?(a, p.comprasPorPersonaConDesc) ∧ def?(a, p.comprasPorPersonaSinDesc) ➔
        ventas(p, a) = ventasAux(obtener(a, p.comprasPorPersonaConDesc)) U ventasAux(obtener(a, p.comprasPorPersonaSinDesc)))
        ∧
        (∀a: persona)(def?(a, p.comprasPorPersonaConDesc) ∧ ¬def?(a, p.comprasPorPersonaSinDesc) ➔
        ventas(p, a) =  ventasAux(obtener(a, p.comprasPorPersonaConDesc)))
        ∧
        (∀a: persona)(¬def?(a, p.comprasPorPersonaConDesc) ∧ def?(a, p.comprasPorPersonaSinDesc) ➔
        ventas(p, a) =  ventasAux(obtener(a, p.comprasPorPersonaSinDesc)))
        ∧
        (∀a: persona)(¬def?(a, p.comprasPorPersonaConDesc) ∧ ¬def?(a, p.comprasPorPersonaSinDesc) ➔
        ventas(p, a) = ∅)
```

Predicados o funciones auxiliares:
```
(∀v: vector(α)), (∀i: nat), (∀d: dicc(item, multiconj(cantidad))), (∀c: multiconj(cantidad)) 

valorDePosicion: vector(nat) x indice ➔ nat
valorDePosicion(v, i) ≡  if (i = 0) then prim(v)
                         else valorDePosicion(fin(v), i-1)
                         fi

ventasAux: dicc(item, multiconj(cant)) ➔ multiconj(<item, cantidad>)
ventasAux(d) ≡  if ∅?(claves(d)) then ∅
                else ventasDeUnItem(dameUno(claves(d)), obtenerUno(d)) U ventasAux(sinUnaClave(d))
                fi 

ventasDeUnItem: item x multiconj(cantidad) ➔ multiconj(<item, cantidad>)
ventasDeUnItem(i, c) ≡  if ∅?(c) then ∅
                        else Ag(<i, dameUno(c)>, ventasDeUnItem(i, sinUno(c)))
                        fi
```


## Algoritmos

```c
iNUEVO_PUESTO(in m: diccLog(item, nat), in s: diccLog(item, nat), in d: diccLog(item, diccLog(cant, nat)) d) -> puesto { 
	    
    menu = m;
    stock = s;
    descuentos = vacio;
    compraPorPersonaConDesc = vacio();
    compraPorPersonaSinDesc = vacio();
    gastoDe = vacio();

    // armo el diccionario de descuentos con vectores
    itItem = crearIt(d);
    contadorCant = 0;
    sgteDesc = 0;
    while(haySiguiente?(itItem)){ // O(I * cantDescuentos * mayorCantDescuento)
        descPorIndice = agregarAtras(vacia(), 0);
        itCant = crearIt(siguienteSignificado(itItem)); 
        while(haySiguiente?(itCant)){  // asumo que va de menor a mayor clave
            while(contadorCant < siguienteClave(itCant)){ // 
                agregarAtras(descPorIndice, sgteDesc);
                contadorCant++;
            }
            // aca contadorCant ya va a ser la proxima cantidad
            sgteDesc = siguienteSignificado(itCant);
            agregarAtras(descPorIndice, sgteDesc);
            contadorCant++;
            avanzar(itCant);
        }
        definir(descuentos, siguienteClave(itItem), descPorIndice);
        contadorCant = 0;
        sgteDesc = 0;
        avanzar(itDesc);
    } // corregido la definicion de descuentos
}
```

```c
iSTOCK_DE(in p: puesto, in i: item) -> nat { 
	if(!definido?(p.stock, i)){ 
	    return 0;
    }
    else {
        return significado(p.stock, i);   // O(log I)
    }
}
```

```c
iDESCUENTO_DE(in p: puesto, in i: item, in cant: nat) -> descuento { 
    descuentos = significado(p.descuentos, i) // O(log I)
    size = longitud(descuentos) // O(1)
	if (cant <= longitud(descuentos)){ // O(1)
        desc = descuentos[cant];	// O(1)
    }
    else{
	    desc = descuentos[size - 1];	// O(1)
    }
    return descuento;
}
```

```c
iGASTO_DE(in p: puesto, in a: persona) -> nat {
    if(definido?(p.gastoDe, a)){
        return significado(p.gastoDe , a) // O(log A)
    }  
    return 0; 	
}
```

```c
iREGISTRAR_COMPRA(inout p: puesto, in a: persona, in i: item, in cant: nat) { 
    // calculo cuanto es el gasto de la compra
    precioTotal = precio_total(p, i, cant); // O(log I)
    descuento = descuento_de(p, i, cant); // O(log I)

    if(descuento > 0){
        //primero veo si la persona existe en el dicc con desc, si no está la creo
       if(!definido?(p.comprasPorPersonaConDesc, a)){ // O(log A)
            // defino el diccionario vacio de la persona
            definir(p.comprasPorPersonaConDesc, a, vacio()); // O(log A) 
        }
        // creo variable del diccionario de items asociado a esa persona
        diccItemConDesc = significado(p.comprasPorPersonaConDesc, a); // O(log A)

        // veo si el item esta definido, si no, creo un multiconj vacio asociado a ese item
        if(!definido(diccItemConDesc, i)){ // O(log I)
        // defino un multiconjLog vacio asociado a ese item
        definir(significado(p.comprasPorPersonaConDesc, a), i, vacio()); // O(log I)
        }
        // creo variable del multiconjLog de cantidades asociado a ese item
        conjCantConDesc = significado(diccItemConDesc, i);
        // agrego esa cantidad al multiconj
        agregar(conjCantConDesc, cant); // O(log cant)
    }
    else {
        //primero veo si la persona existe en el dicc sin desc, si no está la creo
       if(!definido?(p.comprasPorPersonaSinDesc, a)){ // O(log A)
            // defino el diccionario vacio de la persona
            definir(p.comprasPorPersonaSinDesc, a, vacio()); // O(log A) 
        }
        // creo variable del diccionario de items asociado a esa persona
        diccItemSinDesc = significado(p.comprasPorPersonaSinDesc, a); // O(log A)

        // veo si el item esta definido, si no, creo un multiconj vacio asociado a ese item
        if(!definido(diccItemSinDesc, i)){ // O(log I)
        // defino un multiconjLog vacio asociado a ese item
        definir(significado(p.comprasPorPersonaSinDesc, a), i, vacio()); // O(log I)
        }
        // creo variable del multiconjLog de cantidades asociado a ese item
        conjCantSinDesc = significado(diccItemSinDesc, i);
        // agrego esa cantidad al multiconj
        agregar(conjCantSinDesc, cant); // O(log cant)
    }

    // actualizamos gasto total en el puesto
    if(!definido?(p.gastoDe, a)) { 
        definir(p.gastoDe, a, precioTotal);
    }
    else {
        significado(p.gastoDe, a) += precioTotal; 		// O(log A)
    }

    // actualizamos stock
    significado(p.stock, i) -= cant; 		// O(log I)

}
```

```c
iREGISTRAR_HACKEO(inout p: puesto, in a: persona, in i: item){

    // aumento stock
    significado(p.stock, i) += 1; // O(log I)

    // creo una variable de compras sin descuento (referencia modificable)
    comprasSinDesc = significado(significado(p.comprasPorPersonaSinDesc, a), i);
    cantHackeadaIt = crearIt(comprasSinDesc)  // O(log A + log I)
    cantHackeada = siguiente(cantHackeadaIt);
    // 
    if(cantHackeada == 1){ // si la compra era de 1 solo item, entonces la elimino
        borrar(comprasSinDesc, cantHackeada);
    }
    else{ // si no, solo le resto 1
        cantHackeada -= 1;
    }

    // como se hizo el hackeo, se debe modificar el gasto de esa persona en el puesto
    significado(p.gastoDe, a) -= significado(p.menu, i)); // O(log A + log I)
}
```

```c
iPRECIO_TOTAL(in p: puesto, in i: item, in cant: nat) -> nat { 
    precioTotal = significado(p.menu, i) * cant; // O(log I)
	descuento = descuento_de(p, i, cant); // O(1)
	return  precioTotal * ((100 - descuento) / 100); // O(1)
}

```

```c
iES_HACKEABLE(in p: puesto, in a: persona, in i: item) -> res: bool { 
    // si el dicc de compras sin desc para esa persona y ese item es vacio entonces da true, sino false
    if(definido?(p.comprasPorPersonaSinDesc, a)){
        comprasPorItemSinDesc = significado(p.compraPorPersonaSinDesc, a); // O(log A)
        if(definido?(comprasPorItemSinDesc, i)){
            conjCantSinDesc = significado(compraPorPersonaSinDesc, i); // O(log I)
            return vacio?(conjCantSinDesc); 
        }
    }
    return false;
}
```
