#include <iostream>
using namespace std;

#include <stdlib.h>

char* my_malloc(const int bytes_to_alloc, char* total_mem) {
    int bytes_free = 0;
    int offset; // loop counter, holds relative memory location

    // find the required number of free bytes in our total pool
    // since we aren't actually allocating memory at an OS level, we assume NULL is free
    for (offset = 0; offset < 2097152; offset++) {
        if (total_mem[offset] == 0) {
            bytes_free++;
        } else {
            bytes_free = 0;
        }

        if (bytes_free >= bytes_to_alloc) {
            break;
        }
    }

    // return pointer to beginning of allocated memory if found, otherwise 0
    if (bytes_free != bytes_to_alloc) {
        return 0;
    } else {
        return total_mem + offset - bytes_to_alloc + 1;
    }
}


void my_free(int length, char* allocated) {
    // as we don't have any access to OS-level memory management constructs
    // we must be given the length of the allocated memory space
    for (int i = 0; i < length; i++) {
        allocated[i] = 0;
    }
}


int main() {
    // allocate 20MB as our total memory pool
    // initialized to NULL, so we can more easily check for free memory
    char* total_mem = (char*) calloc(2097152,1);

    char* test = my_malloc(3, total_mem);
    test[0] = 'a';
    test[1] = 'b';
    test[2] = 'c';
    char* test2 = my_malloc(2, total_mem);
    test2[0] = 'd';
    test2[1] = 'e';
    char* test3 = my_malloc(1, total_mem);
    test3[0] = 'f';

    cout << "This should print \"abcdef\": " << test[0] << test[1] << test[2] << test2[0] << test2[1] << test3[0] << endl;

    my_free(3, test);

    cout << "This should not segfault, but print NULL: " << test[0] << test[1] << test[2] << endl;

    free(total_mem);

    return 0;
}
