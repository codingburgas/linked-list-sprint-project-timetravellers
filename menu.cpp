#include "menu.h"
#include <iostream>

using namespace std;

void mainMenu() {
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

    switch (choice)
    {
    //case 1: login();
    //case 2: register();
    default: exit(0);
    }
}