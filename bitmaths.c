// arithmetic without using [-+]

int add(int a, int b)
{
  return b?add(a^b, (a&b)<<1):a; 
}

int sub(int a, int b)
{
  return add(a,add(~b,1));
}

int mul(int a, int b)
{
  if (b < 0)
    return mul(sub(0,a), sub(0,b));
  int ret = 0;
  while(b--)
      ret += a;
  return ret;
}

int div(int a, int b)
{
  int flip = 0;
  if (a&0x80000000)
    a = sub(0,a), flip = !flip;
  if (b&0x80000000)
    b = sub(0, b), flip = !flip;
  int ret = 0;
  while (a >= b)
    a=sub(a,b), ret++;
  if (flip)
    return sub(0,ret);
  return ret;
}

int main()
{
  int a;
  int b;
  char c;
  scanf("%d%c%d", &a, &c, &b);
  switch (c) {
    case '+': printf("%d\n", add(a,b)); break;
    case '-': printf("%d\n", sub(a,b)); break;
    case '*': printf("%d\n", mul(a,b)); break;
    case '/': printf("%d\n", div(a,b)); break;
  }
}