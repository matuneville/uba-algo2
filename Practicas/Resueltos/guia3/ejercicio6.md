# Ejercicio 6

altafiesta se representa con _estr_  
donde _estr_ es tupla(invitados: conj(persona), presentes: cola(persona), grupoDe: dicc(grupo, conj(persona)), regaloDeGrupo: dicc(grupo, regalo), grupoMasNumeroso: grupo)

grupo, persona y regalo son _string_

## Resolucion:

### Invariante de Representacion
Tiene que cumplir:
1. Los significados del grupoDe debe tener a todos los presentes y viceversa
2. Las claves del grupoDe deben coincidir con las claves de regaloDeGrupo
3. Todos los presentes deben ser invitados
4. grupoMasNumeroso debe ser algun significado de grupoDe y sea el mas grande, y si hay otro con la misma cantidad de invitados, sea el menor lexicofragicamente
5. Que no haya ni una persona en mas de un grupo

```
Rep: estr ➔ bool
Rep(e) ≡ (1) ∧L (2) ∧L (3) ∧L (4) ∧L (5)

(1) = (∀i: nat)(0 ≤ i < largo(e.presentes) ⇒
    (∃g: grupo)(definido?(g, e.grupoDe) ∧ p ∈ significado(g, e.grupoDe))) ∧
    (∀g: grupo)(definido?(g, e.grupoDe) ⇒ (∀p: persona)(p ∈ significado(g, e.grupoDe) ⇒
    (∃i: nat)((0 ≤ i < largo(e.presentes) ∧ p = e.presentes[i]))))

(2) = (∀g: grupo)(definido?(g, e.grupoDe) ⇔ definido?(g, e.regaloDeGrupo))

(3) = (∀i: nat)(0 ≤ i < largo(e.presentes) ⇒ e.presentes[i] ∈ e.invitados)

(4) = definido?(e.grupoMasNumeroso, e.grupoDe) ∧
  not(∃g: grupo)(definido?(g, e.grupoDe) ∧ g ≠ e.grupoMasNumeroso ∧
  ( #(obtener(g, e.grupoDe)) > #(significado(e.grupoMasNumeroso, e.grupoDe)) ∨
  (#(significado(g, e.grupoDe)) = #(significado(e.grupoMasNumeroso, e.grupoDe) ∧ g > e.grupoMasNumeroso))))

(5) = (∀g,g': grupo)(definido?(g, e.grupoDe) ∧ definido?(g', e.grupoDe) ∧ g ≠ g' ⇒
    (significado(g,e.grupoDe) ∩ significado(g',e.grupoDe) = vacio))
```

### Funcion de abstraccion
Tengo que ver:
1. Los invitados pendientes no esten presentes y que sí esten en invitados
2. Mismos grupos, me fijo a traves de personasPorRegalo, locomplemento con el (3)
3. Mismos regalos por grupo
4. El grupoMasNumeroso sea el mismo
```
Abs: estr e ➔ altaFiesta
Abs(e) = altaFiesta / (1) ∧ (2) ∧ (3) ∧ (4)

(1) = (∀i: nat)(0 ≤ i < largo(e.presentes) ⇒ not(e.presentes[i] ∈ invitadosPendientes(altaFiesta))) ∧
    (∀p: persona)(p ∈ invitadosPendientes(altaFiesta) ⇒ not(∃i: nat)(0 ≤ i < largo(e.presentes) ⇒ e.presentes[i] = p))

(2) = (∀r: regalo)(r ∈ regalos(altaFiesta) ⇒ (∃g:grupo)(definido?(g, e.grupoDe) ∧
    personasPorRegalo(altaFiesta,r) = significado(g, e.grupoDe)))

(3) = (∀g: grupo)(definido?(g, e.grupoDe) ⇒
    personasPorRegalo(altaFiesta, significado(g, e.regaloDeGrupo)) = significado(g, e.grupoDe))

(4) = grupoMasNumeroso(altaFiesta) = e.grupoMasNumeroso
```

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ```