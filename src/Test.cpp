/*
 * Test.cpp
 *
 *  Created on: Apr 26, 2018
 *      Author: mamfarouk
 */
#include <fstream>
#include<iostream>
#include<cstdlib>
#include<math.h>
#include<ctype.h>
#include "SemanticSimilarity.h"
#include "wn/wn.h"

#include "sentence_similarity.h"
#include "wordnet_extended.h"
#include<util.h>
//#include <exception>

typedef WordnetExtended we;

using namespace boost;


char* getLine(FILE* f){
	char* l = new char[800];
	int i=0;
	while(1){
		l[i] = fgetc(f);
		if(l[i] == '\n')
			break;
		i++;
	}
	l[i] = '\0';
	//cout<<i<<endl;
	return l;
}
void preProcess(char* str){

}
double calcPearson(float x[], float y[], int size){
	double sumXY=0, sumX2=0, sumY2=0, sumX=0, sumY=0;
	for(int i=0; i< size; i++){
		sumXY += x[i]*y[i];
		sumX2 += x[i]*x[i];
		sumY2 += y[i]*y[i];
		sumX += x[i];
		sumY += y[i];
	}
	double p = (size*sumXY - sumX*sumY) / (sqrt(size*sumX2 - sumX*sumX) * sqrt(size*sumY2 - sumY*sumY));
	return p;
}
void readDataset(){
	cout << "this is a test message";

		WordModel wm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin", 1);
		SemanticSimilarity ss(&wm);
		FILE *f;
		f = fopen("/research/NLP/dataset","rb");
		if (f == NULL) {
			printf("Input file not found\n");
			return ;
		}
		cout<<endl;
		int i;
		float m1[65];
		float m2[65];
		float m3[65];
		float origin[65];
		float other[65];
		double wos;
		for ( i = 0; i < 65; i++) {
			getLine(f);
			char* line1 = getLine(f);
			char* line2 = getLine(f);
			//cout << line1<<"  --  "<<line2<<endl;
			short result;
			char* st1, *st2;
			st1 = new char[700];
			st2 = new char[700];
			int len = strlen(line1);
			if(len<1)
				break;
			 len = strlen(line2);
						if(len<1)
							break;
			int c1;
			strcpy(st1, line1);
			strcpy(st2, line2);
			//cout<<"test   m  "<<endl;
			Sentence s1(st1);
			Sentence s2(st2);
			//cout<<st1<<" & "<<st2<<" & ";
			s1.initVectors(wm);
			s2.initVectors(wm);
			//cout<<"test   m  "<<i<<endl;
			wos = ss.getWordOrderSim(s1,s2);
			m1[i] = ss.getSentenceSim_Mean(s1, s2)*0.6+0.4*wos;
			m2[i] = ss.getSentenceSim_WordToSentMax(s1, s2)*0.6+0.4*wos;
			m3[i] = ss.getSentenceSim_MaxVector(s1, s2)*0.6+0.4*wos;
			//	ss.getSentenceSim(st1, st2);
			origin[i] = atof(getLine(f));//<<", ";
			other[i] = atof(getLine(f));//<<endl;
			//cout<<m1[i]<<" & "<<m2[i]<<" & "<<m3[i]<<" & "<<origin[i]<<"\\\\ \n \\hline"<<endl;
	//cout<<result<<endl<<st1<<endl<<st2<<endl;
	//cout<<ss.getSentenceSim(st1, st2)<<endl;
		}
		cout<<i<<endl;
		cout<<calcPearson(origin, m1, 65)<<" & "<<calcPearson(origin, m2, 65)<<" & "<<calcPearson(origin, m3, 65);
}
void readDataset_WN(){
	cout << "this is a test message";

		WordModel wm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin", 1);
		SemanticSimilarity ss(&wm);
		FILE *f;
		f = fopen("/research/NLP/dataset2","rb");
		if (f == NULL) {
			printf("Input file not found\n");
			return ;
		}
		cout<<endl;
		int i;
		float m1[65];
		float m2[65];
		float m3[65];
		float origin[65];
		float other[65];
		we we("/Programs/WordNet-3.0/dict/",
									"/research/NLP/tools/semantic-similarity-master/dicts/freq.txt");

		double wos;
		for ( i = 0; i < 60; i++) {
			getLine(f);
			char* line1 = getLine(f);
			char* line2 = getLine(f);
			//cout << line1<<"  --  "<<line2<<endl;
			short result;
			char* st1, *st2;
			st1 = new char[700];
			st2 = new char[700];
			int len = strlen(line1);
			if(len<1)
				break;
			 len = strlen(line2);
						if(len<1)
							break;
			int c1;
			strcpy(st1, line1);
			strcpy(st2, line2);
			//cout<<"test   m  "<<endl;
			Sentence s1(st1);
			Sentence s2(st2);
			cout<<st1<<" & "<<st2<<" & ";
			s1.initVectors(wm);
			s2.initVectors(wm);
			//cout<<"test   m  "<<i<<endl;

			we::UndirectedGraph g;
			SentenceSimilarityLi2006 ssWN(we);
			double v2 = ssWN.compute_similarity(st1, st2, g);
			double v1 = ss.getSentenceSim_WordToSentMaxWN_WE(s1, s2);
			double v3 = ss.getSentenceSim_WordToSentMax(s1, s2);
			//cout<<i<<":  "<<v1<<"    "<<v3<<endl;
			wos = ss.getWordOrderSim(s1,s2);
			m1[i] = v2*0.15+v3*0.55+wos*0.3;
			m2[i] = v2*0.5+v3*0.5;
			m3[i] = v1*0.6+wos*0.4;

			//cout<<wos<<endl;
			//	ss.getSentenceSim(st1, st2);
			origin[i] = atof(getLine(f));//<<", ";
			other[i] = atof(getLine(f));//<<endl;
			cout<<origin[i]<<endl;
			cout<<i<<":   "<<m1[i]<<" & "<<m2[i]<<" & "<<m3[i]<<" & "<<origin[i]<<"\\\\ \n \\hline"<<endl;
	//cout<<result<<endl<<st1<<endl<<st2<<endl;
	//cout<<ss.getSentenceSim(st1, st2)<<endl;
		}
		cout<<i<<endl;
		cout<<calcPearson(origin, m1, 60)<<" & "<<calcPearson(origin, m2, 60)<<" & "<<calcPearson(origin, m3, 60);
}

void readDataset_sts(){
	cout << "this is a test message";
		Util u;
		//WordModel wm2("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin", 1);
		WordModel wm("/Users/mamfarouk/Downloads/paragram_300_sl999/paragram_300_sl999.txt", -1);
		SemanticSimilarity ss(&wm);
		FILE *f;
		f = fopen("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.input.answers-forums.txt","rb");
		if (f == NULL) {
			printf("Input file not found\n");
			return ;
		}
		FILE *fout;
				fout = fopen("/research/NLP/sts datasets/2015/WTWRes_SL999/STS.answers-forums-WTWRes2.txt","w");
				if (f == NULL) {
					printf("Input file not found\n");
					return ;
				}
		FILE *f2;
				f2 = fopen("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.gs.answers-forums.txt","rb");
				if (f2 == NULL) {
					printf("Input file not found\n");
					return ;
				}
		cout<<endl;
		int i;
		float m1[2000];
		float m2[2000];
		float m3[2000];
		float origin[2000];
//		float other[65];
		we we("/Programs/WordNet-3.0/dict/",
									"/research/NLP/tools/semantic-similarity-master/dicts/freq.txt");
		char* line;
		double wos;
		for ( i = 0; i < 2000; i++) {
			line = getLine(f);
			origin[i] = atof(getLine(f2));
		//	if(i<1049)
		//		continue;
			string* subs = u.split(line, 9, 20);
			const char* line1 = subs[0].c_str();

			const char* line2 = subs[1].c_str();
			//cout << line1<<"  --  "<<line2<<endl;
			short result;
			char* st1, *st2;
			st1 = new char[700];
			st2 = new char[700];
			int len = strlen(line1);
			if(len<1)
				break;
			 len = strlen(line2);
						if(len<1)
							break;
			int c1;
	//		if(i<1050)
	//			continue;
			strcpy(st1, line1);
			strcpy(st2, line2);
			//cout<<"test   m  "<<endl;
			Sentence s1(st1);
			Sentence s2(st2);
			cout<<st1<<" & "<<st2<<" & ";
			s1.initVectors(wm);
			s2.initVectors(wm);
		//	s1.initVectors2(wm2);
		//	s2.initVectors2(wm2);
			//cout<<"test   m  "<<i<<endl;

	//		we::UndirectedGraph g;
	//		SentenceSimilarityLi2006 ssWN(we);
	//		cout<<ssWN.compute_similarity("Coupling, an American version of a hit British comedy, will get the valuable Thursday 9:30 p.m. time slot.", "Coupling, an American version of a hit British comedy, will couple with Friends on Thursdays.", g)<<"******"<<endl;
		//	return;
			double v1 = ss.getSentenceSim_WordToSentMaxWN_WE(s1, s2);
	//		double v3 = ss.getSentenceSim_WordToSentMax(s1, s2);
	//		double v2 = ssWN.compute_similarity(st1, st2, g);
		//	cout<<i<<":  "<<v1<<"    "<<v3<<endl;
			wos = ss.getWordOrderSim(s1,s2);
	//		m1[i] = v2*0.15+v3*0.55+wos*0.3;
	//		m2[i] = v2*0.5+v3*0.5;
			m3[i] = v1*0.6+wos*0.4;

			//	ss.getSentenceSim(st1, st2);
			//<<", ";
	//		other[i] = atof(getLine(f));//<<endl;
			cout<<origin[i]<<endl;
	//		cout<<i<<":   "<<m1[i]<<" & "<<m2[i]<<" & "<<m3[i]<<" & "<<origin[i]<<"\\\\ \n \\hline"<<endl;
			char temp[28];
			sprintf(temp, "%f", m3[i]);
			u.writeLine(fout, temp);
		}
		cout<<"finished  ";
		cout<<i<<endl;
		cout<<calcPearson(origin, m1, 1500)<<" & "<<calcPearson(origin, m2, 1500)<<" & "<<calcPearson(origin, m3, 1500);
}
double calcPearsonFromFile(/*File* f1, File* f2,*/ int num){
	cout<<"start..."<<endl;
	FILE *f1;
			f1 = fopen("/research/NLP/sts datasets/2015/WTWRes_SL999/STS.rs.images3Test.txt","rb");
			//f1 = fopen("//research/NLP/sts datasets/2015/test_evaluation_task2a/STS.gs.answers-forums.txt","rb");
			if (f1 == NULL) {
				printf("Input file13 not found\n");
				return 0;
			}
			cout<<"progress 1..."<<endl;
	FILE *f11;
			f11 = fopen("/research/NLP/sts datasets/2015/WTWRes_SL999/STS.images-WTWRes.txt","rb");
			if (f11 == NULL) {
				printf("Input file1 not found\n");
				return 0;
			}
			cout<<"progress 1..."<<endl;
	FILE *f2;
			f2 = fopen("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.gs.images.txt","rb");
			if (f2 == NULL) {
				printf("Input file2 not found\n");
				return 0;
			}
			cout<<"progress 2..."<<endl;
	float* list1 = new float[num];
	float* list2 = new float[num];
	double st, wtw;
	int i=0;
	for(int j=0; j < num; j++,i++){
		cout<<i<<endl;
		st = atof(getLine(f1));
		wtw = atof(getLine(f11));
		char* str = getLine(f2);
	//	if(st == 0)
	//	{ i--; continue;}
	//	else
			list1[i] = st; //(st*0.5 + wtw*0.5);
		//cout<<list1[i]<<"  --  "<<list2[i]<<endl;
		if(strlen(str)<=0)
		{ i--; continue;}
		list2[i] = atof(str);
		if(list1[i] == 0)
		{ i--; continue;}
		cout<<list1[i]<<"    "<<list2[i]<<endl;
		if(isnan(list1[i]) || isnan(list2[i]))
			i--;
	}
	cout<<"final  "<<i<<endl;
	return calcPearson(list1, list2, i);

}
double calcMeasure(WordModel* wm, SemanticSimilarity ss, char* line_Tok1, char* line_Tok2){
	Sentence s1("", line_Tok1);
	//for(int i=0; i<s1.wordCount; i++)
	//	cout<<s1.words[i].w<<"  "<<s1.words[i].POS<<endl;
	Sentence s2("", line_Tok2);
	//return;
	s1.initVectors(*wm);
	s2.initVectors(*wm);
	//cout << endl << endl << i << endl << endl;
	double wos = ss.getWordOrderSim(s1, s2);
	//cout<<endl<<ss.getSentenceSim_Mean(s1, s2) * 0.6 + 0.4 * wos;
	//cout<<endl<<ss.getSentenceSim_WordToSentMax(s1, s2) * 0.6 + 0.4 * wos;
	//cout<<endl<<
			return ss.getSentenceSim_WordToSentMax_Tok(s1, s2) * 0.6 + 0.4 * wos;
	//cout<<endl<<ss.getSentenceSim_MaxVector(s1, s2) * 0.6 + 0.4 * wos;

}
void readDataset_Tok(){
	cout << "this is a test message";

		WordModel wm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin", 1);
		SemanticSimilarity ss(&wm);
		FILE *f;
		f = fopen("/research/NLP/dataset_Tok","rb");
		if (f == NULL) {
			printf("Input file not found\n");
			return ;
		}
		cout<<endl;
		int i;
		float m1[65];
		float m2[65];
		float m3[65];
		float origin[65];
		float other[65];
		double wos;
		for ( i = 0; i < 10; i++) {
			//getLine(f);
			char* line1 = getLine(f);
			char* line_Tok1 = getLine(f);
			char* line2 = getLine(f);
			char* line_Tok2 = getLine(f);

			//cout << line1<<"  --  "<<line2<<endl;
			short result;
			char* st1, *st2;
			st1 = new char[700];
			st2 = new char[700];
			int len = strlen(line1);
			if(len<1)
				break;
			 len = strlen(line2);
						if(len<1)
							break;
		int c1;
		strcpy(st1, line1);
		strcpy(st2, line2);
		//cout<<"test   m  "<<endl;
		if(i==3)
		calcMeasure(&wm, ss, line_Tok1, line_Tok2);
	/*	if (i >= 0) {
			Sentence s1(st1, line_Tok1);
			Sentence s2(st2, line_Tok2);
			s1.initVectors(wm);
			s2.initVectors(wm);
			cout << endl << endl << i << endl << endl;
			//				wos = ss.getWordOrderSim(s1,s2);
			//							m1[i] = ss.getSentenceSim_Mean(s1, s2)*0.6+0.4*wos;
			//						m2[i] = ss.getSentenceSim_WordToSentMax(s1, s2)*0.6+0.4*wos;
			//m3[i] = ss.getSentenceSim_MaxVector(s1, s2) * 0.6 + 0.4 * wos;
		}
		*/
		//cout<<st1<<" & "<<st2<<" & ";
		/*
		 //cout<<"test   m  "<<i<<endl;
		 //	ss.getSentenceSim(st1, st2);
			 *
			 */
			origin[i] = atof(getLine(f));//<<", ";
			other[i] = atof(getLine(f));//<<endl;
			cout<<" \n "<<origin[i]<<"   "<<other[i]<<endl;
			//cout<<m1[i]<<" & "<<m2[i]<<" & "<<m3[i]<<" & "<<origin[i]<<"\\\\ \n \\hline"<<endl;
	//cout<<result<<endl<<st1<<endl<<st2<<endl;
	//cout<<ss.getSentenceSim(st1, st2)<<endl;

		}
		cout<<i<<endl;
		cout<<calcPearson(origin, m1, 65)<<" & "<<calcPearson(origin, m2, 65)<<" & "<<calcPearson(origin, m3, 65);
}
void readDataset_POS(){
	cout << "this is a test message";

		WordModel wm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin", 1);
		SemanticSimilarity ss(&wm);
		FILE *f;
		f = fopen("/research/NLP/dataset_POS","rb");
		if (f == NULL) {
			printf("Input file not found\n");
			return ;
		}
		cout<<endl;
		int i;
		float m1[65];
		float m2[65];
		float m3[65];
		float origin[65];
		float other[65];
		double wos;
		char* line1, *line_Tok1, *line2, *line_Tok2;
		//char* st1, *st2;
		for ( i = 0; i < 65; i++) {
			//getLine(f);
			line1 = getLine(f);
			line_Tok1 = getLine(f);
			line2 = getLine(f);
			line_Tok2 = getLine(f);

			//cout << line1<<"  --  "<<line2<<endl;
			short result;


			int len = strlen(line_Tok1);
			if(len<1)
				break;
			//st1 = new char[len];
			 len = strlen(line_Tok2);
						if(len<1)
							break;
		int c1;

					//st2 = new char[len];
		//cout<<"test   m  "<<endl;
		//if(i==3)
		//m1[i] = calcMeasure(&wm, ss, line_Tok1, line_Tok2);
	//	if (i >= 0) {
			Sentence s1("", line_Tok1);
			Sentence s2("", line_Tok2);
			s1.initVectors(wm);
			s2.initVectors(wm);
			double v1 =ss.getSentenceSim_WordToSentMax_Tok(s1, s2);
			double v2 = ss.getSentenceSim_WordToSentMax(s1, s2);
			double v3 = ss.getSentenceSim_WordToSentMaxWN_WE(s1, s2);
			//cout << endl << endl << i << endl << endl;
			wos = ss.getWordOrderSim(s1,s2);
			m1[i] = v2*0.55+0.45*wos;;//(ss.getSentenceSim_Mean_POS(s1, s2)+v2)*0.3+0.4*wos;
			m2[i] = v1*0.55+0.45*wos;
			m3[i] = v3*0.55+0.45*wos;
	//	}
	//	*/
		//cout<<st1<<" & "<<st2<<" & ";
		/*
		 //cout<<"test   m  "<<i<<endl;
		 //	ss.getSentenceSim(st1, st2);
			 *
			 */
			origin[i] = atof(getLine(f));//<<", ";
			other[i] = atof(getLine(f));//<<endl;
			cout<<" \n "<<origin[i]<<"   "<<other[i]<<endl;
			//cout<<m1[i]<<" & "<<m2[i]<<" & "<<m3[i]<<" & "<<origin[i]<<"\\\\ \n \\hline"<<endl;
	//cout<<result<<endl<<st1<<endl<<st2<<endl;
	//cout<<ss.getSentenceSim(st1, st2)<<endl;

		}
		cout<<i<<endl;
		cout<<calcPearson(origin, m1, 65)<<" & "<<calcPearson(origin, m2, 65)<<" & "<<calcPearson(origin, m3, 65);
}
void addWord(char* w, char** all, int& size, short freq[]){
	for(int i=0; i<strlen(w); i++)
		if(w[i]=='.' || w[i]=='?' || w[i]=='"' || w[i]=='\\'  || w[i]==',' || w[i]=='!' || w[i]==':'){
			for(int j=i; j<=strlen(w); j++)
				w[j] = w[j+1];
			i--;
		}
	w[0] = tolower(w[0]);
	cout<<w<<":::::"<<size<<endl;
	bool found = false;
			for(int j =0; j< size; j++){
				if(strcmp(all[j], w) == 0)
					{ freq[j]++; found = true; break; }
			}
			if(!found)
				{
				all[size] = w;
				freq[size++] = 1;
				}

}
int getWordSet(string* words){
	int count =0;
	for(int i=0; i<50; i++){
		if(words[i].length() <= 0)
			break;
		count++;
	}
	cout<<count<<endl;
	for(int j=0; j< count; j++){
//		words[j][words[j].length()] = '\0';
		for(int i=0; i< words[j].length(); i++)
			if(words[j][i]=='.' || words[j][i]=='?' || words[j][i]=='"' || words[j][i]=='\\'  || words[j][i]==',' || words[j][i]=='!' || words[j][i]==':'){
				int x;
				for(x=i; x<=words[j].length(); x++)
					words[j][x] = words[j][x+1]; //cout<<x<<"  "<<words[j].length()<<endl;}
				words[j][x-1] = '\0';
				i--;
				cout<<words[j]<<endl;
			}
	}
	for(int i=0; i< count; i++){
			cout<<words[i]<<"   ";
		}cout<<endl;
	for(int i=0; i< count; i++){
		for(int j = i+1; j<count; j++){
			if(strcmp(words[i].c_str(), words[j].c_str()) == 0){
				for(int x=j; x<count; x++)
					words[x] = words[x+1];
				words[count-1][0] = '\0';
				j--;
				count--;
			}
		}
	}for(int i=0; i< count; i++){
		cout<<words[i]<<"   ";
	}cout<<endl;
	return count;
}
void calcIDF_File(char* fileName, int length, char** allWords, int& wordSize, short wordFreq[]){
	Util u;
	char* line;
		FILE *f;
				f = fopen(fileName,"rb");
				if (f == NULL) {
					printf("Input file not found\n");
					return ;
				}


		for (int i = 0; i < length; i++) {
			line = getLine(f);
			string* subs = u.split(line, 9, 20);
			const char* line1 = subs[0].c_str();
			const char* line2 = subs[1].c_str();
			cout << line1<<"  --  "<<line2<<endl;
			string* words = u.split((char*)line1, ' ', 50);
			cout<<"before"<<endl;
			int count = getWordSet(words);
			for(int x=0; x<count; x++){
			cout<<words[x]<<" & "<<endl;
			addWord((char*)(words[x].c_str()), allWords, wordSize, wordFreq);
			}
			cout<<endl;
			words = u.split((char*)line2, ' ', 50);
			//cout<<"before"<<endl;
			count = getWordSet(words);
			for(int x=0; x<count; x++){
			cout<<words[x]<<" & "<<endl;
			addWord((char*)(words[x].c_str()), allWords, wordSize, wordFreq);
			}
			cout<<endl<<i<<endl;
		}

}
void calcIDF(){
	Util u;
	char* allWords[20000];
	short wordFreq[20000];
	int wordSize = 0;
	/*cout<<"test test test"<<endl;
	calcIDF_File("/research/NLP/sts datasets/2015/test_evaluation_task2a/temp.txt", 2, allWords, wordSize, wordFreq);
	//char temp[50];
			for(int i=0; i< wordSize; i++){

				//sprintf(temp, "%s %d", allWords[i], wordFreq[i]);
				//u.writeLine(f, temp);
			cout<<allWords[i]<<"  "<<wordFreq[i]<<"    "<<log((double)3/wordFreq[i])<<endl;
			}
		cout<<wordSize<<endl;
		return;
*/
	calcIDF_File("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.input.belief.txt", 2000, allWords, wordSize, wordFreq);
	calcIDF_File("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.input.headlines.txt", 1500, allWords, wordSize, wordFreq);
	calcIDF_File("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.input.images.txt", 1500, allWords, wordSize, wordFreq);
	calcIDF_File("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.input.answers-students.txt", 1500, allWords, wordSize, wordFreq);
	calcIDF_File("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.input.answers-forums.txt", 1500, allWords, wordSize, wordFreq);

	FILE *f;
	f = fopen("/research/NLP/sts datasets/idf2.txt",
			"w");
	if (f == NULL) {
		printf("Input file not found\n");
		return ;
	}
	char temp[50];
		for(int i=0; i< wordSize; i++){

			sprintf(temp, "%s %d", allWords[i], wordFreq[i]);
			u.writeLine(f, temp);
		cout<<allWords[i]<<"  "<<wordFreq[i]<<endl;
		}
	cout<<wordSize<<endl;

}
void loadIDF(char* fileName, const int wordsNum){
	ifstream f;
	f.open(fileName);
	if(!f.is_open())
		cout<<"Error....";
	char** words = new char*[wordsNum];
	for(int i=0; i< wordsNum; i++)
		words[i] = new char[50];

	short* freq = new short[wordsNum];

//	char* w = new char[50]; short x;
	for(int i=0; i< wordsNum; i++)
	{
		f>>words[i];
		f>>freq[i];
		if(!f)  break;

	}
	for(int i=0; i< wordsNum; i++)
		{
	cout<<words[i]<<"    - "<<freq[i]<<"   "<<i<<"   "<<log((double)8000/freq[i])
			<<endl;}

}
int main00() {
//	Util u;
//	string* words = u.split("where were the \"tea partiers\" in late '08!!!!?????", ' ', 50);
//				int count = getWordSet(words);
//				cout<<count;
//	loadIDF("/research/NLP/sts datasets/idf2.txt", 15394);
//	calcIDF();
	//readDataset_POS();
	//readDataset_WN();
	cout<<calcPearsonFromFile(1500);
//	readDataset_sts();
//	WordModel wm("/Users/mamfarouk/Downloads/paragram_300_sl999/paragram_300_sl999.txt",-1);
	return 0;
	cout << "this is a test message";
/*
	WordModel wm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin");
	SemanticSimilarity ss(&wm);
	Sentence s1("boy eat cake");
	Sentence s2("girl eat apple");
	s1.initVectors(wm);
	s2.initVectors(wm);
	cout<<ss.getSentenceSim_WordToSentMaxWN_WE(s1, s2);
	return 0;
	*/
	/*
	cout<<"final  "<<ss.getSentenceSim("Amrozi accused his brother whom he called the witness of deliberately distorting his evidence",
			"Referring to him as only the witness Amrozi accused his brother of deliberately distorting his evidence")<<endl;
	cout<<"final  "<<ss.getSentenceSim("Amrozi accused brother whom he called witness deliberately distorting evidence",
				"Referring him only witness Amrozi accused his brother deliberately distorting evidence")<<endl;

	return 0;
	*/
	FILE *f;
	f = fopen("/research/NLP/MSRParaphraseCorpus/msr_paraphrase_train.txt",
			"rb");
	if (f == NULL) {
		printf("Input file not found\n");
		return -1;
	}
	getLine(f);
	int i;
	for ( i = 0; i < 100; i++) {
		char* line = getLine(f);
		//cout << line;
		short result;
		char* st1, *st2;
		st1 = new char[700];
		st2 = new char[700];
		int len = strlen(line);
		if(len<2)
			break;
		int c1;
		result = (int) line[0] - 48;
		if(result == 0)
			continue;
		int v = 1;
		for (; v < len; v++)
			if ((int) line[v] == 9)
				break;
		for (v++; v < len; v++)
			if ((int) line[v] == 9)
				break;
		for (v++; v < len; v++)
			if ((int) line[v] == 9)
				break;
		c1 = 0;
		for (v++; v < len; v++) {
			if ((int) line[v] == 9)
				break;

			st1[c1++] = line[v];
		}
		c1 = 0;
		for (v++; v < len; v++) {
			if ((int) line[v] == 9)
				break;

			st2[c1++] = line[v];
		}
		//cout<<st1<<endl<<st2<<endl;
		//preProcess(str1);
		//ss.getSentenceSim(st1, st2);
//cout<<result<<endl<<st1<<endl<<st2<<endl;
//cout<<ss.getSentenceSim(st1, st2)<<endl;
	}
	cout<<i;
}
