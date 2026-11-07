#include "Admin.h"

int main() {
    string user_input;
    string username;
    User main_user;
    Admin main_admin;
    int user_action = 0;
    
    cout << "Login as user or admin(U/A)" << "\n";
    cin >> user_input;
    cout << "Please enter Username" << "\n";
    cin >> username;
    if (user_input == "A"){
        cout << main_admin.login(username,false) << "\n";
    }
    else{
        cout << main_user.login(username,false) << "\n";
    }

    User& current_user = user_input == "A" ? static_cast<User&>(main_admin) : main_user;

    while(current_user.is_logged_in){
        user_action = 0;

        cout << "Current User: " + current_user.username
        + " User type: " + current_user.usertype
        + " Current credits: " + to_string(current_user.curr_credits) << "\n";
        cout << "\n";

        cout << "enter what action you would like to perform" << "\n";
        cout << "1: logout" << "\n";
        cout << "2: create new user (admin action)" << "\n";
        cout << "3: refund (admin action)" << endl;
        cout << "4: add credit" << endl;
        cout << "5: remove user (admin action)" << endl;
        cout << "6: Output all active users (admin action)" << endl;
        cout << "7: sell a game" << endl;
        cout << "8: buy a game" << endl;
        cout << "\n";
        string action_input;
        if (!getline(cin >> ws, action_input)){
            break;
        }
        stringstream action_stream(action_input);
        if (!(action_stream >> user_action)){
            cout << "Invalid action. Enter a number from 1 to 8." << endl;
            continue;
        }

        if (user_action == 1){
            string input;
            cout << "would you like to log out Y/n" << "\n";
            cin >> input;
            cout << current_user.logout(input) << "\n";
        }

        if (user_action == 2){
            string new_user;

            cout << "Enter info for new user" << "\n";
            getline(cin >> ws, new_user);
            cout << main_admin.create(new_user,false) << "\n";
        }

        if (user_action == 3){
            main_admin.refund();
        }

        if (user_action == 4){
            if (user_input == "A"){
                main_admin.addcredit();
            }
            else{
                main_user.addcredit();
            }
        }

        if (user_action == 5){
            string del_user;
            cout << "Enter user to be deleted ";
            cin >> del_user;
            main_admin.deleteuser(del_user, false);
        }

        if (user_action == 6){
            main_admin.All_active_accounts();
        }

        if (user_action == 7){
            if (user_input == "A"){
                string game_name;
                string price;

                cout << "Enter the name of the game you want to sell: ";
                cin >> game_name;
                cout << "Enter the price for said game: ";
                cin >> price;

                main_admin.sell(game_name, price);
            }
            else{
                string game_name;
                string price;
                main_user.sell(game_name, price);
            }
        }

        if (user_action == 8){
            if (user_input == "A"){
                string game_name;
                cout << "Enter the name of the game you want to buy: ";
                cin >> game_name;
                string seller_name;
                cout << "Enter seller user: ";
                cin >> seller_name;
                main_admin.buy(game_name,seller_name,false);
            }
            else{
                string game_name;
                string sellar_name;
                main_user.buy(game_name,sellar_name, false);
            }
        }
    }

    cout << "Good bye" << "\n";

    return 0;
};