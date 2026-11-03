#ifndef ADMIN_H // include guard
#define ADMIN_H
#include "User.h"

class Admin: public User 
{
public:
    void create();
    void deleteuser();
    void refund();
    void All_active_accounts();
};

#endif

