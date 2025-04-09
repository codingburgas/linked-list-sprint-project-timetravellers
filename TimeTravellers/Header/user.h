#pragma once
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <random>
#include <string>



struct User {
    int id;
    std::string username;
    std::string password;
    std::string salt;
    std::string role;
    User* next;
};

User* createUser(int id, const std::string& username, const std::string& password, const std::string& salt, const std::string& role);
void registerUser(User*& head);
User* loginUser(User* head);
void loadUsers(User*& head);

std::string hashPassword(const std::string& password);
std::string generateSalt();