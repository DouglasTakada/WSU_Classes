#include <iostream>

int partition(int A[], int p, int q){
    int pivot = A[q], middle = 0;
    for (int i = 0; i< q;i++){
        if(A[i]<= pivot){
            std::swap(A[i],A[middle]);
            middle++;
        }
    }
    std::swap(A[middle],A[q]);
    return middle;
    }

int main(void){

    int arr[] =  {3,2,6,9,5};
    int end  = sizeof(arr)/sizeof(arr[0]);
    
    std::cout<<"before partition: ";
    for(int i =0; i<end; i++){
        std::cout<<arr[i];
    }
    std::cout<<"\n";

    std::cout<<"Middle point index is: "<< partition(arr,0, end-1)<<"\n After partition: ";

    for(int i =0; i<end; i++){
        std::cout<<arr[i];
    }

    return 0;
}