#include "User.h"

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
            cout << "\n";
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

void User::sell(){
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
        ofstream file("../../Data/AvailableGamesFiles.txt");
        file <<  game_name << ", " << price << "\n";
        file.close();

        ofstream MyFile2("../../Data/DailyTransactionFIles/DailyTransactionFileBuy",fstream::app);

        MyFile2 << "03_" + game_name + "_" + this->username + price +"/n";

        MyFile2.close();
    }
}

void User::buy(){
    if (usertype == "SS"){
        cout << "You are not authroized to make this function" << "\n";
    }
    else{
        string game_name;
        string buyer_username;
        string seller_username;

        cout << "Give the buyer username: " << "\n";
        cin >> buyer_username;

        cout << "Give the seller username: " << "\n";
        cin >> seller_username;

        // if game exists and buyer has equal or greater than the amount needed to purchase the game, and the game isnt the buyers library
        // debit buyer, credit seller (increase/ decrease curr_credits)
        // add game to buyers collection


        cout << "Enter game name you wish to purchase: " << "\n";
        cin >> game_name;

        ifstream file("../../Data/AvailableGamesFiles.txt");

        bool game_found = false;
        string game_data;
        int credits = 0;
        string credit;
        string game;
        int buy_creds = 0;
        int sell_creds = 0;

        while(getline(file,game)){
            if(game.find(game_name) != string::npos){
                game_found = true;
                game_data = game;
            }
        }

        file.close();
        if (game_found){
            size_t pos = game_data.find(',');
            credit = game_data.substr(pos + 1, game_data.length());
            credits = stoi(credit);

            ifstream MyFile("../../Data/CurrentUserAccounts.txt");

            ofstream tempFile("../../Data/temp.txt");

            bool user_found = false;
            string line;
            string newLine;

            while (getline(MyFile, line))
            {
                if (line.find(seller_username) != string::npos){
                    pos = line.find(',');
                    newLine = line.substr(0,pos);
                    buy_creds = stoi(line.substr(pos + 1));
                    buy_creds -= credits;
                    
                    char buffer1[33];
                    tempFile << line << itoa(buy_creds, buffer1, 10) << "\n";
                
                }
                if (line.find(buyer_username) != string::npos){
                    pos = line.find(',');
                    newLine = line.substr(0,pos);
                    sell_creds = stoi(line.substr(pos + 1));
                    sell_creds += credits;

                    char buffer2[33];
                    tempFile << newLine << itoa(credits, buffer2, 10) << "\n";
                
                }
            }
        
            MyFile.close();
            tempFile.close();

            remove("../../Data/CurrentUserAccounts.txt");
            rename("../../Data/temp.txt", "../../Data/CurrentUserAccounts.txt");


            ofstream MyFile2("../../Data/DailyTransactionFIles/DailyTransactionFIleBuy",fstream::app);

            MyFile2 << "05_" + buyer_username + "_" + seller_username + to_string(credits) +"/n";

            MyFile2.close();
        }

    }
}

void User::addcredit(){

    if (is_logged_in == false){
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

    ifstream MyFile("../../Data/CurrentUserAccounts.txt");

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