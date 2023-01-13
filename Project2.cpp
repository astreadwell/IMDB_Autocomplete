/*
 * Author: Adrian Treadwell
 * Purpose: repeatedly ask the user to type prefix to match
 *          and generate all the prefix-matched terms 
 *          then display the prefix-matched terms in descending order by weight.
 ***** PLEASE DO NOT CHANGE THIS FILE *****
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "term.h"
#include "SortingList.h"
#include "autocomplete.h"
#include "magicString.h"

using namespace std;

int main(int argc, char** argv) {
    const int ARGUMENTS = 3;
    
    // check the command line argument, an input file name is needed
    if (argc != ARGUMENTS)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }    
    
    // check if the input file can be opened successfully
    ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        cout << "Cannot open the file named " << argv[1] << endl;
        return 2;
    }  
    
    // read in the terms from the input file
    // line by line and store into Autocomplete object
    Autocomplete autocomplete;
    long weight;
    string query;
    int k = atoi(argv[2]); //converts the char stored in argv to an integer.
    while (!infile.eof())
    {
        infile >> weight >> ws;
        getline(infile, query);
        if (query != "")
        {    
            Term newterm(query, weight);
            autocomplete.insert(newterm);
        }    
    } 

    // read the time clock 
    // before calling sort() function and after it
    // to measure the time spent for sorting operation
    clock_t tstart, tstop;
    tstart = clock();
    autocomplete.sort();
    tstop = clock();
    double  elapsed = (double)(tstop-tstart)/CLOCKS_PER_SEC;
    cout << "Time for sorting all terms: "<<  elapsed << " seconds." << endl;
    

    string input;
    string prefix;
    cout << "Please input the search query (type \"exit\" to quit): " << endl;
    getline(cin, input);
    prefix = input;
    magicString stringCleaner(prefix); //Create magicString object with string arg constructor
    prefix = stringCleaner.wordFormat(); //Reformat and pass back the formatted magicString as a string.
    //The above 2 lines fix all extra spaces and case sensitivity.
    while (prefix != "Exit")
    {
        // measure the time spent for searching one prefix-matched term
	    clock_t tstart, tstop;
    	tstart = clock();
        SortingList<Term> matchedTerms = autocomplete.allMatches(prefix);
        tstop = clock();
        double  elapsed = (double)(tstop-tstart)/CLOCKS_PER_SEC;
        cout << "Time for searching the maximum three of matched terms: "<<  elapsed << " seconds." << endl;
        
        if (matchedTerms.size() == 0)
        {    
            cout << "No matched query!" << endl;
        }
        else{
            //First if handles if we have less search results than the cout argument passed in from the command
            //line
            if(matchedTerms.size() < k){
                for(int i = 0; i < matchedTerms.size(); i++){
                    cout << matchedTerms[i] << endl;
                }
            }
            //This couts results equal to the command line arg "k".
            else{
                for(int i = 0; i < k; i++){
                    cout << matchedTerms[i] << endl;
                }
            }
        }

        cout << "Please input the search query (type \"exit\" to quit): " << endl;
        getline(cin, input);
        prefix = input;
        magicString stringCleaner(prefix); //To ensure that the magicString fixing is repeatable, we include 
        prefix = stringCleaner.wordFormat(); //the reformatting code in the structure.
        //Note: I consolidated wordFormat() and removeExtraSpace().

    }    
    return 0;
}

