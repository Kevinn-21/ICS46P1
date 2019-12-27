/*
    Kevin Nguyen
    ICS46B
    Project 1 -- a puzzle solver that solves an equation
    Ex. POT + PAN = BIB
*/

#include "proj1.hpp"
#include <map>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
/*
helpSolve(): returns true if the solution is found, if not return false.
    helpSolve() uses recursion. The base case is when the vector containing letters is empty, check if
    the solution is found otherwise remove the elements from mapping and put the elements back into
    their vectors
*/
bool helpSolve(std::string s1, std::string s2, std::string s3, std::map<char,unsigned>& mapping,
        std::vector<char> letters, std::vector<unsigned> digits);


bool puzzleSolver(std::string s1, std::string s2, std::string s3, std::map<char,unsigned>& mapping)
{

    std:: string s4 = s1 + s2 + s3;     //all of the letters in s4

    std::set<char> setOfLetters;        //make a set to eliminate repeat letters
    for(int i=0; i<s4.length(); i++)
    {
        setOfLetters.insert(s4[i]);
    }

    std::vector<char> letters;
    for(std::set<char>::iterator it = setOfLetters.begin(); it != setOfLetters.end(); it++)
    {
        letters.push_back(*it);     //insert the letters from our set to our vector
    }

    std::vector<unsigned> digits;
    for(unsigned i=0; i<10; i++)
    {
        digits.push_back(i);        //vector containing digits 0-9
    }

    bool answer = helpSolve(s1,s2,s3,mapping,letters,digits);   //call helpSolve and return a bool value

	return answer;
}


/*
helpSolve(): returns true if the solution is found, if not return false.
    @s1,s2,s3 is used to test the solution (if s1+s2=s3, return true)
    @mapping is used to store the pairings which will contain the solution once it is filled with all the letters
    @letters stores all letters and remaining letters
    @digits stores all and remaining digits
*/

bool  helpSolve(std::string s1, std::string s2, std::string s3, std::map<char,unsigned>& mapping,
    std::vector<char> letters, std::vector<unsigned> digits)
    {
        int jDig = digits.size()-1;     //used to get the index of the last element in vector digits

        bool solution = false, outOfLetters = false;    //@solution will hold true or false depending on if
                                                        //the solution is found(true) or there is no solution(false)
        for(int j=0; j<digits.size(); j++)
        {
            char letterMapped = letters[letters.size()-1];  //letterMapped holds the char so that it can be reinserted into the vector
            unsigned digitPair = digits[jDig-j];            //same idea for digitPair

            mapping[letterMapped] = digitPair;

            letters.pop_back();                             //remove an element from each vector
            digits.erase(digits.begin()+jDig-j);

            if(letters.empty())                             //if there are no more letters, set outOfLetters to true
            {                                               //so that we can get to base case
                outOfLetters = true;
            }

            if(outOfLetters == true)
            {
                std::string num1 = "", num2 = "", num3 = "";
                unsigned u1, u2, u3;

                for(int i=0; i<s1.length(); i++)                    //take the mapped unsigned values and combine them
                {                                                   //then convert to unsigned to add num1 and num2
                    num1 += std::to_string(mapping.at(s1[i]));
                }
                for(int j=0; j<s2.length();j++)
                {
                    num2 += std::to_string(mapping.at(s2[j]));
                }
                for(int m=0; m<s3.length(); m++)
                {
                    num3 += std::to_string(mapping.at(s3[m]));
                }

                u1 = stoul(num1);
                u2 = stoul(num2);
                u3 = stoul(num3);

                if((u1+u2)==u3)
                {
                        //mapped solution is good
                        return true;
                }
            }
            else
                {
                   solution = helpSolve(s1,s2,s3,mapping,letters,digits);   //recursive call with new vector letters and digits
                   if (solution)                                            //at each recursive call, both vectors would have one less element
                     return solution;
                }


                mapping.erase(letterMapped);        //if the solution didn't work, take out the pair from mapping
                                                    //and put it back into the vectors


                letters.push_back(letterMapped);
                digits.insert(digits.begin()+jDig-j,digitPair);

        }   //end for-loop
        return solution;
    }   //end helpSolve()

