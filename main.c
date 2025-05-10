// Name: shirdhar pawar
//Batch:-24017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTACTS 100

typedef struct {
    int serialNumber;
    char name[50];
    char mobileNumber[15];
    char email[50];
} Contact;

Contact contacts[MAX_CONTACTS];
int contactCount = 0;

// Validate mobile number
int isValidMobileNumber(char *mobileNumber) {
    if (strlen(mobileNumber) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(mobileNumber[i])) return 0;
    }
    return 1;
}

// Validate email
int isValidEmail(char *email) {
    int atSymbol = -1, dot = -1;
    for (int i = 0; i < strlen(email); i++) {
        if (email[i] == '@') atSymbol = i;
        else if (email[i] == '.') dot = i;
    }
    return (atSymbol != -1 && dot != -1 && atSymbol < dot);
}

// Check if contact details already exist
int isDuplicateContact(char *name, char *mobileNumber, char *email) {
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, name) == 0 || strcmp(contacts[i].mobileNumber, mobileNumber) == 0 || strcmp(contacts[i].email, email) == 0) {
            return 1;  // Duplicate found
        }
    }
    return 0;
}

// Add contact
void addContact() {
    if (contactCount < MAX_CONTACTS) {
        char name[50], mobileNumber[15], email[50];

        printf("Enter Contact Name: ");
        scanf("%s", name);

        do {
            printf("Enter Mobile Number: ");
            scanf("%s", mobileNumber);
            if (!isValidMobileNumber(mobileNumber)) {
                printf("Invalid Mobile Number! Please enter a 10 digit number.\n");
            }
        } while (!isValidMobileNumber(mobileNumber));

        do {
            printf("Enter Email: ");
            scanf("%s", email);
            if (!isValidEmail(email)) {
                printf("Invalid Email! Please enter a valid email address.\n");
            }
        } while (!isValidEmail(email));

        if (isDuplicateContact(name, mobileNumber, email)) {
            printf("Error: Duplicate contact details. Name, mobile number, or email already exists.\n");
        } else {
            contacts[contactCount].serialNumber = contactCount + 1;
            strcpy(contacts[contactCount].name, name);
            strcpy(contacts[contactCount].mobileNumber, mobileNumber);
            strcpy(contacts[contactCount].email, email);
            contactCount++;
            printf("Contact added successfully!\n");
        }
    } else {
        printf("Address book is full!\n");
    }
}

// Display contacts
void displayContacts() {
    printf("------------------------------------------------------------------------------------\n");
    printf("%-6s     %-19s %-16s %-32s\n", "SL.NO", "Contact Name", "Mobile Number", "E-mail Id");
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < contactCount; i++) {
        printf("%d.\t   %-20s %-15s %-30s\n", contacts[i].serialNumber, contacts[i].name, contacts[i].mobileNumber, contacts[i].email);
    }
    printf("------------------------------------------------------------------------------------\n");
}

// Edit contact
void editContact() {
    int serialNumber;
    char newName[50], newMobileNumber[15], newEmail[50];

    printf("Enter Serial Number of contact to edit: ");
    scanf("%d", &serialNumber);

    if (serialNumber > 0 && serialNumber <= contactCount) {
        printf("Enter New Contact Name: ");
        scanf("%s", newName);

        do {
            printf("Enter New Mobile Number: ");
            scanf("%s", newMobileNumber);
            if (!isValidMobileNumber(newMobileNumber)) {
                printf("Invalid Mobile Number! Please enter a 10 digit number.\n");
            }
        } while (!isValidMobileNumber(newMobileNumber));

        do {
            printf("Enter New Email: ");
            scanf("%s", newEmail);
            if (!isValidEmail(newEmail)) {
                printf("Invalid Email! Please enter a valid email address.\n");
            }
        } while (!isValidEmail(newEmail));

        // Check if the new details are duplicates (excluding the current contact)
        for (int i = 0; i < contactCount; i++) {
            if (i != (serialNumber - 1) && (strcmp(contacts[i].name, newName) == 0 || strcmp(contacts[i].mobileNumber, newMobileNumber) == 0 || strcmp(contacts[i].email, newEmail) == 0)) {
                printf("Error: Duplicate contact details. Name, mobile number, or email already exists.\n");
                return;
            }
        }

        // If no duplicates, update the contact
        strcpy(contacts[serialNumber - 1].name, newName);
        strcpy(contacts[serialNumber - 1].mobileNumber, newMobileNumber);
        strcpy(contacts[serialNumber - 1].email, newEmail);

        printf("Contact updated successfully!\n");
    } else {
        printf("Invalid Serial Number!\n");
    }
}

// Delete contact
void deleteContact() {
    int serialNumber;
    printf("Enter Serial Number of contact to delete: ");
    scanf("%d", &serialNumber);
    if (serialNumber > 0 && serialNumber <= contactCount) {
        for (int i = serialNumber - 1; i < contactCount - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        contactCount--;
        printf("Contact deleted successfully!\n");
    } else {
        printf("Invalid Serial Number!\n");
    }
}

// Search contact by name
void searchContact() {
    char name[50];
    printf("Enter Contact Name to search: ");
    scanf("%s", name);
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            printf("Found: %d.\t    %-20s %-15s %-30s\n", contacts[i].serialNumber, contacts[i].name, contacts[i].mobileNumber, contacts[i].email);
            return;
        }
    }
    printf("Contact not found!\n");
}

// Save contacts to CSV file
void saveContacts() {
    FILE *file = fopen("contacts.csv", "w"); // Open CSV file for writing
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write each contact in CSV format: serialNumber,name,mobileNumber,email
    for (int i = 0; i < contactCount; i++) {
        fprintf(file, "%d,%s,%s,%s\n", contacts[i].serialNumber, contacts[i].name, contacts[i].mobileNumber, contacts[i].email);
    }

    fclose(file); // Close the file
    printf("Contacts saved to contacts.csv.\n");
}

// Load contacts from CSV file
void loadContacts() {
    FILE *file = fopen("contacts.csv", "r"); // Open CSV file for reading
    if (file == NULL) {
        printf("No saved contacts found.\n");
        return;
    }

    contactCount = 0;  // Reset contact count before loading

    // Read each line from the CSV file
    while (fscanf(file, "%d,%49[^,],%14[^,],%49[^\n]", &contacts[contactCount].serialNumber, contacts[contactCount].name, contacts[contactCount].mobileNumber, contacts[contactCount].email) != EOF) {
        contactCount++;
    }

    fclose(file); // Close the file
    printf("Contacts loaded from contacts.csv.\n");
}

int main() {
    loadContacts();  // Load contacts when the program starts

    int choice;
    while (1) {
        printf("Address Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Edit Contact\n");
        printf("3. Search Contact\n");
        printf("4. Display Contacts\n");
        printf("5. Delete Contact\n");
        printf("6. Save Contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addContact(); break;
            case 2: editContact(); break;
            case 3: searchContact(); break;
            case 4: displayContacts(); break;
            case 5: deleteContact(); break;
            case 6: saveContacts(); break;
            case 7: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
