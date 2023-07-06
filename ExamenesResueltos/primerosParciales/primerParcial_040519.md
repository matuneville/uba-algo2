# Ejercicio 1

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` ∩ ∪ ⊆

```
TAD Ticket es nat
TAD Premio es nat
TAD Numero es nat (la combinacion de 6 numeros)
TAD Apuesta es tupla(ticket, numero)

TAD OJALA:
    Observadores basicos
        apostadoresHoy: ojala  ➔  conj(persona)
        tablaApuestas: ojala  ➔  dicc(ticket, premio) 
        totalRecaudado: ojala  ➔  nat
        totalEntregado: ojala  ➔  nat
        apuestasHoy: ojala o × persona p ➔  multiconj(apuesta)             {p ∈ apostadoresHoy}
        ticketsUlt100Dias: ojala × persona  ➔  secu(multiconj(apuesta))
    
    Generadores
        nuevoOJALA: dicc(ticket, premio)  ➔  ojala
        personaApuesta: ojala o × persona p  × apuesta t ➔  ojala     
                                                    {puedeApostar(o,p) ∧ {p ∈ apostadoresHoy}
                                              π1(t) ∈ claves(tablaApuestas(o)) ∧ 0 ≤ π2(t) ≤ 999999}
        sorteo: ojala × numero  ➔  ojala            {0 ≤ π2(t) ≤ 999999}

    Otras operaciones
        puedeApostar: ojala × persona  ➔  bool
        balancePositivo?: ojala  ➔  bool
        sumoCantApuestas: secu(multiconj(apuesta))  ➔  nat
        hayGanador?: multiconj(apuesta) × conj(persona) × numero  ➔  bool
        totalPremios: multiconj(apuesta) × numero  ➔  nat
 
    Axiomas
        (∀t: ticket)(∀prem: premio)(∀p,q: persona)(∀tab: dicc(ticket, premio))(∀num: numero)
        (∀apuesta: apuesta)(∀m: multiconj(apuesta))(∀sm: secu(multiconj(apuesta)))(∀ca: conj(persona))

        tablaApuestas(nuevoOJALA(tab)) ≡ tab
        tablaApuestas(personaApuesta(o, p, apuesta)) ≡ tablaApuestas(o)
        tablaApuestas(sorteo(o, num)) ≡ tablaApuestas(o)

        totalRecaudado(nuevoOJALA(tab)) ≡ 0
        totalRecaudado(personaApuesta(o, p, apuesta)) ≡ totalRecaudado(o) + π1(apuesta)
        totalRecaudado(sorteo(o, num)) ≡ totalRecaudado(o)

        totalEntregado(nuevoOJALA(tab)) ≡ 0
        totalEntregado(personaApuesta(o, p, apuesta)) ≡ totalEntregado(o)
        totalEntregado(sorteo(o, num)) ≡
                totalEntregado(o) +
                            (if hayGanador?(apuestasHoy(o, dameUno(apostadoresHoy(o))), sinUno(apostadoresHoy(o)), num)
                                then totalPremios(apuestasHoy(o), num)
                             else 0 fi) 

        apuestasHoy(nuevoOJALA(tab),q) ≡ vacio
        apuestasHoy(personaApuesta(o, p, apuesta),q) ≡ if p = q then Ag(apuesta, apuestasHoy(o,p))
                                                       else apuestasHoy(o,p)
                                                       fi
        apuestasHoy(sorteo(o, num),q) ≡ vacio

        // siempre devuelve una secuencia de 100 elementos, cuando pasa un dia (al sortear)
        // se le quita el ultimo y se le agrega un nuevo dia vacio (esto si esta lleno, o sea, 100 dias)
        ticketsUlt100Dias(nuevoOJALA(tab), q) ≡ vacio
        ticketsUlt100Dias(personaApuesta(p, apuesta), q) ≡ Ag(apuesta, prim(ticketsUlt100Dias)) • fin(ticketsUlt100Dias(o,q))
        ticketsUlt100Dias(sorteo(o, num), q) ≡ if largo(ticketsUlt100Dias(o,q)) = 100 then 
                                                  vacio • ticketsUlt100Dias(o,q)
                                               else
                                                   vacio • com(ticketsUlt100Dias(o,q))
        
        puedeApostar(o, p) ≡ if sumoCantApuestas(ticketsUlt100Dias(o, p)) > 50 then false
                             else true
                             fi

        sumoCantApuestas(sm) ≡ if vacio?(sm) then 0
                               else #(dameUno(sm)) + sumoCantApuestas(sinUno(sm))
                               fi
        
        balancePositivo(o) ≡ totalRecaudado(o) > totalEntregado(o)
        
FIN TAD
```
# Ejercicio 2

1. Verdadero, planteo la desigualdad y aplico cubo a cada lado. easy peacy
2. Falso. Contraejemplo, f(n) = n*n, g(n) = n
3. Mejor caso es O(n), el caso en el que el ciclo de j se realiza una sola vez
4. Peor caso es O(n * raiz(n))

# Ejercicio 3

## Resolucion:

### Invariante de Representacion
Tiene que cumplir:
1. Toda unidad en e.tieneDueño, si es falso, está en e.huerfanas, y todas las de huerfanas son falsas en e.tieneDueño
2. Toda unidad en e.tienedueño, si es verdadera, está en e.dueña, y todas las de dueña son verdaderas en e.tieneDueño
3. Para confirmar 1 y 2, claves de tieneDueña? es igual a la union de claves(dueña) y huerfanas
4. claves de dueña es igual a claves de distDueña
5. Toda antena que aparece en e.dueña va a aparecer en nroClientes con un significado mayor a 0.
6. claves de nroCLientes es igual a claves de unidadesADistancia
7. Toda unidad que tenga asignada una antena en dueña, entonces aparecerá en unidadesADistancia al obtener con distDueña
8. Toda unidad solo aparecera en unidadesADistancia de una distancia si y solo si esta distancia es mayor o igual a distDueña
9. Dada una antena, para cualquier natural, el cardinal de e.unidadesADistancia[a][n] va a ser menor o igual a nroClientes [a]
```
Rep: estr ➔ bool
Rep(e) ≡
```

### Funcion de abstraccion
Tengo que ver que:
1. Unidades es igual a claves(e.tieneDueña)
2. Antenas es igual a claves(e.nroClientes)
3. Alcanza? de una antena a y una unidad u es true si y solo si obtener(u, e.dueña) = a y obtener(u, e.tieneDueña?)
4. Distancia de una antena a y una unidad u es
```
Abs: estr e ➔ t
Abs(e) ≡ t / 
        

```

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` ∩ ∪ ⊆