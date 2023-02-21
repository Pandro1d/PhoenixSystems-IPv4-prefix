//
// Created by pandroid on 19.02.23.
//

#ifndef PHOENIXSYSTEMS_IPV4_PREFIX_IPV4_PREFIX_MANAGER_H
#define PHOENIXSYSTEMS_IPV4_PREFIX_IPV4_PREFIX_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

//IPv4 manager structs
#define MAX_DATA_SIZE 100

struct __attribute__((__packed__))Prefix {
    unsigned int base;
    unsigned int subnetMask;
    //Conversion from subnetMask length into subnetMask
    char mask;
};

//Struct which contains sorted prefixes from the highest mask length number to its lowest number.
struct __attribute__((__packed__))PrefixDataBase {
    struct Prefix data[MAX_DATA_SIZE];
    unsigned int size;
};
//Function definitions
int add(struct PrefixDataBase *dataBase, unsigned int base, char mask);
int del(struct PrefixDataBase *dataBase, unsigned int base, char mask);
inline char check(struct PrefixDataBase *dataBase, unsigned int ip);

//Increases the number 2 to the specified power. Is used by maskLengthToSubnetConv function
unsigned int binPow(unsigned int);
//Changes string ip address to unsigned.
unsigned int IPv4_stringToIntConv(const char *ip);
//Changes subnetMask length into decimal number of subnetMask.
unsigned int maskLengthToSubnetConv(char mask);


#endif//PHOENIXSYSTEMS_IPV4_PREFIX_IPV4_PREFIX_MANAGER_H
