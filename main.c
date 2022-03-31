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
//Function definitions
int add(unsigned int, char);
int del(unsigned int, char);
inline char check(unsigned int);

unsigned int binPow(unsigned int); //Increases the number 2 to the specified power (only positive values for this project).
unsigned int ipToIntConv(const char *); //Changes string ip address to unsigned.
unsigned int maskLengthConv(char); //Changes mask length into decimal number of mask.
int sortPrefixData(); //Simple, once run bubble sort to sort added prefix to database by mask length (The largest number first).

void testFor_add_del_fun(int, unsigned *);
void testFor_check_fun(char, unsigned *);

//GLOBAL VAR
struct prefix_data_base dataBase = {{0,0,0}, 0};

int main() {
    unsigned int iter = 1;
    ///Checking add, check function
    testFor_add_del_fun(add(ipToIntConv("32.64.128.0"), 20), &iter);
    //1.^Should print OK
    testFor_add_del_fun(add(ipToIntConv("32.64.128.0"), 20), &iter);
    //2.Check if the same prefix will be added ^Should print NOK
    testFor_add_del_fun(add(ipToIntConv("10.20.0.0"), 16), &iter);
    //3.^Should print OK
    testFor_add_del_fun(add(ipToIntConv("10.20.0.0"), 15), &iter);
    //4.^Should print OK
    testFor_add_del_fun(add(ipToIntConv("10.20.0.0"), 13), &iter);
    //5.^Should print OK
    testFor_check_fun(check(ipToIntConv("32.64.128.1")), &iter);
    //6.^Should print Mask length: 20 is in the 32.64.128.0/20 prefix
    testFor_check_fun(check(ipToIntConv("10.20.0.1")), &iter);
    //7.^Should Mask length: 16 -> 10.20.0.0 is in the 10.20.0.0/16 prefix (16 is the smallest prefix)
    testFor_check_fun(check(ipToIntConv("10.22.0.0")), &iter);
    //8.^Should print Mask length: -1 -> 10.22.0.0 is not in the prefix database
    testFor_check_fun(check(ipToIntConv("255.255.255.255")), &iter);
    //9.^Should print Mask length: -1 -> 255.255.255.255 is not in the prefix database
    ///Checking del function
    testFor_add_del_fun(add(ipToIntConv("12.20.0.0"), 20), &iter);
    //10.^Should print OK
    testFor_check_fun(check(ipToIntConv("12.20.15.0")), &iter);
    //11.^Should print Mask length: 20 is in the 12.20.0.0/20 prefix
    testFor_add_del_fun(del(ipToIntConv("12.20.0.0"), 20), &iter);
    //12.^Should print OK 12.20.15.1 is in the 12.20.0.0/20 prefix
    testFor_check_fun(check(ipToIntConv("0")), &iter);
    //13.^Should print Mask length: -1 -> 12.20.15.1 is not in the prefix database
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

int del(const unsigned int base, const char mask) {
    for(int i = 0; i<dataBase.dataSize; i++) {
        if(dataBase.data[i].base==base && dataBase.data[i].mask_length==mask) {
            memset(&dataBase.data[i], 0, sizeof(struct prefix));
            for(int j = i; j< dataBase.dataSize -1 ; j++) { //Moving
                dataBase.data[j] = dataBase.data[j+1];
            }
            --dataBase.dataSize;
            return 0;
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

char check(unsigned int ip) {
    for(int i = 0; i<dataBase.dataSize; i++) {
        if((ip & dataBase.data[i].mask) == dataBase.data[i].base) {
            return dataBase.data[i].mask_length;
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

///Tests
void testFor_add_del_fun(const int result, unsigned *testNumber) {
    printf("Test no %d, %s\n", (*testNumber)++, (!result) ? "OK" : "NOK");
}
void testFor_check_fun(const char result, unsigned *testNumber) {
    printf("Test no %d, Mask length: %d\n", (*testNumber)++, result);
}