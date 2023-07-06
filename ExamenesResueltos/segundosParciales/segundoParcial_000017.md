## Ejercicio 1

```cpp
dt se representa con:

   tupla<
        clientesPorPaquete: diccLog(paquete, conjLog(cliente)),
        paquetesPorCliente: diccLog(cliente, diccLog(paquete, tupla<
                                                                   itPack: itDiccLog, 
                                                                   itCliente: itConjLog
                                                                   >))
        >
```

Las operaciones las realizo:
- **AgregarCliente** agrega un cliente a _paquetesPorCliente_ en O(log n) con significado vacío
- **AgregarPaquete** agrega un paquete a _clientesPorPaquete_ en O(log m) con significado vacío
- **DarDeAltaPaquete** busca al paquete en _clientesPorPaquete_ en O(log m), crea un iterador para utilizar luego que apunta a ese paquete, y agrega al cliente al conjunto significado en O(log n), creando tambien un iterador de este cliente en ese conjunto. Luego busca al cliente en _paquetesPorCliente_ en O(log n) y agrega la clave-significado del paquete dado con sus iteradores creados previamente, que cuesta O(log m). Esto es entonces O(2 log m + 2 log n) = O(log n + log m)
- **DarDeBajaPaquete** busca al cliente en _paquetesPorCliente_ en O(log n) y luego en su significado busca al paquete a dar de baja en O(log c). Con este significado, accede en O(1) a su segundo iterador que apunta al cliente en el paquete y lo elimina. Luego también elimina la clave-valor de paquete y tupla de _paquetesPorCliente_ que cuesta O(log n + log c). La complejidad es entonces O(2 log n + 2 log c) = O(log n + log c)
- **EliminarCliente** busca al cliente en _paquetesPorCliente_ en O(log n) y recorre todos sus paquetes contratados iterando sobre ellos que cuesta O(c), y por cada uno accede en O(1) al cliente en los conjuntos de _clientesPorPaquete_ eliminandolos de allí. Luego elimina al cliente de _paquetesPorCliente_. Esto lleva en total O(log n + c)
- **ObtenerClientesPorPaquete** busca al paquete en _clientesPorPaquete_ en O(log m) y devuelve su conjunto significado

```c
darDeBajaPaquete(inout dt: directVision, in pack: paquete, in cl: cliente){
    packsDeCl = obtener(dt.paquetesPorCliente, cl); // O(log n), es referencia modificable
    iteradores = obtener(packsDeCl, pack); // O(log c)

    eliminarSiguiente(iteradores.itCliente); // elimino al cliente en el pack

    borrar(packsDeCl, pack); // O(log n + log c), borra al paquete contradado 
}
```

## Ejercicio 2

Primero armo un arreglo fijo de largo 365 con 0s en cada posición. Luego recorro mi arreglo de intervalos y por cada uno, tomando como índice las posiciones de principio y de fin, sumo +1 en esa posición. Hasta aca va una complejidad O(n). Luego, creo un arreglo del largo de mi arreglo de intervalos original, y por cada intervalo que recorro, me fijo en el arreglo de largo 365 entre su principio y fin cuantos números hay y los voy sumando, pues cada posición indica cuántos intervalos comienzan o terminan ahi (sin contar el mismo número de principio o de fin pues es solo en su interior). Luego añado al arreglo nuevo una tupla con la info <principio, fin, #conflictos>. Esto tiene una complejidad de O(365*n) = O(n). Luego, como la maxima cantidad de conflictos que puede tener un intervalo de 2n-1, puedo hacer un Bucket Sort con un arreglo de listas vacías, con largo 2n-1, en el que añadiré las tuplas según su cantidad de conflictos. Esto tiene una complejidad de O(n+2n) = O(n). Luego simplemente recorro los buckets adecuadamente, en reversa, para que quede ordenado crecientemente según su cantidad de conflictos. Complejidad final: O(n). Me da fiaca hacer el algoritmo pero en esencia es esto que expliqué, _easy peacy bruh_.

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