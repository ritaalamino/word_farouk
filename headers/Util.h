#ifndef SOME_STRING_H
#define SOME_STRING_H

#include<iostream>
#include<string.h>


using namespace std;
class Util{
public:
	char* l = new char[600];
	char* getLine(FILE* f);
	string getStringLine(FILE* f);
	string* split(char* str, char del, int max);
	void writeLine(FILE* f,const char*line );
	void writeToFile(FILE* f,const char*line );
	double calcPearson(float x[], float y[], int size);
	double stringSim(const std::string &s1, const std::string &s2);
//	string exec(const char* cmd);
};

#endif
