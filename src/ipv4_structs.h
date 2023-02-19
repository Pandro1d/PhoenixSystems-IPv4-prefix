//
// Created by pandroid on 19.02.23.
//

#ifndef PHOENIXSYSTEMS_IPV4_PREFIX_IPV4_STRUCTS_H
#define PHOENIXSYSTEMS_IPV4_PREFIX_IPV4_STRUCTS_H

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
#endif //PHOENIXSYSTEMS_IPV4_PREFIX_IPV4_STRUCTS_H
