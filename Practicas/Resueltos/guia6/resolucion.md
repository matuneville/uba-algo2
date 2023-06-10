# Guía práctica 6: Divide & Conquer

## Ejercicio 1

Hago una recursión con ambas mitades de mi arreglo hasta que llegue al caso base. Si el arreglo es tamaño 1, entonces será másALaIzquierda. 

```cpp
int sumar(int arr[], int begin, int end);

bool masALaIzquierda(int arr[], int begin, int end){

    if(end-begin == 1) return true;

    int sumaIzq = sumar(arr, begin, (end+begin)/2);    // O(n/2)
    int sumaDer = sumar(arr, (end+begin)/2, end); // O(n/2)

    if(sumaDer >= sumaIzq) return false;

    else
        return (masALaIzquierda(arr, begin, (end+begin)/2) and masALaIzquierda(arr, (end+begin)/2, end)); // O(log n + log n)

}   // complejidad final O(n log n)

int sumar(int arr[], int begin, int end){
    int output = 0;
    for(int i = begin; i < end; i++){
        output += arr[i];
    }
    return output;
}
```

### Complejidad:
$T(n) = 2T(n/2) + O(n^1)$  
$Sea\ a = 2,\ c = 2,\ f(n) = n$  
$f(n) \in Θ(n^{log_2 2}) = Θ(n¹) = Θ(n)$   
$\rightarrow T(n) = Θ(n^{log_22} * log\ n) = Θ(n\ log\ n)$


## Ejercicio 2

Se hace un algoritmo similar a la búsqueda binaria, aprovechando el dato de que el arreglo esta estríctamente ordenado. Voy achicando mi problema hacia una u otra mitad, dependiendo qué numero sea el encontrado, respecto al índice en el que se encuentra:

```cpp
bool coincideIndiceElemento(int arr[], int begin, int end){ // la indexación comienza en 1
    if(end-begin == 1 and arr[(end+begin)/2] == begin+1)
        return true;
    else if(end-begin == 1 and arr[(end+begin)/2] != begin+1)
        return false;

    else{
        if(arr[((end+begin)/2) - 1] >= (end+begin)/2)
            return coincideIndiceElemento(arr, begin, (end+begin)/2);
        else
            return coincideIndiceElemento(arr, (end+begin)/2, end);
    }
}
```

### Complejidad:
$T(n) = 1*T(n/2) + O(1)$  
$Sea\ a = 1,\ c = 2,\ f(n) = 1$  
$f(n) = 1 \in Θ(n^{log_1 2}) = Θ(n^0) = Θ(1)$   
$\rightarrow T(n) = Θ(n^{log_1 2} * log n) = Θ(n⁰ log\ n) = Θ(log\ n)$

## Ejercicio 3

Lo que hay que hacer es la exponenciación binaria. Su complejidad es O(log n), con n siendo el exponente.

```cpp
int exponenciacionBinaria(int base, int exp){ // calcula base^(n)
    if(exp == 0)
        return 1;

    if(exp % 2 == 0){
        int result = exponenciacionBinaria(base, exp/2);
        return result*result;
    }

    else{
        int result = exponenciacionBinaria(base, exp-1);
        return result*base;
    }
}
```
### Complejidad:
$T(n) = 1*T(n/2) + O(1)$  
$Sea\ a = 1,\ c = 2,\ f(n) = 1$  
$f(n) = 1 \in Θ(n^{log_1 2}) = Θ(n^0) = Θ(1)$   
$\rightarrow T(n) = Θ(n^{log_1 2} * log n) = Θ(n⁰ log\ n) = Θ(log\ n)$


## Ejercicio 5

Quiero calcular la sumatoria de i a n de A^i, en complejidad menor que lineal. Entonces busco la forma de hacerlo en complejidad logarítmica. Por el Teorema Maestro, tengo que hacer una sola recursion sobre mi función para que mi complejidad quede de la forma O(n⁰ log n) = O(log n).  
Para entender mejor cómo hacerlo, hay que desarrollar un poquito la sumatoria. Sea $f$ la función pedida en el ejercicio:  

$$
f(matriz\ A,\ nat\ n) =
\sum_{i=1}^{n} A^i = A^1 + A^2 + ... + A^{n-1} + A^n
$$

Como tengo que resolverlo por Divide & Conquer, tengo que reducir mi problema a pequeños problemas. Me fijo cómo queda viendo la sumatoria antes y despues de n/2 _(créditos a Bian por la pista)_.  

$$
A^1 + A^2 + ... + A^{n-1} + A^n = A^1 + A^2 + ... + A^{n/2} + A^{n/2\ + 1} + A^{n/2\ + 2} + ... + A^{n} 
$$ 

Así se ve más claro como, a partir de n/2, es la misma sumatoria previa, con cada exponente multiplicado por n/2. Por ejemplo, con n = 8:

$$
f(matriz\ A,\ 8) =
\sum_{i=1}^{8} A^i = A^1 + A^2 + A^3 + A^4 + A^5 + A^6 + A^7 + A^8 =
$$
$$
A^1 + A^2 + A^3 + A^4 + A^{4 + 1} + A^{4+ 2} + A^{4 + 3} + A^{4 + 4} = A^1 + A^2 + A^3 + A^4 + A^4*(A^1 + A^2 + A^3 + A^4)
$$

Luego, con la recursion de n/2, quedaría: 

$$
f(matriz\ A,\ 4) =
\sum_{i=1}^{4} A^i = A^1 + A^2 + A^3 + A^4 = A^1 + A^2 + A^{2 + 1} + A^{2 + 2} = A^1 + A^2 + A^2 (A^1 + A^2)
$$

Otra vez n/2:

$$
f(matriz\ A,\ 2) =
\sum_{i=1}^{2} A^i = A^1 + A^2 = A^1 + A^{1 + 1}= A^1 + A^1 (A^1)
$$

Entonces esto lo puedo _anidar_ todo en la sumatoria de n = 8 (no tengo ganas de hacerlo pero se entiende), y se cumple siempre porque el parámetro n de mi función debe ser una potencia de 2, y para todo n que cumpla esto quedará de la forma:

$$
f(matriz\ A,\ n) = f(matriz\ A,\ n/2) + A^{n/2}* f(matriz\ A,\ n/2)
$$

Hago mi algoritmo con caso base n = 1:

```cpp
struct matriz{/*...*/}

matriz potenciaHastaN(matriz A, int n){
    if(n == 1)
        return A;

    matriz potMitad = potencia(A, n/2);

    return (potenciaHastaN(A, n/2) + potMitad * potenciaHastaN(A, n/2))
}
```

### Complejidad:
$T(n) = 1*T(n/2) + O(1)$  
$Sea\ a = 1,\ c = 2,\ f(n) = 1$  
$f(n) = 1 \in Θ(n^{log_1 2}) = Θ(n^0) = Θ(1)$   
$\rightarrow T(n) = Θ(n^{log_1 2} * log n) = Θ(n⁰ log\ n) = Θ(log\ n)$

## Ejercicio 7

