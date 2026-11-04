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
    bool is_logged_in;
    bool allow_transaction;
    bool allow_admin_transaction;
    double curr_credits;
    string login(string username_input,bool istest);
    void logout();
    void sell();
    void buy();
    void addcredit();
};

#endif