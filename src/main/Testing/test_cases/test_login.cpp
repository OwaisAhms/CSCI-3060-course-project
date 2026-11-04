#include <gtest/gtest.h>
#include "../../Admin.h"

User user;

TEST(MyTest, login) {
    string test_input;
    string test_output;
    string test_inputs[9];
    string expected_output[9];
    int i = 0;
    int k = 0;

    ifstream file("../test_inputs/login.txt");
    while(getline(file,test_input)){ 
        test_inputs[i] = user.login(test_input,true);
        i++;
    }
    file.close();

    ifstream newfile("../test_expected_outputs/login.txt");
    while(getline(newfile,test_output)){
        expected_output[k] = test_output;
        k++;
    }
    newfile.close();

    for (int j = 0;j < 9; j++){
        EXPECT_EQ(test_inputs[j], expected_output[j]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}