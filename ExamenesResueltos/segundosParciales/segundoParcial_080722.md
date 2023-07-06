## Ejercicio 1

### Item A

Sabemos que hay ciertos números mayores a H que están en orden creciente, y ciertos números menores que L que estan en orden decreciente. Lo que podemos hacer es crear tres arreglos auxiliares en los que agregaremos las subsecuencias de elementos menores a L (llamemoslo `arrLow`) y mayores a H (llamemoslo `arrHigh`) en su orden correcto. Y en el otro arreglo (llamemoslo `arrLH` guardo los que están entre L y F). Para el de H, recorremos el arreglo linealmente y los vamos pusheando al final de `arrHigh`; lo mismo para `arrLow`, pero para este hay que recorrerlo en reversa pues estan ordenados decrecientemente. En cualquiera de esos dos ciclos podemos también añadir los elementos que están entre L y F en su correspondiente arreglo. Hasta aca tenemos una complejidad de $O(2n) = O(n)$. Luego, para el arreglo `arrLH` podemos utilizar cualquier algoritmo de ordenamiento que sea de complejidad menor o igual a cuadrática, pues su largo es de raíz de n, por lo que quedaría, en el peor caso: $O(\sqrt{n}^2) = O(n)$. Finalmente, hacemos un *append* de estos tres arreglos en su correspondiente orden.

```c
void sortingLowAndHigh(array<int> &arr, int L, int H){
    array<int> arrLow;
    array<int> arrHigh;
    array<int> arrLF;

    for(int n : arr){                       // O(n)
        if(n >= H)
            arrHigh.agregarAtras(n);        // O(1)
        else if(L < n < H)
            arrLF.agregarAtras(n);          // O(1)
    } 
 
    for(int n : arr, en reversa){           // O(n)
        if(n <= L)
            arrLow.agregarAtras(n);         // O(1)
    }

    selectionSort(arrLF);                   // O(sqrt(n)²) = O(n)

    arrLow.append(arrLF.append(arrHigh));   // O(3n) = O(n)

    arr = arrLow;
}
```

### Item B

La complejidad del algoritmo sería $O(3n) = O(n)$, con su cota más ajustada siendo $\Theta(n)$.

## Ejercicio 2

Lo que hay que hacer es crear un diccionario implementado mediante un Trie, en el que insertaremos los países del Ranking, con significado 0. Esto se hace en $O(n*|k|)$ siendo |k| el largo de las palabras, que, al estar acotado, será $O(n)$. Luego, recorremos el arreglo A y contamos las apariciones de cada país buscando su clave en el diccTrie y sumando +1; esto costará $O(m)$, pues buscar elementos en el diccTrie está acotado por |k|. Con esto, nuevamente recorremos el arreglo R y vamos buscando cada clave, y, con la cantidad de apariciones indicada, las vamos ubicando en A hasta que no haya mas apariciones. Esto es de $O(n+m)$, pues la cantidad de apariciones total es m y recorrer R cuesta n operaciones.

```c
void sortingRanking(array<string> R, array<string> &A){
    diccTrie<string, int> apariciones;

    for(string pais : R){                       // O(n * |k|) = O(n)
        definir(apariciones, pais, 0); // O(|k|), acotado
    }

    for(string pais : A){                       // O(m * |k|) = O(m)
        significado(apariciones, pais) ++; // O(|k|, acotado)
        // asumo que es referencia a significado, sino seria redefinirlo con significado + 1
    }

    int pos = 0;
    for(string pais : R){                       // O(n + m)
        while(significado(apariciones, pais) >= 0){
            A[pos] = pais;
            pos++
            significado(apariciones, pais) --;
        }
    }
}
```

## Ejercicio 3

Es básicamente una búsqueda binaria pero chequeando en qué "lado" del arreglo estoy, si en la parte decreciente o en la parte creciente.

```c
int min(array<int> A, int begin, int end){
    if(end - begin == 1)                        // caso base
        return A[begin];

    if(A[(end+begin)/2] > A[(end+begin)/2 - 1]) // caso estoy de la derecha
        min(A, begin, (end+begin)/2);

    else                                        // caso estoy de la derecha
        min(A, (end+begin)/2, end);
}
```

### Complejidad

$T(n) = 1*T(n/2) + O(1)$  
$\text{Sea a = 1, c = 2, f(n) = 1}$  
$f(n)= 1 \in \Theta(n^{log_c(a)}) = \Theta(n^{log_2(1)}) = \Theta(n^{0}) = \Theta(1)$  
$\Rightarrow T(n) = \Theta(log n)$