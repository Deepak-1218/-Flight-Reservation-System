#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store passenger details
struct Passenger {
    int id;
    char name[50];
    char flightNumber[10];
};

// Function to add a new booking
void bookFlight() {
    struct Passenger p;
    FILE *file = fopen("flights.txt", "a");

    printf("Enter Passenger ID: ");
    scanf("%d", &p.id);
    printf("Enter Passenger Name: ");
    scanf("%s", p.name);
    printf("Enter Flight Number: ");
    scanf("%s", p.flightNumber);

    fprintf(file, "%d %s %s\n", p.id, p.name, p.flightNumber);
    fclose(file);
    printf("Booking Successful!\n");
}

// Function to cancel a booking
void cancelBooking() {
    int id;
    printf("Enter Passenger ID to Cancel Booking: ");
    scanf("%d", &id);

    FILE *file = fopen("flights.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    struct Passenger p;
    int found = 0;

    while (fscanf(file, "%d %s %s", &p.id, p.name, p.flightNumber) != EOF) {
        if (p.id == id) {
            found = 1;
            continue;
        }
        fprintf(tempFile, "%d %s %s\n", p.id, p.name, p.flightNumber);
    }

    fclose(file);
    fclose(tempFile);
    remove("flights.txt");
    rename("temp.txt", "flights.txt");

    if (found) {
        printf("Booking Cancelled Successfully!\n");
    } else {
        printf("Passenger ID not found!\n");
    }
}

// Function to display all bookings
void viewBookings() {
    FILE *file = fopen("flights.txt", "r");
    struct Passenger p;

    printf("\n---- Flight Bookings ----\n");
    while (fscanf(file, "%d %s %s", &p.id, p.name, p.flightNumber) != EOF) {
        printf("Passenger ID: %d, Name: %s, Flight: %s\n", p.id, p.name, p.flightNumber);
    }
    fclose(file);
}

// Main Menu
int main() {
    int choice;
    while (1) {
        printf("\nFlight Reservation System\n");
        printf("1. Book Flight\n");
        printf("2. Cancel Booking\n");
        printf("3. View Bookings\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookFlight();
                break;
            case 2:
                cancelBooking();
                break;
            case 3:
                viewBookings();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
