#include "../Header/menu.h"
#include "../Header/user.h"
#include "../Header/events.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Function to display the main menu and handle user interactions
void mainMenu() {
    // Pointers to the head of linked lists for users and historical events
    User* userHead = nullptr;
    HistoricalEvent* eventHead = nullptr;

    // Load all users from the file into the linked list
    loadUsers(userHead);

    int choice;

    // Display the main welcome menu
    cout << "==============================" << endl;
    cout << "           WELCOME           " << endl;
    cout << "==============================" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "==============================" << endl;

    // Input validation loop for menu selection
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle invalid input
        if (cin.fail() || choice < 1 || choice > 3) {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            cin.clear();       
            cin.ignore();      
        }
        else {
            break;
        }
    }

    // Handle user's menu choice
    if (choice >= 1 && choice <= 3)
    {
        if (choice == 1) {
            // Attempt to log in the user
            User* loggedInUser = loginUser(userHead);

            // If login is successful, load event data and show the app menu
            if (loggedInUser != nullptr) {
                loadEventsFromFile(eventHead);
                optionsMenu(eventHead, userHead, loggedInUser->role);
            }
        }
        else if (choice == 2) {
            // Register a new user
            registerUser(userHead);
        }
        else if (choice == 3) {
            // Exit the application
            exit(0);
        }
        else {
            // Should not reach here, but as a fallback reset the menu
            system("cls");
            mainMenu();
        }
    }
}
