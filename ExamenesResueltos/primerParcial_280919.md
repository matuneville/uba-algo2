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


FIN TAD
```

