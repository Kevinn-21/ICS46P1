// If you really want to make a program for the app, be my guest.
// You may prefer to do so in /exp instead.
// Or better yet, use gtest to automate your own test cases!

#include "proj1.hpp"
#include <map>
#include <set>
#include <string>
#include <iostream>

int main()
{
    std::map<char,unsigned> puzzle;
    std::string s1 = "POT", s2 = "PAN", s3 = "BIB";
    bool yes = puzzleSolver(s1,s2,s3,puzzle);
    std::cout << yes;
    return 0;
}



