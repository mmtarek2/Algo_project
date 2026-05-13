#include <stdio.h>
#include <stdlib.h>

/* Compare Function */
int compare(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

/* First Solution*/
void wiggleSort(int nums[], int n)
{
    qsort(nums, n, sizeof(int), compare);

    int temp[n];
    int mid = (n + 1) / 2;
    int left = mid - 1;
    int right = n - 1;

    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
            temp[i] = nums[left--];
        else
            temp[i] = nums[right--];
    }

    for (int i = 0; i < n; i++)
        nums[i] = temp[i];
}

/* Second Solution*/
void anotherWiggleSort(int nums[], int n)
{
    qsort(nums, n, sizeof(int), compare);

    int temp[n];
    int mid = (n + 1) / 2;
    int left = 0;
    int right = mid;

    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
            temp[i] = nums[left++];
        else
            temp[i] = nums[right++];
    }

    for (int i = 0; i < n; i++)
        nums[i] = temp[i];
}

/* Compare Arrays */
int isDifferent(int a[], int b[], int n)
{
    for(int i = 0; i < n; i++)
    {
        if(a[i] != b[i])
            return 1;
    }
    return 0;
}

/* Print Array */
void printArray(int arr[], int n)
{
    printf("[");
    for(int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if(i < n - 1)
            printf(",");
    }
    printf("]");
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    if(scanf("%d", &n) != 1) return 0;

    int nums[n], original[n], another[n];

    printf("Enter elements:\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &nums[i]);
        original[i] = nums[i];
        another[i] = nums[i];
    }

    wiggleSort(nums, n);
    anotherWiggleSort(another, n);

    printf("Input: nums = ");
    printArray(original, n);

    printf("\nOutput: ");
    printArray(nums, n);

    if(isDifferent(nums, another, n))
    {
        printf("\nExplanation: ");
        printArray(another, n);
        printf(" is also accepted.");
    }

    return 0;
}
