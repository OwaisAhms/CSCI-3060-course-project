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
        if (set_username.length() > 15){
            return "Username must be under 15 charcters";
        }
        while (set_username.length() != 15){
            set_username.append("_");
        }

        string user_info = set_username + " " + set_usertype + " " + set_credit;

        MyFile << "\n" + user_info;

        MyFile.close();
        return user_info + " added to Current Users";
    }
    else{
        return "only admin can create new users";
    }
}

// Delete User
string Admin::deleteuser(string user_delete,bool istest){
    
    //cout << filesystem::current_path() << endl;
    if (usertype == "AA"){
        //cout << user_delete << "\n";
        //string user_delete;
        //
        // cout << "Enter username for user to be deleted" << "\n";
        // cin >>  user_delete;

        // checks to see if the user exists and is not the current user and would remove all their perms.
        string filepath; 
        string filepath2;


        if (istest == false){
            filepath = "../../Data/CurrentUserAccounts.txt";
            filepath2 = "../../Data/temp.txt";
        }
        else{
            filepath = "../../../../Data/CurrentUserAccounts.txt";
            filepath2 = "../../../../Data/temp.txt";
        }



        ifstream MyFile(filepath);
        if (!MyFile.is_open()){
            return "error opening accounts file";
        }
        ofstream tempFile(filepath2);
        
        

        string myText;
        bool user_found = false;
        string line;

        while (getline(MyFile, line))
        {
            // cout << line << "\n";
            if (line.find(user_delete) != string::npos){
                user_found = true;
                cout << "user has been deleted" << "\n";
                
            }
            else{

                tempFile << line << "\n";
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
            cout << "user does not exist" << "\n";
            return "user does not exist\r";
        }
        return "user has been deleted";
    }
    else{
        cout << "only admin can delete users" << "\n";
        return "only admin can delete users";
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

    // Output Refund transaction
    ofstream MyFile2("../../Data/DailyTransactionFile.txt", fstream::app);

    if (!MyFile2.is_open()){
        cout << "Could not open Daily Transaction File!" << endl;
        return;
    }

    MyFile2 << "05 " + buyer_username + " " + seller_username + " " + to_string(refund_amount) + "\n";

    MyFile2.close();

    cout << "Refund transaction recorded!" << endl;
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