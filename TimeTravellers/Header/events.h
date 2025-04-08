#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include "user.h"

using namespace std;

struct HistoricalEvent {
    int id;
    int year;
    string event;
    string description;
    HistoricalEvent* next;
};

void addHistoricalEvent(HistoricalEvent*& head, const string& event, int year, const string& description);
void saveEventsToFile(HistoricalEvent* head);
void loadEventsFromFile(HistoricalEvent*& head);
void optionsMenu(HistoricalEvent*& head, User*& userHead,  string role);
void displayHistoricalEvents(HistoricalEvent* head, User*& userHead, string role);
void searchHistoricalEvent(HistoricalEvent* head, User*& userHead, string role);
void deleteHistoricalEvent(HistoricalEvent*& head, int eventID);
void redactHistoricalEvent(HistoricalEvent*& head, int eventID, User*& userHead, string role);