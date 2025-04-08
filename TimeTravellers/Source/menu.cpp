#include "../Header/menu.h"
#include "../Header/user.h"
#include "../Header/events.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

void mainMenu() {
    User* userHead = nullptr;
    HistoricalEvent* eventHead = nullptr;
    loadUsers(userHead);

    int choice;

    cout << "==============================" << endl;
    cout << "           WELCOME       " << endl;
    cout << "==============================" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "==============================" << endl;
    
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 3) {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            cin.clear();
            cin.ignore();
        }
        else {
            break;
        }
    }

    if (choice >= 1 && choice <= 3)
    {
        if (choice == 1) {
            User* loggedInUser = loginUser(userHead);
            if (loggedInUser != nullptr) {
                loadEventsFromFile(eventHead);
                optionsMenu(eventHead, userHead, loggedInUser->role);
            }
        }
        else if (choice == 2) {
            registerUser(userHead);

        }
        else if (choice == 3) {
            exit(0);
        }
        else {
            system("cls");
            mainMenu();
        }
    }
}