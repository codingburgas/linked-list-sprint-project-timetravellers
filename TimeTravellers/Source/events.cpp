﻿#include "../Header/events.h"
#include "../Header/admin.h"
using namespace std;

// Displays the main options menu based on user role
void optionsMenu(HistoricalEvent*& head, User*& userHead, string role) {
    int choice;
    system("cls");

    // Display menu options for admin users
    if (role == "admin") {
        cout << "==============================" << endl;
        cout << "      HISTORY APP MENU       " << endl;
        cout << "==============================" << endl;
        cout << "1. View Historical Events" << endl;
        cout << "2. Search for an Event" << endl;
        cout << "3. Administration Panel" << endl;
        cout << "4. Exit" << endl;
        cout << "==============================" << endl;
        cout << "Select an option: ";
    }
    // Display menu options for normal users
    else {
        cout << "==============================" << endl;
        cout << "      HISTORY APP MENU       " << endl;
        cout << "==============================" << endl;
        cout << "1. View Historical Events" << endl;
        cout << "2. Search for an Event" << endl;
        cout << "3. Exit" << endl;
        cout << "==============================" << endl;
        cout << "Select an option: ";
    }

    // Validate input based on role
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || (role == "admin" && (choice < 1 || choice > 4))) {
            
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            cin.clear(); cin.ignore();
        }
        else if (cin.fail() || (role != "admin" && (choice < 1 || choice > 3))) {

            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            cin.clear(); cin.ignore();
        }
        else {
            break;
        }
    }

    // Handle user selections
    if (choice == 1) {
        system("cls");
        cout << "Historical Events:" << endl;
        displayHistoricalEvents(head, userHead, role);
    }
    else if (choice == 2) {
        searchHistoricalEvent(head, userHead, role);
    }
    else if (choice == 3) {
        if (role == "admin") {
            // Admin panel access
            system("cls");
            adminPanel(userHead, head, role);  
        }
        else {
            saveEventsToFile(head);
            cout << "Saving data... Exiting program. Goodbye!" << endl;
        }
    }
    else if (choice == 4 && role == "admin") {
        saveEventsToFile(head);
        cout << "Saving data... Exiting program. Goodbye!" << endl;
    }
    else {
        cout << "That's not a valid option. Try again." << endl;
        cin.ignore();
        system("cls");
    }
}

// Displays all historical events in a table format
void displayHistoricalEvents(HistoricalEvent* head, User*& userHead, string role) {
    if (!head) {
        cout << endl << "No historical events found." << endl;
        cout << "Press Enter to return to the menu...";
        cin.ignore();
        cin.get();
        optionsMenu(head, userHead, role);
    }

    // Dynamically calculate column widths
    int maxIDWidth = 3, maxYearWidth = 4, maxEventWidth = 5, maxDescWidth = 11;
    HistoricalEvent* temp = head;
    while (temp) {
        maxIDWidth = max(maxIDWidth, (int)to_string(temp->id).length());
        maxYearWidth = max(maxYearWidth, (int)to_string(temp->year).length());
        maxEventWidth = max(maxEventWidth, (int)temp->event.length());
        maxDescWidth = max(maxDescWidth, (int)temp->description.length());
        temp = temp->next;
    }

    // Print formatted table header and events
    cout << endl << string(maxIDWidth + maxYearWidth + maxEventWidth + maxDescWidth + 13, '=') << endl;
    cout << "| " << left << setw(maxIDWidth) << "No." << " | " << setw(maxYearWidth) << "Year" << " | "
        << setw(maxEventWidth) << "Event" << " | " << setw(maxDescWidth) << "Description" << " |" << endl;
    cout << "|" << string(maxIDWidth + 2, '-') << "|" << string(maxYearWidth + 2, '-') << "|"
        << string(maxEventWidth + 2, '-') << "|" << string(maxDescWidth + 2, '-') << "|" << endl;

    temp = head;
    while (temp) {
        cout << "| " << left << setw(maxIDWidth) << temp->id << " | " << setw(maxYearWidth) << temp->year << " | "
            << setw(maxEventWidth) << temp->event << " | " << setw(maxDescWidth) << temp->description << " |" << endl;
        temp = temp->next;
    }

    cout << string(maxIDWidth + maxYearWidth + maxEventWidth + maxDescWidth + 13, '=') << endl;
    cout << endl << "Press Enter to return to the menu...";
    cin.ignore();
    cin.get();
    optionsMenu(head, userHead, role);
}

// Adds a new historical event to the linked list
void addHistoricalEvent(HistoricalEvent*& head, const string& event, int year, const string& description) {
    int newID = 1;
    HistoricalEvent* temp = head;

    while (temp && temp->next) temp = temp->next;
    if (temp) newID = temp->id + 1;

    HistoricalEvent* newEvent = new HistoricalEvent{ newID, year, event, description, nullptr };
    if (!head) head = newEvent;
    else temp->next = newEvent;
}

// Saves events to a file after sorting by year
void saveEventsToFile(HistoricalEvent* head) {
    ofstream file("TimeTravellers/Data/events.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Copy and sort events
    HistoricalEvent* sortedHead = nullptr;
    HistoricalEvent* temp = head;
    while (temp) {
        addHistoricalEvent(sortedHead, temp->event, temp->year, temp->description);
        temp = temp->next;
    }

    // Sort events by year
    bool swapped;
    do {
        swapped = false;
        HistoricalEvent* ptr = sortedHead;
        while (ptr && ptr->next) {
            if (ptr->year > ptr->next->year) {
                swap(ptr->year, ptr->next->year);
                swap(ptr->event, ptr->next->event);
                swap(ptr->description, ptr->next->description);
                swapped = true;
            }
            ptr = ptr->next;
        }
    } while (swapped);

    // Write sorted events to file
    HistoricalEvent* current = sortedHead;
    int newID = 1;
    while (current) {
        current->id = newID++;
        file << current->id << " | " << current->year << " | " << current->event << " | " << current->description << endl;
        current = current->next;
    }

    file.close();
}

// Loads events from file into memory
void loadEventsFromFile(HistoricalEvent*& head) {
    ifstream file("TimeTravellers/Data/events.txt");
    if (!file) {
        cout << "No previous data found." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        int id, year;
        string event, description;

        // Parse the line based on " | " delimiter
        size_t firstPipe = line.find(" | ");
        size_t secondPipe = line.find(" | ", firstPipe + 3);
        size_t thirdPipe = line.find(" | ", secondPipe + 3);
        if (firstPipe == string::npos || secondPipe == string::npos || thirdPipe == string::npos) continue;

        id = stoi(line.substr(0, firstPipe));
        year = stoi(line.substr(firstPipe + 3, secondPipe - (firstPipe + 3)));
        event = line.substr(secondPipe + 3, thirdPipe - (secondPipe + 3));
        description = line.substr(thirdPipe + 3);

        // Add event to linked list
        HistoricalEvent* newEvent = new HistoricalEvent{ id, year, event, description, nullptr };
        if (!head) head = newEvent;
        else {
            HistoricalEvent* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newEvent;
        }
    }

    file.close();
}

// Allows user to search events by name or year
void searchHistoricalEvent(HistoricalEvent* head, User*& userHead, string role) {
    if (!head) {
        cout << "There are no historical events recorded yet." << endl;
        cout << "Press Enter to return to the menu..." << endl;
        cin.ignore();
        cin.get();
        return;
    }

    system("cls");
    cout << "=== Search for a Historical Event ===" << endl;

    int choice;
    cout << "1. Search by Name" << endl;
    cout << "2. Search by Year" << endl;
    cout << "3. Go back" << endl;
    cout << "Enter your choice: ";

    if (!(cin >> choice)) {
        cin.clear(); cin.ignore();
        cout << "Invalid input! Please enter a number." << endl;
        return;
    }

    cin.ignore();
    HistoricalEvent* current = head;

    if (choice == 1) {
        system("cls");
        string searchName;
        cout << "Enter the name of the event: ";
        getline(cin, searchName);

        while (current) {
            if (current->event.find(searchName) != string::npos) {
                cout << endl << "Event Found!" << endl;
                cout << "ID: " << current->id << endl;
                cout << "Year: " << current->year << endl;
                cout << "Event: " << current->event << endl;
                cout << "Description: " << current->description << endl;
            }
            current = current->next;
        }
    }
    else if (choice == 2) {
        system("cls");
        int searchYear;
        cout << "Enter the year to search (1-2025): ";

        while (!(cin >> searchYear) || searchYear < 1 || searchYear > 2025) {
            cin.clear(); cin.ignore();
            cout << "Invalid year! Please enter a number between 1 and 2025: ";
        }

        while (current) {
            if (current->year == searchYear) {
                cout << endl << "Event Found!" << endl;
                cout << "ID: " << current->id << endl;
                cout << "Year: " << current->year << endl;
                cout << "Event: " << current->event << endl;
                cout << "Description: " << current->description << endl;
            }
            current = current->next;
        }
    }
    else if (choice == 3) {
        system("cls");
        optionsMenu(head, userHead, role);
        return;
    }
    else {
        cout << "Invalid selection. Returning to the menu..." << endl;
        searchHistoricalEvent(head, userHead, role);
        return;
    }

    cout << endl << "Press Enter to return to the menu..." << endl;
    cin.ignore();
    cin.get();
    searchHistoricalEvent(head, userHead, role);
}

// Deletes a historical event from the list
void deleteHistoricalEvent(HistoricalEvent*& head, int eventID) {
    if (!head) {
        cout << "No historical events recorded yet." << endl;
        return;
    }

    HistoricalEvent* temp = head;
    HistoricalEvent* prev = nullptr;

    // If head node is to be deleted
    if (temp && temp->id == eventID) {
        head = temp->next;
        delete temp;
        cout << "Event deleted successfully." << endl;
        return;
    }

    // Traverse to find event
    while (temp && temp->id != eventID) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Event with ID " << eventID << " not found." << endl;
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "Event deleted successfully." << endl;
}

// Allows editing an existing historical event
void redactHistoricalEvent(HistoricalEvent*& head, int eventID, User*& userHead, string role) {
    if (!head) {
        cout << "No historical events recorded yet." << endl;
        return;
    }

    HistoricalEvent* temp = head;
    while (temp && temp->id != eventID) {
        temp = temp->next;
    }

    if (!temp) {
        cout << "Event with ID " << eventID << " not found." << endl;
        return;
    }

    // Show current details
    cout << "Editing Event ID: " << temp->id << endl;
    cout << "Current Year: " << temp->year << endl;
    cout << "Current Event: " << temp->event << endl;
    cout << "Current Description: " << temp->description << endl;

    // Take new input
    cout << endl << "Enter new year (current: " << temp->year << "): ";
    int newYear;
    while (!(cin >> newYear)) {
        cin.clear(); cin.ignore();
        cout << "Invalid input. Enter a valid year: ";
    }

    cin.ignore();
    cout << "Enter new event name: ";
    string newEvent;
    getline(cin, newEvent);

    cout << "Enter new description: ";
    string newDesc;
    getline(cin, newDesc);

    // Update values
    temp->year = newYear;
    temp->event = newEvent;
    temp->description = newDesc;

    cout << endl << "Press Enter to return to the menu..." << endl;
    cin.ignore();
    cin.get();
    optionsMenu(head, userHead, role);
}
