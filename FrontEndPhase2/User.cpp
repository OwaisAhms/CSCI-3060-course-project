#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class User {
    public:
        string username;
        string usertype;
        string password;
        bool is_logged_in;
        bool allow_transaction;
        bool allow_admin_transaction;
        int max_credit;

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
                cout << "reading file";
                ifstream MyFile("CurrentUserAccounts.txt");

                while (getline (MyFile,mytext)){
                    cout << mytext;
                }

                MyFile.close();

                cout << "please enter password" << "\n";
                cin >> password_input;

                // to be added: Check if password is correct for that user
                if (password == password_input){
                    correct == true;
                    is_logged_in == true;
                    allow_transaction == true;
                    if (usertype == "admin"){
                        allow_admin_transaction == true;
                    }
                }
            }

        }

        // User logout method, remeoves transaction privilages
        void logout(){
            string user_input;
            cout << "would you like to log out Y/n" << "\n";
            cin >> user_input;
            if (user_input == "Y"){
                is_logged_in == false;
                allow_transaction == false;
                if (usertype == "admin"){
                    allow_admin_transaction == false;
                }
            }
        }

        // Checks for User admin privilages 
        void create(){
            if (usertype != "admin"){
                cout << "only admin can create new users" << "\n";
            }
            string set_username;
            string set_password;
            string set_usertype;
            int set_credit;

            cout << "Enter username for new user" << "\n";
            cin >> set_username;

            cout << "Enter password for new user" << "\n";
            cin >> set_password;

            cout << "Enter usertype for new user" << "\n";
            cin >> set_usertype;

            cout << "Enter credits for new user" << "\n";
            cin >> set_credit;

            // to be added: add all values to new line in current users


        }
};

int main() {
    User main_user;

    main_user.login();

    return 0;
};
