simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` ∩ α

# Ejercicio 2

bookface se representa con _estr_, donde
```
estr es tupla(
    amistades : conj(tupla(usuario, usuario)),
    seguidores : dicc(usuario, conj(usuario)),
    solicitudesPendientes : dicc(usuario, secu(usuario)),
    cantAmigos: dicc(usuario, nat)
)
```
## Resolucion:

### Invariante de Representacion
Tiene que cumplir:
1. En amistades no haya ninguna tupla con los mismos usuarios (no puede haber {u5,u7},{u7,u5})
2. En amistades no haya una amistad con el mismo usuario (no puede haber {u2,u2})
3. En seguidores un usuario no puede seguirse a si mismo
4. En solicitudes un usuario no puede tener una solicitud de un amigo, y la vuelta de implicacion
5. En solicitudes un usuario no puede tener una solicitud de si mismo
6. En cantAmigos de un usuario es igual a la cantidad de veces que aparece ese usuario en alguna tupla de amistades
7. Todos los usuarios de cantAmigos aparecen en amistades, y la vuelta de implicacion
```
Rep: estr ➔ bool
Rep(e) ≡

(1) ≡ not(∃t,t': tupla(usuario,usuario))(t,t' ∈ e.amistades ∧ π1.t = π2.t' ∧ π2.t = π1.t')

(2) ≡ not(∃t: tupla(usuario,usuario))(t ∈ e.amistades ∧ π1.t = π2.t)

(3) ≡ (∀u: usuario)(def?(u, e.seguidores) ⇒ not(u ∈ obtener(u, e.seguidores)))

(4) ≡ (∀u1: usuario)(def?(u1, e.solicitudesPendientes) ⇒
      (∀u2: usuario)(está?(u2, obtener(u1, e.solicitudesPendientes)) ⇒
      not({u1,u2} ∈ e.amistades) ∧ not({u2,u1} ∈ e.amistades)) ∧
      not(∃t: tupla(usuario,usuario))(t ∈ e.amistades ∧ está?(u2, obtener(u1, e.solicitudesPendientes))))

(5) ≡ (∀u1,u2: usuario)(def?(u1, e.solicitudesPendientes) ∧
      está?(u2, obtener(u1, e.solicitudesPendientes)) ⇒ u2 ≠ u1)

(6) ≡ (∀u1,u2: usuario)(def?(u1, e.cantAmigos) ⇒
      obtener(u1, e.cantAmigos) = #apariciones({u1,u2}, e.amistades) + #apariciones({u2,u1}, e.amistades))

(7) ≡ (∀u: usuario)(u ∈ claves(e.cantAmigos) ⇔ (∃t: tupla(usuario,usuario))
      (t ∈ e.amistades ∧ (π1.t = u ∨ π2.t = u)))
```

### Funcion de abstraccion
Tengo que ver que:
1. Coincidan usuarios con los que aparecen en amistades, seguidores, solicitudes y cantAmigos
2. amigos? es verdadero si encuentra una tupla con ambos amigos en e.amistades
3. Coinciden solicitudes pendientes
4. Coinciden seguidores
```
Abs: estr e ➔ BookFace
Abs(e) ≡ bf : BookFace / 
        (∀u: usuario)(u ∈ usuarios(bf) ⇒ seguidores(bf, u) = obtener(u, e.seguidores)) ∧ 

        (∀u1,u2: usuario)(u1,u2 ∈ usuarios(bf) ∧ u2 ∈ (seguidores(bf, u)) ⇒ u2 ∈ obtener(u, e.seguidores)) ∧

        (∀u1,u2: usuario)(u1,u2 ∈ usuarios(bf) ⇒ amigos?(bf, u1, u2) ⇔
        ({u1,u2} ∈ e.amistades ∨ {u2,u1} ∈ e.amistades))  ∧

        (∀u1,u2: usuario)((({u1,u2} ∈ e.amistades ∨ {u2,u1} ∈ e.amistades) ∧
        ((def?(u1, e.seguidores) ⇒ u2 ∈ obtener(u1, e.seguidores)) ∨
        (def?(u2, e.seguidores) ⇒ u1 ∈ obtener(u2, e.seguidores))) ∧
        ((def?(u1, e.solicitudePendientes) ⇒ está?(u2,obtener(u1, e.seguidores))) ∨
        (def?(u2, e.solicitudePendientes) ⇒ está?(u1,obtener(u2, e.seguidores)))) ∧
        (u1 ∈ claves(e.cantAmigos) ∨ u2 ∈ claves(e.cantAmigos)))  ⇒  u1 ∈ usuarios(bf) ∨ u2 ∈ usuarios(bf))
 

```