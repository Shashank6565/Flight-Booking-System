#include <stdio.h>
#include <string.h>
#include "models.h"  

void checkRecentBooking() {
    struct Booking booking;
    FILE *fp = fopen("bookings.txt", "rb"); 
    if (fp == NULL) {
        printf("No bookings found.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);

    if (fileSize < sizeof(struct Booking)) {
        printf("\nNo valid booking data found.\n\n");
        fclose(fp);
        return;
    }

    fseek(fp, -sizeof(struct Booking), SEEK_END);

    if (fread(&booking, sizeof(struct Booking), 1, fp) == 1) {
        printf("\n\t\t\t\t\t\t===== Most Recent Booking =====\n");
        printf("\n\tPassenger Name : %s\n", booking.psgn);
        printf("\tFlight Number  : %d\n", booking.fn);
        printf("\tAmount Paid    : Rs%d\n\n", booking.amount);
    } else {
        printf("\nError reading recent booking.\n\n");
    }

    fclose(fp);
}
// int main()
// {
//     checkRecentBooking();
//     return 0;
// }