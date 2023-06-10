# Guía práctica 6: Divide & Conquer

simbolos × ➔ ∀ ∃ ≡ ∈ π ∧ ∨ ⇔ • ◦ ≥ ≤ ≠ ``` α ¬

## Ejercicio 1

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
T(n) = 2*T(n/2) + O(n¹)  
Sea a = 2, c = 2, f(n) = n    
f(n) ∈ Θ(n^(log₂2)) = Θ(n¹) = Θ(n)  
➔ T(n) = Θ(n^(log₂2) * log n) = **Θ(n log n)**  


## Ejercicio 2

Se hace un algoritmo similar a la búsqueda binaria, aprovechando el dato de que el arreglo esta estríctamente ordenado.

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
T(n) = 1*T(n/2) + O(1)
Sea a = 1, c = 2, f(n) = 1    
f(n) = 1 ∈ Θ(n^(log₁2)) = Θ(n⁰) = Θ(1)  
➔ T(n) = Θ(n^(log₁2) * log n) = Θ(n⁰ log n) = **Θ(log n)**  

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
T(n) = 1*T(n/2) + O(1)
Sea a = 1, c = 2, f(n) = 1    
f(n) = 1 ∈ Θ(n^(log₁2)) = Θ(n⁰) = Θ(1)  
➔ T(n) = Θ(n^(log₁2) * log n) = Θ(n⁰ log n) = **Θ(log n)**  


## Ejercicio 5

Quiero calcular la sumatoria de i a n de A^i, en complejidad menor que lineal. Entonces busco la forma de hacerlo en complejidad logarítmica. Por el Teorema Maestro, tengo que hacer una sola recursion sobre mi función para que mi complejidad quede de la forma O(n⁰ log n) = O(log n).  
Para entender mejor cómo hacerlo, hay que desarrollar un poquito la sumatoria.  

$$
funcion(matriz\ A,\ nat\ n) =
\sum_{i=1}^{n} A^i = A^1 + A^2 + ... + A^{n-1} + A^n
$$

Como tengo que resolverlo por Divide & Conquer, tengo que reducir mi problema a pequeños problemas. Me fijo cómo queda viendo la sumatoria antes y despues de n/2 (gracias Bian por la pista).  

$$
A^1 + A^2 + ... + A^{n-1} + A^n =\\ 
A^1 + A^2 + ... + A^{n/2} + A^{n/2\ + 1} + A^{n/2\ + 2} + ... + A^{n} 
$$ 

