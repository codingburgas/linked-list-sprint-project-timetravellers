#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include "user.h"



struct HistoricalEvent {
    int id;
    int year;
    std::string event;
    std::string description;
    HistoricalEvent* next;
};

void addHistoricalEvent(HistoricalEvent*& head, const std::string& event, int year, const std::string& description);
void saveEventsToFile(HistoricalEvent* head);
void loadEventsFromFile(HistoricalEvent*& head);
void optionsMenu(HistoricalEvent*& head, User*& userHead,  std::string role);
void displayHistoricalEvents(HistoricalEvent* head, User*& userHead, std::string role);
void searchHistoricalEvent(HistoricalEvent* head, User*& userHead, std::string role);
void deleteHistoricalEvent(HistoricalEvent*& head, int eventID);
void redactHistoricalEvent(HistoricalEvent*& head, int eventID, User*& userHead, std::string role);