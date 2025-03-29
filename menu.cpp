#include "menu.h"
#include "user.h"
#include <iostream>

using namespace std;

void mainMenu() {
    User* head = nullptr;
    loadUsers(head);

    int choice;

    cout << "==============================" << endl;
    cout << "      HISTORY APP MENU       " << endl;
    cout << "==============================" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "==============================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        if (loginUser(head)) {
            cout << "Login successful!" << endl;
        }
        else {
            cout << "Invalid username or password." << endl;
        }
    }
    else if (choice == 2) {
        registerUser(head);
    }
    else if (choice == 3) {
        exit(0);
    }
    else {
        system("cls");
        mainMenu();
    }
}