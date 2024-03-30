#include<stdio.h>

void Sort(int nums[], int numsSize){
    int temp;
    for(int i=0; i<numsSize; i++){
        for(int j=0; j<numsSize-i-1; j++){
            if(nums[j]>nums[j+1]){
                temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }
}

int main(){
    int a[] = {5,6,9,1,3,27,4,55,0};
    int size = sizeof(a)/sizeof(a[0]);
    Sort(a,size);
    for(int i=0; i<size; i++){
        printf("%d ",a[i]);
    }
    return 0;
}