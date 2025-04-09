#include "../Header/admin.h"

using namespace std;

// Main function to handle admin panel interactions
void adminPanel(User*& head, HistoricalEvent*& eventHead, string role) {
    int choice;
    string username;

    while (true) {
        // Display admin panel menu
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

        // Validate input for menu choice
        if (!(cin >> choice)) {
            cin.clear();        
            cin.ignore();       
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        // Option 1: Display all registered users
        if (choice == 1) {
            system("cls");
            cout << "===== Registered Users =====" << endl;
            User* temp = head;
            while (temp != nullptr) {
                cout << "ID: " << temp->id << " | Username: " << temp->username << " | Role: " << temp->role << endl;
                temp = temp->next;
            }
        }

        // Option 2: Promote user to admin
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

        // Option 3: Demote admin to regular user
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

        // Option 4: Delete a user
        else if (choice == 4) {
            int id;
            cout << "Enter the ID of the user to delete: ";
            cin >> id;

            User* temp = head;
            User* prev = nullptr;

            // Find user by ID
            while (temp != nullptr && temp->id != id) {
                prev = temp;
                temp = temp->next;
            }

            // Handle user not found
            if (temp == nullptr) {
                cout << "User with ID " << id << " not found." << endl;
            }
            else {
                // Remove user from the linked list
                if (prev == nullptr) {
                    // Deleting head node
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

        // Option 5: Add a historical event
        else if (choice == 5) {
            system("cls");
            cout << "Adding a new Historical Event..." << endl;

            string event, description;
            int year;
            // Clear leftover newline from previous input
            cin.ignore();  
           
            cout << "Event Name: ";
            getline(cin, event);

            // Validate the year input
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

            // Add event to linked list
            addHistoricalEvent(eventHead, event, year, description);
            cout << "Event added successfully!" << endl;

            system("cls");
            // Return to options
            optionsMenu(eventHead, head, role); 
            break;
        }

        // Option 6: Edit an existing event
        else if (choice == 6) {
            system("cls");
            int eventID;
            cout << "Enter the ID of the event you want to edit: ";

            // Validate ID input
            while (!(cin >> eventID)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input. Enter a valid event ID: ";
            }
            // Edit function call
            redactHistoricalEvent(eventHead, eventID, head, role); 
            break;
        }

        // Option 7: Delete an event
        else if (choice == 7) {
            system("cls");
            cout << "Enter the ID of the event to delete: ";
            int eventID;

            while (!(cin >> eventID)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input! Please enter a valid event ID: ";
            }
            // Remove event from list
            deleteHistoricalEvent(eventHead, eventID);  
            cout << "Returning to menu..." << endl;

            system("cls");
            optionsMenu(eventHead, head, role);
            break;
        }

        // Option 8: Exit to main menu
        else if (choice == 8) {
            optionsMenu(eventHead, head, role);
            break;
        }

        // Invalid option entered
        else {
            cout << "Invalid option. Try again." << endl;
        }

        // Pause before continuing
        cout << endl << "Press Enter to continue...";
        // Save any user changes
        saveUsersToFile(head);  
        cin.ignore();
        cin.get();
        system("cls");
    }
}

// Save the current user list to a file
void saveUsersToFile(User* head) {
    ofstream outFile("TimeTravellers/Data/users.txt");
    User* temp = head;

    // Write each user's data line by line
    while (temp != nullptr) {
        outFile << temp->id << " " << temp->username << " " << temp->salt << " "
            << temp->password << " " << temp->role << endl;
        temp = temp->next;
    }

    outFile.close();
}
