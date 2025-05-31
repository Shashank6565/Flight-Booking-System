#include <stdio.h>
#include <string.h>
#include "models.h"

void viewAllBookings() 
{
    struct Booking booking;
    FILE *fp = fopen("bookings.txt", "rb");

    if (fp == NULL) 
    {
        printf("No bookings found.\n");
        return;
    }

    int f=0;
    printf("\n\t\t\t\t\t\t\t===== All Bookings =====\n");
    while (fread(&booking, sizeof(struct Booking), 1, fp)) 
    {
        f=1;
        printf("\tPassenger: %s\n\tFlight No: %d\n\tTotal Amount Paid:%d\n\n", booking.psgn, booking.fn, booking.amount);
    }
    if (!f)
    printf("\tNo bookings found.\n\n\n");

    fclose(fp);
}

void clearAllBookings() 
{
    FILE *fp = fopen("bookings.txt", "wb"); 
    if (fp == NULL) 
    {
        printf("Error clearing booking data.\n\n");
        return;
    }
    fclose(fp);
    printf("All bookings have been cleared.\n\n");
}
