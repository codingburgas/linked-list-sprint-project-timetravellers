#include "../Header/menu.h"
#include "../Header/user.h"

User* createUser(const string& username, const string& passwordHash, const string& salt) {
    User* newUser = new User;
    newUser->username = username;
    newUser->password = passwordHash;
    newUser->salt = salt;
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

    cout << "Enter a new username: ";
    cin >> username;

    cout << "Enter a password: ";
    password = getPassword();

    string salt = generateSalt();
    string saltedPassword = salt + password;
    string hashedPassword = hashPassword(saltedPassword);

    User* newUser = createUser(username, hashedPassword, salt);

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

    ofstream outFile("TimeTravellers/Data/users.txt", ios::app);
    outFile << username << " " << salt << " " << hashedPassword << endl;
    outFile.close();
    system("cls");
    mainMenu();
}

bool loginUser(User* head) {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

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
                cout << "Login successful!" << endl;
                return true;
            }
        }
        temp = temp->next; 
    }

    cout << "Login failed. Invalid username or password." << endl;
    return false;
}



void loadUsers(User*& head) {
    ifstream inFile("TimeTravellers/Data/users.txt");
    string username, salt, passwordHash;

    while (inFile >> username >> salt >> passwordHash) {
        User* newUser = createUser(username, passwordHash, salt);

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