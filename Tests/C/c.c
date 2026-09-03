#include <stdio.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    int *answer;

    answer = (int *)malloc(2 * sizeof(int));

    for (int i = 0; i < numsSize - 1; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if (nums[i] + nums[j] == target)
            {
                answer[0] = i;
                answer[1] = j;
                return answer;
            }
        }
    }

    return NULL;
}

int main(void) 
{
    
}