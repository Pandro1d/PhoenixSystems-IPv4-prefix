//
// Created by pandroid on 19.02.23.
//

#include "IPv4_prefix_manager.h"


int del(struct PrefixDataBase *dataBase, unsigned int base, char mask) {
    if(mask > (char)32||(!dataBase->dataSize)) return -1;
    for(int i = 0; i<dataBase->dataSize; i++) {
        if(dataBase->data[i].base==base && dataBase->data[i].mask == mask) {
            for(int j = i; j< dataBase->dataSize -1 ; j++) { //Moving
                dataBase->data[j] = dataBase->data[j+1];
            }
            --dataBase->dataSize;
            return 0;
        }
    }
    return -1;
}
int add(struct PrefixDataBase *dataBase, unsigned int base, char mask) {

    if(mask > (char)32 || mask < 0 || base > INT_MAX || dataBase->dataSize >= MAX_DATA_SIZE)
        return -1;

    unsigned tempIndex = 0;

    if(dataBase->dataSize == 0) {
        tempIndex = dataBase->dataSize;
    }else {
        for(int i = (int)dataBase->dataSize; i>=0; i--) {
            if(dataBase->data[dataBase->dataSize - i].base == base &&
                dataBase->data[dataBase->dataSize - i].mask == mask) {
                return -1; //This Prefix is already in the database
            }else if(mask > dataBase->data[dataBase->dataSize - i].mask){

            }
        }
    }
    dataBase->data[tempIndex].base = base;
    dataBase->data[tempIndex].mask = mask;
    dataBase->data[tempIndex].subnetMask = maskLengthConv(mask);
    return 0;
}

unsigned char check(struct PrefixDataBase *dataBase, unsigned int ip) {
    for(int i = 0; i<dataBase->dataSize; i++) {
        if((ip & dataBase->data[i].subnetMask) == dataBase->data[i].base) {
            return dataBase->data[i].mask;
        }
    }
    return -1; //Not found ip in Prefix database
}

unsigned int IPv4_stringToIntConv(const char *ip) {

    const char *start = ip;
    char *end;
    unsigned int a = strtoul(start, &end, 10);
    if (*end != '.') return UINT_MAX;
    unsigned int b = strtoul(end + 1, &end, 10);
    if (*end != '.') return UINT_MAX;
    unsigned int c = strtoul(end + 1, &end, 10);
    if (*end != '.') return UINT_MAX;
    unsigned int d = strtoul(end + 1, &end, 10);
    if (*end) return UINT_MAX;

    return ((a << 24) | (b << 16) | (c << 8) | d);
}

unsigned int maskLengthConv(char mask) {
    unsigned int mask_buff = 0;
    for(unsigned int i = (unsigned int)mask; i > 0; i--) {
        mask_buff += binPow(32-i);
    }
    return mask_buff;
}


unsigned int binPow(unsigned int power) {
    if(power == 0) return 0;
    unsigned result = 2;
    for(; power>1; power--) {
        result *= 2;
    }
    return result;
}