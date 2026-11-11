#include "Admin.h"
#include <iomanip>

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
        const size_t decimal_position = set_credit.find('.');
        if (decimal_position != string::npos &&
            set_credit.find('.', decimal_position + 1) != string::npos){
            return "Credit must be between 0 and 999999.99 with at most 2 decimal places.";
        }

        string whole_credit = set_credit.substr(0, decimal_position);
        string fractional_credit = decimal_position == string::npos
            ? ""
            : set_credit.substr(decimal_position + 1);
        if (whole_credit.empty() ||
            (decimal_position != string::npos && fractional_credit.empty()) ||
            fractional_credit.length() > 2){
            return "Credit must be between 0 and 999999.99 with at most 2 decimal places.";
        }
        for (char digit : whole_credit){
            if (digit < '0' || digit > '9'){
                return "Credit must be between 0 and 999999.99 with at most 2 decimal places.";
            }
        }
        for (char digit : fractional_credit){
            if (digit < '0' || digit > '9'){
                return "Credit must be between 0 and 999999.99 with at most 2 decimal places.";
            }
        }

        const size_t first_nonzero = whole_credit.find_first_not_of('0');
        whole_credit = first_nonzero == string::npos
            ? "0"
            : whole_credit.substr(first_nonzero);
        if (whole_credit.length() > 6){
            return "Credit must be between 0 and 999999.99 with at most 2 decimal places.";
        }
        whole_credit.insert(0, 6 - whole_credit.length(), '0');
        fractional_credit.append(2 - fractional_credit.length(), '0');
        set_credit = whole_credit + "." + fractional_credit;

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


string Admin::refund(string input, bool istest){

    if (usertype != "AA"){
        return "you are not authorized for this action";
    }

    string buyer_username;
    string seller_username;
    double refund_amount;

    stringstream s(input);

    if (!(s >> buyer_username >> seller_username >> refund_amount)){
        return "Invalid refund amount";
    }

    if (refund_amount <= 0 || refund_amount > 999999.99){
        return "Invalid refund amount";
    }

    string filepath;
    if (istest == true){
        filepath = "../test_inputs/CurrentUserAccounts.txt";
    }
    else{
        filepath = "../../Data/CurrentUserAccounts.txt";
    }

    ifstream MyFile(filepath);

    if (!MyFile.is_open()){
        return "Could not open User Account file!";
    }

    string myText;
    bool buyer_found = false;
    bool seller_found = false;

    while (getline(MyFile, myText)){
        string name = myText.substr(0, 15);
        name.erase(remove(name.begin(), name.end(), '_'), name.end());

        if (name == buyer_username){
            buyer_found = true;
        }

        if (name == seller_username){
            seller_found = true;
        }
    }

    MyFile.close();

    if (buyer_found == false){
        return "buyer does not exist";
    }

    if (seller_found == false){
        return "seller does not exist";
    }

    string filepath2;
    if (istest == true){
        filepath2 = "../test_actual_outputs/refund_transactions.txt";
    }
    else{
        filepath2 = "../../Data/DailyTransactionFiles/DailyTransactionFileRefund.txt";
    }

    ofstream MyFile2(filepath2, fstream::app);

    if (!MyFile2.is_open()){
        return "Could not open Daily Transaction File!";
    }

    stringstream money;
    money << fixed << setprecision(2) << refund_amount;
    string amount_text = money.str();

    string padded_amount = amount_text;
    while (padded_amount.length() < 9){
        padded_amount = "0" + padded_amount;
    }

    string padded_buyer = buyer_username;
    string padded_seller = seller_username;

    while (padded_buyer.length() < 15){
        padded_buyer += "_";
    }

    while (padded_seller.length() < 15){
        padded_seller += "_";
    }

    MyFile2 << "05 " << padded_buyer << " " << padded_seller
            << " " << padded_amount << "\n";

    MyFile2.close();

    return "transferred " + amount_text + " credit from "
           + seller_username + " to " + buyer_username;
}

string Admin::All_active_accounts(string input,bool istest){
    // Will output all active accounts and relevant information
    if(input == "Y"){
        string filepath;
        if (istest == true){
            filepath = "../../../../Data/CurrentUserAccounts.txt";
        }
        else{
            filepath = "../../Data/CurrentUserAccounts.txt";
        }
        ifstream MyFile(filepath);

        string line;

        while (getline(MyFile, line))
        {
            cout << line + "\n";
        }
        MyFile.close();

        return "All users displayed";
    }else{
        return "Did not display users";
    }
}