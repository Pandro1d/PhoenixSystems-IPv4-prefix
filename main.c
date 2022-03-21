#include <stdio.h>
#define MAX_DATA_SIZE 100 //Depends on size we need (can be of course changed into dynamic allocation, but it is slower)

struct prefix {
    unsigned int base;
    unsigned int mask;
    char mask_length;
};

struct prefix_data_base {
    struct prefix data[MAX_DATA_SIZE];
    size_t dataSize;
};
int main() {

    return 0;
}

