//
// Created by pandroid on 19.02.23.
//

#include <IPv4_prefix_manager.h>
#include <stdio.h>
#include "unity.h"

struct PrefixDatabase dataBase;

void setUp(void) {

}
void tearDown(void){

}

void test_IPv4_stringToIntConv();
void test_maskLengthToSubnetConv();
void test_checkingSortingByAddFunc();
void test_addingPrefixes();
void test_overloadAddingPrefixes();
void test_checking();
void test_deleting();

int main() {

    UNITY_BEGIN();

    RUN_TEST(test_IPv4_stringToIntConv);
    RUN_TEST(test_maskLengthToSubnetConv);
    RUN_TEST(test_addingPrefixes);
    RUN_TEST(test_checkingSortingByAddFunc);
    RUN_TEST(test_overloadAddingPrefixes);
    RUN_TEST(test_checking);
    RUN_TEST(test_deleting);

    return UNITY_END();
}

void test_IPv4_stringToIntConv(){
    char status =0;
    TEST_ASSERT_EQUAL(168430090, IPv4_stringToIntConv("10.10.10.10", &status));
    TEST_ASSERT_EQUAL(4294967295 , IPv4_stringToIntConv("255.255.255.255", &status));
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("0.0.0.0", &status));

    //Some wrong IP addresses. Should print to command line "IP address is wrong" 5x times
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("Not a ip", &status));
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("-1234Random", &status));
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("0", &status));
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("0.0.1", &status));
    TEST_ASSERT_EQUAL(0, IPv4_stringToIntConv("0.0.0.256", &status));

}
void test_maskLengthToSubnetConv() {
    char status =0;
    TEST_ASSERT_EQUAL(0, maskLengthToSubnetConv(0, &status));
    TEST_ASSERT_EQUAL(4293918720, maskLengthToSubnetConv(12, &status));
    TEST_ASSERT_EQUAL(4294967295, maskLengthToSubnetConv(32, &status));
    TEST_ASSERT_EQUAL(4294967294, maskLengthToSubnetConv(31, &status));
    //Some wrong maskLengths. Should print to command line _"Mask length is wrong 2x times"
    TEST_ASSERT_EQUAL(0, maskLengthToSubnetConv(-23, &status));
    TEST_ASSERT_EQUAL(0, maskLengthToSubnetConv(33, &status));

}
void test_overloadAddingPrefixes() {
    struct PrefixDatabase dataBaseTest = {0};
    char status = 0;
    int iter;
    for(iter = 0; iter< MAX_DATA_SIZE; iter++) {
        add(&dataBaseTest, iter, 10, &status);
    }
    TEST_ASSERT_EQUAL(-1, add(&dataBaseTest, iter+1, 10, &status));
}
void test_addingPrefixes() {
    struct PrefixDatabase dataBaseTest = {0};
    char status = 0;
    //Good
    TEST_ASSERT_EQUAL(0, add(&dataBaseTest, IPv4_stringToIntConv("10.10.10.0", &status), 14,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTest, IPv4_stringToIntConv("10.10.10.10", &status), 12,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTest, IPv4_stringToIntConv("0.0.0.0", &status), 32,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTest, IPv4_stringToIntConv("0.0.0.0", &status), 0,
                             &status));
    //Wrong mask
    TEST_ASSERT_EQUAL(-1, add(&dataBaseTest, IPv4_stringToIntConv("5.5.5.0", &status), -1,
                              &status));
    TEST_ASSERT_EQUAL(-1, add(&dataBaseTest, IPv4_stringToIntConv("5.5.5.0", &status), 33,
                              &status));
    //Wrong IP
    TEST_ASSERT_EQUAL(-1, add(&dataBaseTest, IPv4_stringToIntConv("10.0.0.256", &status), 14,
                              &status));
    //Prefix is already in the database
    TEST_ASSERT_EQUAL(-1, add(&dataBaseTest, IPv4_stringToIntConv("10.10.10.10", &status), 14,
                              &status));
    //Prefix base is different in comparison to those from database, but mask is too small for
    // this base. After calculations base is 0.0.0.0 with mask 0 (there is that prefix in the
    // database).
    TEST_ASSERT_EQUAL(-1, add(&dataBaseTest, IPv4_stringToIntConv("255.255.255.255", &status), 0,
                              &status));
}
void test_checkingSortingByAddFunc() {
    char status = 0;

    struct PrefixDatabase dataBaseTestExp = {0};
    struct PrefixDatabase dataBaseTestAct = {0};
    struct Prefix prefixTest1= {169082880
                                 , 4294901760,16}; //10.20.0.0/16
    struct Prefix prefixTest2= {541097984
                                 , 4294963200,20}; //32.64.128.0/20
    struct Prefix prefixTest3= {169082880
                                 , 4294963200,20}; //10.20.0.0/20
    struct Prefix prefixTest4= {167772160

                                 , 4290772992,10}; //10.0.0.0/10
    struct Prefix prefixTest5= {0
                                 , 4294967295,32}; //0.0.0.0/32

    dataBaseTestExp.data[0] = prefixTest5;
    dataBaseTestExp.data[1] = prefixTest2;
    dataBaseTestExp.data[2] = prefixTest3;
    dataBaseTestExp.data[3] = prefixTest1;
    dataBaseTestExp.data[4] = prefixTest4;
    dataBaseTestExp.size = 5;

    TEST_ASSERT_EQUAL(0, add(&dataBaseTestAct, IPv4_stringToIntConv("10.20.0.0", &status), 16,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTestAct, IPv4_stringToIntConv("32.64.128.0", &status), 20,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTestAct, IPv4_stringToIntConv("10.20.0.0", &status), 20,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTestAct, IPv4_stringToIntConv("10.0.0.0", &status), 10,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTestAct, IPv4_stringToIntConv("0.0.0.0", &status), 32,
                             &status));
    TEST_ASSERT_EQUAL_MEMORY(&dataBaseTestExp, &dataBaseTestAct,sizeof(struct Prefix)
                                                                         *dataBaseTestExp.size);

}
void test_deleting() {
    char status = 0;

    struct PrefixDatabase dataBaseTestExp = {0};
    struct PrefixDatabase dataBaseTestAct = {0};
    struct Prefix prefixTest1= {169082880
                                 , 4294901760,16}; //10.20.0.0/16
    struct Prefix prefixTest2= {541097984
                                 , 4294963200,20}; //32.64.128.0/20
    struct Prefix prefixTest5= {0
                                 , 4294967295,32}; //0.0.0.0/32

    dataBaseTestExp.data[0] = prefixTest5;
    dataBaseTestExp.data[1] = prefixTest2;
    dataBaseTestExp.data[2] = prefixTest1;
    dataBaseTestExp.size = 3;

    TEST_ASSERT_EQUAL(0, add(&dataBaseTestAct, IPv4_stringToIntConv("10.20.0.0", &status), 16,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTestAct, IPv4_stringToIntConv("32.64.128.0", &status), 20,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTestAct, IPv4_stringToIntConv("10.20.0.0", &status), 20,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTestAct, IPv4_stringToIntConv("10.0.0.0", &status), 10,
                             &status));
    TEST_ASSERT_EQUAL(0, add(&dataBaseTestAct, IPv4_stringToIntConv("0.0.0.0", &status), 32,
                             &status));

    TEST_ASSERT_EQUAL(0, del(&dataBaseTestAct, IPv4_stringToIntConv("10.20.0.0", &status),20,
                              &status));
    TEST_ASSERT_EQUAL(0, del(&dataBaseTestAct, IPv4_stringToIntConv("10.0.0.0", &status),10,
                              &status));

    TEST_ASSERT(dataBaseTestAct.size == dataBaseTestExp.size);
    for(int i = 0; i< dataBaseTestAct.size; i++) {
        TEST_ASSERT_EQUAL_MEMORY(&dataBaseTestExp.data[i],&dataBaseTestAct.data[i],sizeof
                                 (struct Prefix));
    }
    TEST_ASSERT_EQUAL(-1, del(&dataBaseTestAct, IPv4_stringToIntConv("0.0.0.2", &status),32,
                              &status));
    TEST_ASSERT_EQUAL(-1, del(&dataBaseTestAct, IPv4_stringToIntConv("32.64.128.0", &status),25,
                              &status));
}
void test_checking() {
    struct PrefixDatabase dataBaseTest = {0};
    char status = 0;
    //Good
    add(&dataBaseTest, IPv4_stringToIntConv("10.10.10.10", &status), 14, &status);
    add(&dataBaseTest, IPv4_stringToIntConv("0.0.0.0", &status), 32, &status);
    add(&dataBaseTest, IPv4_stringToIntConv("10.10.10.10", &status), 12, &status);
    add(&dataBaseTest, IPv4_stringToIntConv("32.64.128.0", &status), 20, &status);
    add(&dataBaseTest, IPv4_stringToIntConv("32.64.128.0", &status), 22, &status);

    TEST_ASSERT_EQUAL(32, check(&dataBaseTest, IPv4_stringToIntConv("0.0.0.0", &status),
                                &status));
    TEST_ASSERT_EQUAL(22, check(&dataBaseTest, IPv4_stringToIntConv("32.64.128.0", &status),
                                &status));
    TEST_ASSERT_EQUAL(20, check(&dataBaseTest, IPv4_stringToIntConv("32.64.143.254", &status),
                                &status));
    //Wrong ip
    TEST_ASSERT_EQUAL(-1, check(&dataBaseTest, IPv4_stringToIntConv("Not a ip", &status),
                                &status));
    //No ip in prefix database
    TEST_ASSERT_EQUAL(-1, check(&dataBaseTest, IPv4_stringToIntConv("32.64.127.0", &status),
                                &status));

    //Deleting prefix
    TEST_ASSERT_EQUAL(0, del(&dataBaseTest, IPv4_stringToIntConv("32.64.128.0", &status),20,
                             &status));
    //"32.64.143.254" was the latest host in deleted prefix
    TEST_ASSERT_EQUAL(-1, check(&dataBaseTest, IPv4_stringToIntConv("32.64.143.254", &status),
                                &status));
    //But "32.64.128.125" which contained deleted Prefix is still in the database
    //(Prefix 32.64.128.0/22 is there)
    TEST_ASSERT_EQUAL(22, check(&dataBaseTest, IPv4_stringToIntConv("32.64.128.125", &status),
                                &status));
    //Deleting 0.0.0.0/32
    TEST_ASSERT_EQUAL(0, del(&dataBaseTest, IPv4_stringToIntConv("0.0.0.0", &status),32,
                             &status));
    TEST_ASSERT_EQUAL(-1, check(&dataBaseTest, IPv4_stringToIntConv("0.0.0.0", &status),
                                &status));

}


//Functions declarations


