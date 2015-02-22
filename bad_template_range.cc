// Bad implementation of a python like range generator in C++.
// With -O3, speed is comparable to regular for loop.
namespace inner {
template<typename T, typename I>
class range {
private:
  T l;
  T h;
  I s;
public:
  range(T _l, T _h, I _s) {
    l = _l;
    h = _h;
    s = _s;
  }
  range &begin() {
    return *this;
  }
  range &end() {
    return *this;
  }
  inline bool operator!=(range r) const {
    return l!=h;
  }
  inline T operator*() const {
    return l;
  }
  inline void operator++() {
    l = l + s;
  }
};
} // namespace inner

template<typename T, typename I>
inner::range<T, I> range(T l, T h, I s)
{
  return inner::range<T,I>(l, h, s);
}

#include <iostream>
#include <string>
int main()
{
  for (auto i : range(std::string("a"), std::string("aaaaaaaaaa"), 'a')) {
    std::cout << i << std::endl;
  }
}