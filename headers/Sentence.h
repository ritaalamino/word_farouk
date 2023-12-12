#include "WordModel.h"
#include <iostream>
#include <string.h>
using namespace std;
struct word{
	char* w;
	float* vector;
	float* vector2;
	bool exist;
	char* POS;
	word(int size=300){
		vector = new float[size];
		vector2 = new float[size];
	}
};

class Sentence{
public:
	int vecSize;
	char* sentStr;
	word* words;
	int wordCount;
	Sentence(){wordCount =0;vecSize=300;}
	Sentence(char* str){
		vecSize = 300;
		wordCount =0;
		sentStr = str;
		//cout<<" test  - - "<<str<<endl;
		splite();
	}
	Sentence(char* str, char* tok) {
		cout<<str<<endl<<tok<<endl;
		vecSize = 300;
		wordCount = 0;
		sentStr = tok;
		int count = 0, i=0;
		while(tok[i] != '\0')
		{
			if(tok[i] == ' ')
				count++;
			i++;
		}
		//string* wlist;// = new string[count];
		wordCount = count/2;
		//cout<<wordCount<<endl;
		words = new word[wordCount];
		char* nword = new char[100];
		int start =0;
		for (int i = 0; i < wordCount; i++) {
			//cout<<i<<endl;
			myGetLine(tok, ' ', nword, start);
			//cout<<nword<<endl;
			start += strlen(nword)+1;
			words[i].w = new char[strlen(nword)];
			strcpy(words[i].w, nword);
			myGetLine(tok, ' ', nword, start);
			//cout<<nword<<endl;
			start += strlen(nword)+1;
			words[i].POS = new char[strlen(nword)];
			strcpy(words[i].POS, nword);
		}
		delete[] nword;
	}
	bool myGetLine(char* str, char del, char* temp, int start){
		//temp = new char [strlen(str)];
		int i=0;
		while(str[start] != del &&str[start] != '\0')
			temp[i++] = str[start++];
		if(i==0 &&str[start]=='\0')
			return false;
		temp[i] = '\0';
		return true;
	}
	void splite(){
		bool bol;
		char* swords[] = {"to", "on", "in", "the", "or", "and", "a", "at", "of", "an", "that",
				"such", "as", "you", "is", "A", "", "", "", "", "", "", "", "", "", "",
				"", "", "", "", ""};
		int i = 0;
		int b = 0;
		int s1Len = 0;
		char ws[70][30];
		while (1) {
			if (sentStr[i] == 0)
				break;
			if (sentStr[i] == ' ') {
				ws[s1Len][b] = 0;
				bol = false;
				for (int ss = 0; ss < 16; ss++)
					if (strcmp(ws[s1Len], swords[ss]) == 0) {
						bol = true;
						break;
					}
				if (!bol)
					s1Len++;
				b = 0;
			} else if (sentStr[i] != ',' && sentStr[i] != '.' && sentStr[i]
					!= '"')
				//	continue;
				//else
				ws[s1Len][b++] = sentStr[i];
			i++;
		}
		ws[s1Len][b] = 0;

		s1Len++;
		wordCount = s1Len;
		words = new word[wordCount];
		for (int i = 0; i < wordCount; i++) {
			words[i].w = new char[strlen(ws[i])];
			strcpy(words[i].w, ws[i]);
			//cout<<"wi "<<words[i].w<<"  "<<strlen(words[i].w)<<endl;
		}
	}
	float* generateRandomVector(char* word){
		float *vec = new float[vecSize];
	}
	void initVectors(const WordModel& model){
		for(int i=0; i< wordCount; i++){
			words[i].vector = model.getVector(words[i].w, words[i].exist);
			//cout<<words[i].exist<<endl;
		}
	}
	void initVectors2(const WordModel& model){
		for(int i=0; i< wordCount; i++){
			words[i].vector2 = model.getVector(words[i].w, words[i].exist);
			//cout<<words[i].exist<<endl;
		}
	}
	void copystring(char* dist, char* src){
		int i=0;
		while(src[i] != '\0' && i<30){
			dist[i] = src[i];
			i++;
		}
	}
	float* getMeanVector(){
		float* vec = new float[vecSize];
		for(int j=0; j< vecSize; j++){
			vec[j] = 0;
		for(int i=0; i<wordCount; i++)
				vec[j] += words[i].vector[j];
	}
		return vec;
	}

	float* getNounMeanVector(){
			float* vec = new float[vecSize];
			for(int j=0; j< vecSize; j++){
				vec[j] = 0;
			for(int i=0; i<wordCount; i++)
				if(words[i].POS[0] == 'N')
					vec[j] += words[i].vector[j];
		}
			return vec;
		}
	float* getVerbMeanVector(){
			float* vec = new float[vecSize];
			for(int j=0; j< vecSize; j++){
				vec[j] = 0;
			for(int i=0; i<wordCount; i++)
				if(words[i].POS[0] == 'V')
					vec[j] += words[i].vector[j];
		}
			return vec;
		}
};
