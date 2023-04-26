simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` ∩ α

# Ejercicio 1

```
TAD Arbol Binario Extendido
   
   Otras operaciones
      maximo: ab(nat)           ➔  nat         {not nil?(ab)}
      sumar: ab(nat) × ab(nat)  ➔  ab(nat)

   Axiomas    (∀a,b: ab(nat))(∀n: nat)
      maximo(a) ≡   if esHoja?(a) then raiz(a)
                    else max3(maximo(izq(a)), raiz(a), maximo(der(a)))
                    fi

      sumar(a, b) ≡ if nil?(a) ∧ nil?(b) then nil
                    else
                        if nil?(a) ∧ not(nil?(b))
                           then b
                        else
                            if nil?(ba) ∧ not(nil?(a))
                               then a
                            else bin(sumar(izq(a), izq(b)), raiz(a) + raiz(b), sumar(der(a), der(b)))
                            fi
                        fi
                    fi
```


# Ejercicio 2

```
   Axiomas  (∀p,q,r: producto)(∀s: stock)(∀n: nat)
      // tieneSustituto?(p, abrirTienda) // no se axiomatiza porque no cumple la restriccion de p ∈ productos
      tieneSustituto?(p, nuevoProducto(s, q, n)) ≡ if  p = q  then false
                                                   else tieneSustituto?(s, p)
                                                   fi
      tieneSustituto?(p, compra(s, q, n)) ≡  tieneSustituto?(p, s)
      tieneSustituto?(p, venta(s, q, n)) ≡  tieneSustituto?(p, s)
      tieneSustituto?(p, defSustituto(s, q, r)) ≡  if p = q  then true
                                                   else tieneSustituto?(p, s)
                                                   fi
                                           
      sustituto(p, nuevoProducto(s, q, n)) ≡  sustituto(p, s)
      sustituto(p, compra(s, q, n)) ≡  sustituto(p, s)
      sustituto(p, venta(s, q, n)) ≡  sustituto(p, s)
      sustituto(p, defSustituto(s, q, r)) ≡  if  p = q  then r
                                             else sustituto(p, s)
                                             fi

      #disponibles(p, nuevoProducto(s, q, n)) ≡ if p = q  then 0
                                                else #disponibles(p, s)
                                                fi
      #disponibles(p, compra(s, q, n)) ≡  if p = q  then #disponibles(p, s) + n
                                          else #disponibles(p, s)
                                          fi
      #disponibles(p, venta(s, q, n)) ≡  if p = q  then 
                                             if  #disponibles(p, s) ≤ n  then 0
                                             else  #disponibles(p, s) - n
                                             fi
                                         else  #disponibles(p, s)
                                         fi
      #disponibles(p, defSustituto(s, q, r)) ≡  #disponibles(p, s)

      bajoUmbral (s) ≡ // no entiendo que pide hacer //

      #disponiblesSust(s, p) ≡ if  tieneSustituto?(p, s)  then #disponibles(sustituto(p,s), s)
                               else 0
                               fi
```


# Ejercicio 3
**Datos importantes para diferenciar dos instancias de TAD:** Materias, aulas y su capacidad, franjas horarias, reservas de cada aula con materia y franja.  

Con esa info ya puedo saber el resto de cosas no importantes, y por lo tanto que no son observadores, como que aulas estan libres en cierta franja, o las materias que mas reservaron aulas.

```
TAD Sistema de Aulas
    Generos  SA
    Igualdad observacional

    Observadores
      materias: SA              ➔   conj(materia)
      aulas: SA                 ➔   conj(aula)
      capacidad: SA s × aula a  ➔   nat                        {a ∈ aulas(s)}
      franjas: SA               ➔   franja
      reservas: SA s × aula a   ➔   dicc(franja, materia)      {a ∈ aulas(s)}

    Generadores
      abroAulas: dicc(aula, nat) × conj(materia) × conj(franja) ➔ SA
      reservar: SA s × aula a × materia m × franja f            ➔ SA
                                                        {a ∈ aulas(s), m ∈ materias(s), f ∈ franjas(s)}

        // si al final se acepta o no la solicitud, es comportamiento automatico,
        // a mi me importa cuando sí se puede reservar
    
    Otras Operaciones
      aulasLibres: SA s × franja f             ➔  conj(aula)    {f ∈ franjas(s)}
      buscoAulaLibre: SA × conj(aula) × franja ➔  conj(aula)

    Axiomas (∀s: SA)(∀f: franja)(∀ca: conj(aula))

      aulasLibres(s,f) ≡ buscoAulaLibre(s, aulas(s), f)

      buscoAulaLibre(s, ca, f) ≡ if vacio?(ca) then {}
                                 else
                                     if not def?(f, reservas(sa, dameUno(ca)))
                                        then Ag(dameUno(ca), buscoAulaLibre(s, sinUno(ca), f))
                                     else buscoAulaLibre(s, sinUno(ca), f)
                                 fi
```

simbolos × ➔ ⇒ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` ∩ α