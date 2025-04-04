#pragma once
#include "user.h"
#include <iostream>
#include <fstream>
#include "events.h"

using namespace std;

void adminPanel(User*& head, HistoricalEvent*& eventHead, string role);
void saveUsersToFile(User* head);