# PhoenixSystems-IPv4-Prefix
Simple IPv4 prefix management with adding, deleting and adding functions.
## Requirements and compilation
[Here](build/Compilation.md)

## Functions and structs description
Every project functions and structs definition and declarations may be found in ./IPv4_prefix_manager directory.
### Structs:
* struct Prefix - structure with contains base, subnetMask (added to improve check function efficiency) and maskLength
* struct PrefixDatabase - contains all prefixes and size of database. Prefixes are sorted by mask length

### Functions:
* int add(struct PrefixDatabase *dataBase, unsigned int base, char mask, char *status) - adding prefix to database. Uses binary search to insert new record in sorted way
* int del(struct PrefixDatabase *dataBase, unsigned int base, char mask, const char *status) - deletes prefix from database
* char check(struct PrefixDatabase *dataBase, unsigned int ip, const char *status) - is checking whether IP address is included in some prefix in the database. Returns the greatest mask of the prefix in database (uses linear checking guarantee
  the mask will be the greatest)
## Testing
    
In this project I have used Unity Test framework. Test file is included in ./test directory