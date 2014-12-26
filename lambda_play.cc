#include <cstdio>

int main()
{
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

  int y = 5;
  // mutable required to modify it locally.
  auto f5 = [=](int a) mutable { 
    printf("%d\n", y); // y
    y = a;
    printf("%d\n", y); // y == a
  };
  f5(1);
  printf("%d\n", y);

  auto f6 = [](int a) {
    int x = a;
    auto f7 = [&]() { return x; };
    return f7;
  };

  auto f7 = f6(11);
  printf("%d\n", f7()); // 11!
  printf("%d\n", f7()); // Garbage!
  printf("%d\n", f7()); // Garbage!

}