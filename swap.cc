#include <cstdio>
#include <utility>

namespace std {
template<>
void swap<char>(char &a, char &b) {
  a = '!';
  b = '?';
}
}

int main()
{
  char x = 'a';
  char y = 'b';
  printf("x=%c, y=%c\n", x, y);
  std::swap(x,y);
  printf("x=%c, y=%c\n", x, y);
}