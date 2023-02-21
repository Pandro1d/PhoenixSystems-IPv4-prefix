//
// Created by pandroid on 19.02.23.
//


#include <IPv4_prefix_manager.h>
#include <stdio.h>
#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}
struct PrefixDataBase dataBase;

void test_add_del_fun(int, unsigned *);
void test_check_fun(char, unsigned *);

void resetTest(void);

int main() {
    UNITY_BEGIN();

    unsigned int iter = 1;
    ///Checking add, check function
    test_add_del_fun(add(&dataBase, IPv4_stringToIntConv("32.64.128.0"), 20), &iter);
    //1.^Should print OK
    test_add_del_fun(add(&dataBase,IPv4_stringToIntConv("32.64.128.0"), 20), &iter);
    //2.Check if the same Prefix will be added ^Should print NOK
    //3.^Should print OK
    test_add_del_fun(add(&dataBase,IPv4_stringToIntConv("10.20.0.0"), 15), &iter);
    //4.^Should print OK
    test_add_del_fun(add(&dataBase,IPv4_stringToIntConv("10.20.0.0"), 13), &iter);
    //5.^Should print OK
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("32.64.128.1")), &iter);
    //6.^Should print Mask length: 20 is in the 32.64.128.0/20 Prefix
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("10.20.0.1")), &iter);
    //7.^Should Mask length: 16 -> 10.20.0.0 is in the 10.20.0.0/16 Prefix (16 is the smallest Prefix)
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("10.22.0.0")), &iter);
    //8.^Should print Mask length: -1 -> 10.22.0.0 is not in the Prefix database
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("255.255.255.255")), &iter);
    //9.^Should print Mask length: -1 -> 255.255.255.255 is not in the Prefix database
    ///Checking del function
    test_add_del_fun(add(&dataBase,IPv4_stringToIntConv("12.20.0.0"), 20), &iter);
    //10.^Should print OK
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("12.20.15.0")), &iter);
    //11.^Should print Mask length: 20 is in the 12.20.0.0/20 Prefix
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("12.20.0.0"), 20), &iter);
    //12.^Should print OK 12.20.0.0/20 is in the database
    test_check_fun(check(&dataBase,IPv4_stringToIntConv("12.20.15.1")), &iter);
    //13.^Should print Mask length: -1 -> 12.20.15.1 is not in the Prefix database
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("32.64.128.0"), 20), &iter);
    //14.^Should print OK 32.64.128.0/20 is in the database
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("10.20.0.0"), 15), &iter);
    //15.^Should print OK 10.20.0.0/15 is in the database
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("10.20.0.0"), 16), &iter);
    //16.^Should print OK 10.20.0.0/16 is in the database
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("10.20.0.0"), 13), &iter);
    //17.^Should print OK 10.20.0.0/13 is in the database
    test_add_del_fun(del(&dataBase,IPv4_stringToIntConv("10.20.0.0"), 13), &iter);
    //17.^Should print NOK 10.20.0.0/13 is not in the database
    return UNITY_END();
}
void test_add_del_fun(const int result, unsigned *testNumber) {
    printf("Test no %d, %s\n", (*testNumber)++, (!result) ? "OK" : "NOK");
}
void test_check_fun(const char result, unsigned *testNumber) {
    printf("Test no %d, Mask length: %d\n", (*testNumber)++, result);
}

void test_ip_converter(){

}
void test_adding_one_prefix_to_database() {
    struct PrefixDataBase dataBaseTest;
    struct Prefix prefixTest = {168430090,}; //10.10.10.10 base
    //dataBaseTest.data =
    add(&dataBase, IPv4_stringToIntConv("10.10.10.10"), 20);
}


//Functions declarations


