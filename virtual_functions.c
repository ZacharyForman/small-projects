#include <stdio.h>
#include <stdlib.h>

struct base_vtable;
struct base;
struct derived1;
struct derived2;

struct base_vtable {
    void (*printName)(struct base *b);
} base_vtabl, derived1_vtabl, derived2_vtabl;

struct base {
    struct base_vtable *v;
};

struct derived1 {
    struct base b;
    int instance_no;
};

struct derived2 {
    struct base b;
    const char *instance_string;
};

void base_printName(struct base *b)
{
    b->v->printName(b);
}

void base_print(struct base *b)
{
    printf("Hi from base class!\n");
}

void derived1_print(struct base *b)
{
    printf("Hi from derived1 class %d!\n", ((struct derived1*)b)->instance_no);
}

void derived2_print(struct base *b)
{
    printf("Hi from derived2 class %s!\n", ((struct derived2*)b)->instance_string);
}

struct base *new_base()
{
    struct base *ret = (struct base*) malloc(sizeof(struct base));
    ret->v = &base_vtabl;
    return ret;
}

struct derived1 *new_derived1(int val)
{
    struct derived1 *ret = (struct derived1*) malloc(sizeof(struct derived1));
    ret->b.v = &derived1_vtabl;
    ret->instance_no = val;
    return ret;
}

struct derived2 *new_derived2(const char *str)
{
    struct derived2 *ret = (struct derived2*) malloc(sizeof(struct derived2));
    ret->b.v = &derived2_vtabl;
    ret->instance_string = str;
    return ret;
}

void init() 
{
    base_vtabl.printName = base_print;
    derived1_vtabl.printName = derived1_print;
    derived2_vtabl.printName = derived2_print;
}

int main()
{
    init();
    struct base *b = new_base();
    struct base *d1 = (struct base*)new_derived1(5);
    struct base *d2 = (struct base*)new_derived2("numero uno");
    base_printName(b);
    base_printName(d1);
    base_printName(d2);
}