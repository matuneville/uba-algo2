#include <iostream>
using namespace std;

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

int main(){
    int arr[8] = {-10,1,2,5,6,7,9,16};
    cout<< coincideIndiceElemento(arr, 0, 8)<< endl;
    return 0;
}