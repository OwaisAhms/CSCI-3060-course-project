#include "User.h"
#include <iomanip>

// User login method, checks for username gives user transaction privilages
string User::login(string username_input, bool istest){
    string mytext;
    string filepath;
    if (istest == false) {
        filepath = "../../Data/CurrentUserAccounts.txt";
    }
    else{
        filepath = "../../../../Data/CurrentUserAccounts.txt";
    }
    ifstream MyFile(filepath);
    while (getline (MyFile,mytext)){
        stringstream s(mytext);
        string name;
        string type;
        double credits;
        s >> name;
        s >> type;
        s >> credits;
        char chars[] = "_";
        for (int i = 0;i < strlen(chars); i++){
            name.erase(remove(name.begin(), name.end(), chars[i]),name.end());
        }
        if (username_input == name){
            string output = name + " logged in";
            username = name;
            is_logged_in = true;
            allow_transaction = true;
            usertype = type;
            curr_credits = credits;
            if (usertype == "AA"){
                allow_admin_transaction = true;
            }
            return output;
        }
    }
    MyFile.close();
    return "User does not exist";
}

// User logout method, remeoves transaction privilages
string User::logout(string input){
    if (input == "Y"){
        is_logged_in = false;
        allow_transaction = false;
        if (usertype == "AA"){
            allow_admin_transaction = false; 
        }
        return "logged out";
    }
    return "user did not log out";
}

string User::sell(string game_name, string price){
    if (usertype == "BS"){
        cout << "you are not authorized for this action" << "\n";
        return "you are not authorized for this action";
    }
    else{
        //string game_name;
        //string price;
        // bool pass = true;

        // while (pass){
        //     cout << "Give the name of the game: " << "\n";;
        //     cin >> game_name;

        //     cout << "Give the price of the game: " << "\n";;
        //     cin >> price;

        //     if(game_name.length() > 25){
        //         cout << "Game name not usable\n";
        //     }
        //     else if (stoi(price) > 999.99){
        //         cout << "price above maximum price\n";
        //     }
        //     else {
        //         pass = false;
        //     }
        // }
        
        if(game_name.length() > 25){
            return "Game name not usable\r";
        }
        if (stod(price) > 999.99){
            return "price above maximum price\r";
        }
        

        // if game name is unique and the price isn't over 999.99
        // add game to list of games
        // allow transactions false
        ofstream file("../../Data/AvailableGamesFile.txt");
        file <<  game_name << ", " << price << "\n";
        file.close();

        ofstream MyFile2("../../Data/DailyTransactionFIles/DailyTransactionFileSell",fstream::app);

        MyFile2 << "03_" + game_name + "_" + this->username + price +"/n";

        MyFile2.close();

        return "Game has been listed for sale!";
    }
}

string User::buy(string game_name, string seller_username, bool istest){
    if (usertype == "SS"){
        cout << "you are not authorized for this action\n";
        return "you are not authorized for this action";
    }
    else{
        //string game_name;
        //string buyer_username;
        //string seller_username;

        // cout << "Give the buyer username: " << "\n";
        // cin >> buyer_username;

        // cout << "Give the seller username: " << "\n";
        // cin >> seller_username;

        // if game exists and buyer has equal or greater than the amount needed to purchase the game, and the game isnt the buyers library
        // debit buyer, credit seller (increase/ decrease curr_credits)
        // add game to buyers collection
        string filepath;
        string filepath2;
        string filepath3;
        if (istest == false){
            filepath = "../../Data/CurrentUserAccounts.txt";
            filepath2 = "../../Data/temp.txt";
            filepath3 = "../../Data/AvailableGamesFile.txt";
        }
        else{
            filepath = "../../../../Data/CurrentUserAccounts.txt";
            filepath2 = "../../../../Data/temp.txt";
            filepath3 = "../../../../Data/AvailableGamesFile.txt";
        }
        

        ifstream file(filepath3);
        if (!file.is_open()){
        cout << "Could not open User Account file!" << endl;
        return "Could not open User Account file!";
        }
        //cout << "Game being searched: [" << game_name << "]" << endl;
        bool game_found = false;
        string game_data;
        double credits = 0;
        string credit;
        string game;
        double buy_creds = 0;
        double sell_creds = 0;

        while(!game_found){
            // cout << "Enter game name you wish to purchase: " << "\n";
            // cin >> game_name;

            while(getline(file,game)){
                //cout << game << "\n";
                if(game.find(game_name) != string::npos){
                    game_found = true;
                    game_data = game;
                }
            }
            if (!game_found){
                cout << "Please enter a valid game\n";
                return "Please enter a valid game\r";
            }
        }

        size_t pos1;
        size_t pos2;
        string user;
        string user_type;

        file.close();
        if (game_found){
            size_t pos = game_data.find(',');
            credit = game_data.substr(pos + 1, game_data.length());
            credits = stod(credit);

            if (credits > this->curr_credits){
                return "you do not have the sufficient funds to purchase this game\r";
            }

            ifstream MyFile(filepath);

            ofstream tempFile(filepath2);

            bool user_found = false;
            string line;
            string newLine;

            while (getline(MyFile, line))
            {   
                if (line.find(this->username) != string::npos){
                    pos1 = line.find(' ');
                    user = line.substr(0,pos1);
                    pos2 = line.find(' ', pos1 + 1);
                    user_type = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    buy_creds = this->curr_credits;
                    buy_creds -= credits;
                    this->curr_credits = buy_creds;
                    char buffer2[33];
                    tempFile << user << " " << user_type << " " << to_string(buy_creds) << "\n";
                
                }
                else if (line.find(seller_username) != string::npos){
                    pos1 = line.find(' ');
                    user = line.substr(0,pos1);
                    pos2 = line.find(' ', pos1 + 1);
                    user_type = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    sell_creds = stod(line.substr(pos2 + 1));
                    sell_creds += credits;
                    
                    char buffer1[33];
                    tempFile << user << " " << user_type << " " << to_string(sell_creds) << "\n";
                
                }
                
            }
        
            MyFile.close(); 
            tempFile.close();

            remove("../../Data/CurrentUserAccounts.txt");
            rename("../../Data/temp.txt", "../../Data/CurrentUserAccounts.txt");


            ofstream MyFile2("../../Data/DailyTransactionFIles/DailyTransactionFIleBuy",fstream::app);

            MyFile2 << "05_" + this->username + "_" + seller_username + to_string(credits) +"/n";

            MyFile2.close();
        }
        return "added game to buyer collection";
    }
}



string User::addcredit(string input, bool istest){

    if (is_logged_in == false){
        return "You must be logged in!";
    }

    double amount;
    string recieving_username;
    string recieving_usertype;

    stringstream s(input);
    if (!(s >> amount)){
        return "You cannot add this credit amount!";
    }

    if (amount <= 0 || amount > 1000.00){
        return "credit amount exceeds session maximum";
    }

    if (usertype == "AA"){
        s >> recieving_username;
    }
    else{
        recieving_username = username;
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

    bool user_found = false;
    string myText;

    while (getline(MyFile, myText)){
        string name = myText.substr(0, 15);
        name.erase(remove(name.begin(), name.end(), '_'), name.end());

        if (name == recieving_username){
            user_found = true;
            recieving_usertype = myText.substr(16, 2);
            break;
        }
    }

    MyFile.close();

    if (user_found == false){
        return "user does not exist";
    }

    string filepath2;
    if (istest == true){
        filepath2 = "../test_actual_outputs/addcredit_transactions.txt";
    }
    else{
        filepath2 = "../../Data/DailyTransactionFiles/DailyTransactionFileAddCredit.txt";
    }

    ofstream MyFile2(filepath2, fstream::app);

    if (!MyFile2.is_open()){
        return "Could not open Daily Transaction File!";
    }

    stringstream money;
    money << fixed << setprecision(2) << amount;
    string amount_text = money.str();

    string padded_amount = amount_text;
    while (padded_amount.length() < 9){
        padded_amount = "0" + padded_amount;
    }

    string padded_name = recieving_username;
    while (padded_name.length() < 15){
        padded_name += "_";
    }

    MyFile2 << "06 " << padded_name << " " << recieving_usertype
            << " " << padded_amount << "\n";

    MyFile2.close();

    if (usertype == "AA"){
        return amount_text + " credit added to " + recieving_username;
    }

    return amount_text + " credit added";
}

void User::search(){

    if (is_logged_in == false){
        cout << "You must be logged in!" << endl;
        return;
    }

    string query, line;

    cout << "Enter search query: ";
    getline(cin >> ws, query);

    // Search games
    ifstream MyFile("../../Data/AvailableGamesFiles.txt");

    if (!MyFile.is_open()){
        cout << "Could not open Available Games file!" << endl;
        return;
    }

    cout << "Matching games:" << endl;

    while(getline(MyFile, line)){
        string game_name = line.substr(0, line.find(","));

        if(game_name.find(query) != string::npos){
            cout << line << endl;
        }
    }

    MyFile.close();

    // Search users
    ifstream MyFile2("../../Data/CurrentUserAccounts.txt");

    if (!MyFile2.is_open()){
        cout << "Could not open User Account file!" << endl;
        return;
    }

    cout << "Matching users:" << endl;

    while(getline(MyFile2, line)){

        if(line == "") continue;

        string name = line.substr(0, 15);
        name = name.substr(0, name.find("_"));

        if(name.find(query) != string::npos){

            // Check if an admin is selling games
            if(usertype != "AA" && line.substr(16, 2) == "AA"){

                bool selling = false;
                ifstream SellerFile("../../Data/AvailableGamesFiles.txt");
                string game;

                while(getline(SellerFile, game)){
                    string seller = game.substr(game.find(",") + 1);
                    seller = seller.substr(seller.find(",") + 2);
                    seller = seller.substr(0, seller.find("\r"));

                    if(seller == name){
                        selling = true;
                        break;
                    }
                }

                SellerFile.close();

                if(selling == false) continue;
            }

            cout << name << endl;
        }
    }

    MyFile2.close();
}