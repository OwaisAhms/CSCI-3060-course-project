#include <string>
#include <iostream>

class User {
    public:
        std::string username;
        bool is_logged_in;
        bool allow_transaction;
        bool allow_admin_transaction;
        int max_credit;
    private:
        std::string password;

};

int main() {
    User user1;

    user1.username = "Tahoor";

    std::cout << user1.username << "\n";

    return 0;
};
