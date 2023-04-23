# Ejercicio 5

Se decidio utilizar la siguiente estructura para representar una fila en un banco (Ejercicio 10, Practica 1):  
banco se representa con estr  

donde _estr_ es tupla(entraron: conj(persona), fila: cola(persona), colados: conj(persona), atendidos: conjunto(persona))  

Donde:
_Entraron_ es un conjunto con todas las personas que alguna vez estuvieron en la fila.  
_Colados_ son las personas que estan actualmente en la fila y se colaron al llegar.  
_Atendidos_ son las personas que fueron atendidas en el banco.  

Escribir invariante de representacion y funcion de abstraccion  

## Resolucion:

### Invariante de Representacion
Tiene que cumplir:
1. Las personas de la fila entraron
2. Las personas de la fila no fueron atendidas

```
Rep: estr ➔ bool
Rep(e) ≡ (∀i: nat)(0 ≤ i < tamaño(e.fila) ⇒L (e.fila[i] ∈ e.entraron  ∧  not(e.fila[i] ∈ e.atendidos)))
```

### Funcion de abstraccion
Veo que:
1. Mismas personas que entraron al banco
2. Mismas personas que fueron atendidas
3. Mismas personas que se colaron
4. Mismas personas en fila y misma posicion

Doble inclusion en cada una

```
Abs: estr e ➔ filaBanco
Abs(e) = fila : filaBanco /
        (∀p: persona)(((p ∈ e.entraron ⇒ Entró?(p,fila)) ∧ (Entró?(p,fila) ⇒ p ∈ e.entraron)) ∧ 
        ((p ∈ e.atendidos ⇒ FueAtendido?(p,fila)) ∧ (FueAtendido?(p,fila) ⇒ p ∈ e.atendidos)) ∧ 
        ((seColó?(p,fila) ⇒ p ∈ e.colados) ∧ (p ∈  e.colados ⇒ seColó?(p,fila))) ∧L
        (esperando(p,fila) ⇒ (∃i: nat)(0 ≤ i < largo(e.fila) ∧ e.fila[i] = p ∧ i = posicion(p,fila))) ∧L
        (∀i: nat)(0 ≤ i < largo(e.fila) ⇒ esperando(e.fila[i],fila) ∧ i = posicion(p,fila)) )
```

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ```