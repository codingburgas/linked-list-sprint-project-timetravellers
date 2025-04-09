#pragma once
#include "user.h"
#include <iostream>
#include <fstream>
#include "events.h"



void adminPanel(User*& head, HistoricalEvent*& eventHead, std::string role);
void saveUsersToFile(User* head);