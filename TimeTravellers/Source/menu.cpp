#include "../Header/menu.h"
#include "../Header/user.h"
#include "../Header/addEvents.h"
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
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        if (loginUser(userHead)) {
            system("cls");
            loadEventsFromFile(eventHead);
            optionsMenu(eventHead);
        }
        else {
            cout << "Invalid username or password." << endl;
            system("cls");
            mainMenu();
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