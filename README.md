# PhoenixSystems-IPv4-Prefix
Simple IPv4 prefix management with adding, deleting and checking functions.
## Requirements and compilation
[Here](build/Compilation.md)

## Functions and structs description
Every project functions and structs definition and declarations may be found in [IPv4_prefix_manager](IPv4_prefix_manager) directory.
### Structs:
* struct Prefix - structure with contains base, subnetMask (added to improve check function efficiency) and maskLength
* struct PrefixDatabase - contains all prefixes and size of database. Prefixes are sorted by mask length

### Functions:
* `unsigned int IPv4_stringToIntConv(const char *ip, char *status)` - converting string type ip (like "10.0.0.0") into binary form. Changes `status` into -1 when conversion is invalid and 0 when it is successful
* `unsigned int maskLengthToSubnetConv(char maskLength, char *status)` - converting mask length into binary subnet mask form. Changes `status` into -1 when conversion is invalid and 0 when it is successful
* `int add(struct PrefixDatabase *dataBase, unsigned int base, char mask, char *status)` - adding prefix to database. Uses binary search to insert new record in sorted way
* `int del(struct PrefixDatabase *dataBase, unsigned int base, char mask, const char *status)` - deletes prefix from database
* `char check(struct PrefixDatabase *dataBase, unsigned int ip, const char *status)` - is checking whether IP address is included in some prefix in the database. Returns the greatest mask of the prefix in database (uses linear checking guarantee
  the mask will be the greatest)

## Testing
    
In this project I have used [Unity](http://www.throwtheswitch.org/unity) Test framework. Test file is included in ./test directory
