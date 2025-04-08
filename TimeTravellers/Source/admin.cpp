#include "../Header/admin.h"

void adminPanel(User*& head, HistoricalEvent*& eventHead, string role) {
    int choice;
    string username;

    while (true) {
        cout << "==============================" << endl;
        cout << "         ADMIN PANEL       " << endl;
        cout << "==============================" << endl;
        cout << "1. View all users" << endl;
        cout << "2. Promote a user to admin" << endl;
        cout << "3. Demote an admin to user" << endl;
        cout << "4. Delete a user" << endl;
        cout << "5. Add a Historical Event" << endl;
        cout << "6. Edit an Event" << endl;
        cout << "7. Delete an Event" << endl;
        cout << "8. Exit to main menu" << endl;
        cout << "==============================" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (choice == 1) {
            system("cls");
            cout << "===== Registered Users =====" << endl;
            User* temp = head;
            while (temp != nullptr) {
                cout << "ID: " << temp->id << " | Username: " << temp->username << " | Role: " << temp->role << endl;
                temp = temp->next;
            }
        }

        else if (choice == 2) {
            int id;
            cout << "Enter the ID of the user to promote: ";
            cin >> id;

            User* temp = head;
            while (temp != nullptr) {
                if (temp->id == id) {
                    temp->role = "admin";
                    cout << temp->username << " has been promoted to admin!" << endl;
                    saveUsersToFile(head);
                    break;
                }
                temp = temp->next;
            }

            if (temp == nullptr) {
                cout << "User with ID " << id << " not found." << endl;
            }
        }

        else if (choice == 3) {
            int id;
            cout << "Enter the ID of the user to demote: ";
            cin >> id;

            User* temp = head;
            while (temp != nullptr) {
                if (temp->id == id) {
                    temp->role = "user";
                    cout << temp->username << " has been demoted to user!" << endl;
                    saveUsersToFile(head);
                    break;
                }
                temp = temp->next;
            }

            if (temp == nullptr) {
                cout << "User with ID " << id << " not found." << endl;
            }
        }

        else if (choice == 4) {
            int id;
            cout << "Enter the ID of the user to delete: ";
            cin >> id;

            User* temp = head;
            User* prev = nullptr;

            while (temp != nullptr && temp->id != id) {
                prev = temp;
                temp = temp->next;
            }

            if (temp == nullptr) {
                cout << "User with ID " << id << " not found." << endl;
            }
            else {
                if (prev == nullptr) {
                    head = temp->next;
                }
                else {
                    prev->next = temp->next;
                }
                cout << "User " << temp->username << " has been deleted." << endl;
                delete temp;
                saveUsersToFile(head);
            }
        }

        else if (choice == 5)
        {
            system("cls");
            cout << "Adding a new Historical Event..." << endl;

            string event, description;
            int year;

            cin.ignore();
            cout << "Event Name: ";
            getline(cin, event);

            while (true) {
                cout << "Year (1-2025): ";
                if (cin >> year && year >= 1 && year <= 2025) {
                    break;
                }
                else {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid year! Please enter a number between 1 and 2025." << endl;
                }
            }

            cin.ignore();
            cout << "Description: ";
            getline(cin, description);

            addHistoricalEvent(eventHead, event, year, description);
            cout << "Event added successfully!" << endl;
            system("cls");
            optionsMenu(eventHead, head, role);
            break;
        }
        else if (choice == 6)
        {
            system("cls");
            int eventID;
            cout << "Enter the ID of the event you want to edit: ";
            while (!(cin >> eventID)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input. Enter a valid event ID: ";
            }
            redactHistoricalEvent(eventHead, eventID, head, role);
            break;
        }
        else if (choice == 7)
        {
            system("cls");
            cout << "Enter the ID of the event to delete: ";
            int eventID;

            while (!(cin >> eventID)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input! Please enter a valid event ID: ";
            }

            deleteHistoricalEvent(eventHead, eventID);
            cout << "Returning to menu..." << endl;
            system("cls");
            optionsMenu(eventHead, head, role);
            break;
        }
        else if (choice == 8) {
            optionsMenu(eventHead, head, role);
            break;
        }

        else {
            cout << "Invalid option. Try again." << endl;
        }

        cout << endl << "Press Enter to continue...";
        saveUsersToFile(head);
        cin.ignore();
        cin.get();
        system("cls");
    }
}

void saveUsersToFile(User* head) {
    ofstream outFile("TimeTravellers/Data/users.txt");
    User* temp = head;
    while (temp != nullptr) {
        outFile << temp->id << " " << temp->username << " " << temp->salt << " " << temp->password << " " << temp->role << endl;
        temp = temp->next;
    }
    outFile.close();
}