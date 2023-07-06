simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` ∩ α

# Ejercicio 1

```
TAD Multiconjunto Extendido

   Otras operaciones
      eliminarTodos : multiconj(α) × α         ➔   multiconj(α)
      Nrepetidos : multiconj(α) × nat          ➔   conj
      maxRepetidos : multiconj(α) m            ➔   conj                {¬ ∅?(m)}
      #apariciones : multiconj(α) × α          ➔   nat
      recursivaNrepetidos : multiconj(α) × nat ➔   conj

   Axiomas   (∀mc: multiconj(α))(∀x: α)(∀n: nat)
      eliminarTodos(mc, x) ≡  if not(x ∈ mc) then mc
                              else eliminarTodos(x - mc, x)
                              fi
      
      Nrepetidos(mc, n) ≡ if vacio?(mc) then {}
                          else
                              if #apariciones(dameUno(mc), mc) ≥ n
                                 then Ag(dameUno(mc), Nrepetidos(eliminarTodos(mc, dameUno(mc)), n))
                              else Nrepetidos(eliminarTodos(mc, dameUno(mc)), n)
                              fi
                          fi

      #apariciones(mc, x) ≡ if vacio?(mc) then 0
                            else
                                if x ∈ mc  then 1 + #apariciones(x - mc, x)
                                else 0
                                fi
                            fi

      maxRepetidos(mc) ≡ recursivaNrepetidos(mc, #(mc))

      recursivaNrepetidos(mc, n) ≡  if not(vacio?(Nrepetidos(mc, #(mc)))) then Nrepetidos(mc, #(mc))
                                    else recursivaNrepetidos(mc, n - 1)
                                    fi
```

# Ejercicio 4

**Mejor caso:** Si n = 0, es decir, M es matriz vacía (M = {{}}) entonces no entrará al ciclo pues i = 0 not < n = 0. Su complejidad de mejor caso será constante y se puede acotar por arriba y por abajo como constante, por lo tanto su cota mas ajustada es **Θ(1)**.

**Peor caso:** Si n > 0 entonces siempre ejecutará n*n operaciones, y se puede acotar por arriba y por abajo con n cuadrado. Por lo tanto su complejidad de peor caso es de **Θ(n^2)** siendo esta su cota ams ajustada.


# Ejercicio 5

sv se representa con _estr_, donde
```js
estr es tupla{
    vacunados : dicc(ciudad, secu(persona))
    esperando : dicc(ciudad, conj(persona))
    frascos : conj(tupla(ciudad, nat))
    residencia : dicc(persona, ciudad)
}
```

## Resolucion:

### Invariante de Representacion
Tiene que cumplir:
1. Que en e.vacunados no haya personas repetidas y ninguna persona aparezca en 2 o mas ciudades
2. Que corresponda la ciudad de e.residencia con la de e.vacunados de cada persona
3. Que ninguna persona que este en e.esperando, este en e.vacunados, y viceversa
4. Que corresponda la ciudad de e.residencia con la de e.esperando de cada persona
5. Que ninguna persona aparezca en 2 o mas ciudades en e.esperando
6. Que ninguna persona aparezca en 2 o mas ciudades en e.residencia
7. Que en e.esperando, e.vacunados y e.residencia esten las mismas personas
8. Que en e.frascos no haya ciudades repetidas
9. Solo puede haber frascos disponibles si hay menos de 5 personas esperando a vacunarse
10. Que las ciudades de e.frascos sean las mismas que las de e.vacunados
```
Rep: estr ➔ bool
Rep(e) ≡ (1) ∧ (2) ∧ (3) ∧ (4) ∧ (5) ∧ (6) ∧ (7)

(1) ≡ (∀c: ciudad)(not(∃i,j: nat)(0 ≤ i,j < largo(obtener(c, e.vacunados)) ∧  i ≠ j  ∧
        (obtener(c, e.vacunados))[i] = (obtener(c, e.vacunados))[i])) ∧
      (∀c,c': ciudad)(not(∃p: persona)(está?(p,obtener(c,e.vacunados)) ∧ está?(p,obtener(c',e.vacunados))))

(2) y (4) ≡
      (∀p: persona)(def?(p, e.residencia) ⇒
      p ∈ obtener(obtener(p, e.resicencia), e.vacunados) ∨ p ∈ obtener(obtener(p, e.resicencia), e.esperando))

(7) ≡ (∀p: persona)(def?(p, residencia) ⇔ (∃c: ciudad)(p ∈ obtener(c, e.vacunados) ∨ p ∈ obtener(c, e.esperando)))

(3) ≡ (∀c: ciudad)(obtener(c, e.vacunados) ∩ obtener(c, e.esperando) = vacio)

(5) y (6) ≡
      (∀c,c': ciudad)(obtener(c, e.vacunados) ∩ obtener(c', e.vacunados) = vacio  ∧ 
                      obtener(c, e.esperando) ∩ obtener(c, e.esperando) = vacio)

(8) ≡ not(∃t,t': tupla(ciudad,nat))(t ≠ t' ∧  t ∈ e.frascos ∧  t' ∈ e.frascos ∧  π1.(t) = π1.(t'))

(9) ≡ (∀t: tupla(ciudad,nat))(t ∈ e.frascos ⇒ #(obtener(π1.(t), e.esperando)) < 5)

(10) ≡ (∀t: tupla(ciudad,nat))(t ∈ e.frascos ⇒ π1.(t) ∈ claves(e.vacunados) ∧ #(e.frascos) = #(claves(e.vacunados)))
```

### Funcion de abstraccion
Quiero ver que:
1. Mismas ciudades
2. Coinciden residentes con sus ciudades
3. Coinciden vacunados con sus ciudades
4. Coinciden esperando con sus ciudades
5. Coinciden frascos por ciudad

```
Abs: estr e ➔ sv
Abs(e) ≡ sv: sv /
      me da fiaca hacerlo pero creo que es solo lo de arriba 
```