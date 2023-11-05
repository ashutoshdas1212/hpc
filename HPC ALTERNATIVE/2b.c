#include <omp.h>
#include <stdio.h>

// Structure to represent an item in the customer's bill
typedef struct
{
    char *name;
    float price;
    int quantity;
} Item;

// Function to process the bill for a given section
void processBillSection(Item items[], int numItems, float *totalAmount)
{
    // Calculate the total amount for the given section
    float sectionTotal = 0;
    for (int i = 0; i < numItems; i++)
    {
        sectionTotal += items[i].price * items[i].quantity;
    }

    // Update the total amount for the customer's bill
    *totalAmount += sectionTotal;
}

// Main function
int main()
{
    // Create an array to store the items in the customer's bill
    Item items[] = {
        {"Shirt", 20.00, 1},
        {"Game", 50.00, 1},
        {"Groceries", 100.00, 1},
        {"Pencils", 5.00, 2}};

    // Get the number of items in the customer's bill
    int numItems = sizeof(items) / sizeof(items[0]);

    // Create a variable to store the total amount for the customer's bill
    float totalAmount = 0.00;

// Parallelize the processing of the bill for each section
#pragma omp parallel
    {
        // Get the section ID for the current thread
        int sectionId = omp_get_thread_num();

        // Process the bill for the given section
        processBillSection(items, numItems, &totalAmount);
    }

    // Display the final amount to be paid
    printf("Final amount to be paid: $%.2f\n", totalAmount);

    return 0;
}
