## Ejercicio 3

Si representamos el arbol binario con forma de Heap con un arreglo, lo que hay que hacer es tomar la raiz y acortar el arreglo a la mitad; siempre la nueva raíz será el siguiente nodo a recorrer para llegar al requerido. Esto se ve más fácilmente viendo muchos ejemplos en papel, me da fiaca elaborarlo tanto aca.  
Mi indexación en el arreglo comienza en 1, y, como voy dividiendo en 2 el arreglo, cuando llegue a tamaño 2 o 3 será el caso base pues 2/2 y 2/3 = 1, y ya no podré achicar más el arreglo. En ese momento se añadirá la raíz y el útimo nodo.

```cpp
iCAMINOaNODOrecursion(ab: arr[int], int begin, int end) -> lista(Nodo)
    if (end-begin == 2 or end-begin == 3)
        return lista = {ab[begin], ab[end]} // O(1)
    
    else
        return agregarAdelante(ab[begin], iCAMINOaNODOrecursion(ab, (end+begin)/2, end))


iCAMINOaNODO(ab: arr[int]) -> lista(Nodo)
    tamaño = tamano(ab)

    return iCAMINOaNODOrecursion(ab, 0, tamano)
```

### Complejidad:
$T(n) = 1*T(n/2) + O(1)$  
$Sea\ a = 1,\ c = 2,\ f(n) = 1$  
$f(n) = 1 \in Θ(n^{log_1 2}) = Θ(n^0) = Θ(1)$   
$\rightarrow T(n) = Θ(n^{log_1 2} * log n) = Θ(n⁰ log\ n) = Θ(log\ n)$