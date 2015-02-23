#include <vector>
#include <string>
#include <iostream>

namespace {
enum State {q1, q2, q3};
}
std::vector<std::string> split_path(std::string path)
{
  std::vector<std::string> ret;
  State st = q1;
  const char *str = path.c_str();
  std::string component = "";
  while (*str || st == q3) {
    switch (st) {
      case q1: {
        if (*str == '/') {
          st = q2;
        } else {
          component += *str;
          st = q3;
        }
        break;
      }
      case q2: {
        if (*str != '/') {
          component += *str;
          st = q3;
        }
        break;
      }
      case q3: {
        if (*str == 0) {
          ret.push_back(component);
          return ret;
        }
        if (*str == '/') {
          ret.push_back(component);
          component.clear();
          st = q2;
        } else {
          component += *str;
        }
        break;
      }
    }
    str++;
  }
  return ret;
}

int main()
{
  std::string s;
  std::cin >> s;
  auto v = split_path(s);
  for (auto str : v) {
    std::cout << str << " ";
  }
  std::cout << std::endl;
}
