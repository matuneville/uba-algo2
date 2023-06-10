struct matriz{/*...*/};

matriz potenciaHastaN(matriz A, int n){
    if(n == 1)
        return A;

    matriz recursionPot = potenciaHastaN(A, n/2);

    return (recursionPot + potencia(A, n/2) * recursionPot);
}