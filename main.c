#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100
#define MAXL 50
#define FILENAME "car_list.dat"

struct Car {
    char model[MAXL];
    int year;
    float price;
};

int getUserChoice();
void printCar(struct Car car);
void printCarList(struct Car cars[], int n);
void addCar(struct Car cars[], int *pn);
int searchCar(struct Car cars[], int n, char model[]);
void updateCar(struct Car cars[], int n, char model[]);
void removeCar(struct Car cars[], int *pn, char model[]);
void saveToFile(struct Car cars[], int n);
void loadFromFile(struct Car cars[], int *pn);

int main() {
    struct Car cars[MAXN];
    int n = 0;
    int userChoice;
    loadFromFile(cars, &n);
    do {
        userChoice = getUserChoice();
        switch (userChoice) {
            case 1:
                addCar(cars, &n);
                saveToFile(cars, n);
                break;
            case 2:
                if (n == 0)
                    printf("\nThe car list is empty!\n");
                else
                    printCarList(cars, n);
                break;
            case 3:
                if (n == 0)
                    printf("\nThe car list is empty!\n");
                else {
                    char searchModel[MAXL];
                    printf("\nEnter the model of the car to search: ");
                    fgets(searchModel, MAXL, stdin);
                    searchModel[strcspn(searchModel, "\n")] = '\0'; // Remove newline character
                    int index = searchCar(cars, n, searchModel);
                    if (index != -1) {
                        printf("\nCar found at index %d:\n", index);
                        printCar(cars[index]);
                    } else {
                        printf("\nCar not found!\n");
                    }
                }
                break;
            case 4:
                if (n == 0)
                    printf("\nThe car list is empty!\n");
                else {
                    char updateModel[MAXL];
                    printf("\nEnter the model of the car to update: ");
                    fgets(updateModel, MAXL, stdin);
                    updateModel[strcspn(updateModel, "\n")] = '\0'; // Remove newline character
                    updateCar(cars, n, updateModel);
                    saveToFile(cars, n);
                }
                break;
            case 5:
                if (n == 0)
                    printf("\nThe car list is empty!\n");
                else {
                    char removeModel[MAXL];
                    printf("\nEnter the model of the car to remove: ");
                    fgets(removeModel, MAXL, stdin);
                    removeModel[strcspn(removeModel, "\n")] = '\0'; // Remove newline character
                    removeCar(cars, &n, removeModel);
                    saveToFile(cars, n);
                }
                break;
            case 6:
                printf("\nGoodbye! Exiting program.\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 6.\n");
        }
    } while (userChoice != 6);

    return 0;
}

int getUserChoice() {
    int choice;
    printf("\n============= MENU CAR MANAGEMENT ==================");
    printf("\n| 1. Add a car into the list          Press: 1 |");
    printf("\n| 2. Print out all cars                Press: 2 |");
    printf("\n| 3. Search for a car                  Press: 3 |");
    printf("\n| 4. Update car information            Press: 4 |");
    printf("\n| 5. Remove a car from the list        Press: 5 |");
    printf("\n| 6. Exit the program                  Press: 6 |");
    printf("\n====================================================\n");
    printf("\nEnter Your Choice: ");
    do {
        choice = checkNumb();
        if (choice == 0)
            printf("Wrong choice! Enter again: ");
    } while (choice == 0);
    return choice;
}

void printCar(struct Car car) {
    printf("\nModel: %s\n", car.model);
    printf("Year: %d\n", car.year);
    printf("Price: %.2f\n", car.price);
}

void printCarList(struct Car cars[], int n) {
    printf("\n-- All cars in the list --\n");
    int i; 
    for (i = 0; i < n; i++) {
        printf("\nCar %d:\n", i + 1);
        printCar(cars[i]);
    }
}

void addCar(struct Car cars[], int *pn) {
    printf("\nEnter information about the car:\n");
    printf("Model: ");
    fgets(cars[*pn].model, MAXL, stdin);
    cars[*pn].model[strcspn(cars[*pn].model, "\n")] = '\0'; // Remove newline character
    printf("Year: ");
    scanf("%d", &cars[*pn].year);
    printf("Price: ");
    scanf("%f", &cars[*pn].price);
    getchar(); // Consume newline character left in buffer
    (*pn)++;
}

int searchCar(struct Car cars[], int n, char model[]) {
	int i; 
    for (i = 0; i < n; i++) {
        if (strcmp(cars[i].model, model) == 0)
            return i;
    }
    return -1;
}

void updateCar(struct Car cars[], int n, char model[]) {
    int index = searchCar(cars, n, model);
    if (index != -1) {
        printf("\nFound car!\n");
        printf("Enter new information:\n");
        printf("Model: ");
        fgets(cars[index].model, MAXL, stdin);
        cars[index].model[strcspn(cars[index].model, "\n")] = '\0'; // Remove newline character
        printf("Year: ");
        scanf("%d", &cars[index].year);
        printf("Price: ");
        scanf("%f", &cars[index].price);
        getchar(); // Consume newline character left in buffer
        printf("\nCar information updated successfully!\n");
    } else {
        printf("\nCar not found!\n");
    }
}

void removeCar(struct Car cars[], int *pn, char model[]) {
    int index = searchCar(cars, *pn, model);
    if (index != -1) {
    	int i; 
        for (i = index; i < *pn - 1; i++) {
            cars[i] = cars[i + 1];
        }
        (*pn)--;
        printf("\nCar removed from the list!\n");
    } else {
        printf("\nCar not found!\n");
    }
}

void saveToFile(struct Car cars[], int n) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&n, sizeof(int), 1, file);
    fwrite(cars, sizeof(struct Car), n, file);

    fclose(file);
}

void loadFromFile(struct Car cars[], int *pn) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    fread(pn, sizeof(int), 1, file);
    fread(cars, sizeof(struct Car), *pn, file);

    fclose(file);
}

int checkNumb() {
    int num;
    char term;
    scanf("%d%c", &num, &term);
    fflush(stdin);
    if (term != '\n')
        return 0;
    else
        return num;
}

