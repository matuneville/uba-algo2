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

Quiero calcular la sumatoria de i a n de A^i, en complejidad menor que lineal. Entonces busco la forma de hacerlo en complejidad logarítmica. Por el Teorema Maestro, tengo que hacer una sola recursion sobre mi función para que mi complejidad quede de la forma $O(n⁰\ log\ n) = O(log\ n)$.  
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
struct matriz{/*...*/};

matriz potenciaHastaN(matriz A, int n){
    if(n == 1)
        return A;

    matriz recursionPot = potenciaHastaN(A, n/2);

    return (recursionPot + potencia(A, n/2) * recursionPot);
}
```

### Complejidad:
$T(n) = 1*T(n/2) + O(1)$  
$Sea\ a = 1,\ c = 2,\ f(n) = 1$  
$f(n) = 1 \in Θ(n^{log_1 2}) = Θ(n^0) = Θ(1)$   
$\rightarrow T(n) = Θ(n^{log_1 2} * log n) = Θ(n⁰ log\ n) = Θ(log\ n)$

## Ejercicio 7

Lo que hay que plantear es una especie de Merge Sort para la parte de dividir el problema. La complejidad debe ser menor que $O(n²)$ lo que me permite hacerlo en O(n log n). Por ejemplo, si el arreglo [5, 3] lo divido para hacerle un merge, entonces cuento +1 pareja desordenada cuando se mergean. Si tengo [7, 4, 5, 2], se divide luego en [7, 4] y [5, 2], y luego en [7][4] y [5][2]. Al mergear ambos pares, ya cuento +2 y queda [4, 7] y [2, 5]. Viendolo con pares es fácil porque solo hay que comparar dos numeros, pero ahora tenemos cuatro numeros. Entonces, con el dato de que ambos pares estan ordenados, sabemos que si uno de la izquierda es mas grande que uno de la derecha (como en este caso, 4 y 2), entonces todos los números que estén por delante del arreglo de la izquierda, serán pares desordenados respecto al de la derecha. Entonces con [4, 7] y [2, 5], al mergear ocurre lo siguiente:  
- Teníamos +2 pares en desorden de antes en el primer Merge.
- Comparo 4 y 2: 4 > 2, entonces el 4 y los numeros por delante (en este caso solo el 7) son pares desordenados respecto al 2.  
- Cuento +2 y mergeo. [2, ...  
- Sigue con 4 y 5: 4 < 5. Se mergea y no se cuenta ningún par desordenado: [2, 4, ...  
- Sigue con 7 y 5: 7 > 5. Entonces del 7 para adelante son todos pares desordenados respecto al 5
- Cuento solo +1 porque el 7 es el último. Nos queda [2, 4, 5, 7] y se completa. No hay más pares para contar pues el 7 es el último de la derecha.  

En total conté 5, que es, efectivamente, la cantidad de pares en desorden del arreglo [7, 4, 5, 2], que son [7, 4], [7, 5], [7, 2], [4, 2] y [5, 2].  

Ahora que ya hice el algoritmo en castellano, puedo hacerlo en C++

```cpp
vector<int> mergeAndCount(vector<int> vecA, vector<int> vecB, int & contador){
    vector<int> merged;

    int iA = 0, iB = 0;
    while(iA < vecA.size() and iB < vecB.size()){ // O(n + n) = O(n)
        if(vecA[iA] < vecB[iB]){
            merged.push_back(vecA[iA]);
            iA++;
        }
        else{ // este es el caso en el que cuento las parejas en desorden
            merged.push_back(vecB[iB]);
            contador += vecA.size() - iA; // ACA LO IMPORTANTE PARA EL EJERCICIO
            iB++;
        }
    }
    while(iA < vecA.size()){
        merged.push_back(vecA[iA]);
        iA++;
    }
    while(iB < vecB.size()){
        merged.push_back(vecB[iB]);
        iB++;
    }
    return merged;
}

void contarDisparejasRecursiva(vector<int> &vec, int & contador){    // se hace O(log n) veces recursivamente

    if(vec.size() == 1) return;
    
    vector<int> vecPart1, vecPart2;

    int i = 0;
    for(; i < vec.size()/ 2; i++){      // O(n)
        vecPart1.push_back(vec[i]);
    }
    for(; i < vec.size(); i++){           // O(n)
        vecPart2.push_back(vec[i]);
    }

    contarDisparejasRecursiva(vecPart1, contador); // recursion doble aca con n/2
    contarDisparejasRecursiva(vecPart2, contador);
    vec = mergeAndCount(vecPart1, vecPart2, contador);    // O(n)
}

int contarDisparejas(vector<int> vec){
    int contador = 0;
    contarDisparejasRecursiva(vec, contador);
    // paso contador por referencia, las recursiones le suman lo necesario
    return contador;
}
```
Usé como template del algoritmo el Merge Sorting y lo modifiqué para tener el contador de parejas en desorden, por lo que hay ciertas cosas que tal vez se podrían omitir pues no es el objetivo de este ejercicio el ordenamiento del arreglo.

### Complejidad:
$T(n) = 2*T(n/2) + O(n)$  
$Sea\ a = 2,\ c = 2,\ f(n) = n$  
$f(n) = n \in Θ(n^{log_2 2}) = Θ(n^1) = Θ(n)$   
$\rightarrow T(n) = Θ(n^{log_2 2} * log n) = Θ(n^1 log\ n) = Θ(n\ log\ n)$

## Ejercicio 8

### Item A
Para resolverlo hay que hacer una especie de binary search doble. Veo las conjunciones de cada mitad de la matriz. Si de un lado da true, entonces quiere decir que son todos sus elementos true, por lo que debo ver la otra mitad de la matriz en la que necesariamente habrá algun false. Y si da false de ambos lados, entonces veo en cualquiera de ellos, por lo que de todas formas encontraré un false al seguir buscando.

```cpp
typedef vector<vector<int>> matriz;

pair<int, int> buscarFalsoRecursivo(matriz m, int f1, int f2, int c1, int c2){
    if(f2-f1 == 1 and c2-c1 == 1)
        return make_pair(c1, f1); // solo llega a este caso si ESE elemento es Falso

    if(f2-f1 == 1){
        if (conjuncion(m, f1, f2, c1, (c2+c1)/2) == false)
            return buscarFalsoRecursivo(m, f1, f2, c1, (c2+c1)/2);
        else
            return buscarFalsoRecursivo(m, f1, f2, (c2+c1)/2, c2);
    }
    else{
        if (conjuncion(m, f1, (f2+f1)/2, c1, c2) == false)
            return buscarFalsoRecursivo(m, f1, (f2+f1)/2, c1, c2);
        else
            return buscarFalsoRecursivo(m, (f2+f1)/2, f2, c1, c2);
    }
}

pair<int, int> buscarFalso(matriz m){
    int size = m.size();
    return buscarFalsoRecursivo(m, 0, size, 0, size);
}
```
### Complejidad:
Para calcular esto con el Teorema Maestro hay que hacer un cambio de variables:  

$Sea\ m = n^2,\ \text{siendo m la cantidad de elementos totales de la matriz}$  
$T(m) = 1*T(m/2) + O(1)$  
$Sea\ a = 1,\ c = 2,\ f(m) = 1$  
$f(m) = 1 \in Θ(m^{log_2 1}) = Θ(m^0) = Θ(1)$   
$\rightarrow T(m) = Θ(m^{log_2 1} * log m) = Θ(m^0 log\ m) = Θ(log\ m)$  
$\text{Y por el cambio de variables} \rightarrow Θ(log\ m) = Θ(log\ n^2)$

### Item B

Una idea para resolver esto sería realizar las veces necesarias el algoritmo previo, y cada vez que se hace, poner un False en la coordenada indicada, y contar +1 falso encontrado. Es decir, en el peor caso se realizará cinco veces el algoritmo previo y se contarán cinco falsos encontrados, por lo que su complejidad será de $O(5*log\ n) = O(log\ n)$. No sé si es esta la idea para resolverlo pues no es un algoritmo nuevo de D&C, pero es una solución eficiente.