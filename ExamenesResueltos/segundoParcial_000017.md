## Ejercicio 2

Primero armo un arreglo fijo de largo 365 con booleanos false. Luego recorro mi arreglo de intervalos y por cada uno, escribo en su índice de principio y fin true. Hasta aca va una complejidad O(n). Luego, creo un arreglo del largo de mi arreglo de intervalos original, y por cada intervalo que recorro, me fijo en el arreglo de largo 365 entre su principio y fin cuantos true hay, y luego añado al arreglo nuevo una tupla con la info <principio, fin, #conflictos>. Esto tiene una complejidad de O(365*n) = O(n). Luego, como la maxima cantidad de conflictos que puede tener un intervalo de 365, puedo hacer un Bucket Sort con un arreglo de listas vacías, con largo 365, en el que añadiré las tuplas según su cantidad de conflictos. Esto tiene una complejidad de O(n). Luego simplemente recorro los buckets adecuadamente, en reversa, para que quede ordenado crecientemente según su cantidad de conflictos. Complejidad final: O(n). Me da fiaca hacer el algoritmo pero en esencia es esto que expliqué, _easy peacy bruh_.

## Ejercicio 3

Si justo en el medio es donde se corta un subarreglo CO, entonces calculo la suma de los dos subarreglos crecientes contiguos y hago la recursion. Ej: en [0, 1, 2, 4, 3, 7, 0, 1], en el medio es donde termina [0, 1, 2, 4] y luego empieza [3, 7].  
Si no, puede pasar que justo en el medio esté creciendo, por lo que habría que contar el largo de ese subarreglo creciente y sumarle el mas largo de los subarreglos crecientes contiguos. Ej: en [5, 3, 5, 4, 5, 7, 4, 2], en el medio esta el subarreglo creciente [4, 5, 7], y en sus costados están [3, 5] y [4]. Entonces sumo el mas largo y quedaría 3 + 2 = 5.

```cpp
// O(n), cuenta la cadena C.O. partiendo desde la izquierda
int largoCrecienteDer(int arr[], int begin, int end, int subarrayAContar){
    int largo = 0;
    while(begin < end and subarrayAContar > 0){
        largo ++;
        if(arr[begin] > arr[begin+1])
            subarrayAContar--;
        begin++;
    }
    return largo;
}

int largoCrecienteIzq(int arr[], int begin, int end, int subarrayAContar){
    int largo = 0;
    while(begin > end and subarrayAContar > 0){
        largo ++;
        if(arr[begin] < arr[begin-1])
            subarrayAContar--;
        begin--;
    }
    return largo;
}

int mayorCO_recursivo(int arr[], int begin, int end){
    if(end - begin == 1)
        return 1;  // O(1)
    
    int medio = (end + begin)/2; // O(1)

    int COalMedio, recursion;

    if(arr[medio] < arr[medio - 1]){
        // cuento hacia cada lado 1 solo subarreglo creciente que forma el CO
        int crecienteDer = largoCrecienteDer(arr, medio, end, 1);    // O(n)
        int crecienteIzq = largoCrecienteIzq(arr, medio-1, begin-1, 1);  // O(n)

        COalMedio = crecienteDer + crecienteIzq;
    }
    else{ // cuento hacia cada lado 1 solo subarreglo creciente que forma el CO
        // tambien veo los contiguos, sumando 2 subarreglos crecientes y restandole el primero
        int crecienteDer = largoCrecienteDer(arr, medio, end, 1);    // O(n)
        int crecienteIzq = largoCrecienteIzq(arr, medio-1, begin-1, 1);  // O(n)

        int crecienteDerContiguo = largoCrecienteDer(arr, medio, end, 2) - crecienteDer;    // O(n)
        int crecienteIzqContiguo = largoCrecienteIzq(arr, medio-1, begin-1, 2) - crecienteIzq;  // O(n)

        COalMedio = crecienteDer + crecienteIzq + max(crecienteDerContiguo, crecienteIzqContiguo); // O(1)
    }

    recursion = max(mayorCO_recursivo(arr, begin, medio), mayorCO_recursivo(arr, medio, end));

    return max(COalMedio, recursion);
}
```

### Complejidad
La complejidad del algoritmo sin contar las recursiones es de O(n), cuando calculo el largo de subarreglos. Después hago una doble recursión separando el arreglo en dos. Por Teorema Maestro, cumple el segundo caso, y la complejidad queda:  
$T(n) = 2T(n/2) + O(n)$  
$Sea\ a = 2,\ c = 2,\ f(n) = n$  
$f(n) = n \in Θ(n^{log_2 2}) = Θ(n^1) = Θ(n)$   
$\rightarrow T(n) = Θ(n^{log_2 2}\ log n) = Θ(n^1 log\ n) = Θ(n\ log\ n)$