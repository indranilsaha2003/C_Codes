#include <stdio.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(*returnSize * sizeof(int));
    int i, j;
    for (i = 0; i < numsSize; i++) {
        for (j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                {
                    result[0] = i;
                    result[1] = j;
                    return result;
                }
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

int main() {
    int numsSize, target;
    int returnSize = 2;
    printf("Enter the size of the array: ");
    scanf("%d", &numsSize);
    int nums[numsSize];
    int nums = (int*)malloc(numsSize * sizeof(int));
    printf("Enter the target value: ");
    scanf("%d", &target);
    twoSum(nums, numsSize, target, returnSize);
    return 0;
}