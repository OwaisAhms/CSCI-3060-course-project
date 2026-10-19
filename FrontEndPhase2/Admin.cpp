#include <iostream>
#include "User.cpp"

class Admin: public User {
    public:
        // Create user
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
                ofstream MyFile("textfiles/CurrentUserAccounts.txt",fstream::app);

                MyFile << "\n" + set_username + " " + set_usertype + ", " + to_string(set_credit);

                MyFile.close();
            }
            else{
                cout << "only admin can create new users" << "\n";
            }
        }

        // Delete User
        void deleteuser(){
            if (usertype == "AA"){

                string user_delete;
                
                cout << "Enter username for user to be deleted" << "\n";
                cin >>  user_delete;

                // checks to see if the user exists and is not the current user and would remove all their perms.
                ifstream MyFile("textfiles/CurrentUserAccounts.txt");

                ofstream tempFile("textfiles/temp.txt");

                string myText;
                bool user_found = false;

                while (getline(MyFile, line))
                {
                    if (line.contains(user_delete)){
                        tempFile << line << "\n";
                        
                    }
                    else{
                        user_found = true;
                        cout << "User has been deleted" << "\n";
                    }
                }
                
                MyFile.close;
                tempFile.close;

                remove("textfiles/MyFile.txt");
                rename("textfiles/tempFile.txt", "MyFile.txt");


                if(user_found == false){
                    cout << "User not found" << "\n";
                }

            }
            else{
                cout << "only admin can delete users" << "\n";
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
        void All_active_accounts(){
            // Will output all active accounts and relevant information
        }
};