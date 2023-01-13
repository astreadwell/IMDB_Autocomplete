/* 
 * File:   magicString.cpp
 * Author: Adrian Treadwell
 * Purpose: provide the implementation of member functions of magicString class
 */
#include <iostream> 
#include <algorithm>
#include "magicString.h"

using namespace std;

//constructor
magicString::magicString(string ini_string)
{
    this->str = ini_string;
}

// set the current value of str
void magicString::setMagicString(string value)
{
    this->str = value;
}

// return the value of str
string magicString::getMagicString() const
{
    return this->str;
}

//returns a string which transforms each character of str into lower case
//note that str has not been changed
//(algorithm header file is needed for the definition of transform function)
string magicString::toLower() const
{
    string result = this->str;
    transform(this->str.begin(), this->str.end(), result.begin(), ::tolower);
    return result;
}

//returns a string which transforms each character of str into upper case
// use recursive function to implement
//note that str has not been changed
string magicString::toUpper() const
{
    static int fcount = 0; // use a static variable to count the function calling
    fcount++;   // increase count by one while calling the function
    cout << "Calling the recursive function named " << __func__ << " : " << fcount  << " times." << endl;   // note that __func__ is macro for the funciton name, it may be different for different compiler
    // Base case:
    if (this->str.length() == 0)
        return this->str;
    // Recursive case:
    string first = this->str.substr(0,1);
    const char* front = first.c_str();
    char upperFront[LEN];
    string result;
    upperFront[0] = toupper(front[0]);
    upperFront[1] = '\0';
    result = upperFront;
    magicString part(this->str.substr(1, this->str.length()-1));
    return result + part.toUpper();
}

//it remove the extra blank spaces(including tab) from str
//It defines as:
//   1. it remains only one space if str contains more than
//      one continuous blank spaces between two non-space characters
//      For example, if str is "hello,     world",
//      it should change into "hello, world"
//   2. it removes all spaces before the first non-space character
void magicString::removeExtraSpace()
{
    // your code should start here...
    string result = this->str;
    string output = "";
    output.clear();
    unique_copy(result.begin(), result.end(), back_insert_iterator<string>(output), [](char a, char b){return
            isspace(a) && isspace(b);});
    result = output;
    while(result[0] == ' '){
        result.erase(0,1);
    }
    while(result[result.length() - 1] == ' '){
        result.erase(result.length() - 1, 1);
    }
    this->str = result;
return;
}

// return a string which transforms only the first letter of each word in str into upper case letter
// the word in str is defined as a sequence of characters starting with non-space character and ending right before the next space
// note that str has not been changed
string magicString::wordFormat() const
{
    // before the wordFormat transformation
    // make sure (1)the extra space(s) has been removed from str; 
    //           (2)apply to all lower case letters of str
    // your code should start here...
    string result = this->str;
    string output = result;
    output.clear();
    unique_copy(result.begin(), result.end(), back_insert_iterator<string>(output), [](char a, char b){return
            isspace(a) && isspace(b);});
    result = output;
    //I decided to just paste my code from the removeExtraSpace() function here,
    //since I think having 2 redundant functions is kinda cringe
    for(int i = 0; i < result.length(); i++){
        if(result[i-1] == ' '){
            result[i] = toupper(result[i]);
        
        }
        else{
            result[i] = tolower(result[i]);
        }
    }
    while(result[0] == ' '){
        result.erase(0,1);
    }
    //Was having issues where sometimes I would have spaces at the start so while there is a space at the start
    //delete it
    while(result[result.length()-1] == ' '){
        result.erase(result.length()-1, 1);
    }
    //same with end
    result[0] = toupper(result[0]);
    //since there are no spaces go ahead and uppercase the first letter.
    return result;
}
