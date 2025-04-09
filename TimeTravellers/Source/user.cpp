#include "../Header/menu.h"
#include "../Header/user.h"
using namespace std;

// Function to create a new User object with the provided details
User* createUser(int id, const string& username, const string& passwordHash, const string& salt, const string& role) {
    User* newUser = new User;
    newUser->id = id;
    newUser->username = username;
    newUser->password = passwordHash;
    newUser->salt = salt;
    newUser->role = role;
    // Next is set to null for linked list
    newUser->next = nullptr; 
    return newUser;
}

// Function to hash a password using std::hash
string hashPassword(const string& password) {
    hash<string> hasher;
    // Hash the string
    size_t hashValue = hasher(password); 

    stringstream ss;
    // Convert hash to hexadecimal string
    ss << hex << hashValue; 
    return ss.str();
}

// Generates a 16-character random salt from printable ASCII characters
string generateSalt() {
    random_device rd;
    // Random number generator
    mt19937 gen(rd()); 
    // Printable characters range
    uniform_int_distribution<int> dist(33, 126); 

    string salt;
    for (int i = 0; i < 16; ++i) {
        // Append random character to salt
        salt += static_cast<char>(dist(gen)); 
    }

    return salt;
}

// Securely gets a password input from the user while masking input with '*'
string getPassword() {
    string password = "";
    char ch;

    while (true) {
        // Read character without echoing it
        ch = _getch();
        // Enter key (ASCII 13)
        if (ch == 13) { 
            break;
        }
        // Backspace
        else if (ch == 8) { 
            if (!password.empty()) {
                password.pop_back();
                // Erase the last asterisk
                cout << "\b \b"; 
            }
        }
        else {
            password.push_back(ch);
            // Show asterisk instead of character
            cout << "*"; 
        }
    }

    cout << endl;
    return password;
}

// Handles new user registration
void registerUser(User*& head) {
    string username, password;

    cout << "Enter a new username (or type 'back' to return): ";
    cin >> username;

    if (username == "back") {
        system("cls");
        // Return to main menu
        mainMenu(); 
        return;
    }

    cout << "Enter a password: ";
    // Masked password input
    password = getPassword(); 

    // Generate salt and hash the salted password
    string salt = generateSalt();
    string saltedPassword = salt + password;
    string hashedPassword = hashPassword(saltedPassword);

    string role = "user"; // Default role

    // Determine the next user ID
    int newId = 1;
    User* temp = head;
    while (temp != nullptr) {
        if (temp->id >= newId)
            newId = temp->id + 1;
        temp = temp->next;
    }

    // Create and append the new user to the linked list
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

    // Save the new user to the users file
    ofstream outFile("TimeTravellers/Data/users.txt", ios::app);
    outFile << newId << " " << username << " " << salt << " " << hashedPassword << " " << role << endl;
    outFile.close();

    system("cls");
    cout << "Registration successful. Please log in." << endl;
    // Redirect to login after registration
    loginUser(head); 
}

// Handles user login and authentication
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

                // Recreate the salted password and hash it
                string saltedPassword = storedSalt + password;
                string hashedPassword = hashPassword(saltedPassword);

                if (hashedPassword == storedPasswordHash) {
                    cout << endl << "Login successful!" << endl;
                    // Return the logged in user
                    return temp; 
                }
                // Break if username matches but password doesn't
                break; 
            }
            temp = temp->next;
        }

        cout << endl << "Login failed. Invalid username or password. Please try again." << endl;
    }
}

// Loads all users from the file and stores them in a linked list
void loadUsers(User*& head) {
    ifstream inFile("TimeTravellers/Data/users.txt");
    int id;
    string username, salt, passwordHash, role;

    // Read user info line by line
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
