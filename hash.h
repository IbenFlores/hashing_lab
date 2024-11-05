#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_SIZE 10
#define RESIZE_FACTOR 2

typedef struct Entry {
    int key;       // The original number
    int value;     // Could store the last digit or some related numeric value
    struct Entry *next; // Pointer to the next entry for collision handling
} Entry;

typedef struct HashTable {
    Entry **buckets; // Array of pointers to Entry nodes
    int size;        // Number of buckets
    int count;       // Number of entries
} HashTable;

unsigned int hashFunction(int key, int size);
HashTable* createTable(int initialSize);
void resizeTable(HashTable *table);
void insert(HashTable *table, int key, int value);
int search(HashTable *table, int key);
void freeTable(HashTable *table);
void printTable(HashTable *table);

#endif // HASH_H
