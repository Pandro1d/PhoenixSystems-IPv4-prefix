//
// Created by pandroid on 19.02.23.
//

#include "ipv4_func.h"
unsigned int binPow(unsigned int power) {
    if(power == 0) return 0;
    unsigned result = 2;
    for(; power>1; power--) {
        result *= 2;
    }
    return result;
}

int del(struct prefix_data_base * dataBase, const unsigned int base, const char mask) {
    if(mask > (char)32||(!dataBase->dataSize)) return -1;
    for(int i = 0; i<dataBase->dataSize; i++) {
        if(dataBase->data[i].base==base && dataBase->data[i].mask_length==mask) {
            memset(&dataBase->data[i], 0, sizeof(struct prefix));
            for(int j = i; j< dataBase->dataSize -1 ; j++) { //Moving
                dataBase->data[j] = dataBase->data[j+1];
            }
            --dataBase->dataSize;
            return 0;
        }
    }
    return -1;
}
int add(struct prefix_data_base * dataBase, const unsigned int base, const char mask){

    if(mask > (char)32) return -1;
    struct prefix buff;
    buff.base = base;
    buff.mask_length = mask;
    buff.mask = maskLengthConv(mask);

    if(dataBase->dataSize == 0) {
        dataBase->data[dataBase->dataSize++] = buff;
        return 0;
    }else {
        for(int i = (int)dataBase->dataSize; i>=0; i--) {
            if(dataBase->data[dataBase->dataSize - i].base==base && dataBase->data[dataBase->dataSize - i].mask_length==mask) {
                return -1; //This prefix is already in the database
            }
        }
        dataBase->data[dataBase->dataSize++] = buff;
        sortPrefixData((struct prefix_data_base *) &dataBase);
    }
    return 0;
}

char check(struct prefix_data_base * dataBase, unsigned int ip) {
    for(int i = 0; i<dataBase->dataSize; i++) {
        if((ip & dataBase->data[i].mask) == dataBase->data[i].base) {
            return dataBase->data[i].mask_length;
        }
    }
    return -1; //Not found ip in prefix database
}

unsigned int ipToIntConv(const char *ip) {

    const char *start = ip;
    char *end;
    unsigned int a = strtoul(start, &end, 10);
    if (*end != '.') return -1;
    unsigned int b = strtoul(end + 1, &end, 10);
    if (*end != '.') return -1;
    unsigned int c = strtoul(end + 1, &end, 10);
    if (*end != '.') return -1;
    unsigned int d = strtoul(end + 1, &end, 10);
    if (*end) return -1;

    return ((a << 24) | (b << 16) | (c << 8) | d);
}

unsigned int maskLengthConv(const char mask) {
    unsigned int mask_buff = 0;
    for(unsigned int i = (unsigned int)mask; i > 0; i--) {
        mask_buff += binPow(32-i);
    }
    return mask_buff;
}

int sortPrefixData(struct prefix_data_base * dataBase) {
    struct prefix buff;
    if(dataBase->dataSize<2) return -1; //Nothing to sort
    else {
        for(int step=(int)dataBase->dataSize-1; step>=1; step--){
            if(dataBase->data[step].mask_length<=dataBase->data[step - 1].mask_length) return 0;
            else {
                buff = dataBase->data[step-1];
                dataBase->data[step - 1] = dataBase->data[step];
                dataBase->data[step] = buff;
            }
        }
    }
    return 0;
}