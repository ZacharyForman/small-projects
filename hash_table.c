#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    void (*key_free)(key_t);
    void (*val_free)(val_t);
} map_t;

map_t *make_map(unsigned long sz, unsigned long (*hash_func)(key_t), 
                int (*compare)(key_t, key_t), void (*key_free)(key_t),
                void (*val_free)(val_t))
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
    ret->key_free = key_free;
    ret->val_free = val_free;
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
        } else if (bkt->next != NULL) {
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
        m->key_free(m->d[pos]->key);
        m->val_free(m->d[pos]->val);
        free(m->d[pos]);
        m->d[pos] = NULL;
    }
    bkt = m->d[pos];
    for(;;) {
        if(bkt == NULL) return;
        if(m->compare(k, bkt->key) == 0) {
            prev->next = bkt->next;
            m->key_free(bkt->key);
            m->val_free(bkt->val);
            free(bkt);
            return;
        }
        prev = bkt;
        bkt = bkt->next;
    }
}


/* Funcs used for init */

unsigned long hash_str(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + (unsigned)c; /* hash * 33 + c */

    return hash;
}

int mystrcmp(char *a, char *b)
{
    return strcmp(a,b);
}

void my_str_free(char *a)
{
    free(a);
}

void my_int_free(int a)
{
}

/* cool little map thing */
int main()
{
    int i;
    char c;
    char key[1024];
    int val;
    int *v;
    for (i = 0; i < 1024; i++)
        key[i] = 0;
    map_t *m = make_map(1024, hash_str, mystrcmp, my_str_free, my_int_free);
    for(;;) {
        c = 0;
        scanf("%c", &c);
        switch(c) {
        case 'q': return;
        case 's': 
            scanf("%s %d", key, &val);
            store(m, key, val);
        break;
        case 'r': 
            scanf("%s", key);
            v = get(m, key);
            if(v)
                printf("m[%s] == %d\n", key, *v);
            else 
                printf("m[%s] not stored\n");
        break;
        case 'd': 
            delete(m, key);
            printf("m[%s] removed\n", key);
        break;
        default:
        break;
        }
    }
}