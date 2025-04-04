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
    int id;
    string username;
    string password;
    string salt;
    string role;
    User* next;
};

User* createUser(int id, const string& username, const string& password, const string& salt, const string& role);
void registerUser(User*& head);
User* loginUser(User* head);
void loadUsers(User*& head);

string hashPassword(const string& password);
string generateSalt();