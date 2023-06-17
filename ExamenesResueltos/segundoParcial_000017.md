## Ejercicio 3

```cpp
// O(n), cuenta la cadena C.O. partiendo desde la izquierda
int largoPrimerCO(int arr[], int begin, int end){
    int cadena = 2;
    int largo = 0;
    while(begin < end and cadena > 0){
        largo ++;
        if(arr[begin] > arr[begin+1])
            cadena--;
        begin++;
    }
}

int mayorCO_recursivo(int arr[], int begin, int end){
    int medio = (end + begin)/2;

    

    int primerCOder = largoPrimerCO(arr, medio, end);               // O(n)
    int primerCOizq = largoPrimerCO(reverso(arr), begin, medio);    // O(n)

    int COalMedio = 0;
    if(arr[medio])
}
```