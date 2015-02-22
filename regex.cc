// Implementation of a state machine using nifty C++11 features.

#include <string>
#include <iostream>

struct State {
  virtual State *operator()(std::string::iterator &s) = 0; 
};

template<typename F>

struct _State : public State {

  _State<F>(const F &_f) : f(_f) { }

  const F &f;

  State *operator()(std::string::iterator &s) {
    return f(s);
  }

};

State *astate;
State *bstate;

constexpr auto fa = [](std::string::iterator &s) {
  if (*s == 'a') {
    s++; 
    return bstate;
  } 
  return (State*)nullptr;
};
constexpr auto fb = [](std::string::iterator &s) {
  if (*s == 'b') {
    s++; 
    return astate;
  } 
  return (State*)nullptr;
};

int main()
{
  astate = new _State<decltype(fa)>(fa);
  bstate = new _State<decltype(fb)>(fb);
  std::string s;
  std::cin >> s;
  State *st = astate;
  auto sit = s.begin();
  while (st=(*st)(sit)) {
    std::cout << "parsed a character" << std::endl;
  }
  std::cout << "Done." << std::endl;
}