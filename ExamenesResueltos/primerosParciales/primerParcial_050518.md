simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` ∩ α

# Ejercicio 1

## Resolucion
```
TAD Centro Comunitario de Carpinteros:

    Observadores basicos
        maestros: centro ➔ conj(persona)
        estudiantes: centro ➔ conj(persona)
        desertores: centro ➔ conj(persona)
        nivelDe: centro c × persona p ➔ nat                    {p ∈ estudiantes(c)}
        aprendicesDe: centro c × persona p ➔ conj(persona)     {p ∈ estudiantes(c) ∨ p ∈ maestros(c)}
    
    Generadores
        nuevoCentro: conj(persona) ➔ centro
        subirNivel: centro c × persona p ➔ centro              {p ∈ estudiantes(c)}
        ingresa: centro c × persona p ➔ centro
        abandona: centro c × persona p ➔ centro                {p ∈ estudiantes(c) ∨ p ∈ maestros(c)}

    Otras operaciones
        descendientes: centro c × persona p ➔ centro           {p ∈ estudiantes(c) ∨ p ∈ maestros(c)} 
        agregoDescendientes: centro × conj(persona) ➔ conj(persona)

    Axiomas
        (∀c: centro)(∀p,q: persona)(∀cp: conj(persona))

        maestros(nuevoCentro(cp)) ≡ cp
        maestros(subirNivel(c,p)) ≡ if  nivelDe(p) = 10  then Ag(p, maestros(c))
                                    else  maestros(c)
                                    fi
        maestros(ingresa(c,p)) ≡ maestros(c)
        maestros(abandona(c,p)) ≡ if  p ∈ maestros(c)  then  maestros(c) - p
                                  else  maestros(c)
                                  fi

        estudiantes(nuevoCentro(cp)) ≡ vacio
        estudiantes(subirNivel(c,p)) ≡ if  nivelDe(p) = 10  then estudiantes(c) - p
                                       else  estudiantes(c)
                                       fi
        estudiantes(ingresa(c,p)) ≡ Ag(p, estudiantes(c))
        estudiantes(abandona(c,p)) ≡ if  p ∈ estudiantes(c)  then  estudiantes(c) - p
                                     else  estudiantes(c)
                                     fi

        desertores(nuevoCentro(cp)) ≡ vacio
        desertores(subirNivel(c,p)) ≡ desertores(c)
        desertores(ingresa(c,p)) ≡ desertores(c)
        desertores(abandona(c,p)) ≡ Ag(p, desertores(c))

        // nivelDe(nuevoCentro(cp), q) ≡ no cumple la restriccion
        nivelDe(subirNivel(c,p), q) ≡ if  p = q  then  nivelDe(c, p) + 1
                                      else  nivelDe(c, q)
                                      fi
        nivelDe(ingresa(c,p), q) ≡ if  p = q  then  1
                                   else  nivelDe(c, q)
                                   fi
        nivelDe(abandona(c,p), q) ≡ nivel(q)  // no veo si p = q porque no cumpliria la restriccion

        // aprendicesDe(nuevoCentro(cp), q) ≡ no cumple la restriccion
        aprendicesDe(subirNivel(c,p), q) ≡ aprendicesDe(c, q)  // si p llega al nivel de q es comp automatico
        aprendicesDe(ingresa(c,p), q) ≡ aprendicesDe(c, q)
        aprendicesDe(abandona(c,p), q) ≡ if  p ∈ aprendicesDe(c, q) 
                                             then  (aprendicesDe(c, q) - p) ∪ aprendicesDe(c, p)
                                         else  aprendicesDe(c, q)
                                         fi

        descendientes(c, p) ≡ if vacio?(aprendicesDe(c, p)) then  vacio
                              else  aprendicesDe(c, p) ∪ agregoDescendientes(c, aprendicesDe(c, p))
                              fi

        agregoDescendientes(c, cp) ≡ if vacio?(cp) then vacio
                                     else  descendientes(c, dameUno(cp)) ∪ agregoDescendientes(c, sinUno(cp))
                                     fi

FIN TAD
```

# Ejercicio 2

## Resolucion

1. Falso, contraejemplo: f(n) = c*n, con n > 1
2. Falso, contraejemplo posible: f(n) = n^3, g(n) = n^2
3. Falso. El primer ciclo for lo ejecutará siempre n veces. En el peor caso, i sera menor a 100, pero este ciclo de complejidad n se ejecutará como mucho 100 veces, por lo que al ser una cantidad acotada no llega a ser una complejidad n^2. El peor caso tendria una curva de tipo primero exponencial y luego lineal, por lo que las cotas mas ajustadas por arriba y por abajo serian lineales. Por lo tanto su complejidad seria Theta(n).
4. Verdadero


# Ejercicio 3

TaD se representa con _estr_  

```
estr es tupla{
    técnicos: conj(técnico),
    clientes: conj(dirección),
    ubicación: dicc(técnico, dirección),
    quienesEstánEn: dicc(dirección, conj(técnico)),
    pendientes: secu(dirección),
    visitas: dicc(técnico, multiconj(dirección))
}
```

## Resolucion

### Invariante de Representacion
Tiene que cumplir:
1. Cada tecnico t que esté en e.ubicación d, estará t en el conjunto de e.quienesEstanEn d
2. Cada dirección d que tenga a todos los técnicos t en e.quienesEstanEn d, será la e.ubicacion de cada t
3. Las claves de e.ubicacion esta incluida en e.tecnicos, y e.tecnicos es igual a claves de e.visitas (por 1 y 2 tambien me estaré asegurando de que no haya ningun tecnico extra en e.quienesEstánEn)
4. Si una direccion está en e.pendientes, no tiene a ningun técnico en e.quienesEstánEn (la implicacion no iria al reves)
5. Las claves de e.quienesEstanEn es igual a la union de e.clientes y e.pendientes
```
Rep: estr ➔ bool
Rep(e) ≡ (1) ∧ (2) ∧ (3) ∧ (4) ∧ (5)

(1) ≡ (∀t: tecnico)(def?(t, e.ubicacion) ⇒ def?(obtener(t, e.ubicacion), e.quienesEstánEn) ∧
                                t ∈ obtener(obtener(t, e.ubicacion), e.quienesEstánEn))

(2) ≡ (∀d: direccion)(d ∈ e.clientes ⇒ #(obtener(d, e.quienesEstanEn)) > 0 ⇒(∀t: tecnico)(t ∈ obtener(d, e.quienesEstanEn) ⇒
                                         d = obtener(t, e.ubicacion))) ∧
                                        #(obtener(d, e.quienesEstanEn)) = 0 ⇒(∀t: tecnico)(t ∈ obtener(d, e.quienesEstanEn) ⇒
                                         d ≠ obtener(t, e.ubicacion))

(3) ≡ claves(e.ubicación) ⊆ e.tecnicos ∧ e.tecnicos = claves(e.visitas)

(4) ≡ (∀d: direccion)(está?(d, e.pendientes) ⇒ vacio?(obtener(d, e.quienesEstanEn)))

(5) ≡ (∀d: direccion)(está?(d, e.pendientes) ∧ d ∈ e.clientes ⇔ d ∈ claves(e.quienesEstanEn)) ∧ 
``` 

### Funcion de abstraccion
Tengo que ver que:
1. Los tecnicos que estan en libres, es porque no están en claves de e.ubicacion
2. Los tecnicos que estan en ocupados, es porque si estan en claves de e.ubicacion
3. La union de libres y ocupados es igual a e.tecnicos
4. La ubicacion de un tecnico es la misma de e.ubicacion
5. Secuencia pendientes es igual a e.pendientes
6. Las visitas de un tecnico t en una direccion d, es igual a la cantidad de apariciones de d en e.visitas del tecnico
```
Abs: estr e ➔ Tecnicos a Domicilio
Abs(e) ≡ tad : TaD / 
        not(∃t: tecnico)(t ∈ libres(tad) ∧ t ∈ claves(e.ubicacion)) ∧
        (∀t: tecnico)(t ∈ ocupados(tad) ⇒ t ∈ claves(e.ubicacion)) ∧
        (e.tecnicos = libres(tad) ∪ ocupados(tad)) ∧
        (∀t: tecnico)(t ∈ ocupados(tad) ⇒ obtener(t, e.ubicacion) = ubicacion(tad, t)) ∧
        pendientes(tad) = e.pendientes ∧
        (∀t: tecnico)(∀d: direccion)(d ∈ e.clientes ∧ t ∈ e.tecnicos  ⇒
        visitas(tad, t, d) = #(d,obtener(t, e.visitas)))
```

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` ∩ ∪ ⊆ 