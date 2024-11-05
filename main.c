#include <stdio.h>
#include "hash.h"

int main() {
    HashTable *table = createTable(INITIAL_SIZE);

    // Insert some numbers and their last digits
    insert(table, 123, 3);   // Last digit of 123 is 3
    insert(table, 45, 5);    // Last digit of 45 is 5
    insert(table, 9876, 6);  // Last digit of 9876 is 6
    insert(table, 10, 0);    // Last digit of 10 is 0
    insert(table, 6789, 9);  // Last digit of 6789 is 9
    insert(table, 111, 1);   // Last digit of 111 is 1
    insert(table, 125, 5);

    // Print the contents of the hash table
    printTable(table);

    // Free the hash table after use
    freeTable(table);

    return 0;
}
