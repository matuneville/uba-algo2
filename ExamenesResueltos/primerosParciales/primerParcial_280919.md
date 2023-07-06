simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` ∩ α

# Ejercicio 1

TAD Persona es nat (el DNI)
TAD Gato es string (la raza)

```
TAD Centro:

    Observadores basicos
        gatitos: centro  ➔  dicc(gato, nat)
        listaDeEspera: centro  ➔  cola(persona)             {vacio?(claves(gatitos))}
        tieneGatito?: centro × persona  ➔  bool
        historialPersonasQueAdoptaron: centro  ➔  multiconj(persona)
    
    Generadores
        nuevoCentro:  ➔  centro
        nuevosGatitos: dicc(gato, nat)  ➔  centro
        adoptaGatito: centro c × persona p × gato g ➔  centro            {not tieneGatito?(c,p), obtener(g, gatitos(c)) > 0}
        devuelveGatito: persona × gato  ➔  centro

    Otras operaciones
        personaQueMasAdopto: centro  ➔  persona
        // para axiomatizar este usaria #apariciones de cada persona en historialPersonasQueAdoptaron
        // y me quedaria con el mas grande, gg ez

FIN TAD
```

# Ejercicio 2

```
    UnirMuchos: conj(dicc) ➔ dicc

    UnirMuchos(cd) ≡ 
            if  vacio?(cd)  then vacio
            else
                 if vacio?(sinUno(cd)) then dameUno(cd)
                 else
                    unoDiccionarios(dameUno(cd), UnirMuchos(sinUno(cd)))
                 fi
            fi
                         

    
    unoDiccionarios: dicc × dicc ➔ dicc

    unoDiccionarios(d1, d2) ≡
            if  d1 = vacio  then d2
            else
                if  d2 = vacio  then d1
                else
                    unoDiccionarios(borrar(dameUno(claves(d1)), d1),
                                    definir(dameUno(claves(d1)), obtener(dameUno(claves(d1)), d1), d2)) 
                fi
            fi
```
