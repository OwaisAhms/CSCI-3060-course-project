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
                ifstream MyFile("textfiles/CurrentUserAccounts.txt");

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

        void sell(){
            if (usertype == "BS"){
                cout << "You are not authroized to make this function" << "\n";
            }
            else{
                string game_name;
                string price;

                cout << "Give the name of the game: " << "\n";;
                cin >> game_name;

                cout << "Give the price of the game: " << "\n";;
                cin >> price;

                // if game name is unique and the price isn't over 999.99
                // add game to list of games
                // allow transactions false
                ofstream file("textfiles/AvailableGamesFiles.txt");
                file <<  game_name << ", " << price << "\n";
                file.close;
            }
        }

        void buy(){
            if (usertype == "SS"){
                cout << "You are not authroized to make this function" << "\n";
            }
            else{
                string game_name;
                string buyer_username;
                string seller_username;

                cout << "Give the buyer username: " << "\n";;
                cin >> buyer_username;

                cout << "Give the seller username: " << "\n";;
                cin >> seller_username;

                // if game exists and buyer has equal or greater than the amount needed to purchase the game, and the game isnt the buyers library
                // debit buyer, credit seller (increase/ decrease curr_credits)
                // add game to buyers collection


                cout << "Enter game name you wish to purchase: " << "\n";
                cin >> game_name;

                ifstream file("textfiles/AvailableGamesFiles.txt");

                bool game_found = false;
                string game_data;
                int credits = 0;
                string credit;

                while(getline(file,game)){
                    if(game.contains(game_name)){
                        game_found = true;
                        game_data = game;
                    }
                }

                file.close;
                if (game_found){
                    size_t pos = game_data.find(',');
                    credit = game_data.substr(pos + 1, game_data.length);
                    credits = stoi(credit);

                    ifstream MyFile("textfiles/CurrentUserAccounts.txt");

                    ofstream tempFile("textfiles/temp.txt");

                    bool user_found = false;

                    while (getline(MyFile, line))
                    {
                        if (line.contains(seller_username)){
                            pos = line.find(',');
                            newLine = line.substr(0,pos);
                            credits += stoi(credit);

                            tempFile << line << itos(credits) << "\n";
                        
                        }
                        if (line.contains(buyer_username)){
                            pos = line.find(',');
                            newLine = line.substr(0,pos);
                            credits = stoi(credit) - credits;

                            tempFile << line << itos(credits) << "\n";
                        
                        }
                    }
                
                    MyFile.close;
                    tempFile.close;

                    remove("textfiles/MyFile.txt");
                    rename("textfiles/tempFile.txt", "MyFile.txt");

                }

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
                recieving_username = username;

            }

            ifstream  MyFile("textfiles/CurrentUserAccounts.txt");

            if (!MyFile.is_open()){
                cout << "Could not open User Account file!" << endl;
                return;

            }

            user_found = false;
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

// int main() {
//     User main_user;

//     main_user.login();

//     while(main_user.is_logged_in == true){
//         int user_action = 0;

//         cout << "Current User: " + main_user.username 
//         + " User type: " + main_user.usertype 
//         + " Current credits: " + to_string(main_user.curr_credits) << "\n";
//         cout << "\n";

//         cout << "enter what action you would like to perform" << "\n";
//         cout << "1: logout" << "\n";
//         cout << "2: create new user (admin action)" << "\n";
//         cout << "3: refund (admin action)" << endl;
//         cout << "4: add credit" << endl;
//         cout << "\n";
//         cin >> user_action;

//         if (user_action == 1){
//             main_user.logout();
//         }
//         // if (user_action == 2){
//         //     main_user.create();
//         // }
//         // if (user_action == 3){
//         //     main_user.refund();
//         // }
//         if (user_action == 4){
//             main_user.addcredit();
//         }
//     }

//     cout << "Good bye" << "\n";

//     return 0;
// };