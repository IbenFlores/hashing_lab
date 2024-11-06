#include <stdio.h>
#include "hash.h"

int main() {
    HashTable *table = createTable(INITIAL_SIZE);

    insert(table, 123, 3);
    insert(table, 45, 5);
    insert(table, 9876, 6);
    insert(table, 10, 0);
    insert(table, 6789, 9);
    insert(table, 111, 1);
    insert(table, 125, 5);
    insert(table, 127, 6);

    printTable(table);

    freeTable(table);

    return 0;
}
