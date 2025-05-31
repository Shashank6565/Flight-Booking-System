#include <stdio.h>
#include <string.h>
#include "models.h"
#include "Booking.c"
#include "admin.c"
#include "lastbook.c"
#include "cancellation.c"
#include "cancel.h"
void registerUser();
int loginUser();
void viewFlights(struct Flight flights[], int count);
void searchFlights(struct Flight flights[], int count);
void bookFlight();
void clearAllBookings();
void viewAllBookings(); 
void checkRecentBooking();

void registerUser(struct Flight flights[], int count)
{
    struct User user;
    FILE *fp = fopen("users.txt", "ab");
    printf("\t\t\t\t\t\t==== REGISTER ====\n");
    printf("Enter username: ");
    scanf("%s", user.un);
    printf("\nEnter password: ");
    scanf("%s", user.psw);
    fwrite(&user, sizeof(struct User), 1, fp);
    fclose(fp);
    printf("User registered successfully!\nLOGIN NOW.\n");
    loginUser(flights, count);
}

int loginUser(struct Flight flights[], int count) 
{  
    struct User user, temp;
    FILE *fp = fopen("users.txt", "r");
    int found = 0;
    printf("\t\t\t\t\t\t==== LOGIN ====\n");
    printf("\nEnter username: ");
    scanf("%s", user.un);
    printf("\nEnter password: ");
    scanf("%s", user.psw);
    while (fread(&temp, sizeof(struct User), 1, fp)) 
    {
        if (strcmp(user.un, temp.un) == 0 &&
            strcmp(user.psw, temp.psw) == 0) 
        {
            found = 1;
            break;
        }
    }

    fclose(fp);
    if (found) 
    {
        printf("Login successful!\n");
        printf("\n\t\t\t\t\t\t----Welcome To Flight Booking System----\n");
        int c;
        do
        {
           printf("\t\t\t\t\t\t\t ====== MENU ======\n");
           printf("\n|---------------------------------------------|\n");
           printf("|1. View Flights.                             |\n");
           printf("|2. Search Flights (By Source & Destination). |\n");
           printf("|3. Book Flight.                              |\n");
           printf("|4. View Your All Bookings.                   |\n");
           printf("|5. Check Recent Bookings.                    |\n");
           printf("|6. Clear All Bookings.                       |\n");
           printf("|7. Cancel Ticket.                            |\n");
           printf("|0. Exit.                                     |\n");
           printf("|---------------------------------------------|\n");
           printf("Choose An Option:");
           scanf("%d", &c);

        switch (c) 
        {
            case 1: 
            viewFlights(flights, count); 
            break;
            case 2: 
            searchFlights(flights, count); 
            break;
            case 3:
            bookFlight();
            break;
            case 4:
            viewAllBookings();
            break;
            case 5:
            checkRecentBooking();
            break;
            case 6:
            clearAllBookings();
            break;
            case 7:
            cancelTicket();
            break;
            default:
            break;
        }

        } while (c!=0);
        
    }
    else
    {
        printf("Invalid username or password!\n");
    }
    return found;
}
void viewFlights(struct Flight flights[], int count) 
{
    printf("\nAvailable Flights:\n");
    printf("----------------------------------------------------------------------\n");
    printf("Flight No       From            To              Date            Time\n");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) 
    {
        printf("%-15d%-16s%-16s%-16s%-10s\n",
            flights[i].fn,
            flights[i].org,
            flights[i].desti,
            flights[i].date,
            flights[i].time);
    }
    printf("\n");
}
void searchFlights(struct Flight flights[], int count) 
{
    char dest[30];
    char src[30];
    int found = 0;
    int sel;
    printf("\nSelect Source:\n");
    printf("1. Delhi\n");
    printf("2. Mumbai\n");
    printf("3. Bangalore\n");
    printf("4. Kolkata\n");
    scanf("%d", &sel);
    switch (sel)
    {
    case 1:
        strcpy(src, "Delhi");
        break;
    case 2:
        strcpy(src, "Mumbai");
        break;
        case 3:
        strcpy(src, "Bangalore");
        break;
         case 4:
        strcpy(src, "Kolkata");
        default:
        printf("Invalid selection.\n");
        return;
    }
    printf("\nSelect destination:\n ");
    printf("1. Mumbai\n");
    printf("2. Chennai\n");
    printf("3. Kolkata\n");
    printf("4. Delhi\n");
    scanf("%d", &sel);
    switch (sel)
    {
        case 1:
        strcpy(dest, "Mumbai");
        break;
        case 2:
        strcpy(dest, "Chennai");
        break;
        case 3:
        strcpy(dest, "Kolkata");
        break;
        case 4:
        strcpy(dest, "Delhi");
        break;
        default:
        printf("Invalid selection.\n");
        return;
    }
    printf("\nSearch Results:\n\n");
    for (int i = 0; i < count; i++) 
    {
        if (strcmp(flights[i].desti, dest) == 0 && strcmp(flights[i].org, src) == 0) 
        {
            printf("Flight No: %d | From: %s | To: %s | Date: %s | Time: %s\n\n\n",
                   flights[i].fn, flights[i].org, flights[i].desti,
                   flights[i].date, flights[i].time);
            found = 1;
        }
    }

    if (!found) 
    {
        printf("No flights found to destination: %s\n", dest);
    }
}
int main() 
{ 
    struct Flight flights[5] = 
{
    {101, "Delhi", "Mumbai", "2025-06-01", "10:00"},
    {102, "Delhi", "Chennai", "2025-06-02", "12:00"},
    {103, "Mumbai", "Kolkata", "2025-06-03", "15:00"},
    {104, "Bangalore", "Delhi", "2025-06-04", "18:00"},
    {105, "Kolkata", "Mumbai", "2025-06-05", "09:00"}
};
    int choice;
    printf("\n\t\t\t\t\t\t===== WELCOME TO FLIGHT BOOKING CENTER =====\n");
    printf("\n\t|---------------------|");
    printf("\n\t|1. LOGIN             |\n\t|2. REGISTER          | \n\t|Press 0 to Exit.     |\n");
    printf("\t|---------------------|\n");
    printf("\nChoose an option:");
    scanf("%d", &choice);

    if (choice == 2) 
    {
        registerUser(flights, 5);
    } 
    else if (choice == 1) 
    {
        loginUser(flights, 5);
    }
    else if(choice == 0) 
    {
        return 0;
    }
    else 
    {
        printf("Invalid option.\n");
    }

    return 0;
}