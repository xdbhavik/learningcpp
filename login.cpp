#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdio> // For remove() and rename()

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
    bool exists = false;
    cout << "\nEnter Your Username: ";
    getline(cin, newUsername);

    file.open("loginData.txt", ios::in);
    // FIXED: Only one set of getlines
    while (getline(file, userName, '*') && getline(file, email, '*') && getline(file, password, '\n')) {
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

    file.open("loginData.txt", ios::out | ios::app);
    file << newUsername << "*" << newEmail << "*" << newPass << endl;
    file.close();
    cout << "Registration Successful!";
}

void temp::login() {
    bool found = false;
    cout << "----------LOGIN----------" << endl;
    cout << "Enter Your Username: ";
    getline(cin, searchName);
    cout << "Enter Your Password: ";
    searchPass = getPass();

    file.open("loginData.txt", ios::in);
    while (getline(file, userName, '*') && getline(file, email, '*') && getline(file, password, '\n')) {
        if (userName == searchName && password == searchPass) {
            cout << "\nLogin Successful! Welcome " << userName << endl;
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Invalid Username or Password!";
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

void temp :: changePass() {
    string newPass;
    bool found = false;
cout << "\n--- CHANGE PASSWORD ---" << endl;
    cout << "\nEnter username: ";
    getline(cin, searchName);
    cout << "Enter email: ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);
    tempFile.open("temp.txt", ios::out);
    while (getline(file, userName, '*') && getline(file, email, '*') && getline(file, password, '\n')) {
        if (userName == searchName && email == searchEmail) {
            cout << "Acoount Verified!\nEnter New Password : ";
            newPass = getPass();
            tempFile << userName << "*" << email << "*" << newPass << endl;

            found = true;
        } else {
            tempFile << userName << "*" << email << "*" << password << endl;
        }

    }

    file.close();
    tempFile.close();

    remove("loginData.txt");
    rename("temp.txt", "loginData.txt");

    if(found) {
        cout << "\nPassword Updated Successfully!"<< endl;
    } else {
        cout << "\nUser Not Found" << endl;
    }

}

void temp :: deleteAccount() {
    bool found = false;
cout << "\n--- DELETE ACCOUNT ---" << endl;
    cout << "\nEnter username: ";
    getline(cin, searchName);
    cout << "Enter email: ";
    getline(cin, searchEmail);
    cout << "Enter password : ";
    searchPass = getPass();

    file.open("loginData.txt", ios::in);
    tempFile.open("temp.txt", ios::out);
    while (getline(file, userName, '*') && getline(file, email, '*') && getline(file, password, '\n')) {
        if (userName == searchName && email == searchEmail && password == searchPass) {
            found = true;
            continue;
        } else {
            tempFile << userName << "*" << email << "*" << password << endl;
        }

    }

    file.close();
    tempFile.close();

    remove("loginData.txt");
    rename("temp.txt", "loginData.txt");

    if(found) {
        cout << "\nAccount Deleted Successfully!"<< endl;
    } else {
        cout << "\nUser Not Found" << endl;
    }

}