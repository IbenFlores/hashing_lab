#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

unsigned int hashFunction(int key, int size) {
    return key % size;
}

HashTable* createTable(int initialSize) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (!table) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    table->size = initialSize;
    table->count = 0;

    table->buckets = (Entry **)malloc(table->size * sizeof(Entry *));
    if (!table->buckets) {
        printf("Memory allocation failed for buckets\n");
        free(table);
        return NULL;
    }

    for (int i = 0; i < table->size; i++) {
        table->buckets[i] = NULL;
    }

    return table;
}

void resizeTable(HashTable *table) {
    Entry **oldBuckets = table->buckets;
    int oldSize = table->size;

    table->size *= RESIZE_FACTOR;
    table->buckets = (Entry **)malloc(table->size * sizeof(Entry *));
    if (!table->buckets) {
        printf("Memory allocation failed for resized buckets\n");
        return;
    }

    for (int i = 0; i < table->size; i++) {
        table->buckets[i] = NULL;
    }

    for (int i = 0; i < oldSize; i++) {
        Entry *entry = oldBuckets[i];
        while (entry != NULL) {
            int newBucketIndex = hashFunction(entry->key, table->size);
            Entry *newEntry = (Entry *)malloc(sizeof(Entry));
            if (!newEntry) {
                printf("Memory allocation failed for rehashed entry\n");
                return;
            }
            newEntry->key = entry->key;
            newEntry->value = entry->value;
            newEntry->next = table->buckets[newBucketIndex];
            table->buckets[newBucketIndex] = newEntry;
            
            entry = entry->next;
        }
    }

    free(oldBuckets);
}



void insert(HashTable *table, int key, int value) {
    if (table->count == table->size) {
        resizeTable(table);
    }

    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    if (!newEntry) {
        printf("Memory allocation failed for new entry\n");
        return;
    }
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = NULL;

    int bucketIndex = hashFunction(key, table->size);

    if (table->buckets[bucketIndex] == NULL) {
        table->buckets[bucketIndex] = newEntry;
    } else {
        Entry *current = table->buckets[bucketIndex];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newEntry;
    }

    table->count++;
}



int search(HashTable *table, int key) {
    int bucketIndex = hashFunction(key, table->size);

    Entry *current = table->buckets[bucketIndex];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }

    printf("Key %d not found in the hash table.\n", key);
    return -1;
}

void freeTable(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        Entry *entry = table->buckets[i];
        while (entry != NULL) {
            Entry *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }

    free(table->buckets);

    free(table);
}


void printTable(HashTable *table) {
    printf("HashTable contents:\n");

    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        
        Entry *entry = table->buckets[i];
        if (entry == NULL) {
            printf("NULL\n");
        } else {
            while (entry != NULL) {
                printf("{key: %d, value: %d} -> ", entry->key, entry->value);
                entry = entry->next;
            }
            printf("NULL\n");
        }
    }
}



