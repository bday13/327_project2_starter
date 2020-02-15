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

struct word words[constants::MAX_WORDS];

int arr = 0;
//============================================================================

void extractTokensFromLine(std::string &myString) {
	stringstream ss(myString);
	string tempToken;

	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

void clearArray() {
	arr = 0;
}

int getArraySize() {
	return arr;
}

std::string getArrayWordAt(int i) {
	return words[i].word;
}

int getArrayWord_NumbOccur_At(int i) {
	return words[i].num_occur;
}

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

void processLine(std::string &myString) {
	std::stringstream ss(myString);
	std::string token;

	while (std::getline(ss, token, CHAR_TO_SEARCH_FOR)) {
		processToken(token);
	}
}

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

bool openFile(std::fstream& myfile, const std::string& myFileName,
				std::ios_base::openmode mode) {

	myfile.open(myFileName, mode);

	if (myfile.is_open())
		return true;
	return false;
}

void closeFile(std::fstream& myfile) {

	if (myfile.is_open())
		myfile.close();
};

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

void sortArray(constants::sortOrder so) {

	switch(so) {
		case sortOrder::ASCENDING:
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
		case sortOrder::DESCENDING:
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
		case sortOrder::NUMBER_OCCURRENCES:
			break;
		case sortOrder::NONE:
			break;
		}
}
