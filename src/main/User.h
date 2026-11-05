#ifndef USER_H // include guard
#define USER_H

#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

class User
{
public:
    string username;
    string usertype;
    string password;
    bool is_logged_in = false;
    bool allow_transaction = false;
    bool allow_admin_transaction = false;
    double curr_credits = 0.0;
    string login(string username_input,bool istest);
    string logout(string user_input);
    void sell();
    void buy();
    void addcredit();
};

#endif