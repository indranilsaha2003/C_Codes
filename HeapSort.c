#include <stdio.h>

void printArray(int *arr, int size)
{
    for(int i=0; i<size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void inputArray(int *arr, int size)
{
    printf("ENter the array: ");
    for(int i=0; i<size; i++)
        scanf("%d", &arr[i]);
}

void swap(int *a, int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

// the "max heapify function"
void max_heapify(int *arr, int size, int i)
{
	// lets assume that the root element is the max among its immidiate childrens
	int max = i;
	// indexing the left and right children
	int left = 2*i +1, right = 2*i +2;
	
	// comaring(with left children) and updating if the max index
	if(left < size && arr[max] < arr[left])
		max = left;
	
	// comaring(with right children) and updating if the max index
	if(right < size && arr[max] < arr[right])
		max = right;
	
	// if the root is not the max than "swap" with the max
	//  to make the max the new root
	// and heapify the updated child
	if(max != i)
	{
	
		swap(&arr[max], &arr[i]);
		max_heapify(arr,size,max);
	}
}

// the "min heapify" function
void min_heapify(int arr[], int size, int i)
{
	// lets assume that the root element is the min among its immidiate childrens
	int min = i;
	// indexing the left and right children
	int left = 2*i +1, right = 2*i +2;
	
	// comaring(with left children) and updating if the min index
	if(left < size && arr[min] > arr[left])
		min = left;
	
	// comaring(with right children) and updating if the min index
	if(right < size && arr[min] > arr[right])
		min = right;
	
	// if the root is not the min than "swap" with the min
	// to make the min new root
	// and heapify the updated child
	if(min != i)
	{
		swap(&arr[min], &arr[i]);
		min_heapify(arr,size,min);
	}
}


// the main heap sort function that calls the "heapify" function
void heap_sort(int arr[], int size)
{
    int pass=1;
	// convert the array into a max_heap
	for(int i=size/2-1; i>-1; i--)
		max_heapify(arr,size,i);
	printf("The heapified array is: \n");
	printArray(arr,size);
	// swap the top root element and the last element
	// delete the last element and "max heapify" the root
	// repeat untill the heap is left with only one element
	for(int i=size-1; i>-1; i--)
	{
		swap(&arr[0], &arr[i]);
		max_heapify(arr,i,0);
		printf("pass %d: ", pass++);
		printArray(arr,size);
	}
}

int main()
{
    int arr[100];
	int size;
    printf("Enter the size of the array:");
    scanf("%d",&size);

    printf("Enter the elements:\n");
    for(int i=0; i<size; i++){
        scanf("%d",&arr[i]);
    }
	
	// print the array
	printf("The unsroted array is: \n");
	printArray(arr, size);
	
	// heap sort the array
	heap_sort(arr,size);
    printf("The sorted Array is:\n");
	// print again teh sorted array
	printArray(arr,size);
	
	return 0;
}