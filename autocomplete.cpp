/* File: autocomplete.cpp
 * Author: Adrian Treadwell
 * Purpose: the implementation of member functions for the class named Autocomplete.
 *
 */
#include <iostream>
#include "autocomplete.h"

// default constructor
Autocomplete::Autocomplete()
{
    
    // since the private data member terms has been initialized through default constructor of SortingList class, I left this blank

}


// inserts the newterm to the sequence
// note that a SortingList<Term> object, named terms
//          represents the sequence
void Autocomplete::insert(Term newterm)
{
    terms.insert(newterm);
}


// sort all the terms by query in the lexicographical order  
void Autocomplete::sort()
{
    terms.sort();    
}

// binary search helper function
// as private function
// since it serves binary_search member function only
int Autocomplete::binary_searchHelper(SortingList<Term> terms, string key, int left_index, int right_index)
{
    if(right_index < left_index)
    {
        int KEY_NOT_FOUND = -1;
        return KEY_NOT_FOUND;
    }
    else
    {
        Term keyterm(key, 0);
        int r = key.length();
        int middle = (left_index + right_index) / 2;
        if(Term::compareByPrefix(keyterm,terms[middle],r) > 0)
        {
            return binary_searchHelper(terms, key, left_index, middle - 1);

        }
        else if(Term::compareByPrefix(keyterm,terms[middle],r)  < 0)
        {
            return binary_searchHelper(terms, key, middle + 1, right_index);
        }
        else
        {
            return middle;
        }
    }
}

// return the index number of the term whose query 
// prefix-matches the given prefix, using binary search algorithm
// Note that binary search can only be applied to sorted sequence
// Note that you may want a binary search helper function
int Autocomplete::binary_search(string prefix)
{
    terms.sort();
    return binary_searchHelper(terms, prefix, 0, terms.size() - 1);
    //I think the above solution is the cleanest way to return the index
}

// first: the index of the first query whose prefix matches
//          the search key, or -1 if no such key
// last: the index of the last query whose prefix matches 
//         the search key, or -1 if no such key
// key: the given prefix to match
// hints: you can call binary_search() first to find one matched index number,
//        say hit, then look up and down from hit, to find first and last respectively
void Autocomplete::search(string key, int& firstIndex, int& lastIndex)
{
    int hit = binary_search(key);
    if(hit == -1){
        lastIndex = -1;
        return;
    }
    Term keyTerm(key, 0);
    for(int i = hit; i < terms.size() - 1; i++){
        if(Term::compareByPrefix(terms[i], keyTerm, key.length()) != 0){
            lastIndex = i-1;
            break;
        }

    }
    //Since the list is sorted, the above and below for loops just compareByPrefix to see all the search results
    //you should save by index. Logic is self explanatory
    for(int i = hit; i > 0; i--){
        if(Term::compareByPrefix(terms[i], keyTerm, key.length()) != 0){
            firstIndex = i+1;
            break;
        }
    }
    return;
}

// returns all terms that start with the given prefix, in descending order of weight
SortingList<Term> Autocomplete::allMatches(string prefix)
{   
    int firstIndex = 0;
    int lastIndex = terms.size() - 1;
    search(prefix, firstIndex, lastIndex);
    //this will update firstIndex and lastIndex since they are passed by reference.
    SortingList<Term> AllMatches;
    if(lastIndex == -1){
        return AllMatches;
    }
    for(int i = firstIndex; i <= lastIndex; i++){
        AllMatches.insert(terms[i]);
    } //shove all the terms in allmatches
    for(int i = 0; i < AllMatches.size(); i++){
        for(int j = 0; j < AllMatches.size(); j++){
            if(Term::compareByWeight(AllMatches[i], AllMatches[j]) == 1){
                Term temp = AllMatches[i];
                AllMatches[i] = AllMatches[j];
                AllMatches[j] = temp;
            }
        }
    }
    //My own version of a "bubble" sort but its also pretty self explanatory. temp preserves data and then they swap
    
    return AllMatches;
}

void Autocomplete::print()
{
   cout << this; 
}
