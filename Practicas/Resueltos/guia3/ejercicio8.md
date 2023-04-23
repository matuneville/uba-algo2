# Ejercicio 8

oficina se representa con _estr_  
donde _estr_ es tupla(catPrioritarias: conj(categoria), tramites: dicc(id, categoria), tramites×Cat: dicc(categoria, conj(id)), pendPrioritarios: secu(id), pendientes: secu(id))

## Resolucion:

### Invariante de Representacion
Tiene que cumplir:
1. Coinciden categorias de significados de tramites y de keys de tramitesxCat
2. Las catPrioritarias estan en las mencionadas en el (1)
3. Coinciden los id en tramites, tramitesxCat y pendientes (nunca concluyen los tramites)
4. Los id de pendPrioritarios estan incluidos en pendientes
5. Los tramites con cat prioritaria estan en pendPrioritarios y viceversa.
6. No elem repetidos en pendientes y pendPrioritarios

```
Rep: estr ➔ bool
Rep(e) ≡ (1) ∧ (2) ∧ (3) ∧ (4) ∧ (5)

(1) ≡ (∀id: id)(∀cat: categoria)(obtener(id, e.tramites) = cat  ⇔  id ∈ obtener(cat, e.tramitesxCat))

(2) ≡ (∀cat: categoria)(cat ∈ e.catPrioritarias  ⇒ cat ∈ claves(e.tramitesxCat))
  # no chequeo tambien con e.tramites porque ya lo compare en (1) con e.tramitesxCat

(3) ≡ (∀id: id)((∃i: nat)(e.pendientes[i]) = id  ⇔  id ∈ claves(e.tramites))
 # no chequeo tambien con tramitesxCat porque ya lo compare en (1) con tramites

(4) ≡ (∀id: id)((∃i,j: nat)(e.pendPrioritarios[i] = id  ⇒ e.pendientes[j] = id))
 # hubiera usado está?(elem,secu) pero ya no lo voy a cambiar jeje

(5) ≡ (id: id)(obtener[id, e.tramites] ∈ e.catPreioritarias  ⇔  está?(id, e.pendPrioritarios))

(6) ≡ not(∃i,j: nat)(0 ≤ i < largo(e.pendientes) ∧  i≠j  ∧ e.pendientes[i] = e.pendientes[j]) ∧
    not(∃i,j: nat)(0 ≤ i < largo(e.pendPrioritarios) ∧  i≠j  ∧ e.pendPrioritarios[i] = e.pendPrioritarios[j])
```

### Funcion de abstraccion

Tengo que ver que
1. Mismas categorias de tramites
2. Mismos tramites pendientes (todos pues nunca terminan)
3. Mismas categorias prioritarias
4. Mismas categorias de cada tramite
```
Abs: estr e ➔ oficina
Abs(e) ≡ ofi: oficina / 
    categorias(ofi) = claves(e.tramitesxCat)  ∧  pendientes(ofi) = e.pendientes  ∧
    prioritarias(ofi) = e.catPrioritarias  ∧
    (∀id: id)(∀cat: categoria)(catTram(id, ofi) = cat  ⇔  obtener(id, e.tramites))
```

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ```