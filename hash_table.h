#ifndef _hash_table_h_
#define _hash_table_h_

#include <cstdlib> //NULL

template<typename Key, typename Value>
class Bucket {
public:
    Key *k;
    Value *v;
    Bucket<Key, Value> *next;

    Bucket(Key k, Value v)
    {
        this->k = new Key(k);
        this->v = new Value(v);
        this->next = NULL;
    }

    ~Bucket()
    {
        delete k;
        delete v;
        delete next;
    }
};

template<typename Key, typename Value>
class Map {
public:
    Map(int size, unsigned long (*hash)(Key)) {
        this->sz = size;
        this->hash = hash;
        this->d = new Bucket<Key,Value>*[size];
        for(int i = 0; i < sz; i++) {
            d[i] = NULL;
        }
    }

    ~Map()
    {
        for(int i = 0; i < sz; i++) {
            delete d[i];
        }
        delete[] d;
    }

    Value *get(const Key k)
    {
        Bucket<Key, Value> *bkt;
        unsigned long pos = this->hash(k) % this->sz;
        if (this->d[pos] == NULL) {
            return NULL;
        }
        bkt = this->d[pos];
        for(;;)
            if (k == *bkt->k){
                return bkt->v;
            } else if (bkt->next == NULL) {
                bkt = bkt->next;
            } else {
                return NULL;
            }
        return NULL;
    }

    void remove(const Key k)
    {
        unsigned long pos;
        Bucket<Key, Value> *bkt;
        Bucket<Key, Value> *prev;

        prev = NULL;
        pos = this->hash(k) % this->sz;
        if (this->d[pos] == NULL) {
            return;
        }
        if (*this->d[pos]->k == k) {
            delete this->d[pos];
            this->d[pos] = NULL;
        }
        bkt = this->d[pos];
        for(;;) {
            if (bkt == NULL) return;
            if (k == *bkt->k) {
                prev->next = bkt->next;
                bkt->next = NULL;
                delete bkt;
                return;
            }
            prev = bkt;
            bkt = bkt->next;
        }
    }

    void store(const Key k, const Value v)
    {
        unsigned long pos;
        Bucket<Key, Value> *bkt;

        pos = this->hash(k) % this->sz;
        if (this->d[pos] == NULL) {
            this->d[pos] = new Bucket<Key, Value>(k, v);
            return;
        }
        bkt = this->d[pos];
        while (bkt->next != NULL) {
            if (k == *bkt->k) {
                *bkt->v = v;
                return;
            }
            bkt = bkt->next;
        }
        if (*bkt->k == k) {
            *bkt->v = v;
            return;
        }
        bkt->next = new Bucket<Key, Value>(k,v);
        return;
    }



private:
    Bucket<Key,Value> **d;
    int sz;
    unsigned long (*hash)(Key);

};

#endif