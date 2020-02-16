/*
 *
 *  Created on: Feb 14, 2020
 *      Author: Brandon Day
 */

//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"
using namespace constants;
using namespace std;
//============================================================================

//============================================================================
struct word {
	string word;
	int num_occur;
};

word words[constants::MAX_WORDS];

int arr = 0;
//============================================================================

void extractTokensFromLine(std::string &myString) {
	stringstream ss(myString);
	string tempToken;

	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

/**
 * zero out array that tracks words and their occurrences
 */
void clearArray() {
	arr = 0;
}

/**
 * how many unique words are in array
 */
int getArraySize() {
	return arr;
}

/**
 * get data at a particular location
 */
std::string getArrayWordAt(int i) {
	return words[i].word;
}

/**
 * get data at a particular location
 */
int getArrayWord_NumbOccur_At(int i) {
	return words[i].num_occur;
}

/**
 * loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise
 */
bool processFile(std::fstream &myfstream) {
	if (myfstream.is_open()) {
		std::string line;

		while (std::getline(myfstream, line)) {
			processLine(line);
		}

		return true;
	}
	return false;
}

/**
 * take 1 line and extract all the tokens from it
 * feed each token to processToken for recording
 */
void processLine(std::string &myString) {
	std::stringstream ss(myString);
	std::string token;

	while (std::getline(ss, token, CHAR_TO_SEARCH_FOR)) {
		processToken(token);
	}
}

/**
 * Keep track of how many times each token seen
 */
void processToken(std::string &token) {
	strip_unwanted_chars(token);

	if (token == "")
		return;

	for (int i = 0; i < arr; i++) {
		std::string x = token;
		std::string y = words[i].word;
		toUpper(x);
		toUpper(y);

		if (x == y) {
			words[i].num_occur++;
			return;
		}
	}

	word w;
	w.word = token;
	w.num_occur = 1;

	words[arr] = w;
	arr++;
}

/**
 * if you are debugging the file must be in the project parent directory
 * in this case Project2 with the .project and .cProject files
 */
bool openFile(std::fstream& myfile, const std::string& myFileName,
				std::ios_base::openmode mode) {

	myfile.open(myFileName, mode);

	if (myfile.is_open())
		return true;
	return false;
}

/**
 * iff myfile is open then close it
 */
void closeFile(std::fstream& myfile) {

	if (myfile.is_open())
		myfile.close();
}

/**
 * serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 */
int writeArraytoFile(const std::string &outputfilename) {

	std::ofstream outfile;
	outfile.open(outputfilename);

	if(!outfile.is_open())
		return constants::FAIL_FILE_DID_NOT_OPEN;
	if (arr == 0)
		return constants::FAIL_NO_ARRAY_DATA;

	for (int i = 0; i < arr; i++) {
		outfile << words[i].word << " " << words[i].num_occur << std::endl;
		std::cout << words[i].word << " " << words[i].num_occur << std::endl;
	}

	outfile.close();
	return constants::SUCCESS;
}

/**
 * Sort myEntryArray based on so enum value.
 * The presence of the enum implies a switch statement
 */
void sortArray(constants::sortOrder so) {

	switch(so) {

		case sortOrder::ASCENDING: {

			for (int i = 0 ; i < arr - 1 ; i++) {
				for (int j = 0 ; j < arr - i - 1 ; j++) {
					std::string temp1 = words[j].word;
					std::string temp2 = words[j + 1].word;
					toUpper(temp1);
					toUpper(temp2);

					if (temp1 > temp2) {
						word temp = words[j];
						words[j] = words[j+1];
						words[j+1] = temp;
					}
				}
			}

			break;
		}
		case sortOrder::DESCENDING: {

			for (int i = 0 ; i < arr - 1 ; i++) {
				for (int j = 0 ; j < arr - i - 1 ; j++) {
					std::string temp1 = words[j].word;
					std::string temp2 = words[j+1].word;
					toUpper(temp1);
					toUpper(temp2);

					if (temp1 < temp2) {
						word temp = words[j];
						words[j] = words[j+1];
						words[j+1] = temp;
					}
				}
			}

			break;
		}
		case sortOrder::NUMBER_OCCURRENCES: {

			for (int i = 1; i < arr; i++) {
				for (int j = 1; j < arr; j++) {

					if (words[j - 1].num_occur < words[j].num_occur) {
						word temp;
						temp.word = words[j - 1].word;
						temp.num_occur = words[j - 1].num_occur;
						words[j - 1] = words[j];
						words[j] = temp;
					}
				}
			}
		}
			break;
		case sortOrder::NONE:
			break;
		}
}
