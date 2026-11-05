#include "Admin.h"

string Admin::create(string set_user,bool istest){
    if (usertype == "AA"){
        string filepath; 
        string set_username;
        string set_usertype;
        string set_credit;

        if (istest == false){
            filepath = "../../Data/CurrentUserAccounts.txt";
        }
        else{
            filepath = "../../../../Data/CurrentUserAccounts.txt";
        }
        ofstream MyFile(filepath,fstream::app);
        stringstream s(set_user);
        if (!(s >> set_username >> set_usertype >> set_credit)){
            return "Invalid user info. Enter username, user type, and credit.";
        }

        string user_info = set_username + "________ " + set_usertype + " " + set_credit;

        MyFile << "\n" + user_info;

        MyFile.close();
        return user_info + " added to Current Users";
    }
    else{
        return "only admin can create new users";
    }
}

// Delete User
void Admin::deleteuser(){
    if (usertype == "AA"){

        string user_delete;
        
        cout << "Enter username for user to be deleted" << "\n";
        cin >>  user_delete;

        // checks to see if the user exists and is not the current user and would remove all their perms.
        ifstream MyFile("../../Data/CurrentUserAccounts.txt");

        ofstream tempFile("../../Data/temp.txt");

        string myText;
        bool user_found = false;
        string line;

        while (getline(MyFile, line))
        {
            if (line.find(user_delete) != string::npos){
                tempFile << line << "\n";
                
            }
            else{
                user_found = true;
                cout << "User has been deleted" << "\n";
            }
        }
        
        MyFile.close();
        tempFile.close();

        remove("../../Data/CurrentUserAccounts.txt");
        rename("../../Data/temp.txt", "../../Data/CurrentUserAccounts.txt");


        ofstream MyFile2("../../Data/DailyTransactionFIles/DailyTransactionFIleDelete",fstream::app);

        MyFile2 << "02_" + user_delete + "_" + "AA\n";

        MyFile2.close();

        if(user_found == false){
            cout << "User not found" << "\n";
        }

    }
    else{
        cout << "only admin can delete users" << "\n";
    }
}

void Admin::refund(){

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

    ifstream MyFile("../../Data/CurrentUserAccounts.txt");

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
void Admin::All_active_accounts(){
    // Will output all active accounts and relevant information
    ifstream MyFile("../../Data/CurrentUserAccounts.txt");

    string line;

    while (getline(MyFile, line))
    {
        cout << line + "\n";
    }
    MyFile.close();
}