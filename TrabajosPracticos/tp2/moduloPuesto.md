# Módulo Puesto de Comida

## Interfaz

### Parámetros formales

### Operaciones básicas

```
NUEVO_PUESTO (in n: nat, in m: diccLog(item, precio), in s: diccLog(item, cantidad), in d: diccLog(item, vector(porcentaje))) ➔ res = puesto
    Pre ≡  {claves(m) = claves(s) ∧ claves(d) ⊆ claves(m)}
    Post ≡ {menu(res) = m  ∧ (∀i: item) stock(res, i) = obtener(i, s) ∧ (∀ cant: nat) descuentos(res, i, cant) = obtener(i, d)[cant] ∧ (∀a: persona)(a ventas(p, a) = vacío)}
    Complejidad ≡ O(1)
    Aliasing ≡ Crea un puesto por referencia y modificable
    Descripción ≡ Crea una nueva instancia de Puesto de Comida
```

```
STOCK (in p: puesto, in i: item) ➔ res: nat 
    Pre ≡ {true}
    Post ≡ {res = stock(p,i)}
    Complejidad ≡ O(log I)
    Aliasing ≡ Devuelve un natural por copia
    Descripción ≡ Crea una nueva instancia de Lolla-Patuza
```

```
DESCUENTO_ITEM (in p: puesto, in i: item, in cant: cantidad) ➔ res: porcentaje 
    Pre ≡  {i ∈ menu(p)}
    Post ≡ {res = descuento(p,i,cant) ∧ 0 < res < 100}
    Complejidad ≡ O(1)
    Aliasing ≡ Devuelve un natural por copia
    Descripción ≡ Devuelve qué descuento corresponde dado un ítem y una cantidad
```

```
GASTO_DE (in p: puesto, in a: persona) ➔ res: nat 
    Pre ≡  {definido?(a.DNI, p.compradoresPorDNI)}
    Post ≡ {res = gastosDe(p, a)}
    Complejidad ≡ O(log A)
    Aliasing ≡ Devuelve un natural por copia
    Descripción ≡ Devuelve cuánto gastó una persona en el puesto

```

### Otras operaciones
```
REGISTRAR_COMPRA (inout p: puesto, in a: persona, in i: item, in cant: nat)
    Pre ≡  {el ítem existe en el menú y hay stock del mismo en el puesto}
    Post ≡ {la compra se registra en ventas del puesto, las demás ventas quedan iguales}
    Complejidad ≡ O(log A + log I)
    Aliasing ≡ Modifica el puesto pasado por referencia
    Descripción ≡ Registra la compra de ese item y cantidad en el puesto
```

```
REGISTRAR_HACKEO (inout p: puesto, in a: persona, in i: item)
    Pre ≡  {la persona ya compró ese item sin descuento en ese puesto}
    Post ≡ {se asegura de que el puesto recupera +1 en el stock del item, que la compra en la persona pierda -1 en alguna cantidad comprada sin descuento del item, y que en el gasto de pierda el precio del item dado}
    Complejidad ≡ O(log A + log I)
    Aliasing ≡ Modifica el puesto pasado por referencia
    Descripción ≡ Dado un pueto, una persona y un ítem, se realiza el hackeo correspondiente
```

```
PRECIO_TOTAL (in p: puesto, in i: item, in cant: nat) ➔ res: nat 
    Pre ≡  {el item tiene que estar en el menu}
    Post ≡ {el nat que devuelve tiene que ser el precio con el descuento correspondiente aplicado }
    Complejidad ≡ O(log A)
    Descripción ≡ Dado un ítem y una cantidad, calcula su precio total.
```

```
ES_HACKEABLE? (in p: puesto, in a: persona, in i:item) ➔ res: bool
    Pre ≡  {la persona compró en algún momento ese ítem sin descuento}
    Post ≡ {el resultado da true si el multiconjunto de cantidades en compras sin descuento es vacío }
    Complejidad ≡ O(log A + log I)
    Descripción ≡ Dado un puesto, una perona y un ítem, chequea si el puesto sigue siendo hackeable.
```

## Representación

### Estructura

TAD Puesto de Comida se representa con `puesto`,  
donde `puesto` es:
```
tupla<
      id                        : nat,
	  menu		                : diccLog(item, precio),
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
2. El conjunto de claves de descuentos tiene que ser igual al conjunto de claves de menu
3. La union del conjunto de claves de comprasPorPersonaConDesc y de comprasPorPersonaSinDesc es igual al conjunto de claves de gastoDe
4. La cantidad de items en comprasPorPersonaConDesc tiene que ser válida para aplicar el descuento
5. La cantidad de items en comprasPorPersonaSinDesc no tiene que ser válida para aplicar el descuento
6. Los items de comprasPorPersonaConDesc y comprasPorPersonaSinDesc tienen que estar en menú
7. Para cada vector de descuentos, el indice 0 tiene que valer 0 y en adelante cada valor tiene que ser mayor o igual que su anterior valor
8. El gasto de una persona en gastoDe tiene que corresponder con la cantidad de items que compró por el precio y el descuento

```
Rep: puesto ➔ bool
Rep(p) ≡ (1) ∧ (2) ∧ (3) ∧ (4) ∧ (5) ∧ (6) ∧ (7) ∧ (8)

(1) ≡ claves(p.stock) = claves(p.menu) ∧

(2) ≡ claves(p.descuentos) subconj claves(p.menu) ∧

(3) ≡ claves(p.comprasPorPersonaConDesc) U claves(p.comprasPorPersonaSinDesc) = claves(p.gastoDe) ∧L

(4) ≡ (∀a: persona)(∀i: item)(∀c: cantidad)(a ∈ claves(p.comprasPorPersonaConDesc) ∧L 
i ∈ claves(obtener(a, p.comprasPorPersonaConDesc)) ∧L 
c ∈ obtener(i, obtener(a, p.comprasPorPersonaConDesc))  ➔L 
obtener(i, p.descuentos)[c] ≠ 0) ∧L

(5) ≡ (∀a: persona)(∀i: item)(∀c: cantidad)(a ∈ claves(p.comprasPorPersonaSinDesc) ∧L
 i ∈ claves(obtener(a, p.comprasPorPersonaSinDesc)) ∧L 
c ∈ obtener(i, obtener(a, p.comprasPorPersonaSinDesc))  ➔L 
obtener(i, p.descuentos)[c] = 0) ∧

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

gastoTotalSinDesc(p,dp) ≡ if vacio?(claves(dp)) then 0 
                          else 
                                gasto(obtener(dameUno(claves(dp)),dp), obtener(dameUno(claves(dp)),p.menu)) + 
	                                gastoTotalSinDesc(p,borrar(dameUno(claves(dp)),dp))
                          fi

gasto(cp,precio) ≡ if vacio?(claves(dp)) then 0
                   else precio * dameUno(cp) + gasto(sinUno(cp),precio)
                   fi

gastoTotalConDesc(p,dp) ≡ if vacio?(dp) then 0
                          else gastoDesc(obtener(dameUno(claves(dp)),dp),obtener(dameUno(claves(dp)),p.menu),
                               obtener(dameUno(claves(dp)),p.descuentos)) + gastoTotalConDesc(p,borrar(dameUno(claves(dp)),dp))
                          fi


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
        (∀ i:item)(∀ c: nat)(def?(i,p.menu) ∧ def?(i,p.stock) ∧ def?(i,p.descuentos) ∧
        0 ≤ c ≤ obtener(p.stock,i) ➔ precio(p,i) = obtener(i,p.menu) ∧ stock(p,i) = obtener(i,p.stock))
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
iNUEVO_PUESTO(in n: nat, in m: diccLog(item, precio), in s: diccLog(item, cantidad), in d: diccLog(item, vector(porcentaje))) -> puesto { 
	id 	= n;
	menu = m;
	stock  = s;
	descuentos = d;
	compraPorPersonaConDesc = vacío();
	compraPorPersonaSinDesc = vacío();
	gastoDe = vacío();
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
	if (cant ≤ largo(p.descuentos)){
        descuento = significado(p.descuentos, i)[cant];		// O(I + 1)
    }
    else{
	    descuento = significado(p.descuentos, i)[largo(p.descuentos)];	// O(I + 1)
    }
    return descuento;
}
```

```c
iGASTO_DE(in p: puesto, in a: persona) -> nat {  
    return significado(p.gastoDe , a).gastoTotal; // O(log A)	
}
```

```c
iREGISTRAR_COMPRA(inout p: puesto, in a: persona, in i: item, in cant: nat) { 
	// calculo cuánto es el gasto de la compra
	precioTotal = precio_total(p, i, cant); // O(log I)
	descuento = descuento_de(p, i, cant);
		
    // modifico comprasPorPersonaConDesc
    if(descuento > 0){ // O(1)
        // vemos si está definida esa persona
        if (!definido?(p.comprasPorPersonaConDesc, a)){ // O(log A)
            definirRapido(p.comprasPorPersonaConDesc, a, vacío()); //este vacio es de dicc
            definirRapido(significado(p.comprasPorPersonaConDesc, a), i, vacio()); // este vacio es de multiconj
        }
        nuevaCompra =(significado(significado(p.comprasPorPersonaConDesc, a), i)).agregar(cant);//O(log A + log I)
        definir(significado(p.comprasPorPersonaConDesc, a), i, nuevaCompra);  		// O(log A + log I)
    }

    // modifico comprasPorPersonaSinDesc
    else{
        if (!definido?(p.comprasPorPersonaSinDesc, a)){ // O(log A)
            definirRapido(p.comprasPorPersonaSinDesc, a, vacío()); //este vacio es de dicc
            definirRapido(significado(p.comprasPorPersonaSinDesc, a), i, vacio()); //este vacio es de multiconj
    }

        nuevaCompra = (significado(significado(p.comprasPorPersonaSinDesc, a), i)).agregar(cant); 
        definir(significado(p.comprasPorPersonaSinDesc, a), i, nuevaCompra);  // O(log A + log I) ambos
    }

    // actualizamos gasto total en el puesto
    if(!definido?(p.gastoDe, a)) { 
        definir(p.gastoDe, a, precioTotal);
    }
    else {
        definir(p.gastoDe, a, significado(p.gastoDe, a) + precioTotal); 		// O(2 log A)
    }

    // actualizamos stock
    definir(p.stock, i, significado(p.stock, i) - cant); 		// O(2 log I)

}
```

```c
iREGISTRAR_HACKEO(inout p: puesto, in a: persona, in i: item){

    definir(p.stock, i, significado(p.stock, i) + 1);	// O(log I)

    aSacarIt = crearIt(significado(significado(p.comprasPorPersonaSinDesc, a), i))  // O(log A + log I)
    aSacar = siguiente(aSacarIt);
    if(aSacar == 1){
        nuevoCompras = borrar(significado(significado(p.comprasPorPersonaSinDesc, a), i), aSacar);
        definir(p.comprasPorPersonaSinDesc, a, definir(significado(p.comprasPorPersonaSinDesc, a), i, nuevoCompras));
    }
    else{
        definir(significado(significado(p.comprasPorPersonaSinDesc, a)), i, aSacar - 1);
    }

    definir(p.gastoDe, a, significado(p.gastoDe, a) - significado(p.menu, i)); // O(2 log A + log I)
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
iES_HACKEABLE(in p: puesto, in a: persona, in i: item) → res: bool { 
	// si el dicc de compras sin desc para esa persona y ese item es vacio entonces da true, sino false
	return vacío() == significado(significado(p.comprasPorPersonaSinDesc, a), i);
}

```