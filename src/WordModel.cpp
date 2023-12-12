/*
 * WordModel.cpp
 *
 *  Created on: Apr 22, 2018
 *      Author: mamfarouk
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include<iostream>
#include<fstream>
#include "WordModel.h"
using namespace std;

const static long long max_size = 2000;         // max length of strings
const static long long N = 40;                  // number of closest words that will be shown
const static long long max_w = 50;
int type =-1;
int run = 0;
WordModel::WordModel(char* fileName, int typ){
	type = typ;
	if(typ == 1)
		initialize(fileName);
	else
		load("/Users/mamfarouk/Downloads/paragram_300_sl999/paragram_300_sl999.txt");
		//load(fileName);
}
bool WordModel::initialize(char* file_name){
	if(!run)
		return false;
	  FILE *f;
	  float len;
	  long long a, b;

	  //  "/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin"

	  f = fopen(file_name, "rb");
	  if (f == NULL) {
	    printf("Input file not found\n");
	    return -1;
	  }
	  fscanf(f, "%lld", &words);
	  fscanf(f, "%lld", &size);
	  printf("test %lld   %i", words, size);
	  words = 100000;
	  vocab = new char[words * max_w];//(char *)malloc((long long)words * max_w * sizeof(char));
	 // for (a = 0; a < N; a++) bestw[a] = new char[max_size];//(char *)malloc(max_size * sizeof(char));
	  M = new float[words * (long long)size ];//(float *)malloc((long long)words * (long long)size * sizeof(float));
	  if (M == NULL) {
	    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
	    return -1;
	  }
	  for (b = 0; b < words; b++) {
	    a = 0;
	    while (1) {
	      vocab[b * max_w + a] = fgetc(f);
	      if (feof(f) || (vocab[b * max_w + a] == ' ')) break;
	      if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
	    }
	    vocab[b * max_w + a] = 0;
	    for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
	    len = 0;
	    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
	    len = sqrt(len);
	    for (a = 0; a < size; a++) M[a + b * size] /= len;
	  }
	  fclose(f);
}
bool WordModel::load(char* file_name){
	if(!run)
		return false;
cout<<"test are strated"<<endl;
	fstream f;
	f.open(file_name, ios::in);
	  float len;
	  long long a, b;

	  //  "/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin"

	//  f = fopen(file_name, "rb");
	  if (!f.is_open()) {
	    printf("Input file not found\n");
	    return -1;
	  }
	  size = 300;
	  words = 200000;
	  vocab = new char[words * max_w];//(char *)malloc((long long)words * max_w * sizeof(char));
	  mat = new float*[words];
	  for(int i=0; i< words; i++)
		  mat[i] = new float[size];
	  voc = new char*[words];
	  	  for(int i=0; i< words; i++)
	  		  voc[i] = new char[40];
	 // for (a = 0; a < N; a++) bestw[a] = new char[max_size];//(char *)malloc(max_size * sizeof(char));
	  double d;
	  char temp[50];
	  for (b = 0; b < words; b++) {
	    f>>voc[b];
	    //cout<<voc[b]<<"  "<<b<<endl;
	    for (a = 0; a < size; a++) //fread(&M[a + b * size], sizeof(float), 1, f);
	    	f>>mat[b][a];
	/*    len = 0;
	    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
	    len = sqrt(len);
	    for (a = 0; a < size; a++) M[a + b * size] /= len;
	    */
	  }
	  f.close();
	  cout<<"END LOOP";
}
float* WordModel::getDeepVector(char* word, bool &e) const{
	float *vec1 = getVector(word, e);
	if (e && word[0] > 96)
		word[0] -= 32;
	float *vec2 = getVector(word, e);
	for (int i = 0; i < size; i++) {
		vec1[i] += vec2[i];
		vec1[i] /= 2.0;
	}
	return vec1;
}
float* WordModel::getVector(char* word, bool &e) const{
	//cout<<"get vetc ......"<<type<<endl;
	float *vec = new float[size];
	int a;
	for (a = 0; a < size; a++) {
		vec[a] =0;
	}
		int b;
		if(type ==1){
		for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], word)) break;
		if (b == words)
		{
			//printf("Out of dictionary word!\n");
			e = false;
			return vec;
		}
		else
			{
			//printf("\nWord: %s  Position in vocabulary: %lld\n", word, b);
			for (a = 0; a < size; a++) {
				vec[a] += M[a + b * size];
			}
			e = true;
			}
		return vec;
		}
		else{
			for (b = 0; b < words; b++) if (!strcmp(voc[b], word)) break;
					if (b == words)
					{
						//printf("Out of dictionary word!\n");
						e = false;
						return vec;
					}
					else
						{
						//printf("\nWord: %s  Position in vocabulary: %lld\n", word, b);
						double temp = 0;
						for (a = 0; a < size; a++) {
							vec[a] += mat[b][a];
							temp += mat[b][a]*mat[b][a];
						}
						temp = sqrt(temp);
						for (a = 0; a < size; a++) vec[a] /= temp;
						e = true;
						}
					//cout<<"okokokokokokokokok"<<endl;
					return vec;
		}
		}

