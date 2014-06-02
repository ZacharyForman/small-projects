#include <cstdio>
#include <cstdlib>
#include <ctime>

struct node {
    node *next;
    int val;
};

void swap_vals(node *a, node *b) {
    int tmp = b->val;
    b->val = a->val;
    a->val = tmp;
}

void print_list(node *root)
{
    printf("[ ");
    while(root != NULL) {
        printf("%d ", root->val);
        root = root->next;
    }
    printf("]\n");
}

void qs(node *start, node *end)
{
    if (start == end) {
        return;
    }
    node *last = start;
    for (node *pos = start; pos != end; pos = pos->next) {
        if (pos->val < start->val) {
            last = last->next;
            swap_vals(last, pos);
        }
    }
    swap_vals(start, last);
    qs(start, last);
    qs(last->next, end);
}

node *generate_list(int i)
{
    if (!i) return NULL;
    node *n = new node();
    n->val = rand() % 200;
    n->next = generate_list(i-1);
    return n;
}

int main()
{
    srand(time(NULL));
    node * root = generate_list(100);
    print_list(root);
    qs(root, NULL);
    print_list(root);
}