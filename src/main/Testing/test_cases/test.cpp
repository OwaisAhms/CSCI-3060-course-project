#include "../../User.h"
#include "../../Admin.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

template <typename UserType, typename TestFunction>
bool test_output(
    const string& input_file,
    const string& expected_output_file,
    UserType& user,
    TestFunction function
) {
    ifstream input(input_file);
    if (!input.is_open()) {
        cerr << "Could not open input file: " << input_file << '\n';
        return false;
    }

    std::ifstream expected_output(expected_output_file);
    if (!expected_output.is_open()) {
        cerr << "Could not open expected output file: "
                  << expected_output_file << '\n';
        return false;
    }

    string input_line;
    string expected_line;
    size_t test_number = 0;
    bool passed = true;

    while (getline(input, input_line)) {
        ++test_number;
        if (!getline(expected_output, expected_line)) {
            cerr << "Test " << test_number
                      << " failed: expected output has fewer lines than input\n";
            return false;
        }

        const string actual_output = function(user, input_line);
        if (actual_output == expected_line) {
            cout << "Test " << test_number << " passed\n";
        } else {
            cout << "Test " << test_number << " failed\n"
                      << "  Expected: " << expected_line << '\n'
                      << "  Actual:   " << actual_output << '\n';
            passed = false;
        }
    }

    if (input.bad() || expected_output.bad()) {
        cerr << "Error while reading test files\n";
        return false;
    }

    if (getline(expected_output, expected_line)) {
        cerr << "Test failed: expected output has more lines than input\n";
        return false;
    }

    return passed;
}

int main() {
    User user;
    Admin admin_user;
    Admin non_admin_user;
    User credit_user;
    Admin refund_user;
    admin_user.usertype = "AA";

    cout << "login test" << endl;
    const bool login_passed = test_output(
        "../test_inputs/login.txt",
        "../test_expected_outputs/login.txt",
        user,
        [](User& test_user, const string& input) {
            return test_user.login(input, true);
        }
    );

    cout << "logout test" << endl;
    const bool logout_passed = test_output(
        "../test_inputs/logout.txt",
        "../test_expected_outputs/logout.txt",
        user,
        [](User& test_user, const string& input) {
            return test_user.logout(input);
        }
    );

    
    // Add Credit test
    ofstream("../test_actual_outputs/addcredit_transactions.txt").close();

    cout << "addcredit test" << endl;
    const bool addcredit_passed = test_output(
        "../test_inputs/addcredit.txt",
        "../test_expected_outputs/addcredit.txt",
        credit_user,
        [](User& test_user, const string& input) {
            stringstream s(input);
            string type;
            s >> type;

            string info;
            getline(s >> ws, info);

            test_user.usertype = type;
            test_user.username = type == "AA" ? "User001" : "User003";
            test_user.is_logged_in = true;

            return test_user.addcredit(info, true);
        }
    );

    // Refund test
    ofstream("../test_actual_outputs/refund_transactions.txt").close();

    cout << "refund test" << endl;
    const bool refund_passed = test_output(
        "../test_inputs/refund.txt",
        "../test_expected_outputs/refund.txt",
        refund_user,
        [](Admin& test_user, const string& input) {
            stringstream s(input);
            string type;
            s >> type;

            string info;
            getline(s >> ws, info);

            test_user.usertype = type;
            test_user.is_logged_in = true;

            return test_user.refund(info, true);
        }
    );

    cout << "create test" << endl;
    const bool create_passed = test_output(
        "../test_inputs/create.txt",
        "../test_expected_outputs/create.txt",
        admin_user,
        [](Admin& test_user, const string& input) {
            return test_user.create(input,true);
        }
    );

    cout << "All_active_accounts test" << endl;
    const bool All_active_accounts_passed = test_output(
        "../test_inputs/CurrentUserAccounts.txt",
        "../test_expected_outputs/CurrentUserAccounts.txt",
        admin_user,
        [](Admin& test_user, const string& input) {
            return test_user.All_active_accounts(input,true);
        }
    );
    
    
    cout << "delete test" << endl;
    admin_user.usertype = "AA";
    const bool delete_validation_passed = test_output(
        "../test_inputs/delete.txt",
        "../test_expected_outputs/delete.txt",
        admin_user,
        [](Admin& test_user, const string& input) {
            return test_user.deleteuser(input,true);
        }
    );

    cout << "Sell test" << endl;
    non_admin_user.usertype = "BS";
    const bool sell_permission_passed = test_output(
        "../test_inputs/sell_permission.txt",
        "../test_expected_outputs/sell_permission.txt",
        non_admin_user,
        [](User& test_user, const string& input) {
            size_t pos = input.find(',');

            string game_name = input.substr(0, pos);
            string price = input.substr(pos + 1);
            return test_user.sell(input, price);
        }
    );

    non_admin_user.usertype = "SS";
    const bool sell_validation_passed = test_output(
        "../test_inputs/sell.txt",
        "../test_expected_outputs/sell.txt",
        non_admin_user,
        [](User& test_user, const string& input) {
            size_t pos = input.find(',');

            string game_name = input.substr(0, pos);
            string price = input.substr(pos + 1);
            return test_user.sell(input, price);
        }
    );

    cout << "buy test" << endl;
    non_admin_user.usertype = "SS";
    const bool buy_permission_passed = test_output(
        "../test_inputs/buy_permission.txt",
        "../test_expected_outputs/buy_permission.txt",
        non_admin_user,
        [](User& test_user, const string& input) {
            size_t pos = input.find(',');

            string game_name = input.substr(0, pos);
            string sell_name = input.substr(pos + 1);
            return test_user.buy(game_name, sell_name,true);
        }
    );

    non_admin_user.usertype = "BS";
    admin_user.curr_credits = 100;
    const bool buy_validation_passed = test_output(
        "../test_inputs/buy.txt",
        "../test_expected_outputs/buy.txt",
        admin_user,
        [](User& test_user, const string& input) {
            size_t pos = input.find(',');

            string game_name = input.substr(0, pos);
            string sell_name = input.substr(pos + 1);
            return test_user.buy(game_name, sell_name,true);
        }
    );

    if (login_passed && logout_passed && addcredit_passed && refund_passed && create_passed && All_active_accounts_passed
    && delete_validation_passed && sell_permission_passed && sell_validation_passed
    && buy_permission_passed && buy_validation_passed) {
        cout << "All tests passed\n";
        return 0;
    }

    cerr << "One or more tests failed\n";
    return 1;
}
