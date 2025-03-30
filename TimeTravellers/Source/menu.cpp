#include "../Header/menu.h"
#include "../Header/user.h"
#include"../Header/optionsMenu.h"
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
           

            system("cls");
            optionsMenu();
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

void optionsMenu()
{
    int choice;

    while (true) {
        cout << endl;
       cout << "============ MENU ============"<<endl;
        cout << "1. View Historical events" << endl;
        cout << "2. Add Historical event" << endl;
        cout << "3. Search Historical event" << endl;
        cout << "4. Delete Historical event" << endl;
       cout << "5. Exit" << endl;
       cout << "Enter your choice: " << endl;

        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Viewing Historical events..." << endl;
            break;
        case 2:
           cout << "Adding a new Historical event..." << endl;
            break;
        case 3:
            cout << "Searching for a Historical event..." << endl;
            break;
        case 4:
            cout << "Deleting a Historical event..." << endl;
            break;
        case 5:
            cout << "Exiting program. Goodbye!" << endl;
            system("cls");
            
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

}