// making a airport management system

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// structure for flight details

struct flight_time{
    int hour;
    int min;
};
struct flight{
    char flight_no[25];
    char flight_from[25];
    char flight_to[25];
    struct flight_time time;
    int seat_available;
};

// structure for flight booking

struct DOB{
    int date;
    int month;
    int year;
};
struct book{
    char email[25];
    char contact_no[15];
    char depurture[25];
    char arrival[25];
    char name[25];
    struct DOB birth;
    char gender[25];
    char seating[25];
};

// function for admin login

int adminLogin(){
    printf("\n============= Admin Login =============\n");
    char user1[25] = "Airport", pass1[25] = "Airport@007", user2[25], pass2[25];
    printf("Username : ");
    scanf(" %[^\n]", &user2);
    printf("Password : ");
    scanf(" %[^\n]", &pass2);
    if (strcmp(user2, user1) == 0 && strcmp(pass2, pass1) == 0) return 1;
    else return 0;
}

// function for customer account creation

void customerAccount(){
    FILE *account = fopen("Passengeracc.txt", "a");
    char cuser1[25], cpass1[25];
    if (account == NULL){
        printf("ERROR: File Can't Accessed !!");
        return;
    }

    printf("Create a Username : ");
    scanf(" %[^\n]", &cuser1);
    printf("Create a strong Password : ");
    scanf(" %[^\n]", &cpass1);
    printf("\n");

    fprintf(account, "Username: %s|Password: %s\n", cuser1, cpass1);
    fclose(account);
    printf("Successfully Created Your Account\n");
}

// function for customer login

int customerLogin(){
    FILE *account = fopen("Passengeracc.txt", "r");
    char cuser2[25], cpass2[25], line[200], fuser[25], fpass[25];
    int found = 0;
    if (account == NULL){
        printf("ERROR: File Can't Accessed !!");
        return 0;
    }

    printf("Enter Username : ");
    scanf(" %[^\n]", &cuser2);
    printf("Enter Password : ");
    scanf(" %[^\n]", &cpass2);

    while (fgets(line, sizeof(line), account)){
        sscanf(line, "Username: %[^|]|Password: %[^\n]", fuser, fpass);
        if (strcmp(fuser, cuser2) == 0 && strcmp(fpass, cpass2) == 0) return 1;
    }
    fclose(account);
}

// function for adding flights by admin

void addFlight(){
    FILE *flight = fopen("Flight.txt", "a");
    struct flight f;
    int count;
    if (flight == NULL){
        printf("ERROR: File Can't Accessed !!");
        return;
    }
    printf("Enter No of Upcoming Flights : ");
    scanf("%d", &count);
    for (int i = 0; i < count; i++){
        printf("\nEnter details for flight %d:\n", i + 1);
        printf("Flight No: ");
        scanf("%s", &f.flight_no);
        printf("Flight From: ");
        scanf(" %[^\n]", f.flight_from);
        printf("Flight To: ");
        scanf(" %[^\n]", &f.flight_to);
        printf("Flight Time (HH:MM): ");
        scanf("%d%d", &f.time.hour, &f.time.min);
        printf("Available Seats: ");
        scanf("%d", &f.seat_available);

        fprintf(flight, "Flight No is: %s|Flight From: %s|Flight To: %s|Flight Time(HH:MM): %d %d|Available Seats: %d\n", f.flight_no, f.flight_from, f.flight_to, f.time, f.seat_available);
    }
    fclose(flight);
    printf("\n");
    printf("Upcoming %d Flights Are Added Successfully\n", count);
}

// function for viewing the flights

void viewFlight(){
    FILE *flight = fopen("Flight.txt", "r");
    struct flight f;
    char line[200];

    if (flight == NULL){
        printf("ERROR: File Can't Accessed !!\n");
        return;
    }
    printf("\n=========== Upcoming Flights ==========\n");

    while (fgets(line, sizeof(line), flight)){

        sscanf(line, "Flight No is: %[^|]|Flight From: %[^|]|Flight To: %[^|]|Flight Time(HH:MM): %d %d|Available Seats: %d", f.flight_no, f.flight_from, f.flight_to, &f.time.hour, &f.time.min, &f.seat_available);
        printf("Flight No           : %s\n", f.flight_no);
        printf("Flight From         : %s\n", f.flight_from);
        printf("Flight To           : %s\n", f.flight_to);
        printf("Flight Time (HH:MM) : %02d:%02d\n", f.time.hour, f.time.min);
        printf("Available Seats     : %d\n\n", f.seat_available);
    }
    printf("---------------------------------------\n\n");
    fclose(flight);
}

// function for deleteing the saved flights

void deleteFlight(){
    FILE *flight, *temp;
    char line[200], delete[25];
    int found = 0;

    printf("Enter the flight number : ");
    scanf("%s", &delete);
    printf("\n");

    flight = fopen("Flight.txt", "r");
    if (flight == NULL){
        printf("ERROR: File Can't Accessed !!\n");
        return;
    }
    temp = fopen("temp.txt", "w");
    if (temp == NULL){
        printf("ERROR: File Can't Accessed !!\n");
        fclose(temp);
        return;
    }

    while (fgets(line, sizeof(line), flight)){
        if (strstr(line, delete) == NULL){
            fputs(line, temp);
        }
        else found = 1;
    }
    fclose(flight);
    fclose(temp);

    remove("Flight.txt");
    rename("temp.txt", "Flight.txt");

    if (found) printf("Flight deleted successfully\n");
    else printf("Flight not found");
}

// function for booking flights

void bookFlight(){
    FILE *book = fopen("Bookflight.txt", "a");
    FILE *flight = fopen("Flight.txt", "r");
    struct book b;
    struct flight f;
    int count, seed, hour, min;
    char flightno[15], line[200];
    if (book == NULL || flight == NULL){
        printf("ERROR: File Can't Accessed !!");
        return;
    }
    srand(time(NULL));
    seed = rand() % 900000 + 100000;

    printf("Enter Your Email : ");
    scanf("%s", b.email);
    printf("Enter Your Contact Number : ");
    scanf("%s", b.contact_no);
    printf("Enter Your Flight From : ");
    scanf(" %[^\n]", b.depurture);
    printf("Enter Your Flight To : ");
    scanf(" %[^\n]", b.arrival);

    while (fgets(line, sizeof(line), flight)){
        sscanf(line, "Flight No is: %[^|]|Flight From: %[^|]|Flight To: %[^|]|Flight Time(HH:MM): %d %d|Available Seats: %d", f.flight_no, f.flight_from, f.flight_to, &f.time.hour, &f.time.min, &f.seat_available);
        if (strcmp(f.flight_from, b.depurture) == 0 && strcmp(f.flight_to, b.arrival) == 0){
            strcpy(flightno, f.flight_no);
            hour = f.time.hour;
            min = f.time.min;
        }
    }

    fprintf(book, "PNR No: P%d|Flight No: %s|Flight Time(HH:MM): %d %d|Email: %s|Contact No: %s|Depurture: %s|Arrival: %s|", seed, flightno, hour, min, b.email, b.contact_no, b.depurture, b.arrival);

    printf("Enter No of Person to be Travel : ");
    scanf("%d", &count);
    for (int i = 0; i < count; i++){
        printf("\nEnter details for Person %d:\n", i + 1);
        printf("Enter Name: ");
        scanf(" %[^\n]", &b.name);
        printf("Enter DOB(DD:MM:YYYY): ");
        scanf("%d%d%d", &b.birth.date, &b.birth.month, &b.birth.year);
        printf("Enter Gender: ");
        scanf("%s", &b.gender);
        printf("Enter Seating Preference: ");
        scanf("%s", &b.seating);
        fprintf(book, "Name: %s|DOB: %d %d %d|Gender: %s|Seating: %s|", b.name, b.birth.date, b.birth.month, b.birth.year, b.gender, b.seating);
    }
    fprintf(book,"\n");
    fclose(book);
    fclose(flight);
    printf("You Successfully Booked Your Flight\n");
    printf("=======================================\n");
    printf("Your PNR No : P%d\n", seed);
    printf("---------------------------------------\n");
}

// function for viewing the booked flight

void viewBooking() {
    FILE *book = fopen("Bookflight.txt", "r");
    char pnr[20], line[2000];
    int found = 0;

    if (book == NULL) {
        printf("ERROR: File Can't Accessed !!\n");
        return;
    }

    printf("Enter PNR No : ");
    scanf("%s", pnr);
    printf("---------------------------------------\n");

    while (fgets(line, sizeof(line), book)) {
        if (strstr(line, pnr) != NULL) {
            found = 1;

            char pnr[20], flight_no[20], email[30], contact[20];
            char dep[30], arr[30];
            int hour, min;

            sscanf(line,
                "PNR No: %[^|]|Flight No: %[^|]|Flight Time(HH:MM): %d %d|Email: %[^|]|Contact No: %[^|]|Depurture: %[^|]|Arrival: %[^|]|",
                pnr, flight_no, &hour, &min, email, contact, dep, arr);

            printf("\n=========== Booking Details ===========\n");
            printf("PNR Number       : %s\n", pnr);
            printf("Flight Number    : %s\n", flight_no);
            printf("Flight Time      : %02d:%02d\n", hour, min);
            printf("Flight From      : %s\n", dep);
            printf("Flight To        : %s\n", arr);
            printf("Email            : %s\n", email);
            printf("Contact Number   : %s\n", contact);

            char *ptr = strstr(line, "|Name:");
            int passenger = 1;

            while (ptr != NULL) {
                char name[30], gender[15], seating[20];
                int day, month, year;

                int matched = sscanf(ptr, "|Name: %[^|]|DOB: %d %d %d|Gender: %[^|]|Seating: %[^|]",
                    name, &day, &month, &year, gender, seating);

                if (matched == 6) {
                    printf("\nPassenger %d\n", passenger++);
                    printf("Name             : %s\n", name);
                    printf("Date of Birth    : %02d-%02d-%04d\n", day, month, year);
                    printf("Gender           : %s\n", gender);
                    printf("Seating Pref     : %s\n", seating);
                }

                ptr = strstr(ptr + 6, "|Name:");
            }

            printf("---------------------------------------\n");
            break;
        }
    }

    if (!found) {
        printf("No Booking Found With This PNR No.\n");
    }

    fclose(book);
}

// function for deleteing booked flights by pnr number

void deleteBooking(){
    FILE *book, *temp;
    char pnr[20], line[500];
    int found = 0;

    printf("Enter PNR No : ");
    scanf("%s", pnr);
    printf("\n");

    book = fopen("Bookflight.txt", "r");
    if (book == NULL){
        printf("ERROR: File Can't Accessed !!\n");
        return;
    }
    temp = fopen("temp.txt", "w");
    if (temp == NULL){
        printf("ERROR: File Can't Accessed !!\n");
        fclose(temp);
        return;
    }

    while (fgets(line, sizeof(line), book)){
        if (strstr(line, pnr) == NULL){
            fputs(line, temp);
        }
        else found = 1;
    }
    fclose(book);
    fclose(temp);

    remove("Bookflight.txt");
    rename("temp.txt", "Bookflight.txt");

    if (found) printf("Booking With PNR %s Deleted Successfully.\n", pnr);
    else printf("No booking found with PNR %s.\n", pnr);
}

// function for viewing booked flights for admin

void viewAdminBooking() {
    FILE *book = fopen("Bookflight.txt", "r");
    char line[2000];

    if (book == NULL) {
        printf("ERROR: File Can't Accessed !!\n");
        return;
    }

    printf("============= All Bookings =============\n");

    while (fgets(line, sizeof(line), book)) {
        char pnr[20], flight_no[20], email[30], contact[20];
        char dep[30], arr[30];
        int hour, min;

        int matched = sscanf(line,
            "PNR No: %[^|]|Flight No: %[^|]|Flight Time(HH:MM): %d %d|Email: %[^|]|Contact No: %[^|]|Depurture: %[^|]|Arrival: %[^|]|",
            pnr, flight_no, &hour, &min, email, contact, dep, arr);

        if (matched == 8) {
            printf("\n=========== Booking Details ===========\n");
            printf("PNR Number       : %s\n", pnr);
            printf("Flight Number    : %s\n", flight_no);
            printf("Flight Time      : %02d:%02d\n", hour, min);
            printf("Flight From      : %s\n", dep);
            printf("Flight To        : %s\n", arr);
            printf("Email            : %s\n", email);
            printf("Contact Number   : %s\n", contact);

            char *ptr = strstr(line, "|Name:");
            int passenger = 1;

            while (ptr != NULL) {
                char name[30], gender[15], seating[20];
                int day, month, year;

                int matched_passenger = sscanf(ptr, "|Name: %[^|]|DOB: %d %d %d|Gender: %[^|]|Seating: %[^|]",
                    name, &day, &month, &year, gender, seating);

                if (matched_passenger == 6) {
                    printf("\nPassenger %d\n", passenger++);
                    printf("Name             : %s\n", name);
                    printf("Date of Birth    : %02d-%02d-%04d\n", day, month, year);
                    printf("Gender           : %s\n", gender);
                    printf("Seating Pref     : %s\n", seating);
                }

                ptr = strstr(ptr + 6, "|Name:");
            }

            printf("---------------------------------------\n");
        }
    }

    fclose(book);
}


int main(){
    int mainCount;
    mainmenu:
    while (1){
        printf("             Welcome To\n      Airport Management System\n");
        printf("=======================================\n");
        printf("\n============== Main Menu ==============\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. View Flights\n");
        printf("4. Exit\n");

        printf("Enter your choice : ");
        scanf("%d", &mainCount);

        // this is for the mainmenu
        
        switch (mainCount){
        case 1:{
            while (1){
                if (adminLogin() == 1){
                    int adminCount;
                    adminmenu:
                    printf("\n============== Admin Menu =============\n");
                    printf("1. Add Flights\n");
                    printf("2. Delete Flights\n");
                    printf("3. View Bookings\n");
                    printf("4. Cancel Bookings\n");
                    printf("5. Logout\n");

                    printf("Enter your choice : ");
                    scanf("%d", &adminCount);
                    printf("=======================================\n");
                    // this is for adminmenu
                    switch (adminCount){
                    case 1: addFlight(); goto adminmenu;
                    case 2: deleteFlight(); goto adminmenu;
                    case 3: viewAdminBooking(); goto adminmenu;
                    case 4: deleteBooking(); goto adminmenu;
                    case 5: printf("Successfully Logged Out\n\n"); goto mainmenu;
                    default: printf("Invalid Input.Try Again\n"); break;
                    }
                }
                else{
                    printf("Access Denied !!\n");
                }
            }
            goto mainmenu;
        }
        case 2:{
            while (1){
                int cloginchoice;

                printf("\n============== User Login =============\n");
                printf("1. Create Account\n");
                printf("2. Log In\n");
                printf("3. Exit\n");

                printf("Enter your choice : ");
                scanf("%d", &cloginchoice);
                printf("\n");
                // this is for customer mainmenu
                switch (cloginchoice){
                case 1: customerAccount(); break;
                case 2:{
                    while (1){
                        if (customerLogin() == 1){
                            int customerchoice;
                            customermenu:
                            printf("\n============== User Menu ==============\n");
                            printf("1. Book Flight\n");
                            printf("2. Cancel Flight\n");
                            printf("3. View My Flight\n");
                            printf("4. Logout\n");

                            printf("Enter your choice : ");
                            scanf("%d", &customerchoice);
                            printf("=======================================\n");

                            // this is for customer submenu
                            
                            switch (customerchoice){
                            case 1: bookFlight(); goto customermenu;
                            case 2: deleteBooking(); goto customermenu;
                            case 3: viewBooking(); goto customermenu;
                            case 4: printf("Successfully Logged Out\n\n"); goto mainmenu;
                            default: printf("Invalid Input.Try Again\n"); goto customermenu;
                            }
                        }
                        else{
                            printf("Access Denied !!\n");
                            printf("---------------------------------------\n");
                        }
                    }
                    break;
                }
                case 3: printf("Exited Successfully\n"); goto mainmenu;
                default: printf("Invalid Input.Try Again\n"); break;
                }
            }
            break;
        }
        case 3: viewFlight(); break;
        case 4: printf("Succesfully Exited\nThank You For Choosing Us\n"); printf("=======================================\n"); return 0;
        default: printf("Invalid Choice. Please Try Again\n"); printf("---------------------------------------\n");
        }
    }
    return 0;
}