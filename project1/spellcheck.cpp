// Joseph Mercedes
// Data Structures and Algorithms II
// Program Assignment #1
// spellcheck.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include "hash.h"

using namespace std;

hashTable dict(250000);

// Function Declarations
void loadDict(ifstream &dict_file);
int spellcheck(ifstream &input, ofstream &output);

int main(){

	// Enter the Preferred Dictionary
	string inFileName, outFileName;
	cout << "Enter name of dictionary: ";
	cin >> inFileName;
	ifstream input(inFileName.c_str());
	if (!input){
		cerr << "Error: could not open " << inFileName << endl;
		exit(1);
	}
	
	// Times the Dictionary Load
	clock_t time1 = clock();
	loadDict(input);
	clock_t time2 = clock();
	double dictLoadTime = (double(time2-time1))/CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to load dictionary: " << dictLoadTime << endl;
	input.close();

	// Enter the preffered document to spellcheck
	cout << "Enter name of input file: ";
	cin >> inFileName;
	cout << "Enter name of output file: ";
	cin >> outFileName;
	ifstream fileToSpellCheck(inFileName.c_str());
	ofstream fileToOutput(outFileName.c_str());

	// Times the Spellcheck
	time1 = clock();
	int spellcheckSuccess = spellcheck(fileToSpellCheck, fileToOutput);
	time2 = clock();
	double spellcheckTime = double((time2-time1))/CLOCKS_PER_SEC;
	cout <<  "Total time (in seconds) to check document: " << spellcheckTime << endl;

	return 0;
}

// Loads the Dictionary
void loadDict(ifstream &dict_file){

	string word;
	while (getline(dict_file, word)){
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		dict.insert(word);
	}

	return;
}


// Spellchecks the Document
int spellcheck(ifstream &input, ofstream &output){

	string validChar = "abcdefghijklmnopqrstuvwxyz0123456789\'-";
	string numbers = "0123456789";
	string line, word;
	int lineNumber = 1, start, end;

	while(getline(input, line)){

		// Make Lowercase and Skip Blank Lines
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		if(line==""){
			lineNumber++;
			continue;
		}

		// Check the document to determine if each word satisfies the following:
		// Cannot contain numbers
		// Cannot be longer than 20 characters
		// Must be contained in dictionary
		start = line.find_first_of(validChar);
		while (start != string::npos) {

            end = line.find_first_not_of(validChar, start);
            word = line.substr(start,end-start);
            start = line.find_first_of(validChar, end);

            
            if (word.find_first_of(numbers) != string::npos)
                continue;

            else if (word.length() > 20) {
                output << "Long word at line " << lineNumber << ", starts: " << word.substr(0,20) << endl;
            }

            else if (!dict.contains(word)) {
                output << "Unknown word at line " << lineNumber << ": " << word << endl;
            }

            else if (end == string::npos){
                break;
			}
        }

        lineNumber++;
    }
    return 0;
}