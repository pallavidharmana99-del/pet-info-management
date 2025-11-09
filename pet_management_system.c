
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PETS 200
#define FILE_NAME "pet_data.txt"
#define PER_DAY_CHARGE 500

struct Pet {
    int id;
    char name[30];
    int age;
    char type[20];  
    char owner[30];
    char checkinDate[15];
    char checkoutDate[15];
};

struct Pet pets[MAX_PETS];
int count = 0;

// Function declarations
void loadData();
void saveData();
void addPet();
void editPet();
void deletePet();
void searchPet();
void showCheckedIn();
void showCheckedOut();
void generateBill();
void generateRandomData();
void clearInput();

int main() {
    int choice;
    loadData();
    if (count == 0)
        generateRandomData();  // Fill with random pets if file empty

    do {
        printf("\n=== PET CARE RECORD SYSTEM ===\n");
        printf("1. Add Pet Record\n");
        printf("2. Edit Pet Record\n");
        printf("3. Delete Pet Record\n");
        printf("4. Search Pet\n");
        printf("5. Show Checked-in Pets\n");
        printf("6. Show Checked-out Pets\n");
        printf("7. Generate Bill\n");
        printf("8. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInput();

        switch (choice) {
            case 1: addPet();
             break;
            case 2: editPet(); 
             break;
            case 3: deletePet();
             break;
            case 4: searchPet(); 
             break;
            case 5: showCheckedIn(); 
             break;
            case 6: showCheckedOut(); 
             break;
            case 7: generateBill(); 
             break;
            case 8: saveData(); 
            printf("Data saved successfully \n");
             break;
            default: 
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 8);

    return 0;
}

// Clear input buffer
void clearInput() {
    while (getchar() != '\n');
}

// Load data from file
void loadData() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return;
    count = 0;
    while (fscanf(fp, "%d,%29[^,],%d,%19[^,],%29[^,],%14[^,],%14[^\n]\n",&pets[count].id,pets[count].name,&pets[count].age,pets[count].type,pets[count].owner,pets[count].checkinDate,pets[count].checkoutDate) != EOF) {
        count++;
    }
    fclose(fp);
}

// Save data to file
void saveData() {
    FILE *fp = fopen(FILE_NAME, "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%d,%s,%s,%s,%s\n",pets[i].id, pets[i].name, pets[i].age,pets[i].type, pets[i].owner,pets[i].checkinDate, pets[i].checkoutDate);
    }
    fclose(fp);
}

// Add pet record
void addPet() {
    if (count >= MAX_PETS) {
        printf("Storage full!\n");
        return;
    }
    struct Pet p;
    p.id = count + 1;
    printf("Enter Pet Name: ");
    gets(p.name);
    printf("Enter Pet Age: ");
    scanf("%d", &p.age);
    clearInput();
    printf("Enter Pet Type (Dog/Cat/etc): ");
    gets(p.type);
    printf("Enter Owner Name: ");
    gets(p.owner);
    printf("Enter Check-in Date (DD/MM/YYYY): ");
    gets(p.checkinDate);
    strcpy(p.checkoutDate, "N/A");
    pets[count++] = p;
    printf("Pet record added successfully!\n");
}

// Edit record
void editPet() {
    int id, found = 0;
    printf("Enter Pet ID to edit: ");
    scanf("%d", &id);
    clearInput();
    for (int i = 0; i < count; i++) {
        if (pets[i].id == id) {
            found = 1;
            printf("Editing record of %s\n", pets[i].name);
            printf("Enter new Type: ");
            gets(pets[i].type);
            printf("Enter new Owner Name: ");
            gets(pets[i].owner);
            printf("Enter Check-out Date (DD/MM/YYYY or N/A): ");
            gets(pets[i].checkoutDate);
            printf("Record updated!\n");
            break;
        }
    }
    if (!found) printf("Pet not found!\n");
}

// Delete record
void deletePet() {
    int id, found = 0;
    printf("Enter Pet ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (pets[i].id == id) {
            found = 1;
            for (int j = i; j < count - 1; j++)
                pets[j] = pets[j + 1];
            count--;
            printf("Record deleted!\n");
            break;
        }
    }
    if (!found) printf("Pet not found!\n");
}

// Search record
void searchPet() {
    char key[30];
    int found = 0;
    printf("Enter Pet Name or Owner Name to search: ");
    gets(key);
    for (int i = 0; i < count; i++) {
        if (strcasecmp(pets[i].name, key) == 0 || strcasecmp(pets[i].owner, key) == 0) {printf("\nID:%d  Name:%s  Age:%d  Type:%s  Owner:%s  In:%s  Out:%s\n",pets[i].id, pets[i].name, pets[i].age, pets[i].type,pets[i].owner, pets[i].checkinDate, pets[i].checkoutDate);
            found = 1;
        }
    }
    if (!found) printf("No matching record found!\n");
}

// Show pets still checked in
void showCheckedIn() {
    printf("\n--- Checked-in Pets ---\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(pets[i].checkoutDate, "N/A") == 0)
            printf("%d. %s (%s) - Owner: %s, In: %s\n", pets[i].id, pets[i].name, pets[i].type, pets[i].owner, pets[i].checkinDate);
    }
}

// Show pets already checked out
void showCheckedOut() {
    printf("\n--- Checked-out Pets ---\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(pets[i].checkoutDate, "N/A") != 0)
            printf("%d. %s (%s) - Owner: %s, In: %s, Out: %s\n",pets[i].id, pets[i].name, pets[i].type,pets[i].owner, pets[i].checkinDate, pets[i].checkoutDate);
    }
}

// Generate bill
void generateBill() {
    int id, days;
    printf("Enter Pet ID for bill: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (pets[i].id == id) {
            printf("Enter number of days stayed: ");
            scanf("%d", &days);
            int bill = days * PER_DAY_CHARGE;
            printf("Pet: %s | Owner: %s | Days: %d | Bill: Rs.%d\n",
                   pets[i].name, pets[i].owner, days, bill);
            return;
        }
    }
    printf("Pet not found!\n");
}

// Generate random names and fill file initially
void generateRandomData() {
    char *petNames[] = {"kaliya","Charlie","Max","Luna","Rocky","Milo","Lucy","bunny","Leo","Coco"};
    char *types[] = {"Dog","Cat","Rabbit","Parrot","Hamster"};
    char *owners[] = {"pallavi","hema","vasu","harini","dinesh","raghini","chinni","abhi","rishi","karthik"};

    srand(time(0));
    for (int i = 0; i < MAX_PETS; i++) {
        pets[i].id = i + 1;
        strcpy(pets[i].name, petNames[rand() % 10]);
        pets[i].age = rand() % 15 + 1;
        strcpy(pets[i].type, types[rand() % 5]);
        strcpy(pets[i].owner, owners[rand() % 10]);
        strcpy(pets[i].checkinDate, "01/11/2025");
        strcpy(pets[i].checkoutDate, "N/A");
    }
    count = MAX_PETS;
    saveData();
    printf("Generated %d random pet records!\n", MAX_PETS);
}



