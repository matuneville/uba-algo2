# Guía 2: Complejidad Computacional


## Ejercicio 3
1.  Esta notacion O(f) ⊆ O(g) significa que la función f tiene un crecimiento asintótico menor o igual que la función g a medida que los valores de entrada aumentan hacia el infinito; es decir, f está asintóticamente acotada superiormente por g.  
Si tenemos O(f) ⊆ O(g) y O(g) ⊆ O(f) se puede concluir que las funciones f y g tienen una tasa de crecimiento equivalente, y que se encuentran asintoticamente acotadas entre ellas.

2.  Ordeno las complejidades por inclusion:
    - O(1/x) ⊆ O(1) ⊆ O(√x) ⊆ O(x + 1) ⊆ O(x^2)
    - O(√2) ⊆ O(log x) ⊆ O(log^2 x) ⊆ O(log x^2) ⊆ O(x^x)
    - O(1 + sin^2 x) ⊆ O(log log x) ⊆ O(log x!) ⊆ O(x log x) ⊆ O(x!)

## Ejercicio 4
1.  **Peor caso**: O(|A|) = O(n)

2.  **Peor caso**: O(n * n) = O(n^2)

3.  **Peor caso**: O(p * r * q)

## Ejercicio 5
1.  **Mejor caso**: O(n)  
**Peor caso**: O(n^2)

2.  **Mejor caso**: O(1)  
**Peor caso**: O(log n)

3.  **Mejor caso**: O(n); si se permite array vacio, sería O(1)  
**Peor caso**: O(n^2 log n)

## Ejercicio 6
Aclaración: los metodos aplicados sobre arrays (vectores de C++ en este caso), como v.size(), los tomo como complejidad O(1).

1. Calcular la media de un arreglo de enteros. Complejidad O(n).

```cpp
float calcMedia (vector<int> v){
    int sum = 0;
    for (int i : v)
        sum += i;
    return float(sum / v.size());
}
```
2. Calcular la mediana de un arreglo de enteros. Asumo que el array está ordenado.  Complejidad O(1). Si no estuviera ordenado, habria que meterle un sorting y pasaría a ser O(n^2).

```cpp
float calcMediana (vector<int> v){
    float result;
    int n = v.size():
    if (n == 0)
        return 0
    else if (n % 2 == 1)
        result = v[n/2];
    else
        result = (v[(n/2)-1] + v[n/2])/2;
    return result;
}
```

3. Determinar, dado un n natural, si n es (o no) primo. Con el algoritmo de la Criba de Eratostenes, complejidad O(n log( log n)).

```cpp
bool esPrimo (int n){

    if (n <= 1)
        return false;

    vector<bool> is_prime(n+1, true);
    
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    return is_prime[n];
}
```
