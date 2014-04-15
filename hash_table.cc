#include <string>
#include "hash_table.h"
#include <iostream>

unsigned long hash_str(std::string str)
{
    unsigned long hash = 5381;
    int c;
    int i = 0;

    while (c = str[i++])
        hash = ((hash << 5) + hash) + (unsigned)c; /* hash * 33 + c */

    return hash;
}


int main()
{
    Map<std::string, std::string> m(1024, hash_str);

    char opt;
    std::string s;
    std::string t;
    std::string *res;
    while(true) {
        std::cin >> opt;
        switch (opt) {
            case 'q': return 0;
            case 's':
                std::cin >> s >> t;
                m.store(s, t);
            break;
            case 'g':
                std::cin >> s;
                res = m.get(s);
                if(res)
                    std::cout << "m[" << s << "] = " << *res << std::endl;
                else
                    std::cout << "m[" << s << "] doesn't exist." << std::endl;
            break;
            case 'd':
                std::cin >> s;
                m.remove(s);
            break;
            default:
                std::cout << "Invalid option " << opt << std::endl;
            break;
        }
    }
}