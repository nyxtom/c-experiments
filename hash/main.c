#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct ht_entry {
    struct ht_entry *next;
    const char *key;
    void* value;
} ht_entry;

typedef struct ht {
    struct ht_entry **entries;
    size_t capacity;
    size_t length;
} ht;

#define INITIAL_CAPACITY 26

ht* ht_create() {
    ht* table = malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }

    table->length = 0;
    table->capacity = INITIAL_CAPACITY;
    table->entries = calloc(table->capacity, sizeof(ht_entry));
    if (table->entries == NULL) {
        free(table);
        return NULL;
    }
    return table;
}

void ht_destroy(ht *table) {
    free(table->entries);
    free(table);
}

uint64_t hash(char *s) {
    uint64_t hash = 5381;

    for (; *s != '\0'; s++) {
        hash = ((hash << 5) + hash) + *s;
    }

    return hash;
}

ht_entry *lookup(ht *table, char *key) {
    uint64_t hashcode = hash(key);
    size_t index = (size_t)(hashcode & (uint64_t)(table->capacity - 1));

    ht_entry *node;
    for (node = table->entries[index]; node != NULL; node = node->next) {
        if (strcmp(key, node->key) == 0) {
            return node;
        }
    }

    return NULL;
}

void* ht_get(ht *table, char *key) {
    ht_entry *node = lookup(table, key);
    if (node == NULL) {
        return NULL;
    }

    return node->value;
}

void ht_set(ht *table, char *key, void *value) {
    // TODO: if length is greater than capacity -> expand
    ht_entry *node = lookup(table, key);
    if (node == NULL) {
        ht_entry *node = (ht_entry*)malloc(sizeof(ht_entry));
        if (node == NULL || (node->key = strdup(key)) == NULL) {
            return;
        }

        uint64_t hashcode = hash(key);
        size_t index = (size_t)(hashcode & (uint64_t)(table->capacity - 1));
        node->next = table->entries[index];
        node->key = key;
        node->value = value;
        table->entries[index] = node;
        table->length++;
    }
}

int main() {
    ht *table = ht_create();
    ht_set(table, "foo", "bar");
    ht_set(table, "bleh", "asdf");
    ht_set(table, "bah", "askdfja");

    printf("%s: %s\n", "foo", (char*)ht_get(table, "foo"));
    printf("%s: %s\n", "bleh", (char*)ht_get(table, "bleh"));
    printf("%s: %s\n", "bah", (char*)ht_get(table, "bah"));

    ht_destroy(table);
}
