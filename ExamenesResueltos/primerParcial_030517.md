# Ejercicio 1

```
TAD Persona es nat (el DNI)

// para mi las ventanillas son enumeradas segun cuantas hay, ej:
// si cantVentanillas = 5, entonces tengo las ventanillas 1,2,3,4 y 5
// (no cuento la ventanilla 0, mala practica como programador jeje)

TAD CGT:
    Observadores basicos
        cantVentanillas: cgt ➔ nat
        personaAtendida: cgt c × nat v ➔ persona                   {0 < v ≤ cantVentanillas(c), ventanillaOcupada(c, v)}
        filaVentanilla: cgt c × nat v ➔ cola                       {0 < v ≤ cantVentanillas(c)}
        cuantosAtendio: cgt c × nat v ➔ nat                        {0 < v ≤ cantVentanillas(c)}
        tramitesPendientes: cgt c × persona p ➔ secu(nat)          {(∃v: nat)(0 < v ≤ cantVentanillas(c) ∧
                                                              p ∈ filaventanilla(c,v) v personaAtendida(c,v) = p)}

    Generadores
        abrirCGT: nat ➔ cgt
        atiendeVentanilla: cgt × nat v × persona ➔ cgt             {0 < v ≤ cantVentanillas(c)}
        llegaPersona: cgt c × persona p × secu(nat) s ➔ cgt        {(∀v: nat)(v ∈ s 0 ⇒ 0 < v ≤ cantVentanillas(c)) 
                                                                    ∧ not(∃v: nat)(0 < v ≤ cantVentanillas(c) ∧
                                                              p ∈ filaventanilla(c,v) v personaAtendida(c,v) = p)}

    Otras operaciones
        ventanillaOcupada: cgt c × nat v ➔ bool                    {0 < v ≤ cantVentanillas(c)}
        ventanillaQueMasAtendio: cgt c ➔ bool     
        buscoVentConMasAtendidos: cgt × nat v ➔ nat                {0 < v ≤ cantVentanillas(c)}
        maxAtendidosEnVents: cgt c × nat v ➔ nat                   {v = cantVentanillas(c)}


    Axiomas
        (∀v,v': nat)(∀p,p': persona)(∀c: cgt)(∀s: secu(nat))
        cantVentanillas(abrirCGT(v)) ≡ v
        cantVentanillas(atiendeVentanilla(c, v, p)) ≡ cantVentanillas(c)
        cantVentanillas(llegaPersona(c, p, s)) ≡ cantVentanillas(c)

        // personaAtendida(abrirCGT(v), v) ≡ // no cumple la restriccion
        personaAtendida(atiendeVentanilla(c, v, p), v') ≡ if v = v' then p else personaAtendida(c, v') fi
        personaAtendida(llegaPersona(c, p, s), v) ≡ if prim(s) = v ∧ vacia?(filaVentanilla(c, v)) then
                                                    else personaAtendida(c, v)
                                                    fi

        filaVentanilla(abrirCGT(v), v) ≡ vacia
        filaVentanilla(atiendeVentanilla(c, v, p), v) ≡ desencolar(filaVentanilla(c,v))
        filaVentanilla(llegaPersona(c, p, s), v) ≡ if prim(s) = v then encolar(fila) else filaventanilla(c, v) fi

        cuantosAtendio(abrirCGT(v), v) ≡ 0
        cuantosAtendio(atiendeVentanilla(c, v, p), v') ≡ cuantosAtendio(c, v) + (if v = v' then 1 else 0 fi)
        cuantosAtendio(llegaPersona(c, p, s), v) ≡ cuantosAtendio(c, v)

        // tramitesPendientes(abrirCGT(v), p) // no cumple la restriccion
        tramitesPendientes(atiendeVentanilla(c, v, p), p') ≡ if p = p' then fin(tramitesPendientes(c, p))
                                                             else tramitesPendientes(c, p')
                                                             fi
        tramitesPendientes(llegaPersona(c, p, s), p') ≡ if p = p' then s else tramitesPendientes(c, p')

        ventanillaOcupada(abrirCGT(), v) ≡ false
        ventanillaOcupada(atiendeVentanilla(c, v, p), v') ≡ if v = v' then true else ventanillaOcupada(c, v) fi
        ventanillaOcupada(llegaPersona(c, p, s), v) ≡ if vacia?(filaVentanilla(v)) ∧ prim(s) = v then true
                                                      else ventanillaOcupada(c, v)
                                                      fi

        ventanillaQueMasAtendio(c) ≡ buscoVentConMasAtendidos(c, cantVentanillas(c))

        buscoVentConMasAtendidos(c, v) ≡ if maxAtendidosEnVents(c, v) = cuantosAtendio(c, v) then v
                                         else buscoVentConMasAtendidos(c, v-1)
                                         fi

        maxAtendidosEnVents(c, n) ≡ if n = 1 then cuantosAtendio(c, 1)
                                   else max(cuantosAtendio(c, n), maxAtendidosEnVents(c, n-1))
                                   fi

FIN TAD

Por ultimo como use el operador ∈ para ver si las personas estaban en la fila, tengo que extender
el TAD Cola

TAD COLA
    Otras operaciones
        • ∈ • :  α  ×  cola(α)  ➔  bool
    
    Axiomas
        (∀a: α)(∀c: cola(α))
        a ∈ c ≡ if  vacia?(c)  then false
                else
                    if  próximo(c) = a  then true
                    else a ∈ desencolar(c)
                    fi
                fi

FIN TAD
```

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` ∩ ∪ ⊆


# Ejercicio 2
1. Falso, contraejemplo: f(n) = n³
2. Falso, contraejempplo: f(n) = 1/n
3. Verdadero pues mejor caso es O(n) y tambien pertenece a O(n²)
4. Verdadero pues peor caso es O(n²) y tambien pertenece a Omega(n)