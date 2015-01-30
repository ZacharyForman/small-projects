// arithmetic without using [-+]

int add(int a, int b)
{
  return b?add(a^b, a&b):a; 
}

int sub(int a, int b)
{
  return add(a,add(~b,1));
}