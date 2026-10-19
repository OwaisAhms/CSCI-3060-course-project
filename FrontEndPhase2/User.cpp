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

        void deleteuser(){
            if (usertype == "AA"){

                string user_delete;
                cout << "Enter username for user to be deleted" << "\n";
                cin >>  user_delete;

                // checks to see if the user exists and is not the current user and would remove all their perms.
            }
            else{
                cout << "only admin can delete users" << "\n";
            }
        }

        void sell(){
            if (usertype == "BS"){
                cout << "You are not authroized to make this function" << "\n";
            }
            else{
                string game_name;
                double price;

                // if game name is unique and the price isn't over 999.99
                // create game object
                // add game to list of games
                // allow transactions false

            }
        }

        void buy(){
            if (usertype == "SS"){
                cout << "You are not authroized to make this function" << "\n";
            }
            else{
                string game_name;

                // if game exists and buyer has equal or greater than the amount needed to purchase the game, and the game isnt the buyers library
                // debit buyer, credit seller (increase/ decrease curr_credits)
                // add game to buyers collection
            }
        }

        void refund(){

            if (usertype != "AA"){
                cout << "You arent allowed to do this action!" << endl;
                return;

            }

            string buyer_username;
            string seller_username;
            double refund_amount;

            cout << "Give the buyer username: ";
            cin >> buyer_username;

            cout << "Give the seller username: ";
            cin >> seller_username;

            cout << "Enter the refund amount: ";
            cin >> refund_amount;

            ifstream MyFile("textfiles/CurrentUserAccounts.txt");

            if(!MyFile.is_open()){
                cout << "Could not open User Account file!" << endl;
                return;

            }

            string myText;
            bool buyer_found = false;
            bool seller_found = false;

            while(getline(MyFile, myText)){

                if(myText.find(buyer_username) != string::npos){
                    buyer_found = true;

                }

                if(myText.find(seller_username) != string::npos){
                    seller_found = true;

                }

            }

            MyFile.close();

            if(buyer_found == false){
                cout << "Buyer does not exist" << endl;
                return;

            }
            
            if(seller_found == false){
                cout << "Seller does not exist" << endl;
                return;

            }

            if(refund_amount <= 0){
                cout << "Invalid refund amount" << endl;
                return;

            }

        }

        void addcredit(){

            if (!is_logged_in){
                cout << "You must be logged in!" << endl;
                return;

            }

            double amount;
            string recieving_username;
            string recieving_usertype;
            bool user_found = false;

            cout << "Add credit: " << endl;
            cin >> amount;

            if (amount <= 0 || amount > 1000.00){
                cout << "You cannot add this credit amount!" << endl;
                return;

            }

            if (usertype == "AA"){
                cout << "Enter username: " << endl;
                cin >> recieving_username;

            }
            else{
                recieving_username == username;

            }

            ifstream  MyFile("textfiles/CurrentUserAccounts.txt");

            if (!MyFile.is_open()){
                cout << "Could not open User Account file!" << endl;
                return;

            }

            bool user_found = false;
            string myText;

            while(getline(MyFile, myText)){
                if (myText.find(recieving_username) != string::npos){
                    user_found = true;
                    break;

                }

            }

            MyFile.close();

            if (user_found == false){
                cout << "User does not exist!" << endl;
                return;

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
        cout << "3: refund (admin action)" << endl;
        cout << "4: add credit" << endl;
        cout << "\n";
        cin >> user_action;

        if (user_action == 1){
            main_user.logout();
        }
        if (user_action == 2){
            main_user.create();
        }
        if (user_action == 3){
            main_user.refund();

        }
        if (user_action == 4){
            main_user.addcredit();
        }
    }

    cout << "Good bye" << "\n";

    return 0;
};
