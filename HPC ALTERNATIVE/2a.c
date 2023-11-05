#include <stdio.h>
#include <omp.h>

// Function to calculate the bill amount for a given section
double calculateSectionBill(double *items, int numItems) {
    double sectionBill = 0.0;
    for (int i = 0; i < numItems; i++) {
        sectionBill += items[i];
    }
    return sectionBill;
}

int main() {
    // Number of items in each section
    int numClothingItems = 5;
    int numGamingItems = 4;
    int numGroceryItems = 10;
    int numStationaryItems = 3;

    // Prices of items in each section
    double clothingItems[] = {10.5, 20.0, 15.75, 30.25, 12.5};
    double gamingItems[] = {60.0, 45.5, 32.0, 25.75};
    double groceryItems[] = {5.0, 2.25, 3.5, 8.0, 12.75, 7.0, 6.5, 14.0, 10.25, 9.5};
    double stationaryItems[] = {2.0, 4.5, 3.75};

    // Variables to store the section bills
    double clothingBill = 0.0;
    double gamingBill = 0.0;
    double groceryBill = 0.0;
    double stationaryBill = 0.0;

    #pragma omp parallel sections
    {
        #pragma omp section
        clothingBill = calculateSectionBill(clothingItems, numClothingItems);

        #pragma omp section
        gamingBill = calculateSectionBill(gamingItems, numGamingItems);

        #pragma omp section
        groceryBill = calculateSectionBill(groceryItems, numGroceryItems);

        #pragma omp section
        stationaryBill = calculateSectionBill(stationaryItems, numStationaryItems);
    }

    // Calculate the final amount to be paid
    double totalAmount = clothingBill + gamingBill + groceryBill + stationaryBill;

    // Display the results
    printf("Clothing Bill: $%.2f\n", clothingBill);
    printf("Gaming Bill: $%.2f\n", gamingBill);
    printf("Grocery Bill: $%.2f\n", groceryBill);
    printf("Stationary Bill: $%.2f\n", stationaryBill);
    printf("Total Amount to be Paid: $%.2f\n", totalAmount);

    return 0;
}
