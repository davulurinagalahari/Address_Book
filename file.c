#include <stdio.h>
#include <stdlib.h>
#include "file.h"
// Function to save all contacts into contact.csv file

void saveContactsToFile(AddressBook *addressBook) {
    FILE *save; // File pointer for saving
    save=fopen("contact.csv","w+");  // Open CSV file in write mode
    if(save == NULL)  // Check if file open failed
    {
        printf("File doesn't exsits...\n"); // Error message
        return;  // Exit function
    }

    fprintf(save,"#%d\n",addressBook->contactCount); // Store contact count
   
    // Loop to write each contact into file
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(save, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email); // Write contact details
    }
    fclose(save); // Close the file
}
// Function to load contacts from contact.csv file

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *load = fopen("contact.csv", "r"); // Open CSV file in read mode

    if (load == NULL) {  // If file does not exist
        
        // Create new CSV file
        load = fopen("contact.csv", "w");
        if (load == NULL) // Check file creation failure
        {
            printf("Unable to create contact.csv\n");
            return;
        }
        fprintf(load, "#0\n");  // no contacts initially
        fclose(load);

        printf("contact.csv created (empty file)\n"); // Status message
        addressBook->contactCount = 0; // Set contact count to zero
        return;
    }

    fscanf(load, "#%d\n", &addressBook->contactCount); // Read contact count

    // Loop to read each contact from file
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        // Read CSV formatted data
        fscanf(load, "%[^,],%[^,],%[^\n]\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email
        );
    }

    fclose(load);  // Close the file
}
