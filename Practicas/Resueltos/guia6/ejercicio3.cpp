#include <iostream>
using namespace std;

int exponenciacionBinariaCiclo(int base, int n){ // calcula base^(n)
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

int main(){
    cout<< exponenciacionBinaria(3, 13);
}