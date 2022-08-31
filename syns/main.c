#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/**
 * Intrusive list implementation
 */
typedef struct list {
    struct list *next;
} list;

typedef struct listitem {
    list items;
    void* data;
    bool visited;
} listitem;


/**
 * Hash table implementation with djb2 hash function
 * use linkedlist for collisions
 */
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

ht* ht_create(size_t capacity) {
    ht* table = malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }

    table->length = 0;
    table->capacity = capacity;
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

bool ht_contains(ht *table, char *key) {
    ht_entry *node = lookup(table, key);
    return node != NULL && node->key != NULL;
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
    } else {
        node->value = value;
    }
}

/**
 * Add a list to the map (w1 -> [w2..etc])
 */
void add_map(ht *table, char* w1, char* w2) {
    if (!ht_contains(table, w1)) {
        listitem* item = (listitem*)malloc(sizeof(listitem));
        item->items.next = NULL;
        item->data = w2;
        ht_set(table, w1, item);
    } else {
        listitem* root = (listitem*)ht_get(table, w1);
        listitem* item = (listitem*)malloc(sizeof(listitem));
        item->data = w2;
        item->items.next = &root->items;
    }
}

/**
 * Find all entries by traversing the list (dfs) and backtrack with visited flags
 */
void dfs(void* key, ht* table, listitem* syns) {
    if (syns == NULL) {
        syns = (listitem*)malloc(sizeof(listitem));
        syns->data = key;
    } else {
        listitem* next = (listitem*)malloc(sizeof(listitem));
        next->data = key;
        syns->items.next = &next->items;
        syns = next;
    }

    listitem* root = ht_get(table, key);
    while (root != NULL) {
        if (!root->visited) {
            root->visited = true;
            dfs(root->data, table, syns);
            root->visited = false;
        }
        if (root->items.next != NULL) {
            root = (void*)root->items.next - offsetof(listitem, items);
        } else {
            root = NULL;
        }
    }
}

void backtrack(ht* table, char* text, char* curr, int index, listitem* output, int* count) {
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** generateSentences(char *** synonyms, int synonymsSize, int* synonymsColSize, char * text, int* returnSize){
    // map<string, list<string>> for acyclic graph of syns
    //
    // given a term, dfs to find all neighbors

    ht* table = ht_create(synonymsSize * *synonymsColSize);
    for (int i = 0; i < synonymsSize; i++) {
        for (int j = i + 1; j < *synonymsColSize; j++) {
            char* syn1 = synonyms[i][i];
            char* syn2 = synonyms[i][j];
            add_map(table, syn1, syn2);
            add_map(table, syn2, syn1);
        }
    }


    listitem* output = malloc(sizeof(listitem));
    int count = 0;
    backtrack(table, text, "", 0, output, &count);

    char** results = calloc(count, sizeof(char*));
    int i = 0;
    while (output != NULL) {
        results[i++] = (char*)output->data;
        if (output->items.next != NULL) {
            output = (void*)output->items.next - offsetof(listitem, items);
        } else {
            output = NULL;
        }
    }

    free(output);
    ht_destroy(table);

    return results;
}


int main() {
    // given an acyclic graph if syns
    // ["happy", "joy"], ["sad", "sorrow"], ["joy", "cheerful"]
    //
    // and a sentence
    // "I am happy today and I would like to make something cheerful"
    //
    // produce all the possible sentences based on the syns

    generateSentences()

    return 0;
}
