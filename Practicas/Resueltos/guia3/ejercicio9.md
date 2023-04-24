# Ejercicio 9

planta se representa con _estr_  
    donde _estr_ es tupla(alarmas: dicc(alarma, conj(sensor)), sensores: dicc(sensor,tupla{alarmas : conj(alarma), umbral : nat, medicion : nat}))

## Resolucion:

### Invariante de Representacion
Tiene que cumplir:
1. Todo sensor que corresponde a una determinada alarma, tendra a esa alarma asignada
2. Toda alarma que corresponde a un determinado sensor, tendra a ese sensor asignada
Con eso tambien chequeo que no aparezca ninguna alarma o sensor que en el otro diccionario no aparezca
```
Rep: estr ➔ bool
Rep(e) ≡ (1) ∧ (2)

(1) ≡ (∀s: sensor)(∀a: alarma)(def?(a, e.alarmas) ∧ s ∈ obtener(a, e.alarmas) ⇒
      def?(s, e.sensores) ∧ a ∈ π1.(obtener(s, e.sensores)))

(2) ≡ (∀a: alarma)(∀s: sensor)(def?(s, e.sensores) ∧ a ∈ π1.(obtener(s, e.sensores)) ⇒
      def?(a, e.alarmas) ∧ s ∈ obtener(a, e.alarmas))
```

### Funcion de abstraccion
Tengo que ver que:
1. Todas las claves de e.alarma cumplen esAlarma
2. Todas las claves de e.sensores cumplen esSensor
3. Coinciden sensoresAlarma con los sensores de e.alarmas
4. Coinciden umbral y medicion de e.sensores
```
Abs: estr e ➔ Planta
Abs(e) ≡ planta : Planta /
        (1) ∧ (2) ∧ (3) ∧ (4) ∧ (5)

(1) ≡ (∀a: alarma)(a ∈ claves(e.alarmas) ⇔ esAlarma(planta, a))

(2) ≡ (∀s: sensor)(s ∈ claves(e.sensores) ⇔ esSensor(planta, s))

(3) ≡ (∀a: alarma)(def?(a, e.alarmas) ∧ obtener(a, e.alarmas) = sensoresAlarma(planta, a))

(4) ≡ (∀s: sensor)(def?(s, e.sensores) ⇒
      π2.(obtener(s, e.sensores)) = umbral(planta, s) ∧ π3.(obtener(s, e.sensores)) = medicion(planta, s))
```

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ```