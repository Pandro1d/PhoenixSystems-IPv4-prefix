//
// Created by pandroid on 19.02.23.
//

#include "IPv4_prefix_manager.h"


int del(struct PrefixDatabase *dataBase, unsigned int base, char mask, const char *status) {
    if(dataBase->size == 0 || *status == -1) {
        return -1;
    }

    for(int i = 0; i<dataBase->size; i++) {
        if(dataBase->data[i].base==base && dataBase->data[i].maskLength == mask) {
            //Shifting data
            for(int j = i; j < dataBase->size-1 ; j++) {
                dataBase->data[j] = dataBase->data[j+1];
            }
            dataBase->size--;
            return 0;
        }
    }
    //No prefix found
    return -1;
}
int add(struct PrefixDatabase *dataBase, unsigned int base, char mask, char *status) {
    if(dataBase->size >= MAX_DATA_SIZE || *status == -1) {
        return -1;
    }
    unsigned insertIndex = 0;
    struct Prefix prefixBuff;
    prefixBuff.maskLength = mask;
    prefixBuff.subnetMask = maskLengthToSubnetConv(mask, status);
    //Checking if mask is proper
    if (*status == -1) {
        return -1;
    }
    //Calculating network address based on base and mask
    prefixBuff.base = base&prefixBuff.subnetMask;

    if(dataBase->size == 0) {
        insertIndex = 0;
    } else {
        for(int i = 0; i < dataBase->size; i++) {
            if(prefixBuff.maskLength > dataBase->data[i].maskLength){
                insertIndex = i;
                // Setting temporary index to iteration in which smaller maskLength was found
                break;
            } else if(dataBase->data[i].base == prefixBuff.base &&
                dataBase->data[i].maskLength == prefixBuff.maskLength) {
                return -1;
                // This Prefix is already in the database
            } else if(i == dataBase->size - 1) {
                // Case in witch no prefix maskLength length in the database is less than new prefix
                // maskLength
                insertIndex = dataBase->size;
            }
        }
    }
    //Shifting data

    for(int j = (int)dataBase->size; j > insertIndex; j--) {
        dataBase->data[j] = dataBase->data[j-1];
    }
    dataBase->size++;
    dataBase->data[insertIndex]=prefixBuff;

    return 0;
}

char check(struct PrefixDatabase *dataBase, unsigned int ip, const char *status) {
    if (*status == -1) {
        return -1;
    }
    for(int i = 0; i < dataBase->size; i++) {
        if((ip & dataBase->data[i].subnetMask) ==
            dataBase->data[i].base) {
            return dataBase->data[i].maskLength;
            // Length of the maskLength is the longest possible, because database is sorted by
            // maskLength
        }
    }
    // Not found ip in Prefix database
    return -1;

}

unsigned int IPv4_stringToIntConv(const char *ip, char *status) {
    const char *start = ip;
    char *end;
    unsigned int result = 0;
    unsigned int temp;

    temp = strtoul(start, &end, 10);
    if (*end != '.' || temp > 255) {
        printf("\nIP address is wrong\n");
        *status = -1;
        return 0;
    }else result |= temp << 24;

    temp = strtoul(end + 1, &end, 10);
    if (*end != '.' || temp > 255) {
        printf("\nIP address is wrong\n");
        *status = -1;
        return 0;
    }else result |= temp << 16;

    temp = strtoul(end + 1, &end, 10);
    if (*end != '.'|| temp > 255) {
        printf("\nIP address is wrong\n");
        *status = -1;
        return 0;
    }else result |= temp << 8;

    temp = strtoul(end + 1, &end, 10);
    if (*end || temp > 255) {
        printf("\nIP address is wrong\n");
        *status = -1;
        return 0;
    }else result |= temp;
    *status = 0;
    return result;
}

unsigned int maskLengthToSubnetConv(char maskLength, char *status) {
    if(maskLength < 0 || maskLength > 32) {
        printf("\nMask length is wrong\n");
        *status = -1;
        return 0;
    }
    if(maskLength == 32) return UINT_MAX;
    unsigned int mask_buff = (1 << (unsigned)maskLength)-1;
    mask_buff = mask_buff << (32 - maskLength);

    *status = 0;
    return mask_buff;
}

