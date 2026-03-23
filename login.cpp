#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdio> // For remove() and rename()
#include <random>
#include <sstream>

using namespace std;

class temp {
    string userName, email, password;
    string searchName, searchPass, searchEmail;
    fstream file, tempFile;

    string getPass() {
        string pass = "";
        char ch;
        while ((ch = _getch()) != 13) {
            if (ch == 8) {
                if (!pass.empty()) {
                    pass.pop_back();
                    cout << "\b \b";
                }
            } else {
                pass.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;
        return pass;
    }

    string simpleHash(string input) {
        unsigned long hash = 5381;
        for (char c : input) {
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }
        
        // Convert the math result into a Hexadecimal string 
        // (so it looks like a real, professional hash)
        stringstream ss;
        ss << hex << hash;
        return ss.str();
    }

    string generateSalt(int length = 16) {
        // 1. Define the characters allowed in the salt
        const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
        
        // 2. Setup the Random Device (Hardware-level randomness)
        std::random_device rd; 
        
        // 3. Initialize the Mersenne Twister pseudo-random generator with the random device
        std::mt19937 generator(rd()); 
        
        // 4. Define the range (from index 0 to the last character of charset)
        std::uniform_int_distribution<int> distribution(0, charset.length() - 1);

        string salt = "";
        // 5. Build the string
        for (int i = 0; i < length; ++i) {
            salt += charset[distribution(generator)];
        }

        return salt;
    }
public:
    void login();
    void signUp();
    void forgot();
    void changePass();
    void deleteAccount();
} obj;

int main() {
    char choice = ' ';
    while (choice != '4') {
        cout << "\n1- Login\n2- Sign Up\n3- Forgot Password\n4- Change Password\n5- Delete Account\n6- Exit" << endl;
        cout << "Enter Your Choice :: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case '1': obj.login(); break;
            case '2': obj.signUp(); break;
            case '3': obj.forgot(); break;
            case '4': obj.changePass(); break;
            case '5': obj.deleteAccount(); break;
            case '6': return 0;
            default: cout << "Invalid Selection!";
        }
    }
    return 0;
}

void temp::signUp() {
    string newUsername, newEmail, newPass;
    string dummyHash, dummySalt;
    bool exists = false;
    cout << "\nEnter Your Username: ";
    getline(cin, newUsername);

    file.open("loginData.txt", ios::in);
    // FIXED: Only one set of getlines
    while (getline(file, userName, '*') && 
           getline(file, email, '*') && 
           getline(file, dummyHash, '*') && 
           getline(file, dummySalt, '\n')) {
        if (userName == newUsername) {
            exists = true;
            break;
        }
    }
    file.close();

    if (exists) {
        cout << "User already exists!" << endl;
        return;
    }

    cout << "Enter Your Email Address: ";
    getline(cin, newEmail);
    cout << "Enter a Secure Password: ";
    newPass = getPass();

    string salt = generateSalt();
    string hashedPassword = simpleHash(newPass + salt);

    file.open("loginData.txt", ios::out | ios::app);
    file << newUsername << "*" << newEmail << "*" << hashedPassword << "*" << salt << endl;
    file.close();
    cout << "Registration Successful!";
}

void temp::login() {
    bool found = false;
    string storedHash, storedSalt;
    cout << "----------LOGIN----------" << endl;
    cout << "Enter Your Username: ";
    getline(cin, searchName);
    cout << "Enter Your Password: ";
    searchPass = getPass();



    file.open("loginData.txt", ios::in);
    while (getline(file, userName, '*') && getline(file, email, '*') && getline(file, storedHash, '*') && getline(file, storedSalt, '\n')) {
        if (userName == searchName) {
            string checkHash = simpleHash(searchPass + storedSalt);

            if (checkHash == storedHash) {
                cout << "Login Successful! " << userName << endl;
                found = true;
                break;
            } else {
                cout << "\nIncorrect Password" << endl;
                found = true;
                break;
            }
        }
    }
    file.close();
    if (!found) cout << "User not found.";
}

void temp::forgot() {
    bool found = false;
    cout << "\nEnter username: ";
    getline(cin, searchName);
    cout << "Enter email: ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);
    while (getline(file, userName, '*') && getline(file, email, '*') && getline(file, password, '\n')) {
        if (userName == searchName && email == searchEmail) {
            cout << "\nAccount found! Password: " << password << endl;
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Record not found!";
}

void temp::changePass() {
    string newPass;
    bool found = false;
    string storedHash, storedSalt;

    cout << "\n--- CHANGE PASSWORD ---" << endl;
    cout << "Enter username: ";
    getline(cin, searchName);
    cout << "Enter email: ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    // UPDATED: Read 4 items
    while (getline(file, userName, '*') && 
           getline(file, email, '*') && 
           getline(file, storedHash, '*') && 
           getline(file, storedSalt, '\n')) {
        
        if (userName == searchName && email == searchEmail) {
            cout << "Account Verified!\nEnter New Password : ";
            newPass = getPass();
            
            // Generate NEW security data
            string newSalt = generateSalt();
            string newHash = simpleHash(newPass + newSalt);
            
            // Write the NEW 4 items
            tempFile << userName << "*" << email << "*" << newHash << "*" << newSalt << endl;
            found = true;
        } else {
            // Write the OLD 4 items exactly as they were
            tempFile << userName << "*" << email << "*" << storedHash << "*" << storedSalt << endl;
        }
    }

    file.close();
    tempFile.close();
    remove("loginData.txt");
    rename("temp.txt", "loginData.txt");

    if(found) cout << "\nPassword Updated Successfully!"<< endl;
    else cout << "\nUser Not Found" << endl;
}   

void temp::deleteAccount() {
    bool found = false;
    string storedHash, storedSalt;

    cout << "\n--- DELETE ACCOUNT ---" << endl;
    cout << "Enter username: ";
    getline(cin, searchName);
    cout << "Enter email: ";
    getline(cin, searchEmail);
    cout << "Enter password: ";
    searchPass = getPass();

    file.open("loginData.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    // UPDATED: Read 4 items
    while (getline(file, userName, '*') && 
           getline(file, email, '*') && 
           getline(file, storedHash, '*') && 
           getline(file, storedSalt, '\n')) {
        
        if (userName == searchName && email == searchEmail) {
            // Verify password using hashes!
            string checkHash = simpleHash(searchPass + storedSalt);
            
            if (checkHash == storedHash) {
                found = true;
                continue; // Skip writing to tempFile (this deletes them!)
            }
        }
        
        // If it's not them, OR they got the password wrong, keep them in the file
        tempFile << userName << "*" << email << "*" << storedHash << "*" << storedSalt << endl;
    }

    file.close();
    tempFile.close();
    remove("loginData.txt");
    rename("temp.txt", "loginData.txt");

    if(found) cout << "\nAccount Deleted Successfully!"<< endl;
    else cout << "\nInvalid Credentials or User Not Found" << endl;
}