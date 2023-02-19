//
// Created by pandroid on 19.02.23.
//

#ifndef PHOENIXSYSTEMS_IPV4_PREFIX_IPV4_FUNC_H
#define PHOENIXSYSTEMS_IPV4_PREFIX_IPV4_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ipv4_structs.h"

//Function definitions
int add(struct prefix_data_base *, unsigned int, char); //Adding prefix to the database with sorting from the greatest to the smallest mask length.
int del(struct prefix_data_base *, unsigned int, char);
int sortPrefixData(struct prefix_data_base *); //Simple, once run bubble sort to sort added prefix to database by mask length (The largest number first).
inline char check(struct prefix_data_base *,unsigned int);

unsigned int binPow(unsigned int); //Increases the number 2 to the specified power (only positive values for this project).
unsigned int ipToIntConv(const char *); //Changes string ip address to unsigned.
unsigned int maskLengthConv(char); //Changes mask length into decimal number of mask.


#endif //PHOENIXSYSTEMS_IPV4_PREFIX_IPV4_FUNC_H
