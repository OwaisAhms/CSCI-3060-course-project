#include<iostream>
#include "Admin.cpp"

int main() {
    string user_input;
    User main_user;
    Admin main_admin;
    
    cout << "Login as user or admin(U/A)" << "\n";
    cin >> user_input;
    if (user_input == "U"){
        main_user.login();
    }
    else{
        main_admin.login();
    }


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
        cout << "5: remove user (admin action)" << endl;
        cout << "6: Output all active users (admin action)" << endl;
        cout << "7: sell a game" << endl;
        cout << "8: buy a game" << endl;
        cout << "\n";
        cin >> user_action;

        if (user_action == 1){
            main_user.logout();
        }
        if (user_action == 2){
            main_admin.create();
        }
        if (user_action == 3){
            main_admin.refund();
        }
        if (user_action == 4){
            main_user.addcredit();
        }
        if (user_action == 5){
            main_admin.deleteuser();
        }
        if (user_action == 6){
            main_admin.All_active_accounts();
        }
        if (user_action == 7){
            main_user.sell();
        }
        if (user_action == 8){
            main_user.buy();
        }
    }

    cout << "Good bye" << "\n";

    return 0;
};