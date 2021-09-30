//============================================================================
// Name        : 4_Vector_List.cpp
// Author      : Julia Nichols
// Version     : 9/30/21
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../includes/constants.h"
#include "../includes/utilities.h"
#include "../includes/test.h"
using namespace std;

int main() {

#ifdef TEST
	test();
#else
	string infile = KP::ORIGINAL_STUDENT_DATA;
	string outfile = KP::CALCULATED_STUDENT_DATA;
	
	vector<KP::studentData> allstudentData;

	int iret=readFile(infile,allstudentData);
	if(iret != KP::SUCCESS)
		return iret;
	
	//ignoring return types
	calculateFinalGrade(allstudentData);
	sortStudentData(allstudentData,KP::FINAL_GRADE);
	
	iret = writeFile(outfile,allstudentData);
	
    return iret; 
#endif
}






















//ALTERNATIVE- pass the files as arguments
//const int FAIL_WRONG_NUMBER_ARGS = -5;
//const int EXPECTED_NUMBER_ARGUMENTS =4;
//const string WRONG_NUMB_ARGS = "This program expects 3 arguments, infile passfile failfile";
//
//int main( int argc, char *argv[] )  {
//	//argc = how many arguments passed in (including this program)
//	//char *argv[] char array of those arguments
//
//	//expect progname infile passfile failfile   //program and 3 arguments, argc=4
//   if( argc != EXPECTED_NUMBER_ARGUMENTS ) {
//	   cout<< WRONG_NUMB_ARGS <<endl;
//	   return FAIL_WRONG_NUMBER_ARGS;
//   }
//   string infile = argv[1];
//   string Passfile = argv[2];
//   string Failfile = argv[3];
//
//   return process_Data(infile,Passfile, Failfile);
//}



