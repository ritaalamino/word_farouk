/*
 * SemanticSimilarity.h
 *
 *  Created on: Apr 22, 2018
 *      Author: mamfarouk
 */

#ifndef SEMANTICSIMILARITY_H_
#define SEMANTICSIMILARITY_H_
//#include "Parser.h"
#include "Sentence.h"

#include "wn/wn.h"

#include "sentence_similarity.h"
#include "wordnet_extended.h"
#include "fstream"
#include "Graph.h"
//typedef WordnetExtended we;
struct wordidf{
	char word[50];
	double idf;
};

using namespace boost;

class SemanticSimilarity{
	public:
	WordModel* model;
	wordidf* Allidf;
	int segma;
	SemanticSimilarity(WordModel*);
	wordidf* loadIDF(char* fileName, const int wordsNum, int docsNum);
	double getIdf(char* word, Sentence s);
	double getIdf(string word, Graph *g);
	double getMatch(word w1, word w2, SentenceSimilarityLi2006*);
	double getWordSim(char* w1, char* w2);
	double getWordSimLowerUpper(char* w1, char* w2);
	double getWordCosineSim(float* vec1, char* vec2);
	double getWordEuclideanSim(float* vec1, char* vec2);
	double getSentenceSim(char* s1, char* s2);
	double getSentenceSim_Mean(Sentence s1, Sentence s2);
	double getSentenceSim_Mean_POS(Sentence s1, Sentence s2);
	double getSentenceSim_MeanNew(Sentence s1, Sentence s2);
	double getSentenceSim_WordToSentMax(Sentence s1, Sentence s2);
	double getSentenceSim_MaxVector(Sentence s1, Sentence s2);
	double getSentenceSim_CommonWords(Sentence s1, Sentence s2, double th);
	double getMaxMatch(word w, Sentence s);
	double cosineSim(float* v1, float* v2);
	double ManhSim(float* v1, float* v2);
	double getSentenceSim_WordsToMean(Sentence s1, Sentence s2);
	double getSentenceSim_WordsToWords(Sentence s1, Sentence s2);
	double getWordOrderSim(Sentence s1, Sentence s2);
	double getMaxMatch_Tok(word w, Sentence s);
	double getSentenceSim_WordToSentMax_Tok(Sentence s1, Sentence s2);
	double getPOSWeight(char* t1, char* t2);
	double getMaxMatchWN_WE_Mix(word w, Sentence s);
	double getSentenceSim_WordToSentMaxWN_WE(Sentence s1, Sentence s2);

};


#endif /* SEMANTICSIMILARITY_H_ */
