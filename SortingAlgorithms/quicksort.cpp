void swap(int &a, int &b);

int partition(int arr[], int low, int high);

void quicksort(int arr[], int low, int high){

    if(low < high){
        int partIndex = partition(arr, low, high);
        quicksort(arr, low, partIndex-1);
        quicksort(arr, partIndex+1, high); 
    }
}

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int partIndex = low;

    for(int i = low; i < high; i++){
        if(arr[i] <= pivot){
            swap(arr[partIndex], arr[i]);
            partIndex++;
        }
    }
    swap(arr[partIndex], arr[high]);

    return partIndex;
}

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}