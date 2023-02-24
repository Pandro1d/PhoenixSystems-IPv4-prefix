//
// Created by pandroid on 19.02.23.
//

#include <stdio.h>
#include <IPv4_prefix_manager.h>
struct PrefixDatabase dataBase;

void test_add_del_fun(int, unsigned *);
void test_check_fun(char, unsigned *);

int main() {
    unsigned int iter = 1;
    char status = 0;
    ///Checking add, check function
    test_add_del_fun(add(&dataBase, IPv4_stringToIntConv("32.64.128.0",&status), 20,&status), &iter);
    //1.^Should print OK
    test_add_del_fun(add(&dataBase,IPv4_stringToIntConv("32.64.128.0",&status), 20,&status), &iter);
    //2.Check if the same Prefix will be added ^Should print NOK
    //3.^Should print OK
    test_add_del_fun(add(&dataBase,IPv4_stringToIntConv("10.20.0.0",&status), 15,&status), &iter);
    //4.^Should print OK
    test_add_del_fun(add(&dataBase,IPv4_stringToIntConv("10.20.0.0",&status), 13,&status), &iter);
    //5.^Should print OK
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("32.64.128.1",&status),&status), &iter);
    //6.^Should print Mask length: 20 is in the 32.64.128.0/20 Prefix
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("10.20.0.1",&status),&status), &iter);
    //7.^Should Mask length: 16 -> 10.20.0.0 is in the 10.20.0.0/16 Prefix (16 is the smallest Prefix)
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("10.22.0.0",&status),&status), &iter);
    //8.^Should print Mask length: -1 -> 10.22.0.0 is not in the Prefix database
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("255.255.255.255",&status),&status), &iter);
    //9.^Should print Mask length: -1 -> 255.255.255.255 is not in the Prefix database
    ///Checking del function
    test_add_del_fun(add(&dataBase,IPv4_stringToIntConv("12.20.0.0",&status), 20,&status), &iter);
    //10.^Should print OK
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("12.20.15.0",&status),&status), &iter);
    //11.^Should print Mask length: 20 is in the 12.20.0.0/20 Prefix
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("12.20.0.0",&status), 20,&status), &iter);
    //12.^Should print OK 12.20.0.0/20 is in the database
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("12.20.15.1",&status),&status), &iter);
    //13.^Should print Mask length: -1 -> 12.20.15.1 is not in the Prefix database
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("32.64.128.0",&status), 20,&status), &iter);
    //14.^Should print OK 32.64.128.0/20 is in the database
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("10.20.0.0",&status), 15,&status), &iter);
    //15.^Should print OK 10.20.0.0/15 is in the database
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("10.20.0.0",&status), 16,&status), &iter);
    //16.^Should print OK 10.20.0.0/16 is in the database
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("10.20.0.0",&status), 13,&status), &iter);
    //17.^Should print OK 10.20.0.0/13 is in the database
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("10.20.0.0",&status), 13,&status), &iter);
    //17.^Should print NOK 10.20.0.0/13 is not in the database
    return 0;
}

void test_add_del_fun(const int result, unsigned *testNumber) {
    printf("Test no %d, %s\n", (*testNumber)++, (!result) ? "OK" : "NOK");
}
void test_check_fun(const char result, unsigned *testNumber) {
    printf("Test no %d, Mask length: %d\n", (*testNumber)++, result);
}


