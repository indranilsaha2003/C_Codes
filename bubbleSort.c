#include <stdio.h>

int main() {
    
    int i,j,temp;
    int arr[]={3,4,2,1,5};
    int n=5;

    printf("[ ");
    for(i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("]");

    for(i=0;i<n-1;i++){
        for(j=0;j<n-1;j++){             //(j<n-1-i) for optimized Bubble Sort
            if(arr[j]>arr[j+1]){
                temp= arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }  

    printf("\n"); 

    printf("[ ");
    for(i=0;i<n;i++){
        printf("%d ",arr[i]);
    } 
    printf("]");

    return 0;
}
