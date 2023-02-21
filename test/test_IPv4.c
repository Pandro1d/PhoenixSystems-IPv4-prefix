//
// Created by pandroid on 19.02.23.
//


#include <IPv4_prefix_manager.h>
#include <stdio.h>
#include "unity.h"

struct PrefixDataBase dataBase;


void test_IPv4_stringToIntConv();
void setUp(void) {

}
void tearDown(void){

}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_IPv4_stringToIntConv);

    return UNITY_END();
}

void test_IPv4_stringToIntConv(){
    TEST_ASSERT_EQUAL(168430090, IPv4_stringToIntConv("10.10.10.10"));
    TEST_ASSERT_EQUAL(4294967295
                      , IPv4_stringToIntConv("255.255.255.255"));
    TEST_ASSERT_EQUAL(0
                      , IPv4_stringToIntConv("0.0.0.0"));

    //Some fake IP addresses. Should print communication to command line "IP address is wrong" 5x
    //times
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("Not a ip"));
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("-1234Random"));
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("0"));
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("0.0.1"));
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("0.0.0.256"));

}
void test_maskLengthToSubnetConv() {

}
void test_adding_one_prefix_to_database() {
    struct PrefixDataBase dataBaseTest;
    struct Prefix prefixTest = {168430090,}; //10.10.10.10 base
    //dataBaseTest.data =
    add(&dataBase, IPv4_stringToIntConv("10.10.10.10"), 20);
}


//Functions declarations


