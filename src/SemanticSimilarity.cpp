/*
 * SemanticSimilarity.cpp
 *
 *  Created on: Apr 22, 2018
 *      Author: mamfarouk
 */
#include "math.h"
#include "SemanticSimilarity.h"
#include <iostream>
#include <string.h>
using namespace std;
double dotProduct(float* vec1, float* vec2, int size){
	double dot =0;
	for(int i=0; i<size; i++){
		dot += vec1[i] * vec2[i];
	}
	return dot;
}
SemanticSimilarity::SemanticSimilarity(WordModel* wm){
	model = wm;
	loadIDF("/research/NLP/sts datasets/idf2.txt", 15394,8000);
}
double SemanticSimilarity::getSentenceSim(char* str1, char* str2){
	Sentence s1(str1);
	Sentence s2(str2);
	double wos = getWordOrderSim(s1,s2);
	//return 0;
	//cout<<str1<<"  ---  \n"<<str2<<endl;
	s1.initVectors(*model);
	s2.initVectors(*model);
	//cout<<"getSentenceSim_WordToSentMax    "
			//cout<<getSentenceSim_WordToSentMax(s1, s2)<<endl;
	//cout<<"getSentenceSim_Word To Mean    ";
	//cout<<getSentenceSim_WordsToMean(s1, s2)<<endl;
	//cout<<"getSentenceSim_Word To Words    ";
	//cout<<getSentenceSim_WordsToWords(s1, s2)<<endl;
	//test
	//cout<<getSentenceSim_MaxVector(s1, s2);
	//return 0;
	//end test
	cout<<getSentenceSim_MeanNew(s1, s2)*0.85+0.15*wos<<", "<<getSentenceSim_Mean(s1, s2)*0.85+0.15*wos
			<<", "<<getSentenceSim_WordToSentMax(s1, s2)*0.85+0.15*wos<<", "<<getSentenceSim_WordsToMean(s1, s2)*0.85+0.15*wos
			<<", "<<getSentenceSim_WordsToWords(s1, s2)*0.85+0.15*wos<<", "<<getSentenceSim_MaxVector(s1, s2)*0.85+0.15*wos<<", ";

	return 0;//
}
double SemanticSimilarity::getSentenceSim_Mean(Sentence s1, Sentence s2){
	float* vecM1 = s1.getMeanVector();
	float* vecM2 = s2.getMeanVector();
	double cos = cosineSim(vecM1, vecM2);//double cos = dotProduct(vecM1, vecM2, model->size) / (sqrt(dotProduct(vecM1, vecM1, model->size))*sqrt(dotProduct(vecM2, vecM2, model->size)));
	return cos;
}
double SemanticSimilarity::getSentenceSim_Mean_POS(Sentence s1, Sentence s2){
	float* vecM1 = s1.getNounMeanVector();
	float* vecM2 = s2.getNounMeanVector();
	double cos = cosineSim(vecM1, vecM2);//double cos = dotProduct(vecM1, vecM2, model->size) / (sqrt(dotProduct(vecM1, vecM1, model->size))*sqrt(dotProduct(vecM2, vecM2, model->size)));
	float* vecM3 = s1.getVerbMeanVector();
		float* vecM4 = s2.getVerbMeanVector();
		double cos2 = cosineSim(vecM3, vecM4);//double cos = dotProduct(vecM1, vecM2, model->size) / (sqrt(dotProduct(vecM1, vecM1, model->size))*sqrt(dotProduct(vecM2, vecM2, model->size)));
		return (cos+cos2)/2;
}
double SemanticSimilarity::getSentenceSim_MeanNew(Sentence s1, Sentence s2){
	float* vecM1 = s1.getMeanVector();
	float* vecM2 = s2.getMeanVector();
	float* vec = new float[model->size];
	for(int i=0; i<model->size; i++){
		vec[i] = vecM1[i] - vecM2[i];
		//cout<<" test  "<<vec[i];
	}
	//double cos = cosineSim(vecM1, vecM2);//double cos = dotProduct(vecM1, vecM2, model->size) / (sqrt(dotProduct(vecM1, vecM1, model->size))*sqrt(dotProduct(vecM2, vecM2, model->size)));
	double d = dotProduct(vec, vec, model->size);;
	//cout<<" test  "<<d;
	return d;
}
double SemanticSimilarity::cosineSim(float* v1, float* v2){
	double cos = dotProduct(v1, v2, model->size) / (sqrt(dotProduct(v1, v1, model->size))*sqrt(dotProduct(v2, v2, model->size)));
	return cos;
}
double SemanticSimilarity::ManhSim(float* v1, float* v2){
	double tDis = 0;
	for(int i=0; i< model->size; i++)
		tDis += (v1[i] - v2[i])*(v1[i] - v2[i]);
	cout<<"*"<<tDis<<endl;
	return (((tDis)/ (sqrt(dotProduct(v1, v1, model->size))*sqrt(dotProduct(v2, v2, model->size)))));
}
	WordnetExtended wen("/Programs/WordNet-3.0/dict/","/research/NLP/tools/semantic-similarity-master/dicts/freq.txt");
	WordnetExtended::UndirectedGraph g;
	SentenceSimilarityLi2006 ssWN(wen);
double SemanticSimilarity::getMatch(word w1, word w2, 	SentenceSimilarityLi2006 *ssW){

	double d1 = cosineSim(w1.vector, w2.vector);
//	double temp = cosineSim(w1.vector2, w2.vector2);
//	cout<<d1<<"    -    "<<temp<<endl;
//	if(isnan(d1))
//		d1 = temp;
/*	else
	{
		float v1[600];
		float v2[600];
		for(int i=0; i< 300; i++){
			v1[i] = w1.vector[i];
			v1[i+300] = w1.vector2[i];
			v2[i] = w2.vector[i];
			v2[i+300] = w2.vector2[i];
		}
		d1 = dotProduct(v1, v2, 600) / (sqrt(dotProduct(v1, v1, 600))*sqrt(dotProduct(v2, v2, 600)));
	}
	*/
	if(!w1.exist && !w2.exist && strcmp(w1.w, w2.w)==0)
		{ d1 = 1; cout<<"++++++++++////okokokokoko///////////////////////////\\\\\\\\\\\\\\\\++++++++++++++++++"<<endl;
		return 1;}
//	cout<<w1.w<<"  WordNet sim  "<<w2.w<<endl;
	double d2 = ssW->compute_similarity(w1.w, w2.w, g);
	//return d2;
	//cout<<w1.w<<" - "<<w2.w<<"  &  "<<d1<<"  &  "<<d2<<"  & "<<d1*0.75+d2*0.25<<"\\\\ \\hline"<<endl;
//	if(d1 <= 0)
//		return d2;
	return (d1*0.75+d2*0.25);
	//else
		//return d1*0.85;
}
double getMatchOfUnfound(word w, Sentence s){
	double d;
		for(int i=0; i <s.wordCount; i++){
			if(!s.words[i].exist && strcmp(w.w, s.words[i].w)==0)
				return 1;
		}
		return 0;
}
double SemanticSimilarity::getMaxMatch(word w, Sentence s){
	if(!w.exist)
		return getMatchOfUnfound(w, s);
	double max =0;
	double d;
	for(int i=0; i <s.wordCount; i++){
		d = cosineSim(w.vector, s.words[i].vector);
		//cout<<s.words[i].w<<"   "<<d<<"   ; ";
		if(d > max)
			max = d;
	}
	return max;
}
double SemanticSimilarity::getMaxMatchWN_WE_Mix(word w, Sentence s){
	double max =0;
	double d;

	for(int i=0; i <s.wordCount; i++){
		d = getMatch(w, s.words[i], &ssWN);
		if(d > max)
			max = d;
	}
	return max;
}
double SemanticSimilarity::getMaxMatch_Tok(word wo , Sentence s){
	double max =0;
	double d, w;
	for(int i=0; i <s.wordCount; i++){
		w = getPOSWeight(wo.POS, s.words[i].POS);
		d = cosineSim(wo.vector, s.words[i].vector)*w;
		if(d > max)
			max = d;
	}
	return max;
}
double SemanticSimilarity::getSentenceSim_WordToSentMax(Sentence s1, Sentence s2){
	double sim=0, d;
	int count =0;
	if(s1.wordCount < s2.wordCount){
		for(int i=0; i<s1.wordCount; i++){
			if(s1.words[i].exist){
			d =getMaxMatch(s1.words[i], s2);
			sim += d;
			count++;
			}
			//cout<<s1.words[i].w<<"   "<<d<<endl;
		}
		return sim/count;
	}
	else{
		for(int i=0; i<s2.wordCount; i++){
			if(s2.words[i].exist){
					d =getMaxMatch(s2.words[i], s1);
					sim += d;
					count++;
			}
			//cout<<s2.words[i].w<<"   "<<d<<endl;
				}
				return sim/s2.wordCount;
	}
}
double SemanticSimilarity::getSentenceSim_WordToSentMaxWN_WE(Sentence s1, Sentence s2){
	double sim=0, d;
	int count =0;
	if(s1.wordCount < s2.wordCount){
		for(int i=0; i<s1.wordCount; i++){
			//if(s1.words[i].exist)
			d =getMaxMatchWN_WE_Mix(s1.words[i], s2);
			if(d>0)
			{

				sim += d;//*getIdf(s1.words[i].w, s1);
				count++;
			}
			//cout<<s1.words[i].w<<"   "<<d<<endl;
		}
		return sim/count;
	}
	else{
		for(int i=0; i<s2.wordCount; i++){
			//if(s2.words[i].exist)
			d = getMaxMatchWN_WE_Mix(s2.words[i], s1);
			if(d>0)
			{
				sim += d;//*getIdf(s1.words[i].w, s2);
				count++;
			}
		}
		return sim/s2.wordCount;
	}
}

double SemanticSimilarity::getSentenceSim_WordsToMean(Sentence s1, Sentence s2){
	float* vMean = s1.getMeanVector();
	double sum = 0, d;
	short count = 0;
	for (int i = 0; i < s2.wordCount; i++) {
		d = cosineSim(s2.words[i].vector, vMean);
		if (!isnan(d)) {
			sum += d;
			count++;
		}
	}
	float* vMean2 = s2.getMeanVector();
	for (int i = 0; i < s1.wordCount; i++) {
		d = cosineSim(s1.words[i].vector, vMean2);
		if (!isnan(d)) {
			sum += d;
			count++;
		}
	}
	return sum / count;
}
double SemanticSimilarity::getSentenceSim_WordsToWords(Sentence s1, Sentence s2){
	double sum = 0, d;
	short count = 0;
	for (int i = 0; i < s1.wordCount; i++) {
		for(int j = 0; j<s2.wordCount; j++){
		d = cosineSim(s1.words[i].vector, s2.words[j].vector);
		if (!isnan(d)) {
			sum += d;
			count++;
		}
		}
	}
	return sum / count;
}
double SemanticSimilarity::getSentenceSim_CommonWords(Sentence s1, Sentence s2, double th){
	double sum = 0, d;
	short count = 0;
	for (int i = 0; i < s1.wordCount; i++) {
		if(s1.words[i].exist){
			d = getMaxMatch(s1.words[i], s2);
			if(d > th)
				count++;
		}
	}
	int len = (s1.wordCount > s2.wordCount )?s1.wordCount : s2.wordCount;
	return count/len;
}
double SemanticSimilarity::getSentenceSim_MaxVector(Sentence s1, Sentence s2){
	int len = (s1.wordCount > s2.wordCount)? s1.wordCount : s2.wordCount;
	float* v1 = new float[len];
	float* v2 = new float[len];
	for(int i=0; i<len; i++){
		if(i<s1.wordCount){
			v1[i] = getMaxMatch(s1.words[i], s2);
		}
		else
			v1[i] = 0.0;
		if(i<s2.wordCount){
						v2[i] = getMaxMatch(s2.words[i], s1);
					}
					else
						v2[i] = 0.0;
	}
	for(int i=0; i<len; i++){
	//		cout<<v1[i]<<"        \t"<<v2[i]<<endl;
		}
	double cos = dotProduct(v1, v2, len) / (sqrt(dotProduct(v1, v1, len))*sqrt(dotProduct(v2, v2, len)));
		return cos;
}
double SemanticSimilarity::getWordSim(char* w1, char* w2){
	bool b;
	float* vec1 = model->getVector(w1,b);
	float* vec2 = model->getVector(w2,b);
	double s = cosineSim(vec1, vec2);
	delete vec1;
	delete vec2;
	return s;
	//cout<<w1<<"   "<<w2<<"    "<<cosineSim(vec1, vec2)<<"    "<<ManhSim(vec1, vec2)<<endl;
	//return ManhSim(vec1, vec2);
}
double SemanticSimilarity::getWordSimLowerUpper(char* w1, char* w2){
	bool b;
	float* vec1 = model->getVector(w1,b);
	float* vec2 = model->getVector(w2,b);
	float* vec11, *vec22, *vec111, *vec222;
	if(w1[0]>='a')
	{
		char* w11 = new char[50];
		strcpy(w11,w1);
		w11[0] -=32;
		vec11 = model->getVector(w11, b);
		for(int i=1;i<strlen(w11);i++)
				w11[i] -=32;
		vec111 = model->getVector(w11, b);
		for(int i=0; i<model->size; i++)
			{
			vec1[i] +=vec11[i];//+vec111[i];
			vec1[i] /=3.0;
			}
	}
	if(w2[0]>='a')
		{
			char* w22 = new char[50];
			strcpy(w22,w2);
			w22[0] -=32;
			vec22 = model->getVector(w22, b);
			for(int i=1; i<strlen(w22); i++)
				w22[i] -=32;
			vec222 = model->getVector(w22, b);
			for(int i=0; i<model->size; i++)
				{
				vec2[i] +=vec22[i];// + vec222[i];
				vec2[i] /=3.0;
				}
		}
	return cosineSim(vec1, vec2);//+cosineSim(vec11,vec22)+cosineSim(vec1, vec22)+cosineSim(vec11, vec2))/4.0;
}
double SemanticSimilarity::getWordOrderSim(Sentence s1, Sentence s2) {
	Sentence s;
	bool f;
	//cout<<"dddddddddddddd"<<endl;
	s.words = new word[s1.wordCount + s2.wordCount];
	s.wordCount = 0;
	//cout<<"dddddddddddddd  "<<s.wordCount + s1.wordCount<<endl;
	for (int i = 0; i < s1.wordCount; i++) {
		f = 1;
		for (int j = 0; j < s.wordCount; j++) {
			//cout<<"dddddddddddddd  "<<endl;
			if (strcmp(s1.words[i].w, s.words[j].w) == 0) {
				f = 0;
				break;
			}
		}
		if (f) {
			s.words[s.wordCount].w = new char[strlen(s1.words[i].w)];
			strcpy(s.words[s.wordCount].w, s1.words[i].w);
			s.wordCount++;
		}
	}
	//cout<<"dddddddddddddd  end"<<s.wordCount<<endl;
	for (int i = 0; i < s2.wordCount; i++) {
		f = 1;
		for (int j = 0; j < s.wordCount; j++) {
			if (strcmp(s2.words[i].w, s.words[j].w) == 0) {
				f = 0;
				break;
			}
		}
		if (f) {
			//cout<<"dddddddddddddd22"<<endl;
			s.words[s.wordCount].w = new char[strlen(s2.words[i].w)];
			strcpy(s.words[s.wordCount].w, s2.words[i].w);
			s.wordCount++;
		}
	}
	for(int i=0; i< s.wordCount; i++)
		cout<<s.words[i].w<<"   ";
	cout<<endl;
	//cout<<"dddddddddddddd"<<endl;
	float* v1 = new float[s.wordCount];
	float* v2 = new float[s.wordCount];
	for (int i = 0; i < s.wordCount; i++) {
		f = 1;
		for (int j = 0; j < s1.wordCount; j++) {
			if (strcmp(s.words[i].w, s1.words[j].w) == 0) {
				v1[i] = j+1;
				f = 0;
				break;
			}
			if (f)
				v1[i] = 0;
		}
	}
	for (int i = 0; i < s.wordCount; i++) {
		v2[i] =0;
		for (int j = 0; j < s2.wordCount; j++) {
			if (strcmp(s.words[i].w, s2.words[j].w) == 0) {
				v2[i] = j+1;
				break;
			}
		}
	}
/*	for(int i=0; i< s.wordCount; i++)
			cout<<s.words[i].w<<"   ";
		cout<<endl;
		for(int i=0; i< s.wordCount; i++)
				cout<<v1[i]<<"   ";
			cout<<endl;
			for(int i=0; i< s.wordCount; i++)
					cout<<v2[i]<<"   ";
				cout<<endl;
				*/
	double sum1 = 0, sum2=0;
	for (int i = 0; i < s.wordCount; i++) {
		//cout<<v1[i]<<"    \t"<<v2[i]<<"   \t"<<s.words[i].w<<endl;
		sum1 += (v1[i]-v2[i])*(v1[i]-v2[i]);
		sum2 += (v1[i]+v2[i])*(v1[i]+v2[i]);
	}
	//cout<< 1-(sqrt(sum1)/sqrt(sum2))<<endl;
	return 1-(sqrt(sum1)/sqrt(sum2));
}

double SemanticSimilarity::getSentenceSim_WordToSentMax_Tok(Sentence s1, Sentence s2){
	double sim=0, d;
	int count =0;
	if(s1.wordCount < s2.wordCount){
		for(int i=0; i<s1.wordCount; i++){
			if(s1.words[i].exist){
			d =getMaxMatch_Tok(s1.words[i], s2);
			sim += d;
			count++;
			}
			//cout<<s1.words[i].w<<"   "<<d<<endl;
		}
		return sim/count;
	}
	else{
		for(int i=0; i<s2.wordCount; i++){
			if(s2.words[i].exist){
					sim += getMaxMatch_Tok(s2.words[i], s1);
					count++;
			}
				}
				return sim/s2.wordCount;
	}
}
double SemanticSimilarity::getPOSWeight(char* t1, char* t2) {
	//get matrix similarity between tokens
	// weight for corresponding token is 1
	// others is 0.5
	// n to n is 1, n to v is 0.75
	float w = 0.0;
	if (t1[0] == t2[0])
		w = 1;
	/*else if ((t1[0] == 'V' && t2[0] == 'N') || (t1[0] == 'N'
			&& t2[0] == 'V'))
		w = 0.575;
	else if ((t1[0] == 'N' && t2[0] == 'J') || (t1[0] == 'J'
			&& t2[0] == 'N'))
		w = 0.57;
	else if ((t1[0] == 'N' && t2[0] == 'R') || (t1[0] == 'R'
			&& t2[0] == 'N'))
		w = 0.15;
	else if ((t1[0] == 'V' && t2[0] == 'J') || (t1[0] == 'J'
			&& t2[0] == 'V'))
		w = 0.15;
	else if ((t1[0] == 'V' && t2[0] == 'R') || (t1[0] == 'R'
			&& t2[0] == 'V'))
		w = 0.15;
	else if ((t1[0] == 'R' && t2[0] == 'J') || (t1[0] == 'J'
			&& t2[0] == 'R'))
		w = 0.15;
		*/
	else w=0;

	return w;
}
wordidf* SemanticSimilarity::loadIDF(char* fileName, const int wordsNum, int docsNum){
	segma = wordsNum;
	ifstream f;
	f.open(fileName);
	if(!f.is_open())
		cout<<"Error....";

	int freq;
	Allidf = new wordidf[wordsNum];
	for(int i=0; i< wordsNum; i++)
	{
		f>>Allidf[i].word;
		f>>freq;
		if(!f)  break;
		Allidf[i].idf = log( (double)docsNum/freq);

	}
	for(int i=0; i< wordsNum; i++)
		{
	cout<<Allidf[i].word<<"    - "<<Allidf[i].idf<<"   "<<i<<"   "<<endl;}
	return Allidf;

}
double SemanticSimilarity::getIdf(char* word, Sentence s){
	double idf =0;
	double totalIdf =0;
	for(int i=0; i<segma; i++){
		if(strcmp(word, Allidf[i].word) == 0)
		{
			idf = Allidf[i].idf;
			break;
		}
	}
	for(int z =0; z < s.wordCount; z++){
		for(int i=0; i<segma; i++){
				if(strcmp(s.words[z].w, Allidf[i].word) == 0)
				{
					totalIdf = Allidf[i].idf;
					break;
				}
			}
	}
	double tf =0.0;
	for(int i=0; i< s.wordCount; i++){
		if(strcmp(word, s.words[i].w) == 0)
			tf++;
	}
	int wcount =s.wordCount;
		for(int i=0; i< s.wordCount; i++){
			for(int j=i+1; j<s.wordCount; j++)
			if(strcmp(s.words[i].w, s.words[j].w) == 0)
				{wcount--; break; }
		}

	return tf/wcount*idf/totalIdf;
}
double SemanticSimilarity::getIdf(string word, Graph *g){
	double idf =0;
	double totalIdf =0;
	for(int i=0; i<segma; i++){
		if(word.compare(Allidf[i].word) == 0)
		{
			idf = Allidf[i].idf;
			break;
		}
	}
	for(int j=0; j< g->conceptCount; j++){
		for(int i=0; i<segma; i++){
			if(g->nodes[j].lemma.compare(Allidf[i].word) == 0)
			{
				totalIdf += Allidf[i].idf;
				break;
			}
		}
	}
	double tf =0.0;
	for(int i=0; i< g->conceptCount; i++){
		if(word.compare(g->nodes[i].lemma) == 0)
			tf++;
	}
	int wcount = g->conceptCount;
		for(int i=0; i< g->conceptCount; i++){
			for(int j=i+1; j<g->conceptCount; j++)
			if(g->nodes[i].lemma.compare(g->nodes[j].lemma) == 0)
				{wcount--; break; }
		}
		cout<<word<<"=-=-=-=-=-=-= "<<tf/wcount*idf<<endl;
	return /*tf/wcount**/idf/totalIdf;
}
