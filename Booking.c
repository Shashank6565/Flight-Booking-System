#include <stdio.h>
#include <string.h>
#include "models.h"

void clearInputBuffer() 
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
void bookFlight() 
{
    printf("\t\t\t\t\tWELCOME TO TICKET BOOKING CENTER.\n");
    printf("\t\t\t\t\t---------------------------------\n");
    int n, c, p=0;
    printf("Enter Number Of Tickets To Book:");
    scanf("%d", &n);
    struct Booking booking;
    FILE *fp = fopen("bookings.txt", "ab");
    printf("\nEnter Flight Number to book: \n\n");
    scanf("%d", &booking.fn);
    clearInputBuffer(); 
    if(booking.fn==101)
    {
        p=5000;
        printf("Total Ticket Price: %d INR.\n", p*n);
    }
    else if(booking.fn==102)
    {
        p=8000;
        printf("Total Ticket Price: %d INR.\n", p*n);
    }
    else if(booking.fn==103)
    {
        p=9200;
        printf("Total Ticket Price: %d INR.\n", p*n);
    }
    else if(booking.fn==104)
    {
        p=13000;
        printf("Total Ticket Price: %d INR.\n", p*n);
    }
    else if(booking.fn==105)
    {
        p=15000;
        printf("Total Ticket Price: %d INR.\n", p*n);
    }
    for(int i=0; i<n; i++)
    {
       printf("\nEnter Name of Passeger %d: ",i+1);
       scanf(" %[^\n]", booking.psgn);
       clearInputBuffer();
       printf("\nAmount to be Paid(%d INR) : ", p);
       scanf("%d", &booking.amount); 
       if(booking.amount!=p)
       {
        printf("----------------------------------------------------------------------\n");
              printf("\nWarning :Invalid Amount Entered! Please enter the correct amount.\n");
              printf("----------------------------------------------------------------------\n");
              i--;
              continue;
       }
       fwrite(&booking, sizeof(struct Booking), 1, fp);
    }
    printf("\n\t\t\t\t\t\t=====PAYMENT=====\n1. Proceed To Pay.\n2. Not Interested.\nChoose an Option: ");
    scanf("%d", &c);
    if(c==1)
    {
        printf("\nEnter card number (16 digits): ");
        scanf("%s", booking.cn);
        if (strlen(booking.cn) != 16) 
    {
        printf("\nInvalid card number! Must be 16 digits.");
        return;
    }

    printf("\nEnter CVV (3 digits): ");
    scanf("%s", booking.cvv);
    clearInputBuffer(); 

    if (strlen(booking.cvv) != 3) 
    {
        printf("Invalid CVV! Must be 3 digits.\n");
        return;
    }
    printf("\n====== Payment of %d INR successful. ======\n====== THANK YOU! ======", booking.amount*n);
    }
   
    fclose(fp);

    printf("\nFlight booked successfully for %d. (Flight No: %d)\n\n", n, booking.fn);
}
