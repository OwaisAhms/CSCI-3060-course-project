#include <string>
#include <iostream>

class User {
    public:
        std::string username;
        std::string usertype;
        std::string password;
        bool is_logged_in;
        bool allow_transaction;
        bool allow_admin_transaction;
        int max_credit;

        // User login method, checks for username and password, gives user transaction privilages
        void login(){
            std::string username_input;
            std::string password_input;
            bool correct = false;

            while(correct == false){
                std::cout << "please enter username" << "\n";
                std::cin >> username_input;

                // to be added: Check if username input is in current users file

                std::cout << "please enter password" << "\n";
                std::cin >> password_input;

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
            std::string user_input;
            std::cout << "would you like to log out Y/n" << "\n";
            std::cin >> user_input;
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
                std::cout << "only admin can create new users" << "\n";
            }
            std::string set_username;
            std::string set_password;
            std::string set_usertype;
            int set_credit;

            std::cout << "Enter username for new user" << "\n";
            std::cin >> set_username;

            std::cout << "Enter password for new user" << "\n";
            std::cin >> set_password;

            std::cout << "Enter usertype for new user" << "\n";
            std::cin >> set_usertype;

            std::cout << "Enter credits for new user" << "\n";
            std::cin >> set_credit;

            // to be added: add all values to new line in current users


        }
};

int main() {
    User main_user;

    main_user.login();

    return 0;
};
