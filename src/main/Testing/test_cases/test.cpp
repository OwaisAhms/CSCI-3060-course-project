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

    cout << "create test" << endl;
    non_admin_user.usertype = "FS";
    const bool create_permission_passed = test_output(
        "../test_inputs/create.txt",
        "../test_expected_outputs/create_permission.txt",
        non_admin_user,
        [](Admin& test_user, const string& input) {
            return test_user.create(input, true);
        }
    );

    admin_user.usertype = "AA";
    const bool create_validation_passed = test_output(
        "../test_inputs/create.txt",
        "../test_expected_outputs/create.txt",
        admin_user,
        [](Admin& test_user, const string& input) {
            return test_user.create(input,true);
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

    if (login_passed && logout_passed && create_permission_passed &&
        create_validation_passed && delete_validation_passed && sell_permission_passed
        && sell_validation_passed && buy_permission_passed && buy_validation_passed) {
        cout << "All tests passed\n";
        return 0;
    }

    cerr << "One or more tests failed\n";
    return 1;
}
