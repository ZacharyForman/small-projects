//count the 1 bits in a number
int pop(unsigned int x)
{
    x = x - ((x >> 1) & 0x55555555U);
    x = (x & 0x33333333U) + ((x >> 2) & 0x33333333U);
    x = (x + (x >> 4)) & 0x0F0F0F0FU;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003FU;
}

//carry sum adder
#define CSA(h,l, a,b,c) \
    {unsigned u = a ^ b; unsigned v = c; \
    h = (a & b) | (u & v); l = u ^ v;}

//count the on bits in an array
int arrpop(unsigned A[], unsigned n)
{
    int tot = 0, i;
    unsigned ones = 0, twos = 0;
    for (i = 0; i <= n-2; i += 2) {
        CSA(twos, ones, ones, A[i], A[i+1]);
        tot = tot + pop(twos);
    }
    tot = 2*tot + pop(ones);

    if (n & 1) 
        tot = tot + pop(A[i]);

    return tot;
}