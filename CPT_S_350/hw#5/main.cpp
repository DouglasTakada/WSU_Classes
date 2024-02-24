#include <iostream>

void linear_max_min(int arr[], int size){
    int smallest = arr[0];
    int largest = arr[0];
    int cur_smal = arr[0], cur_larg = arr[0];
    std::cout<<"\n";

    for(int i =0; i < size-1; i += 2){ 

        if(arr[i] > arr[i+1]){
            if(arr[i] > largest){
                largest = arr[i];
            }
            if(arr[i+1] < smallest){
                smallest = arr[i+1];
            }
        }else{
            if(arr[i+1] > largest){
                largest = arr[i];
            }
            if(arr[i] < smallest){
                smallest = arr[i+1];
            }
        }
    }

    // //Now the low values should be in the odd index and the high values should be in the even indexes
    // //Now just compare the lower values to find smallest and higher values to find the highest
    // //n/2 comparisons
    // for(int i = 0; i < size; i += 2){
    //     if(arr[i] < smallest){
    //         smallest = arr[i];
    //     }
    // }
    // //n/2 comparisons
    // for(int i = 1; i < size; i += 2){
    //     if(arr[i] > largest){
    //         largest = arr[i];
    //     }
    // }

    std::cout<< "Largest: " << largest << "\nSmallest: " << smallest<<"\n";

}

int main (void){

    int arr[] = {0,9,8,7,65,5,4,-33,3,666666};
    int size = sizeof(arr)/sizeof(arr[0]);
    linear_max_min(arr, size);

    return 0;
}