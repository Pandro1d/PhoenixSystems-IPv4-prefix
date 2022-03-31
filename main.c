#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DATA_SIZE 100 //Depends on size we need (can be of course changed into dynamic allocation, but it is slower)

struct __attribute__((__packed__))prefix {
    unsigned int base;
    unsigned int mask; //Conversion from mask length made during adding process - thanks to that checking will be faster.
    char mask_length;
};

struct __attribute__((__packed__))prefix_data_base { //Struct which contains sorted prefixes from the highest mask number to its lowest number.
    struct prefix data[MAX_DATA_SIZE];
    unsigned int dataSize;
};
//
int add(unsigned int, char);
int del(unsigned int, char);
inline char check(unsigned int);
unsigned int binPow(unsigned int);
unsigned int ipToIntConv(const char *);
unsigned int maskLengthConv(char);
int sortPrefixData(); //Simple, once run bubble sort to sort added prefix to database by mask length
//GLOBAL VAR
    struct prefix_data_base dataBase = {{0,0,0}, 0};
//

int main() {
    unsigned int i = 1;

    printf("Test no %d, %s\n", i++, (!add(ipToIntConv("32.64.128.0"), 20)) ? "OK" : "NOK");
    printf("Test no %d, %s\n", i++, (!add(ipToIntConv("32.64.128.0"), 20)) ? "OK" : "NOK"); //Check if the same prefix will be added
    printf("Test no %d, %s\n", i++, (!add(ipToIntConv("11.20.0.0"), 16)) ? "OK" : "NOK");
    printf("Test no %d, %s\n", i++, (!add(ipToIntConv("10.20.0.0"), 15)) ? "OK" : "NOK");
    printf("Test no %d, %s\n", i++, (!add(ipToIntConv("10.20.0.0"), 16)) ? "OK" : "NOK");
    printf("Test no %d, %s\n", i++, (!add(ipToIntConv("10.20.0.0"), 32)) ? "OK" : "NOK");
    printf("Test no %d, Mask length: %d\n", i++,check(ipToIntConv("32.64.128.1")));
    printf("Test no %d, Mask length: %d\n", i++,check(ipToIntConv("10.20.0.0")));
    printf("Test no %d, Mask length: %d\n", i,check(ipToIntConv("10.22.0.0"))); //Should return -1 (it is not in the prefix database)

    printf("Test no %d, %s\n", i++, (!add(ipToIntConv("12.20.0.0"), 20)) ? "OK" : "NOK");
    printf("Test no %d, Mask length: %d\n", i++,check(ipToIntConv("12.20.128.1")));
    printf("Test no %d, %s\n", i++, (!del(ipToIntConv("12.20.0.0"), 20)) ? "OK" : "NOK");
    printf("Test no %d, Mask length: %d\n", i++,check(ipToIntConv("12.20.128.1")));


    return 0;
}

//Functions declarations
unsigned int binPow(unsigned int power) {
    if(power == 0) return 0;
    unsigned result = 2;
    for(; power>1; power--) {
        result *= 2;
    }
    return result;
}
/// 1 4 6 0
int del(const unsigned int base, const char mask) {
    for(int i = (int)dataBase.dataSize; i>=0; i--) {
        if(dataBase.data[dataBase.dataSize - i].base==base && dataBase.data[dataBase.dataSize - i].mask_length==mask) {
            memset(&dataBase.data[dataBase.dataSize-i], 0, sizeof(struct prefix));
            for(int j = i; j< dataBase.dataSize -1 ; i++) { //Moving
                dataBase.data[j] = dataBase.data[j+1];
            }
            --dataBase.dataSize;
            return 0; //This prefix is already in the database
        }
    }
    return -1;
}
int add(const unsigned int base, const char mask){

    if(mask > (char)32) return -1;
    struct prefix buff;
    buff.base = base;
    buff.mask_length = mask;
    buff.mask = maskLengthConv(mask);

    if(dataBase.dataSize == 0) {
        dataBase.data[dataBase.dataSize++] = buff;
        return 0;
    }else {
        for(int i = (int)dataBase.dataSize; i>=0; i--) {
            if(dataBase.data[dataBase.dataSize - i].base==base && dataBase.data[dataBase.dataSize - i].mask_length==mask) {
                return -1; //This prefix is already in the database
            }
        }
        dataBase.data[dataBase.dataSize++] = buff;
        sortPrefixData(&dataBase);
    }
    return 0;
}
unsigned int ipToIntConv(const char *ip) {

    const char *p = ip;
    char *end;
    unsigned int a = strtoul(p, &end, 10);
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

char check(unsigned int ip) {
    for(int i = 0; i<dataBase.dataSize; i++) {
        if((ip & dataBase.data[i].mask) == dataBase.data[i].base) {
            return dataBase.data[i].mask_length;
        }
    }
    return -1; //Not found ip in prefix database
}

int sortPrefixData() {
    struct prefix buff;
    if(dataBase.dataSize<2) return -1; //Nothing to sort
    else {
        for(int step=(int)dataBase.dataSize-1; step>=1; step--){
            if(dataBase.data[step].mask_length<=dataBase.data[step - 1].mask_length) return 0;
            else {
                buff = dataBase.data[step-1];
                dataBase.data[step - 1] = dataBase.data[step];
                dataBase.data[step] = buff;
            }
        }
    }
    return 0;
}