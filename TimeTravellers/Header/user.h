#pragma once
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <random>
#include <string>

using namespace std;

struct User {
    string username;
    string password;
    string salt;
    User* next;
};

User* createUser(const string& username, const string& password, const string& salt);
void registerUser(User*& head);
bool loginUser(User* head);
void loadUsers(User*& head);

string hashPassword(const string& password);
string generateSalt();