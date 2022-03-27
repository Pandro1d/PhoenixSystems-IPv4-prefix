#include <stdio.h>
#define MAX_DATA_SIZE 100 //Depends on size we need (can be of course changed into dynamic allocation, but it is slower)

struct prefix {
    char masks[32]; //Each IPv4 base can have 32 different masks -> 32 different sets of addresses
    unsigned int base;
    short masks_no;
};

struct prefix_data_base {
    struct prefix data[MAX_DATA_SIZE];
    size_t dataSize;
};
//
inline unsigned int getIPAddress(char, char, char, char);
int add(unsigned int, char);
int del(unsigned int, char);
inline char check(unsigned int);
unsigned int binPow(unsigned int);
//GLOBAL VAR
    struct prefix_data_base dataBase;
//
int main() {

    return 0;
}

unsigned int binPow(unsigned int power) {
    unsigned result = 2;
    for(int i =1; i<power; i++) {
        result *= 2;
    }
    return result;
}

int add(unsigned int base, char mask){
    struct prefix buff;
    buff.base = base;
    buff.masks[0] = mask;
    dataBase.data[dataBase.dataSize++] = buff;
    return 1;
}
