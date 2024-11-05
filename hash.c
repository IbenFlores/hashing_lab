#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

// Hash function that uses the table size
unsigned int hashFunction(int key, int size) {
    return key % size; // Correctly computes the bucket index
}

// Initialize the hash table
HashTable* createTable(int initialSize) {
    // Allocate memory for the hash table
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (!table) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Set initial size and count
    table->size = initialSize;
    table->count = 0;

    // Allocate memory for the array of buckets (pointers to Entry)
    table->buckets = (Entry **)malloc(table->size * sizeof(Entry *));
    if (!table->buckets) {
        printf("Memory allocation failed for buckets\n");
        free(table);
        return NULL;
    }

    // Initialize each bucket to NULL
    for (int i = 0; i < table->size; i++) {
        table->buckets[i] = NULL;
    }

    return table;
}

// Resize the table when needed
void resizeTable(HashTable *table) {
    // Save the old buckets and the old size
    Entry **oldBuckets = table->buckets;
    int oldSize = table->size;

    // Double the size of the table
    table->size *= RESIZE_FACTOR;
    table->buckets = (Entry **)malloc(table->size * sizeof(Entry *));
    if (!table->buckets) {
        printf("Memory allocation failed for resized buckets\n");
        return;
    }

    // Initialize new buckets to NULL
    for (int i = 0; i < table->size; i++) {
        table->buckets[i] = NULL;
    }

    // Rehash all entries from the old buckets and insert them into the new table
    for (int i = 0; i < oldSize; i++) {
        Entry *entry = oldBuckets[i];
        while (entry != NULL) {
            // Rehash and insert the entry into the new table
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

    // Free the old buckets
    free(oldBuckets);
}



// Insert a key-value pair into the hash table
void insert(HashTable *table, int key, int value) {
    // Resize the table if necessary (when the table is full)
    if (table->count == table->size) {
        resizeTable(table);
    }

    // Create a new entry
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    if (!newEntry) {
        printf("Memory allocation failed for new entry\n");
        return;
    }
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = NULL;

    // Find the appropriate bucket using the hash function
    int bucketIndex = hashFunction(key, table->size);

    // Insert the entry into the corresponding bucket
    if (table->buckets[bucketIndex] == NULL) {
        // No collision, place the entry in the bucket
        table->buckets[bucketIndex] = newEntry;
    } else {
        // Collision: add the entry to the linked list in this bucket
        Entry *current = table->buckets[bucketIndex];
        while (current->next != NULL) {
            current = current->next;  // Traverse to the end of the list
        }
        current->next = newEntry;  // Link the new entry
    }

    // Increment the number of entries in the hash table
    table->count++;
}



// Retrieve a value by key from the hash table
int search(HashTable *table, int key) {
    // Find the bucket index using the hash function
    int bucketIndex = hashFunction(key, table->size);

    // Traverse the linked list at that bucket index
    Entry *current = table->buckets[bucketIndex];
    while (current != NULL) {
        // If the key matches, return the value
        if (current->key == key) {
            return current->value;  // Return the value associated with the key
        }
        current = current->next;  // Move to the next entry in the linked list
    }

    // If the key is not found, return an indicator (e.g., -1)
    // You can also return a custom error code or a flag to indicate key not found
    printf("Key %d not found in the hash table.\n", key);
    return -1;  // or any value indicating "not found"
}

// Free the memory allocated for the hash table
void freeTable(HashTable *table) {
    // Traverse through all the buckets
    for (int i = 0; i < table->size; i++) {
        Entry *entry = table->buckets[i];
        while (entry != NULL) {
            Entry *temp = entry;
            entry = entry->next;  // Move to the next entry
            free(temp);  // Free the current entry
        }
    }

    // Free the buckets array
    free(table->buckets);

    // Free the hash table itself
    free(table);
}


void printTable(HashTable *table) {
    printf("HashTable contents:\n");

    // Traverse through each bucket
    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        
        // Traverse the linked list at this bucket index
        Entry *entry = table->buckets[i];
        if (entry == NULL) {
            printf("NULL\n");  // No entries in this bucket
        } else {
            while (entry != NULL) {
                printf("{key: %d, value: %d} -> ", entry->key, entry->value);
                entry = entry->next;  // Move to the next entry
            }
            printf("NULL\n");  // End of the linked list
        }
    }
}



