#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;


struct HistoricalEvent {
    int year;
    string event;
    string description;
    HistoricalEvent* next;
};

void addHistoricalEvent(HistoricalEvent*& head, const string& event, int year, const string& description);
void saveEventsToFile(HistoricalEvent* head);
void loadEventsFromFile(HistoricalEvent*& head);
void optionsMenu(HistoricalEvent*& head);