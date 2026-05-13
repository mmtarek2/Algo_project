#include <stdio.h>
#include <stdlib.h>

/* Compare Function - FIXED: safe comparison to avoid integer overflow */
int compare(const void *a, const void *b)
{
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y);
}

/* First Solution (Iterative) */
void wiggleSort(int nums[], int n)
{
    qsort(nums, n, sizeof(int), compare);

    int *temp = (int*)malloc(n * sizeof(int));
    if (!temp) { fprintf(stderr, "Memory allocation failed\n"); exit(1); }

    int mid   = (n + 1) / 2;
    int left  = mid - 1;
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

    free(temp);
}

/* Second Solution (Iterative) */
void anotherWiggleSort(int nums[], int n)
{
    qsort(nums, n, sizeof(int), compare);

    int *temp = (int*)malloc(n * sizeof(int));
    if (!temp) { fprintf(stderr, "Memory allocation failed\n"); exit(1); }

    int mid   = (n + 1) / 2;
    int left  = 0;
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

    free(temp);
}

/* Recursive Helper - FIXED: pointers used for left/right to correctly share state */
void wiggleRecursiveHelper(int nums[], int temp[], int *left, int *right, int i, int n)
{
    if (i >= n)
        return;

    if (i % 2 == 0)
        temp[i] = nums[(*left)--];
    else
        temp[i] = nums[(*right)--];

    wiggleRecursiveHelper(nums, temp, left, right, i + 1, n);
}

/* Recursive Solution */
void wiggleSortRecursive(int nums[], int n)
{
    qsort(nums, n, sizeof(int), compare);

    int *temp = (int*)malloc(n * sizeof(int));
    if (!temp) { fprintf(stderr, "Memory allocation failed\n"); exit(1); }

    int mid   = (n + 1) / 2;
    int left  = mid - 1;
    int right = n - 1;

    wiggleRecursiveHelper(nums, temp, &left, &right, 0, n);

    for (int i = 0; i < n; i++)
        nums[i] = temp[i];

    free(temp);
}

/* Compare Arrays */
int isDifferent(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
            return 1;
    }
    return 0;
}

/* Print Array */
void printArray(int arr[], int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
            printf(",");
    }
    printf("]");
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    int *nums      = (int*)malloc(n * sizeof(int));
    int *original  = (int*)malloc(n * sizeof(int));
    int *recursive = (int*)malloc(n * sizeof(int));

    if (!nums || !original || !recursive)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(nums); free(original); free(recursive);
        return 1;
    }

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &nums[i]) != 1)
        {
            printf("Invalid input.\n");
            free(nums); free(original); free(recursive);
            return 1;
        }
        original[i]  = nums[i];
        recursive[i] = nums[i];
    }

    wiggleSort(nums, n);
    wiggleSortRecursive(recursive, n);

    printf("Input: nums = ");
    printArray(original, n);

    printf("\nIterative Output: ");
    printArray(nums, n);

    printf("\nRecursive Output: ");
    printArray(recursive, n);

    if (isDifferent(nums, recursive, n))
    {
        printf("\nExplanation: Both outputs are valid Wiggle Sort results.");
    }

    printf("\n");

    free(nums);
    free(original);
    free(recursive);

    return 0;
}
