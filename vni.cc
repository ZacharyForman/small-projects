#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct State {
  std::string id;
  std::string image_name;
  std::string text;
  std::vector<std::string> destinations;
  std::vector<std::string> options;
};

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " f";
  }

  std::fstream f(argv[1]);
  std::map<std::string, State> states;

  while (f) {
    State s;
    f >> s.id;
    f >> s.image_name;
    std::getline(f, s.text); // deal with trailing newline
    std::getline(f, s.text);
    int w = 0;
    for (int i = 0; i < s.text.length(); i++) {
      if (s.text[i] == '\\' && s.text[i+1] == 'n') {
        s.text[w++] = '\n';
        i++;
      } else {
        s.text[w++] = s.text[i];
      }
    }
    s.text.resize(w);
    char c;
    std::string str;
    for (;;) {
      c = f.get();
    if (c != ' ' && c != '\t') break;
      f >> str;
      s.destinations.push_back(str);
      getline(f, str);
      s.options.push_back(str);
    }
    f.putback(c);
    states[s.id] = s;
  }

  State s = states["start"];
  for (;;) {
    char opt = 'a';
    std::cout << s.text << std::endl;
    for (int i = 0; i < s.destinations.size(); i++) {
      std::cout << opt++ << ") " << s.options[i] << std::endl;
    }
    std::cout << std::endl;
  if (s.destinations.size() == 0) break;
    std::cin >> opt;
    if (opt >= 'a' && opt - 'a' < s.destinations.size()) {
      s = states[s.destinations[opt-'a']];
    } else {
      std::cout << opt << " is not an option." << std::endl;
    }
  }

  std::cout << "Game over!" << std::endl;
}
