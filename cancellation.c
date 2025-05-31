#include <stdio.h>
#include <string.h>
#include "models.h"

void cancelTicket() {
    char una[100];
    struct Booking booking={0};
    int found = 0;

    printf("Enter passenger name to cancel booking: \n");
    scanf(" %[^\n]", una); 
    una[strcspn(una, "\n")] = '\0'; 

    FILE *fp = fopen("bookings.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&booking, sizeof(struct Booking), 1, fp)) 
    {
        if (strncmp(booking.psgn, una, strlen(una)) != 0)
        {
            fwrite(&booking, sizeof(struct Booking), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if (found) {
        printf("Booking for '%s' has been cancelled.\n\n", una);
        
    } else {
        printf("No booking found for %s\n", una);
    }
}
// int main() {
//     cancelTicket();
//     return 0;
// }