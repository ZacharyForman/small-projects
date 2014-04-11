int add(int a, int b)
{
    if(!b) return a;
    return add(a^b, (a&b)<<1);
}

int sub(int a, int b)
{
    return add(a, add(~b, 1));
}

int mult(int a, int b)
{
    int ret = 0;
    if (b < 0) {
        a = sub(0, a);
        b = sub(0, a);
    }
    while(b-->0)
        ret = add(ret, a);
    return ret;
}