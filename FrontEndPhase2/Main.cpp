#include<iostream>
#include "Admin.cpp"

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
        // if (user_action == 2){
        //     main_user.create();
        // }
        // if (user_action == 3){
        //     main_user.refund();
 
        // }
        if (user_action == 4){
            main_user.addcredit();
        }
    }

    cout << "Good bye" << "\n";

    return 0;
};