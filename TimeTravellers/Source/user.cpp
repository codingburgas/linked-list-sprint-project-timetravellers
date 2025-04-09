#include "../Header/menu.h"
#include "../Header/user.h"
using namespace std;
User* createUser(int id, const string& username, const string& passwordHash, const string& salt, const string& role) {
    User* newUser = new User;
    newUser->id = id;
    newUser->username = username;
    newUser->password = passwordHash;
    newUser->salt = salt;
    newUser->role = role;
    newUser->next = nullptr;
    return newUser;
}

string hashPassword(const string& password) {
    hash<string> hasher;
    size_t hashValue = hasher(password);

    stringstream ss;
    ss << hex << hashValue;
    return ss.str();
}

string generateSalt() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(33, 126);

    string salt;
    for (int i = 0; i < 16; ++i) {
        salt += static_cast<char>(dist(gen));
    }

    return salt;
}

string getPassword() {
    string password = "";
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 13) {
            break;
        }
        else if (ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            cout << "*";
        }
    }

    cout << endl;
    return password;
}

void registerUser(User*& head) {
    string username, password;

    cout << "Enter a new username (or type 'back' to return): ";
    cin >> username;

    if (username == "back") {
        system("cls");
        mainMenu();
        return;
    }

    cout << "Enter a password: ";
    password = getPassword();

    string salt = generateSalt();
    string saltedPassword = salt + password;
    string hashedPassword = hashPassword(saltedPassword);

    string role = "user";

    int newId = 1;
    User* temp = head;
    while (temp != nullptr) {
        if (temp->id >= newId)
            newId = temp->id + 1;
        temp = temp->next;
    }

    User* newUser = createUser(newId, username, hashedPassword, salt, role);

    if (head == nullptr) {
        head = newUser;
    }
    else {
        temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newUser;
    }

    ofstream outFile("TimeTravellers/Data/users.txt", ios::app);
    outFile << newId << " " << username << " " << salt << " " << hashedPassword << " " << role << endl;
    outFile.close();

    system("cls");
    cout << "Registration successful. Please log in." << endl;
    loginUser(head);
}

User* loginUser(User* head) {
    while (true) {
        string username, password;

        cout << "Enter username (or type 'back' to return): ";
        cin >> username;

        if (username == "back") {
            system("cls");
            mainMenu();
            return nullptr;
        }

        cout << "Enter password: ";
        password = getPassword();

        User* temp = head;
        while (temp != nullptr) {
            if (temp->username == username) {
                string storedSalt = temp->salt;
                string storedPasswordHash = temp->password;

                string saltedPassword = storedSalt + password;
                string hashedPassword = hashPassword(saltedPassword);

                if (hashedPassword == storedPasswordHash) {
                    cout << endl << "Login successful!" << endl;
                    return temp;
                }
                break;
            }
            temp = temp->next;
        }

        cout << endl << "Login failed. Invalid username or password. Please try again." << endl;
    }
}

void loadUsers(User*& head) {
    ifstream inFile("TimeTravellers/Data/users.txt");
    int id;
    string username, salt, passwordHash, role;

    while (inFile >> id >> username >> salt >> passwordHash >> role) {
        User* newUser = createUser(id, username, passwordHash, salt, role);

        if (head == nullptr) {
            head = newUser;
        }
        else {
            User* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newUser;
        }
    }

    inFile.close();
}