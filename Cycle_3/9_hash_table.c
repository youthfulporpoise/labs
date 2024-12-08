/* Program: HASH TABLE
 * Date: 8 Dec. '24
 *
 * Implement a hash table using division hash.  The collisions are resolved
 * using chaining method.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* VS is the value size.
 * That is the length of the value string.*/
#define VS 18

/* Declare each element of our hash table. */
typedef struct node Node;
typedef struct node {
    unsigned key;
    char value[VS];
    Node* next;
} Node;
/* Each key-value pair is a node, since we are using chaining to resolve
 * collisions.  In this implementation, a bucket can have as many slots as is
 * needed. */

/* A hash table is simply an array of key-value pairs. */
typedef Node** HashTable;

/* The size of hash table.  Making this global will help us avoid always passing
 * it as an argument to functions and procedures, and will render them
 * semantically more meaningful. */
size_t ht_size;

/* Initialize the hash table with size n. */
HashTable initialize(HashTable ht)
{
    printf("Table size: ");
    scanf("%zu", &ht_size);

    printf("Initializing hash table of size %zu ...\n", ht_size);
    ht = calloc(ht_size, sizeof (Node*));
    return ht;
}

/* Calculate the hash of a string s.
 * We use division hashing. */
unsigned hash(unsigned key)
{
    return key % ht_size;
}

/* Insert a key-value pair into the hash table.
 * The collisions are resolved through chaining.  Collisions are always
 * resolved; there will be no overflows (unless physical memory exhausted). */
void insert(HashTable ht, unsigned key, char *value)
{
    unsigned hv = hash(key); /* hv is th hash value. */
    Node* p = ht[hv];

    if (p == NULL) {
        p = ht[hv] = calloc(1, sizeof (Node));
        p->key = key;
        strlcpy(p->value, value, VS); 
    } else {
        while (p->next != NULL)
            p = p->next;
        p->next = calloc(1, sizeof (Node));
        p = p->next;

        p->key = key;
        strlcpy(p->value, value, VS);
    }
    printf("Inserted: (%u, %s) at %u\n", key, value, hv);
}

/* Print a hash table. */
void print(HashTable ht)
{
    for (size_t i = 0; i < ht_size; ++i) {
        printf("%zu: ", i);
        Node* p = ht[i];

        while (p != NULL) {
            printf("(%u, %s) -> ", p->key, p->value);
            p = p->next;
        } printf("NULL\n");
    }
}

/* Delete an entry corresponding to the key specified. */
void delete(HashTable ht, unsigned key)
{
    unsigned hv = hash(key);
    Node *p = ht[hv], *q = ht[hv];

    while (p != NULL) {
        if (p->key == key) {
            if (p == q) ht[hv] = NULL;
            else q->next = p->next;
            free(p);
        } else {
            q = p;
            p = p->next;
        }
    }
    printf("Deleted: Key %u\n", key);
}

int main()
{
    HashTable ht;
    ht = initialize(ht);

    /* These variables might be useful. */
    unsigned key;
    char value[16];
    char choice;

    printf("\n(i) Insert  (d) Delete  (p) Print  (q) Quit");
    while (true) {
        printf("\nChoice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'i':
                printf("Key, Value: ");
                scanf("%u %s", &key, value);
                insert(ht, key, value);
                break;

            case 'd':
                printf("Key: ");
                scanf("%u", &key);
                delete(ht, key);
                break;

            case 'p':
                print(ht);
                break;

            case 'q':
                puts("Quitting ...");
                exit(0);

            default:
                printf("%c: invalid choice\n", choice);
                continue;
        }
    }
}
