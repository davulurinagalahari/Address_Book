// ================================================================
// Address Book – Core Operations
// Handles create, edit, search, delete and listing of contacts
// ================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Function to check duplicate phone number or email
int isDuplicate(AddressBook *addressBook, char *phone, char *email)
{
    int i = 0;                                      // Loop index initialization
    do                                               // Start loop to check contacts
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0 ||   // Compare phone
            strcmp(addressBook->contacts[i].email, email) == 0)     // Compare email
        {
            return 1;                               // Return duplicate found
        }
        i++;                                        // Move to next contact
    } while (i < addressBook->contactCount);         // Loop until last contact

    return 0;                                       // No duplicate found
}

// Function to list all contacts
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    if (addressBook->contactCount == 0)             // Check if list is empty
    {
        printf("No contacts available\n");          // Print message
        return;                                     // Exit function
    }

    printf("%-3s %-20s %-15s %-30s\n",               // Print table header
           "No", "Name", "Phone", "Email");

    printf("---------------------------------------------------------------\n"); // Separator

    int i = 0;                                      // Index initialization
    do                                               // Loop through contacts
    {
        printf("%-3d %-20s %-15s %-30s\n",            // Print contact details
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
        i++;                                        // Increment index
    } while (i < addressBook->contactCount);         // Continue till end
}

// Function to initialize address book
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;                  // Reset contact count
    populateAddressBook(addressBook);               // Populate default contacts
    loadContactsFromFile(addressBook);              // Load contacts from file
}

// Function to create a new contact
void createContact(AddressBook *addressBook)
{
    Contact temp;                                   // Temporary contact structure
    int i;                                          // Index variable

name_loop:
    printf("Enter Name:\n");                        // Prompt for name
    getchar();                                      // Clear input buffer
    scanf("%[^\n]", temp.name);                     // Read full name

    i = 0;                                          // Reset index
    do                                               // Validate name characters
    {
        if (!((temp.name[i] >= 'A' && temp.name[i] <= 'Z') ||   // Check uppercase
              (temp.name[i] >= 'a' && temp.name[i] <= 'z') ||   // Check lowercase
               temp.name[i] == ' '))                              // Allow space
        {
            printf("Invalid name\n");               // Invalid name message
            goto name_loop;                         // Re-enter name
        }
        i++;                                        // Increment index
    } while (temp.name[i] != '\0');                 // Until end of string

phone_loop:
    printf("Enter Phone:\n");                       // Prompt for phone
    scanf("%s", temp.phone);                        // Read phone number

    if (strlen(temp.phone) != 10)                   // Validate length
    {
        printf("Invalid phone\n");                  // Invalid phone message
        goto phone_loop;                            // Re-enter phone
    }

    i = 0;                                          // Reset index
    do                                               // Validate digits
    {
        if (temp.phone[i] < '0' || temp.phone[i] > '9') // Check digit
        {
            printf("Invalid phone\n");              // Invalid digit
            goto phone_loop;                        // Re-enter phone
        }
        i++;                                        // Increment index
    } while (temp.phone[i] != '\0');                // Until end

email_loop:
    printf("Enter Email:\n");                       // Prompt for email
    scanf("%s", temp.email);                        // Read email

    char domain[] = "@gmail.com";                   // Gmail domain
    char *ptr = strstr(temp.email, domain);         // Find domain

    if (temp.email[0] == '@' ||                     // Check invalid start
        ptr == NULL ||                              // Domain missing
        strcmp(ptr, domain) != 0 ||                 // Wrong domain
        strlen(ptr) != strlen(domain))              // Extra characters
    {
        printf("Invalid email\n");                  // Invalid email message
        goto email_loop;                            // Re-enter email
    }

    i = 0;                                          // Reset index
    do                                               // Validate email characters
    {
        if ((temp.email[i] >= 'A' && temp.email[i] <= 'Z') ||  // Uppercase check
            temp.email[i] == ' ')                               // Space check
        {
            printf("Invalid email\n");              // Invalid email message
            goto email_loop;                         // Re-enter email
        }
        i++;                                        // Increment index
    } while (temp.email[i] != '\0');                // Until end

    if (isDuplicate(addressBook, temp.phone, temp.email)) // Check duplicate
    {
        printf("Duplicate contact\n");              // Duplicate message
        goto phone_loop;                            // Re-enter details
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name, temp.name);   // Copy name
    strcpy(addressBook->contacts[addressBook->contactCount].phone, temp.phone); // Copy phone
    strcpy(addressBook->contacts[addressBook->contactCount].email, temp.email); // Copy email

    addressBook->contactCount++;                    // Increment count
    printf("Contact created successfully\n");       // Success message
}

// Function to search contact
void searchContact(AddressBook *addressBook)
{
    int choice;                                     // Search option
    printf("Search by:\n1.Name\n2.Phone\n3.Email\n"); // Display menu
    scanf("%d", &choice);                           // Read choice

    int i = 0, found = 0;                           // Index and flag

    if (choice == 1)                                // Search by name
    {
        char key[50];                               // Search key
        getchar();                                  // Clear buffer
        scanf("%[^\n]", key);                       // Read name
        do                                           // Loop contacts
        {
            if (strcasestr(addressBook->contacts[i].name, key)) // Match name
            {
                printf("%s %s %s\n",
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                found = 1;                           // Mark found
            }
            i++;                                    // Increment index
        } while (i < addressBook->contactCount);    // Until end
    }
    else if (choice == 2)                           // Search by phone
    {
        char key[50];                               // Phone key
        scanf("%s", key);                           // Read phone

        do
        {
            if (strstr(addressBook->contacts[i].phone, key)) // Match phone
            {
                printf("%s %s %s\n",
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                found = 1;
            }
            i++;
        } while (i < addressBook->contactCount);
    }
    else if (choice == 3)                           // Search by email
    {
        char key[50];                               // Email key
        scanf("%s", key);                           // Read email

        do
        {
            if (strstr(addressBook->contacts[i].email, key)) // Match email
            {
                printf("%s %s %s\n",
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                found = 1;
            }
            i++;
        } while (i < addressBook->contactCount);
    }

    if (!found)                                    // If no match
        printf("Not found\n");                     // Print message
}

// Function to edit contact
void editContact(AddressBook *addressBook)
{
    int choice;                                    // Edit option
    printf("Edit by:\n1.Name\n2.Phone\n3.Email\n"); // Menu
    scanf("%d", &choice);                          // Read option

    int i = 0;                                    // Index

    if (choice == 1)                               // Edit name
    {
        char oldName[50], newName[50];             // Buffers
        scanf("%s", oldName);                      // Old name
        getchar();                                 // Clear buffer
        scanf("%[^\n]", newName);                  // New name

        do
        {
            if (strcasestr(addressBook->contacts[i].name, oldName)) // Match name
            {
                strcpy(addressBook->contacts[i].name, newName);    // Update
                printf("Updated successfully\n");
                return;
            }
            i++;
        } while (i < addressBook->contactCount);
    }
    else if (choice == 2)                          // Edit phone
    {
        char oldPhone[50], newPhone[50];
        scanf("%s", oldPhone);
        scanf("%s", newPhone);

        do
        {
            if (strcmp(addressBook->contacts[i].phone, oldPhone) == 0)
            {
                strcpy(addressBook->contacts[i].phone, newPhone);
                printf("Updated successfully\n");
                return;
            }
            i++;
        } while (i < addressBook->contactCount);
    }
    else if (choice == 3)                          // Edit email
    {
        char oldEmail[50], newEmail[50];
        scanf("%s", oldEmail);
        scanf("%s", newEmail);

        do
        {
            if (strcmp(addressBook->contacts[i].email, oldEmail) == 0)
            {
                strcpy(addressBook->contacts[i].email, newEmail);
                printf("Updated successfully\n");
                return;
            }
            i++;
        } while (i < addressBook->contactCount);
    }

    printf("Not found\n");                         // If no match
}

// Function to delete contact
void deleteContact(AddressBook *addressBook)
{
    int choice;                                    // Delete option
    printf("Delete by:\n1.Name\n2.Phone\n3.Email\n");
    scanf("%d", &choice);

    int i = 0;                                    // Index

    if (choice == 1)                               // Delete by name
    {
        char key[50];
        scanf("%s", key);

        do
        {
            if (strcasestr(addressBook->contacts[i].name, key))
            {
                int j = i;
                do
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    j++;
                } while (j < addressBook->contactCount - 1);

                addressBook->contactCount--;
                printf("Deleted successfully\n");
                return;
            }
            i++;
        } while (i < addressBook->contactCount);
    }
    else if (choice == 2)                          // Delete by phone
    {
        char key[50];
        scanf("%s", key);

        do
        {
            if (strcmp(addressBook->contacts[i].phone, key) == 0)
            {
                int j = i;
                do
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    j++;
                } while (j < addressBook->contactCount - 1);

                addressBook->contactCount--;
                printf("Deleted successfully\n");
                return;
            }
            i++;
        } while (i < addressBook->contactCount);
    }
    else if (choice == 3)                          // Delete by email
    {
        char key[50];
        scanf("%s", key);

        do
        {
            if (strcmp(addressBook->contacts[i].email, key) == 0)
            {
                int j = i;
                do
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    j++;
                } while (j < addressBook->contactCount - 1);

                addressBook->contactCount--;
                printf("Deleted successfully\n");
                return;
            }
            i++;
        } while (i < addressBook->contactCount);
    }

    printf("Not found\n");                         // If nothing deleted
}
