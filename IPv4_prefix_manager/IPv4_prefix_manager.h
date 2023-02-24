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
    char maskLength;
};

//Struct which contains sorted prefixes from the highest maskLength length number to its lowest
//number
struct __attribute__((__packed__)) PrefixDatabase {
    struct Prefix data[MAX_DATA_SIZE];
    unsigned int size;
};
//Function definitions
int add(struct PrefixDatabase *dataBase, unsigned int base, char mask, char *status);
int del(struct PrefixDatabase *dataBase, unsigned int base, char mask, const char *status);
char check(struct PrefixDatabase *dataBase, unsigned int ip, const char *status);

//Increases the number 2 to the specified power. Is used by maskLengthToSubnetConv function
unsigned int IPv4_stringToIntConv(const char *ip, char *status);
//Changes subnetMask length into decimal number of subnetMask.
unsigned int maskLengthToSubnetConv(char maskLength, char *status);


#endif//PHOENIXSYSTEMS_IPV4_PREFIX_IPV4_PREFIX_MANAGER_H
