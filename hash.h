#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_SIZE 10
#define RESIZE_FACTOR 2

typedef struct Entry {
    int key;
    int value;
    struct Entry *next;
} Entry;

typedef struct HashTable {
    Entry **buckets;
    int size;
    int count;
} HashTable;

unsigned int hashFunction(int key, int size);
HashTable* createTable(int initialSize);
void resizeTable(HashTable *table);
void insert(HashTable *table, int key, int value);
int search(HashTable *table, int key);
void freeTable(HashTable *table);
void printTable(HashTable *table);

#endif
