#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <string>

std::map< char, std::vector<std::string> > ascii_chars = {
  {'A', {
    " AAA ",
    "A   A",
    "AAAAA",
    "A   A",
    "A   A"
  }},
  {'B', {
    "BBBB ",
    "B   B",
    "BBBB ",
    "B   B",
    "BBBB "
  }},
  {'C', {
    " CCCC",
    "C    ",
    "C    ",
    "C    ",
    " CCCC"
  }},
  {'D', {
    "DDDD ",
    "D   D",
    "D   D",
    "D   D",
    "DDDD "
  }},
  {'E', {
    "EEEEE",
    "E    ",
    "EEEEE",
    "E    ",
    "EEEEE"
  }},
  {'F', {
    "FFFFF",
    "F    ",
    "FFFFF",
    "F    ",
    "F    "
  }},
  {'G', {
    " GGGG",
    "G    ",
    "G  GG",
    "G   G",
    " GGGG"
  }},
  {'H', {
    "H   H",
    "H   H",
    "HHHHH",
    "H   H",
    "H   H"
  }},
  {'I', {
    "IIIII",
    "  I  ",
    "  I  ",
    "  I  ",
    "IIIII"
  }},
  {'J', {
    "JJJJJ",
    "    J",
    "    J",
    "J   J",
    " JJJ "
  }},
  {'K', {
    "K  K ",
    "K K  ",
    "KKK  ",
    "K  K ",
    "K   K",
  }},
  {'L', {
    "L    ",
    "L    ",
    "L    ",
    "L    ",
    "LLLLL"
  }},
  {'M', {
    "M   M",
    "MM MM",
    "M M M",
    "M   M",
    "M   M"
  }},
  {'N', {
    "N   N",
    "NN  N",
    "N N N",
    "N  NN",
    "N   N"
  }},
  {'O', {
    " OOO ",
    "O   O",
    "O   O",
    "O   O",
    " OOO "
  }},
  {'P', {
    "PPPP ",
    "P   P",
    "PPPP ",
    "P    ",
    "P    "
  }},
  {'Q', {
    " QQQ ",
    "Q   Q",
    "Q Q Q",
    "Q  Q ",
    " QQ Q"
  }},
  {'R', {
    "RRRR ",
    "R   R",
    "RRRR ",
    "R  R ",
    "R   R"
  }},
  {'S', {
    " SSSS",
    "S    ",
    " SSS ",
    "    S",
    "SSSS "
  }},
  {'T', {
    "TTTTT",
    "  T  ",
    "  T  ",
    "  T  ",
    "  T  "
  }},
  {'U', {
    "U   U",
    "U   U",
    "U   U",
    "U   U",
    " UUU "
  }},
  {'V', {
    "V   V",
    "V   V",
    " V V ",
    " VVV ",
    "  V  "
  }},
  {'W', {
    "W   W",
    "W   W",
    "W W W",
    "WW WW",
    "W   W"
  }},
  {'X', {
    "X   X",
    " X X ",
    "  X  ",
    " X X ",
    "X   X"
  }},
  {'Y', {
    "Y   Y",
    " Y Y ",
    "  Y  ",
    "  Y  ",
    "  Y  "
  }},
  {'Z', {
    "ZZZZZ",
    "   Z ",
    "  Z  ",
    " Z   ",
    "ZZZZZ"
  }},
  {'a', {
    " AAA ",
    "A   A",
    "AAAAA",
    "A   A",
    "A   A"
  }},
  {'b', {
    "BBBB ",
    "B   B",
    "BBBB ",
    "B   B",
    "BBBB "
  }},
  {'c', {
    " CCCC",
    "C    ",
    "C    ",
    "C    ",
    " CCCC"
  }},
  {'d', {
    "DDDD ",
    "D   D",
    "D   D",
    "D   D",
    "DDDD "
  }},
  {'e', {
    "EEEEE",
    "E    ",
    "EEEEE",
    "E    ",
    "EEEEE"
  }},
  {'f', {
    "FFFFF",
    "F    ",
    "FFFFF",
    "F    ",
    "F    "
  }},
  {'g', {
    " GGGG",
    "G    ",
    "G  GG",
    "G   G",
    " GGGG"
  }},
  {'h', {
    "H   H",
    "H   H",
    "HHHHH",
    "H   H",
    "H   H"
  }},
  {'i', {
    "IIIII",
    "  I  ",
    "  I  ",
    "  I  ",
    "IIIII"
  }},
  {'j', {
    "JJJJJ",
    "    J",
    "    J",
    "J   J",
    " JJJ "
  }},
  {'k', {
    "K  K ",
    "K K  ",
    "KKK  ",
    "K  K ",
    "K   K",
  }},
  {'l', {
    "L    ",
    "L    ",
    "L    ",
    "L    ",
    "LLLLL"
  }},
  {'m', {
    "M   M",
    "MM MM",
    "M M M",
    "M   M",
    "M   M"
  }},
  {'n', {
    "N   N",
    "NN  N",
    "N N N",
    "N  NN",
    "N   N"
  }},
  {'o', {
    " OOO ",
    "O   O",
    "O   O",
    "O   O",
    " OOO "
  }},
  {'p', {
    "PPPP ",
    "P   P",
    "PPPP ",
    "P    ",
    "P    "
  }},
  {'q', {
    " QQQ ",
    "Q   Q",
    "Q Q Q",
    "Q  Q ",
    " QQ Q"
  }},
  {'r', {
    "RRRR ",
    "R   R",
    "RRRR ",
    "R  R ",
    "R   R"
  }},
  {'s', {
    " SSSS",
    "S    ",
    " SSS ",
    "    S",
    "SSSS "
  }},
  {'t', {
    "TTTTT",
    "  T  ",
    "  T  ",
    "  T  ",
    "  T  "
  }},
  {'u', {
    "U   U",
    "U   U",
    "U   U",
    "U   U",
    " UUU "
  }},
  {'v', {
    "V   V",
    "V   V",
    " V V ",
    " VVV ",
    "  V  "
  }},
  {'w', {
    "W   W",
    "W   W",
    "W W W",
    "WW WW",
    "W   W"
  }},
  {'x', {
    "X   X",
    " X X ",
    "  X  ",
    " X X ",
    "X   X"
  }},
  {'y', {
    "Y   Y",
    " Y Y ",
    "  Y  ",
    "  Y  ",
    "  Y  "
  }},
  {'z', {
    "ZZZZZ",
    "   Z ",
    "  Z  ",
    " Z   ",
    "ZZZZZ"
  }},
  {' ', {
    "     ",
    "     ",
    "     ",
    "     ",
    "     "
  }},
  {'1', {
    "  1  ",
    "111  ",
    "  1  ",
    "  1  ",
    "11111"
  }},
  {'2', {
    "22222",
    "    2",
    "22222",
    "2    ",
    "22222"
  }},
  {'3', {
    "33333",
    "    3",
    "33333",
    "    3",
    "33333"
  }},
  {'4', {
    "4  4 ",
    "4  4 ",
    "44444",
    "   4 ",
    "   4 "
  }},
  {'5', {
    "55555",
    "5    ",
    "55555",
    "    5",
    "55555"
  }},
  {'6', {
    "66666",
    "6    ",
    "66666",
    "6   6",
    "66666"
  }},
  {'7', {
    "77777",
    "   7 ",
    "  7  ",
    " 7   ",
    "7    "
  }},
  {'8', {
    "88888",
    "8   8",
    "88888",
    "8   8",
    "88888"
  }},
  {'9', {
    "99999",
    "9   9",
    "99999",
    "    9",
    "99999"
  }},
  {'0', {
    "00000",
    "0  00",
    "0 0 0",
    "00  0",
    "00000"
  }},
  {'!', {
    " !!! ",
    " !!! ",
    " !!! ",
    "     ",
    " !!! "
  }},
  {'@', {
    "@@@@ ",
    "@   @",
    "@ @@ ",
    "@    ",
    " @@@@"
  }},
  {'#', {
    " # # ",
    "#####",
    " # # ",
    "#####",
    " # # "
  }},
  {'$', {
    " $$$$",
    "$ $  ",
    " $$$ ",
    "  $ $",
    "$$$$ "
  }},
  {'%', {
    "%   %",
    "   % ",
    "  %  ",
    " %   ",
    "%   %",
  }},
  {'^', {
    "  ^  ",
    " ^ ^ ",
    "     ",
    "     ",
    "     "
  }},
  {'&', {
    "&&&  ",
    "& &  ",
    "&&& &",
    "&  & ",
    " && &"
  }},
  {'*', {
    "  *  ",
    " *** ",
    "  *  ",
    "     ",
    "     ",
  }},
  {'(', {
    " (   ",
    "(    ",
    "(    ",
    "(    ",
    " (   "
  }},
  {')', {
    "   ) ",
    "    )",
    "    )",
    "    )",
    "   ) "
  }},
  {'-', {
    "     ",
    "     ",
    "-----",
    "     ",
    "     "
  }},
  {'_', {
    "     ",
    "     ",
    "     ",
    "     ",
    "_____"
  }},
  {'=', {
    "     ",
    "=====",
    "     ",
    "=====",
    "     "
  }},
  {'+', {
    "     ",
    "  +  ",
    " +++ ",
    "  +  ",
    "     "
  }},
  {'`', {
    "``   ",
    " ``  ",
    "     ",
    "     ",
    "     "
  }},
  {'~', {
    "     ",
    " ~   ",
    "~ ~ ~",
    "   ~ ",
    "     "
  }}
};

void asciify(char *str)
{
  int i, j, k = 0;
  while (str[11*k]) {
    for (i = 0; i < 5; i++) {
      for (j = 0; j < 11 && str[k*11+j]; j++) {
        std::cout << ascii_chars[str[k*11+j]][i] << "  ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    if (!str[11*k+j]) {
      return;
    }
    k++;
  }
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << *argv << " [TEXT]" << std::endl;
    return 1;
  }
  std::cout << std::endl;
  while (--argc) {
    argv++;
    asciify(*argv);
    std::cout << std::endl;
  }
  return 0;
}