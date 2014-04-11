#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned long hash_str(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + (unsigned)c; /* hash * 33 + c */

    return hash;
}

typedef char *key_t;
typedef int val_t;

struct bucket
{
    key_t  key;
    val_t  val;
    struct bucket *next;
};

struct bucket *make_bucket(key_t key, val_t val)
{
    struct bucket *ret;

    ret = (struct bucket*)malloc(sizeof(struct bucket));
    ret->key = key;
    ret->val = val;
    ret->next = NULL;
    return ret;
}

typedef struct hash_table
{
    struct bucket **d;
    unsigned long sz;
    unsigned long (*hash_func)(key_t);
    int (*compare)(key_t, key_t);
} map_t;

map_t *make_map(unsigned long sz, unsigned long (*hash_func)(key_t), int (*compare)(key_t, key_t))
{
    int i = 0;
    map_t *ret;

    ret = (map_t*)malloc(sizeof(map_t));
    ret->sz = sz;
    ret->d = (struct bucket**) malloc(sz * sizeof(struct bucket*));
    for (i = 0; i < sz; i++)
        ret->d[i] = NULL;
    ret->hash_func = hash_func;
    ret->compare = compare;
    return ret;
}

void store(map_t *m, const key_t k, const val_t val)
{
    unsigned long pos;
    struct bucket *bkt;

    pos = m->hash_func(k) % m->sz;
    if (m->d[pos] == NULL) {
        m->d[pos] = make_bucket(k, val);
        return;
    }
    bkt = m->d[pos];
    while (bkt->next != NULL) {
        if (m->compare(k, bkt->key) == 0) {
            bkt->val = val;
            return;
        }
        bkt = bkt->next;
    }
    if (m->compare(k, bkt->key) == 0) {
        bkt->val = val;
        return;
    }
    bkt->next = make_bucket(k, val);
    return;
}

val_t *get(map_t *m, const key_t k)
{
    unsigned long pos;
    struct bucket *bkt;

    pos = m->hash_func(k) % m->sz;
    if (m->d[pos] == NULL) {
        return NULL;
    }
    bkt = m->d[pos];
    for(;;)
        if (m->compare(k, bkt->key) == 0){
            return &(bkt->val);
        } else if (bkt->next == NULL) {
            bkt = bkt->next;
        } else {
            return NULL;
        }
}

void delete(map_t *m, const key_t k)
{
    unsigned long pos;
    struct bucket *bkt;
    struct bucket *prev;

    prev = NULL;
    pos = m->hash_func(k) % m->sz;
    if (m->d[pos] == NULL) {
        return;
    }
    if (m->compare(m->d[pos]->key, k) == 0) {
        free(m->d[pos]->key);
        free(m->d[pos]);
        m->d[pos] = NULL;
    }
    bkt = m->d[pos];
    for(;;) {
        if(bkt == NULL) return;
        if(m->compare(k, bkt->key) == 0) {
            prev->next = bkt->next;
            free(bkt->key);
            free(bkt);
            return;
        }
        prev = bkt;
        bkt = bkt->next;
    }
}

int mystrcmp(char* a, char* b)
{
    return strcmp(a,b);
}

int main()
{
    map_t *m = make_map(1024, hash_str, mystrcmp);
    store(m, strdup("hello"), 1);
    store(m, strdup("world"), 2);
    printf("m[hello]: %d\n", *get(m, "hello"));
    printf("m[world]: %d\n", *get(m, "world"));
    printf("&m[foo]:  %p\n\n", get(m, "foo"));
    delete(m, "hello");
    printf("m[hello]: %p\n", get(m, "hello"));
    printf("m[world]: %d\n", *get(m, "world"));
    printf("&m[foo]:  %p\n\n", get(m, "foo"));
    store(m, "world", 100);
    printf("m[hello]: %p\n", get(m, "hello"));
    printf("m[world]: %d\n", *get(m, "world"));
    printf("&m[foo]:  %p\n\n", get(m, "foo"));
}