# Guía práctica 6: Divide & Conquer

## Ejercicio 1

El algoritmo propuesto se llama a sí mismo logaritmicamente con complejidad O(2 log n) = O(log n), y su complejidad dentro es de O(2 n/2) = O(n). Por lo tanto, su complejidad temporal final es de O(n log n), siendo asi menor estricta que O(n²).

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


## Ejercicio 2

Se hace un algoritmo similar a la búsqueda binaria, aprovechando el dato de que el arreglo esta estríctamente ordenado. Su complejidad es O(log n), siendo n el largo del arreglo. 

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

## Ejercicio 3

Lo que hay que hacer es la exponenciación binaria. Su complejidad es O(log n), con n siendo el exponente.

```cpp
int exponenciacionBinaria(int base, int n){ // calcula base^(n)
    int result = 1;
    bool negativo = false;

    if (n < 0){
        n = n * (-1);
        negativo = true;
    }

    while(n > 0){
        if(n % 2 == 1){
            result *= base;
            n /= 2;
        }
        else{
            n /= 2;
        }
        base *= base;
    }
    
    if (negativo) return 1/result;

    return result;
}
```
