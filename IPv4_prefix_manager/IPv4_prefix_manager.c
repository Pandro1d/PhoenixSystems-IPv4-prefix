//
// Created by pandroid on 19.02.23.
//

#include "IPv4_prefix_manager.h"


int del(struct PrefixDataBase *dataBase, unsigned int base, char mask) {
    //Mask length must be unsigned integer from range 0 to 32 and base must be unsigned integer
    //from 0 to INT_MAX (max base number possible)
    if(mask > (char)32||mask < 0||dataBase->size == 0) return -1;

    for(int i = 0; i<dataBase->size; i++) {
        if(dataBase->data[i].base==base && dataBase->data[i].mask == mask) {
            for(int j = i; j< dataBase->size -1 ; j++) { //Moving
                dataBase->data[j] = dataBase->data[j+1];
            }
            dataBase->size--;
            return 0;
        }
    }
    //No prefix found
    return -1;
}
int add(struct PrefixDataBase *dataBase, unsigned int base, char mask) {

    if(mask > (char)32 || mask < 0 || dataBase->size >= MAX_DATA_SIZE)
        return -1;

    unsigned tempIndex = 0;

    if(dataBase->size == 0) {
        tempIndex = 0;
    } else {
        for(int i = 0; i < dataBase->size; i++) {
            if(mask > dataBase->data[i].mask){
                tempIndex = i;
                //Setting temporary index to iteration in which smaller mask was found
                break;
            } else if(dataBase->data[i].base == base &&
                dataBase->data[i].mask == mask) {
                return -1;
                //This Prefix is already in the database
            } else if(i == dataBase->size - 1) {
                //No prefix mask length in the database is less than new prefix mask length case
                tempIndex = dataBase->size;
            }
        }
    }
    //Shifting data
    for(int j = (int)tempIndex; j > dataBase->size; j++) {
        dataBase->data[j+1] = dataBase->data[j];
    }

    dataBase->data[tempIndex].base = base;
    dataBase->data[tempIndex].mask = mask;
    dataBase->data[tempIndex].subnetMask = maskLengthToSubnetConv(mask);

    dataBase->size++;

    return 0;
}

char check(struct PrefixDataBase *dataBase, unsigned int ip) {

    for(int i = (int)dataBase->size; i>=0; i--) {
        if((ip & dataBase->data[dataBase->size - i].subnetMask) ==
            dataBase->data[dataBase->size - i].base) {
            return dataBase->data[dataBase->size - i].mask;
            //Length of the mask is the longest possible, because database is sorted by mask length
        }
    }
    return -1;
    //Not found ip in Prefix database
}

unsigned int IPv4_stringToIntConv(const char *ip) {

    const char *start = ip;
    char *end;
    unsigned int a = strtoul(start, &end, 10);
    if (*end != '.' || a > 255) {
        printf("\nIP address is wrong\n");
        return 0;
    }
    unsigned int b = strtoul(end + 1, &end, 10);
    if (*end != '.' || b > 255) {
        printf("\nIP address is wrong\n");
        return 0;
    }
    unsigned int c = strtoul(end + 1, &end, 10);
    if (*end != '.'|| c > 255) {
        printf("\nIP address is wrong\n");
        return 0;
    }
    unsigned int d = strtoul(end + 1, &end, 10);
    if (*end || d > 255) {
        printf("\nIP address is wrong\n");
        return 0;
    }

    return ((a << 24) | (b << 16) | (c << 8) | d);
}

unsigned int maskLengthToSubnetConv(char mask) {
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