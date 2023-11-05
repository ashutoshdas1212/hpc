#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int r, i, ans = 0;
    printf("Enter number of sections : ");
    scanf("%d", &r);
    int **arr = (int **)malloc(r * sizeof(int *));
    int *size = (int *)malloc(r * sizeof(int));
    omp_set_num_threads(r);

#pragma omp parallel
    {
#pragma omp for
        for (i = 0; i < r; i++)
        {
            // Ensure that each thread has a different random seed
            srand(i + omp_get_thread_num());

            int j, sum = 0;
            size[i] = rand() % 20;
            arr[i] = (int *)malloc(size[i] * sizeof(int));

            for (j = 0; j < size[i]; j++)
            {
                arr[i][j] = rand() % 100;
                sum += arr[i][j];
            }

// Use reduction to update the total amount in parallel
#pragma omp critical
            ans += sum;
        }
    }

    // Display the details for each section
    for (i = 0; i < r; i++)
    {
        printf("Section - %2d ( %3d Items ) : ", i, size[i]);
        for (int j = 0; j < size[i]; j++)
            printf("%3d ", arr[i][j]);
        printf("\n");
    }

    // Display the final total amount to be paid
    printf("Total Amount : %d\n", ans);

    // Free allocated memory
    for (i = 0; i < r; i++)
    {
        free(arr[i]);
    }
    free(arr);
    free(size);

    return 0;
}
