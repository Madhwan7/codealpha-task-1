#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdlib> // for system()

using namespace std;

class AuthSystem {
private:
    string filename = "users.txt";
    unordered_map<string, string> users;

    void loadUsers() {
        users.clear();
        ifstream file(filename);
        string uname, pass;
        while (file >> uname >> pass) {
            users[uname] = pass;
        }
        file.close();
    }

    void saveUser(const string& uname, const string& pass) {
        ofstream file(filename, ios::app);
        file << uname << " " << pass << endl;
        file.close();
    }

public:
    AuthSystem() {
        loadUsers();
    }

    void registerUser() {
        string uname, pass;

        cout << "Enter new username: ";
        cin >> uname;

        if (users.find(uname) != users.end()) {
            cout << "⚠️ Username already exists!\n";
            return;
        }

        cout << "Enter new password: ";
        cin >> pass;

        saveUser(uname, pass);
        cout << "✅ Registration successful!\n";

        // Create user file
        string userFile = uname + ".txt";
        ofstream ufile(userFile);
        ufile << "Welcome " << uname << "!\nThis is your personal file.\n";
        ufile.close();
    }

    bool login() {
        string uname, pass;
        int attempts = 3;

        while (attempts--) {
            cout << "Enter username: ";
            cin >> uname;
            cout << "Enter password: ";
            cin >> pass;

            loadUsers();

            if (users.find(uname) != users.end() && users[uname] == pass) {
                cout << "\n✅ Login successful!\n";
                openUserFile(uname);
                return true;
            } else {
                cout << "❌ Incorrect username or password. Attempts left: " << attempts << "\n";
            }
        }

        cout << "\n🚫 Login failed. Too many attempts.\n";
        return false;
    }

    void openUserFile(const string& uname) {
        string filePath;

        if (uname == "make") {
            filePath = "/Users/madhwan/Desktop/login";
        } else {
            filePath = uname + ".txt";
        }

        ifstream file(filePath);
        if (!file) {
            cout << "❌ Cannot open file at: " << filePath << endl;
            return;
        }
        file.close(); // Close before launching

        cout << "📂 Opening file: " << filePath << endl;

        // macOS: open file with default app
        string command = "open \"" + filePath + "\"";
        system(command.c_str());
    }
};

int main() {
    AuthSystem auth;
    int choice;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                auth.registerUser();
                break;
            case 2:
                auth.login();
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
