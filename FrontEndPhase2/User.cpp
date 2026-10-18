#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

class User {
    public:
        string username;
        string usertype;
        string password;
        bool is_logged_in;
        bool allow_transaction;
        bool allow_admin_transaction;
        double curr_credits;

        // User login method, checks for username and password, gives user transaction privilages
        void login(){
            string username_input;
            string password_input;
            bool correct = false;

            while(correct == false){
                cout << "please enter username" << "\n";
                cin >> username_input;

                // to be added: Check if username input is in current users file
                string mytext;
                ifstream MyFile("/Users/tahoo/OneDrive/Desktop/Software Quality Assurance/CSCI-3060-course-project/FrontEndPhase2/textfiles/CurrentUserAccounts.txt");

                while (getline (MyFile,mytext)){
                    stringstream s(mytext);
                    string name;
                    string type;
                    double credits;
                    s >> name;
                    s >> type;
                    s >> credits;
                    if (username_input == name){
                        cout << "user found" << "\n";
                        cout << name + " logged in" << "\n";
                        cout << "\n";

                        correct = true;
                        username = name;
                        is_logged_in = true;
                        allow_transaction = true;
                        usertype = type;
                        curr_credits = credits;

                        if (usertype == "AA"){
                            allow_admin_transaction = true;
                        }
                        break;
                    }
                }

                MyFile.close();

                // cout << "please enter password" << "\n";
                // cin >> password_input;

                // // to be added: Check if password is correct for that user
                // if (password == password_input){
                //     correct == true;
                //     is_logged_in == true;
                //     allow_transaction == true;
                //     if (usertype == "admin"){
                //         allow_admin_transaction == true;
                //     }
                // }
            }

        }

        // User logout method, remeoves transaction privilages
        void logout(){
            string user_input;
            cout << "would you like to log out Y/n" << "\n";
            cin >> user_input;
            if (user_input == "Y"){
                is_logged_in = false;
                allow_transaction = false;
                if (usertype == "AA"){
                    allow_admin_transaction = false; 
                }
            }
        }

        // Checks for User admin privilages 
        void create(){
            if (usertype == "AA"){
                string set_username;
                string set_password;
                string set_usertype;
                double set_credit;

                cout << "Enter username for new user" << "\n";
                cin >> set_username;

                cout << "Enter password for new user" << "\n";
                cin >> set_password;

                cout << "Enter usertype for new user" << "\n";
                cin >> set_usertype;

                cout << "Enter credits for new user" << "\n";
                cin >> set_credit;

                // to be added: add all values to new line in current users
                ofstream MyFile("/Users/tahoo/OneDrive/Desktop/Software Quality Assurance/CSCI-3060-course-project/FrontEndPhase2/textfiles/CurrentUserAccounts.txt",fstream::app);

                MyFile << "\n" + set_username + " " + set_usertype + " " + to_string(set_credit);

                MyFile.close();
            }
            else{
                cout << "only admin can create new users" << "\n";
            }
        }
};

int main() {
    User main_user;

    main_user.login();

    while(main_user.is_logged_in == true){
        int user_action = 0;

        cout << "Current User: " + main_user.username 
        + " User type: " + main_user.usertype 
        + " Current credits: " + to_string(main_user.curr_credits) << "\n";
        cout << "\n";

        cout << "enter what action you would like to perform" << "\n";
        cout << "1: logout" << "\n";
        cout << "2: create new user (admin action)" << "\n";
        cout << "\n";
        cin >> user_action;

        if (user_action == 1){
            main_user.logout();
        }
        if (user_action == 2){
            main_user.create();
        }
    }

    cout << "Good bye" << "\n";

    return 0;
};
