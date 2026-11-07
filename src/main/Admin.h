#ifndef ADMIN_H // include guard
#define ADMIN_H
#include "User.h"

class Admin: public User 
{
public:
    string create(string setuser,bool istest);
    string deleteuser(string user_delete, bool istest);
    void refund();
    void All_active_accounts();
    void Search();
};

#endif

