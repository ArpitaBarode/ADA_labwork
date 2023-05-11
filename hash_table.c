#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node *table[TABLE_SIZE];
} HashTable;

unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % TABLE_SIZE;
}

Node* create_node(const char *key, const char *value) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;
    return node;
}

void free_node(Node *node) {
    free(node->key);
    free(node->value);
    free(node);
}

void put(HashTable *ht, const char *key, const char *value) {
    unsigned long index = hash(key);
    Node *node = ht->table[index];
    if (node == NULL) {
        ht->table[index] = create_node(key, value);
        return;
    }
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            free(node->value);
            node->value = strdup(value);
            return;
        }
        if (node->next == NULL) {
            node->next = create_node(key, value);
            return;
        }
        node = node->next;
    }
}

char* get(HashTable *ht, const char *key) {
    unsigned long index = hash(key);
    Node *node = ht->table[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void remove_key(HashTable *ht, const char *key) {
    unsigned long index = hash(key);
    Node *node = ht->table[index];
    Node *prev = NULL;
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (prev == NULL) {
                ht->table[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free_node(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

void print_table(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *node = ht->table[i];
        printf("%d: ", i);
        while (node != NULL) {
            printf("%s=%s ", node->key, node->value);
            node = node->next;
        }
        printf("\n");
    }
}

int main() {
    HashTable ht;
    memset(&ht, 0, sizeof(HashTable));
    put(&ht, "apple", "red");
    put(&ht, "banana", "yellow");
    put(&ht, "cherry", "red");
    print_table(&ht);
    printf("%s\n", get(&ht, "banana"));
    remove_key(&ht, "banana");
    print_table(&ht);
    return 0;
}
