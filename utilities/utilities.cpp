//============================================================================
// Name        : utilities.cpp
// Author      : Julia Nichols
// Version     : 10/2/21
// Copyright   : Your copyright notice
//============================================================================

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

#include "../includes/constants.h"
#include "../includes/utilities.h"
using namespace std;

//if you are debugging the file must be in the project parent directory
std::string DoubleToString(double Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

//if myString does not contain a string rep of number returns 0
//if int not large enough has undefined behavior,
//this is a very fragile function
//ex. string a="3";
//    int i = stringToInt(a.c_str()); //i contains 3
//    a="s";
//    i = stringToInt(a.c_str()); //i receives 0
int stringToInt(const char *myString) {
	return atoi(myString);
}

//if myString does not contain a string rep of number returns 0
//this is a very fragile function
//ex. string b="4.5";
//    double d = stringToDouble(b.c_str()); //d receives 4.5
double stringToDouble(const char *myString) {
	return atof(myString);
}

/***
 * Clears allStudentData, Opens file, For each line; parses name, midterm1,midterm2 and an 
 * optional finalgrade (if present in file)from that line. Puts this info into a studentData struct,
 * adds this struct to allstudentData vector.
 * NOTE:
 * Ignore empty lines
 * Non empty lines will contain 4 or 5 values to be parsed.
 * the default param separator_char is defined in the header file declaration of readFile ONLY, it is not in the readFile definition.
 * @param file - where student data is stored
 * @param allstudentData - a vector that holds the student data info after it has been read from file
 * @param separator_char - the character that separates each bit of data in a line of student data
 * @return COULD_NOT_OPEN_FILE
 *         SUCCESS
 */
int readFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char /*=KP::SEPERATOR_CHAR*/) {
	ifstream myInFile; // Reading file Use
	myInFile.open(file, ios::in); // .open(filename, mode)

	// Will return COULD_NOT_OPEN_FILE if the file isn't open after running .open()
	if(!myInFile.is_open()) {
		return KP::COULD_NOT_OPEN_FILE;
	}
	
	std::string line;
	std::string token;
	KP::studentData myStudentData; // Used KP:: because all constants are in namespace KP
	stringstream ss;

	// clear the vector
	//allstudentData.clear();

	// Use stringstream to parse each line 
	while (std::getline(myInFile, line)) {
	// get a line from the file (name, midterm1, midterm2, and possibly finalgrade)
		ss.clear();
		ss.str(line);

		// get rid of the old values
		myStudentData.clear();

		// get the name
		getline(ss, myStudentData.name, separator_char);

		// get midterm1
		getline(ss, token, separator_char);
		myStudentData.midterm1 = stringToInt(token.c_str());

		// get midterm2
		getline(ss, token, separator_char);
		myStudentData.midterm2 = stringToInt(token.c_str());

		// get finalgrade
		if(getline(ss, token, separator_char)) {
			getline(ss, token, separator_char);
			myStudentData.finalgrade = stringToInt(token.c_str());
		}
		//allstudentData.push_back(myStudentData); // adds myStudentData to the back of allStudentData
	}

	//myInFile.close(); // close when gone through all of the file
	return KP::SUCCESS;
}

/***
 * Iterates over all students in vector, and averages midterm1 and midterm2 to get the finalgrade
 * @param allstudentData
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int calculateFinalGrade(std::vector<KP::studentData> &allstudentData) {
	// If there are no students it returns KP::VECTOR_CONTAINS_NO_STUDENTS
	if(allstudentData.empty()) {
			return KP::VECTOR_CONTAINS_NO_STUDENTS; 
	}

	// Creates an iterator to go through the vector of students
	std::vector<KP::studentData>::iterator iter = allstudentData.begin();

	// Calculates finalGrade for each student (finalgrade comes from constants.h)
	for (iter = allstudentData.begin(); iter != allstudentData.end(); ++iter){ // Goes through allstudentData
		(*iter).finalgrade = ((*iter).midterm1+(*iter).midterm2)/2; //calculates the grade(s)
	}

	return KP::SUCCESS;
}

/***
 * Opens file, serializes data from allstudentData to file, closes file 
 * the default param seperator_char is defined in the header file ONLY
 * @param file - where student data is stored
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param separator_char - the character that separates each bit of data in a line of student data
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         COULD_NOT_OPEN_FILE
 *         SUCCESS
 */
int writeFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char/*=KP::SEPERATOR_CHAR*/) {
	ofstream myOutfile; 
	myOutfile.open(file, ios::out); // .open(filename, mode)



	// Will return COULD_NOT_OPEN_FILE if the file isn't open after running .open()
	if(!myOutfile.is_open()) {
		return KP::COULD_NOT_OPEN_FILE;
	}

	// Checks if there are students
	if(allstudentData.empty()) {
			return KP::VECTOR_CONTAINS_NO_STUDENTS; 
	}

	// Creates an iterator to go through the vector of students
	std::vector<KP::studentData>::iterator iter = allstudentData.begin();

	//myOutfile << "Writing this to a file.\n";

	// Uses the iterator to go through allstudentData and writes the information to the file
	for (iter = allstudentData.begin(); iter != allstudentData.end(); ++iter){
		std::string mid1 = DoubleToString((*iter).midterm1);
		std::string mid2 = DoubleToString((*iter).midterm2);
		std::string finalg = DoubleToString((*iter).finalgrade);

		// what the iterator is checking for
		myOutfile << (*iter).name << " " << mid1 << " " << mid2 << " " << finalg << "\n";

	}

	myOutfile.close();
	return KP::SUCCESS;
}

// Sort algorithm to compare name (compares name x and name y) 
	// -> puts the names in alphabetical order
bool compareName(KP::studentData& x,  KP::studentData& y) {
	return x.name < y.name;
}

// Sort algorithm to final grades (compares final grade x and final grade y) 
	// -> Will help sort students by highest/lowest grade
bool compareFinal(KP::studentData& x, KP::studentData& y) {
	return x.finalgrade > y.finalgrade;
}

//sorts studentdata based on SORT_TYPE
/***
 * 
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param st - how to sort the vector
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int sortStudentData(std::vector<KP::studentData> &allstudentData,KP::SORT_TYPE st) {
	// Checks if there are students
	if(allstudentData.empty()) {
			return KP::VECTOR_CONTAINS_NO_STUDENTS; 
	}

	// If the sort type is name, it will sort by name
	if(st == KP::NAME) {
		std::sort(allstudentData.begin(), allstudentData.end(), compareName);
	}

	// If the sort type is Final Grade, it will sort by that
	else if(st == KP::FINAL_GRADE) {
		std::sort(allstudentData.begin(), allstudentData.end(), compareFinal);
	}

	return KP::SUCCESS;
}
