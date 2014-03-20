#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
//god regex producer
//Produces a regex of form s/{stuff}/{stuff} that transforms the first input into the second input.
//Meant for silliness with IRC bots.

int main()
{
    std::string s; //start string
    std::string e; //end string
    while(true)
    {
        std::getline(std::cin, s); //read start string
        std::getline(std::cin, e); //read end string
        
        //time to do the grunt work.
        std::vector<char> chars;
        for(unsigned int i = 0; i < e.size(); i++)
        {
            if(std::find(chars.begin(), chars.end(), e[i]) == chars.end())
            {
                //if the character is not in chars
                chars.push_back(e[i]); //add it to chars
            }
        }
        //capgroup stores the grouping number.
        std::vector<int> capgroup = std::vector<int>(chars.size());
        for(unsigned int i = 0; i < capgroup.size(); i++)
        {
            capgroup[i] = -1;
        }
        //prepare the output string...
        std::stringstream regex;
        //^ matches the start of a sentence.
        regex << "s/^";
        int curr_cap_group = 1; //start with \1, then \2, etc.
        int count = 0; //number of 'useless' char's we're absorbing.
        for(unsigned int i = 0; i < s.size(); i++)
        {
            bool b = false; //is this char useful?
            for(unsigned int j = 0; j < chars.size(); j++) //Go through all characters.
            {
                if(s[i] == chars[j] && capgroup[j] == -1)
                {
                    switch(count)
                    {
                        case 3:
                            regex << ".";
                        case 2:
                            regex << ".";
                        case 1:
                            regex << ".";
                        case 0: 
                            break; //teehee, silly C switches.
                        default:
                            regex << ".{" << count << "}"; 
                            break;
                    }
                    capgroup[j] = curr_cap_group++; //advance our capture group
                    regex << "(" << "." << ")"; //capture it.
                    b = true; //it is.
                }
            }
            if(b)
            {
                count = 0; //reset count
            }
            else
            {
                count++; //otherwise add to count.
            }
        }
        switch(count)
        {
            case 3:
                regex << ".";
            case 2:
                regex << ".";
            case 1:
                regex << ".";
            case 0: 
                break; //teehee, silly C switches.
            default:
                regex << ".{" << count << "}"; 
        }
        regex << "$/";
        for(unsigned int i = 0; i < e.size(); i++)
        {
            int index = std::find(chars.begin(), chars.end(), e[i])
                      - chars.begin();
            if(capgroup[index] == -1)
            {
                regex << chars[index];
            }
            else
            {
                regex << "\\" << capgroup[index];
            }
        }

        regex << "/";

        std::cout << regex.str() << std::endl;
    }
}