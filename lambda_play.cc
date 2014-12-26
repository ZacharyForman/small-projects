#include <cstdio>

int main()
{
namespace{
  // basics
  int x = 5;

  auto f1 = [](int a) { return a + 1; };
  auto f2 = [=](int a) { return a + x; };
  auto f3 = [&](int a) { return a + x; };
  auto f4 = [&](int a) { x = a; };

  printf("x = %d\n", x);
  printf("f1(5) = %d\n", f1(5));
  printf("f2(3) = %d\n", f2(3));
  printf("f3(1) = %d\n", f3(1));

  f4(0);

  printf("x = %d\n", x);
  printf("f1(5) = %d\n", f1(5));
  printf("f2(3) = %d\n", f2(3));
  printf("f3(1) = %d\n", f3(1));
}
namespace{
  // stack smashing

}
}