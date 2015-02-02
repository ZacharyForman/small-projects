// Bad implementation of a python like range generator in C++.
// With -O3, speed is comparable to regular for loop.
class range {
private:
  int l;
  int h;
  int s;
public:
  range(int _h) {
    l = 0;
    h = _h;
    s = 1;
  }
  range(int _l, int _h) {
    l = _l;
    h = _h;
    s = 1;
  }
  range(int _l, int _h, int _s) {
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
    return s<0?l>=r.h:l<r.h;
  }
  inline int operator*() const {
    return l;
  }
  inline void operator++() {
    l = l + s;
  }
};