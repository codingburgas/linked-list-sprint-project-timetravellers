#include "../Header/addEvents.h"
#include <fstream>
#include <limits>

void optionsMenu(HistoricalEvent*& head) {
    int choice;

    while (true) {
        cout << "==============================" << endl;
        cout << "      HISTORY APP MENU       " << endl;
        cout << "==============================" << endl;
        cout << "1. View Historical Events" << endl;
        cout << "2. Add a Historical Event" << endl;
        cout << "3. Search for an Event" << endl;
        cout << "4. Delete an Event" << endl;
        cout << "5. Exit" << endl;
        cout << "==============================" << endl;
        cout << "Select an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1: {
            system("cls");
        }

        case 2: {
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

            addHistoricalEvent(head, event, year, description);
            cin.ignore();
            cout << "Event added successfully!" << endl;
            system("cls");
            break;
        }

        case 5:
            saveEventsToFile(head);
            cout << "Saving data... Exiting program. Goodbye!" << endl;
            return;

        default:
            cout << "That's not a valid option. Try again." << endl;
            cin.ignore();
            system("cls");
            break;
        }
    }
}

void addHistoricalEvent(HistoricalEvent*& head, const string& event, int year, const string& description) {
    HistoricalEvent* newEvent = new HistoricalEvent{ year, event, description, nullptr };

    if (!head) {
        head = newEvent;
    }
    else {
        HistoricalEvent* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newEvent;
    }
}

void saveEventsToFile(HistoricalEvent* head) {
    ofstream file("TimeTravellers/Data/events.txt");

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    HistoricalEvent* temp = head;
    while (temp) {
        file << temp->year << " - " << temp->event << " : " << temp->description << endl;
        temp = temp->next;
    }

    file.close();
}

void loadEventsFromFile(HistoricalEvent*& head) {
    ifstream file("TimeTravellers/Data/events.txt");

    if (!file) {
        cout << "No previous data found. Starting fresh.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        int year;
        string event, description;

        size_t firstDash = line.find(" - ");
        size_t colon = line.find(" : ");

        if (firstDash == string::npos || colon == string::npos) {
            continue;
        }

        year = stoi(line.substr(0, firstDash));
        event = line.substr(firstDash + 3, colon - (firstDash + 3));
        description = line.substr(colon + 3);

        addHistoricalEvent(head, event, year, description);
    }

    file.close();
}