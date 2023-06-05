typedef unsigned int uint;

bool tieneAgujero(uint arr[], uint size){
    uint maxElem = max(arr);    // O(n)
    uint minElem = min(arr);    // O(n)

    if (maxElem - minElem >= size) return true;

    else{ // puede tener repetidos
        uint countArr[max - min + 1];
        for(uint n : arr){              // O(n)
            countArr[n - minElem]++;
        }

        for(uint occurr : countArr){    // O(n)
            if (occurr == 0) return true;
        }
    }
    return false;
}