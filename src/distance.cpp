//  Copyright 2013 Google Inc. All Rights Reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.


//
//#include <stdio.h>
//#include <string.h>
//#include <math.h>
//#include <malloc.h>
//#include <iostream>
////#include "Sentence.h"
//#include "SemanticSimilarity.h"
//const static long long max_size = 2000;         // max length of strings
//const static long long N = 40;                  // number of closest words that will be shown
//const static long long max_w = 50;              // max length of vocabulary entries
//
//double getSentSim(char* s1, char* s2) {
//	int i = 0;
//	int b = 0;
//	int s1Len = 0;
//	char s1w[50][30];
//	while (1) {
//		if (s1[i] == 0)
//			break;
//		if (s1[i] == ' ') {
//			s1w[s1Len][b] = 0;
//			s1Len++;
//			b = 0;
//		} else
//			s1w[s1Len][b++] = s1[i];
//		i++;
//	}
//	s1w[s1Len][b] = 0;
//	s1Len++;
//
//	i = 0;
//	b = 0;
//	int s2Len = 0;
//	char s2w[50][30];
//	while (1) {
//		if (s2[i] == 0)
//			break;
//		if (s2[i] == ' ') {
//			s2w[s2Len][b] = 0;
//			s2Len++;
//			b = 0;
//		} else
//			s2w[s2Len][b++] = s2[i];
//		i++;
//	}
//	s2w[s2Len][b] = 0;
//	s2Len++;
//		return 0.87;
//}
//float* getVector(char* word, int size, float *M, char *vocab, int words){
//	float *vec = new float[size];
//	int a;
//	for (a = 0; a < size; a++) {
//		vec[a] =0;
//	}
//		int b;
//		for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], word)) break;
//		if (b == words)
//		{
//			printf("Out of dictionary word!\n");
//			return vec;
//		}
//		else
//			{
//			double test =0;
//			printf("\nWord: %s  Position in vocabulary: %lld\n", word, b);
//			for (a = 0; a < size; a++) {
//				vec[a] += M[a + b * size];
//				test += M[a + b * size];
//			}
//			}
//		return vec;
//}
//double getSim(char* w1, char* w2, char *vocab, long words, float *M, int size){
//	//printf("first word is %s", w1);
//	int p1, p2;
//	int b;
//	for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], w1)) break;
//	if (b == words)
//	{
//		printf("Out of dictionary word!\n");
//		return 0.0;
//	}
//	else
//		{
//		//printf("\nWord: %s  Position in vocabulary: %lld\n", w1, b);
//		p1 = b;
//		}
//
//	for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], w2)) break;
//	if (b == words)
//	{
//		printf("Out of dictionary word!\n");
//		return 0.0;
//	}
//	else
//		{
//		//printf("\nWord: %s  Position in vocabulary: %lld\n", w2, b);
//		p2 = b;
//		}
//
//	double dist = 0;
//	int a;
//    for ( a = 0; a < size; a++)
//    	{dist += M[a + p1 * size] * M[a + p2 * size];
//    	//printf("test  @ %i %f ",a + p1 * size, M[a + p1 * size]);
//    	}
//
//	return dist;
//}
//
//double getSim2(char* w1, char* w2, char *vocab, long words, float *M, int size){
//	float* vec1 = getVector(w1, size, M, vocab, words);
//
//	float* vec2 = getVector(w2, size, M, vocab, words);
//	double dist = 0;
//	int a;
//    for ( a = 0; a < size; a++)
//    	{
//    	dist += vec1[a] * vec2[a];
//    	//printf("vect1  @ %i %f ",a, vec1[a]);
//    	}
//
//	return dist;
//}
//Sentence getSentence(char* str,  char *vocab, long words, float *M, int size){
//	Sentence s(str);
//	for(int i=0; i<s.wordCount; i++){
//		s.words[i].vector = getVector(s.words[i].w,size, M, vocab, words);
//	}
//	return s;
//}
//int main2(int argc, char **argv) {
////	Sentence s1 = getSentence("this is a test sentence", size, M, vocab, words);
////	cout<<s1.wordCount;
////	Sentence s2("test sent first good kj");// = new Sentence();
//	//s2.splite();
////		cout<<s2.wordCount;
//	WordModel wm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin");
//	SemanticSimilarity ss(&wm);
//	ss.getSentenceSim("a gem is a jewel or stone that is used in jewellery",
//			"a jewel is a precious stone used to decorate valuable things that you wear, such as rings or necklaces");
//	//cout<<wm.words;
//	return 0;
//  FILE *f;
//  char st1[max_size];
//  char *bestw[N];
//  char file_name[max_size], st[100][max_size];
//  float dist, len, bestd[N], vec[max_size];
//  long long words, size, a, b, c, d, cn, bi[100];
//  char ch;
//  float *M;
//  char *vocab;
// /* if (argc < 2) {
//    printf("Usage: ./distance <FILE>\nwhere FILE contains word projections in the BINARY FORMAT\n");
//    return 0;
//  }*/
//  strcpy(file_name, "/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin");
//  f = fopen(file_name, "rb");
//  if (f == NULL) {
//    printf("Input file not found\n");
//    return -1;
//  }
//  fscanf(f, "%lld", &words);
//  fscanf(f, "%lld", &size);
//  printf("test %lld   %i", words, size);
//  words = 1000;
//  vocab = new char[words * max_w];//(char *)malloc((long long)words * max_w * sizeof(char));
//  for (a = 0; a < N; a++) bestw[a] = new char[max_size];//(char *)malloc(max_size * sizeof(char));
//  M = new float[words * (long long)size ];//(float *)malloc((long long)words * (long long)size * sizeof(float));
//  if (M == NULL) {
//    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
//    return -1;
//  }
//  for (b = 0; b < words; b++) {
//    a = 0;
//    while (1) {
//      vocab[b * max_w + a] = fgetc(f);
//      if (feof(f) || (vocab[b * max_w + a] == ' ')) break;
//      if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
//    }
//    vocab[b * max_w + a] = 0;
//    for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
//    len = 0;
//    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
//    len = sqrt(len);
//    for (a = 0; a < size; a++) M[a + b * size] /= len;
//  }
//
//	// test new function
//
//  /*cout<<endl<<ss.getWordSimLowerUpper("gem", "jewel")<<"    \t"<<getSim("gem", "jewel",vocab, words, M, size);
//  	cout<<endl<<ss.getWordSimLowerUpper("gem", "jewekjil")<<"    \t"<<getSim("gem", "jewekjil",vocab, words, M, size);
//  	cout<<endl<<ss.getWordSimLowerUpper("automobile", "car")<<"    \t"<<getSim("automobile", "car",vocab, words, M, size);
//  	cout<<endl<<ss.getWordSimLowerUpper("lad", "boy")<<"    \t"<<getSim("lad", "boy",vocab, words, M, size);
//  	cout<<endl<<ss.getWordSimLowerUpper("brother", "monk")<<"    \t"<<getSim("brother", "monk",vocab, words, M, size);
//  	cout<<endl<<ss.getWordSim("glass", "jewel")<<"    \t"<<getSim("glass", "jewel",vocab, words, M, size);
//  	*/
//  cout<<endl<<"start";
//  cout<<endl<<ss.getWordSimLowerUpper("smile" , "cord");
//  cout<<endl<<ss.getWordSimLowerUpper("string" , "noon");
//  cout<<endl<<ss.getWordSimLowerUpper("voyage" , "rooster");
//  cout<<endl<<ss.getWordSimLowerUpper("furnace" , "fruit");
//  cout<<endl<<ss.getWordSimLowerUpper("shore" , "autograph");
//  cout<<endl<<ss.getWordSimLowerUpper("wizard" , "automobile");
//  cout<<endl<<ss.getWordSimLowerUpper("stove" , "mound");
//  cout<<endl<<ss.getWordSimLowerUpper("implement" , "grin");
//  cout<<endl<<ss.getWordSimLowerUpper("fruit" , "asylum");
//  cout<<endl<<ss.getWordSimLowerUpper("monk" , "asylum");
//  cout<<endl<<ss.getWordSimLowerUpper("Madhouse" , "graveyard");
//  cout<<endl<<ss.getWordSimLowerUpper("rooster" , "boy");
//  cout<<endl<<ss.getWordSimLowerUpper("magician" , "glass");
//  cout<<endl<<ss.getWordSimLowerUpper("jewel" , "cushion");
//  cout<<endl<<ss.getWordSimLowerUpper("slave" , "monk");
//  cout<<endl<<ss.getWordSimLowerUpper("cemetery" , "asylum");
//  cout<<endl<<ss.getWordSimLowerUpper("forest" , "coast");
//  cout<<endl<<ss.getWordSimLowerUpper("lad" , "grin");
//  cout<<endl<<ss.getWordSimLowerUpper("woodland" , "shore");
//  cout<<endl<<ss.getWordSimLowerUpper("oracle" , "monk");
//  cout<<endl<<ss.getWordSimLowerUpper("sage" , "boy");
//  cout<<endl<<ss.getWordSimLowerUpper("cushion" , "automobile");
//  cout<<endl<<ss.getWordSimLowerUpper("shore" , "mound");
//  cout<<endl<<ss.getWordSimLowerUpper("wizard" , "lad");
//  cout<<endl<<ss.getWordSimLowerUpper("graveyard" , "forest");
//  cout<<endl<<ss.getWordSimLowerUpper("rooster" , "food");
//  cout<<endl<<ss.getWordSimLowerUpper("woodland" , "cemetery");
//  cout<<endl<<ss.getWordSimLowerUpper("voyage" , "shore");
//  cout<<endl<<ss.getWordSimLowerUpper("woodland" , "bird");
//  cout<<endl<<ss.getWordSimLowerUpper("hill" , "coast");
//  cout<<endl<<ss.getWordSimLowerUpper("implement" , "furnace");
//  cout<<endl<<ss.getWordSimLowerUpper("rooster" , "crane");
//  cout<<endl<<ss.getWordSimLowerUpper("woodland" , "hill");
//  cout<<endl<<ss.getWordSimLowerUpper("journey" , "car");
//  cout<<endl<<ss.getWordSimLowerUpper("mound" , "cemetery");
//  cout<<endl<<ss.getWordSimLowerUpper("jewel" , "glass");
//  cout<<endl<<ss.getWordSimLowerUpper("oracle" , "magician");
//  cout<<endl<<ss.getWordSimLowerUpper("implement" , "crane");
//  cout<<endl<<ss.getWordSimLowerUpper("lad" , "brother");
//  cout<<endl<<ss.getWordSimLowerUpper("wizard" , "sage");
//  cout<<endl<<ss.getWordSimLowerUpper("sage" , "oracle");
//  cout<<endl<<ss.getWordSimLowerUpper("cock" , "bird");
//  cout<<endl<<ss.getWordSimLowerUpper("crane" , "bird");
//  cout<<endl<<ss.getWordSimLowerUpper("fruit" , "food");
//  cout<<endl<<ss.getWordSimLowerUpper("monk" , "brother");
//  cout<<endl<<ss.getWordSimLowerUpper("madhouse" , "asylum");
//  cout<<endl<<ss.getWordSimLowerUpper("stove" , "furnace");
//  cout<<endl<<ss.getWordSimLowerUpper("wizard" , "magician");
//  cout<<endl<<ss.getWordSimLowerUpper("mound" , "hill");
//  cout<<endl<<ss.getWordSimLowerUpper("string" , "cord");
//  cout<<endl<<ss.getWordSimLowerUpper("tumbler" , "glass");
//  cout<<endl<<ss.getWordSimLowerUpper("smile" , "grin");
//  cout<<endl<<ss.getWordSimLowerUpper("slave" , "serf");
//  cout<<endl<<ss.getWordSimLowerUpper("voyage" , "journey");
//  cout<<endl<<ss.getWordSimLowerUpper("signature" , "autograph");
//  cout<<endl<<ss.getWordSimLowerUpper("shore" , "coast");
//  cout<<endl<<ss.getWordSimLowerUpper("woodland" , "forest");
//  cout<<endl<<ss.getWordSimLowerUpper("tool" , "implement");
//  cout<<endl<<ss.getWordSimLowerUpper("rooster" , "cock");
//  cout<<endl<<ss.getWordSimLowerUpper("lad" , "boy");
//  cout<<endl<<ss.getWordSimLowerUpper("pillow" , "cushion");
//  cout<<endl<<ss.getWordSimLowerUpper("graveyard" , "cemetery");
//  cout<<endl<<ss.getWordSimLowerUpper("car" , "automobile");
//  cout<<endl<<ss.getWordSimLowerUpper("jewel" , "gem");
//  cout<<endl<<ss.getWordSimLowerUpper("noon" , "midday");
//
//  	return 0;
//	double s = getSim("height", "size", vocab, words, M, size);
//	printf("\ntest sim is %f\n\n", s);
//
//	s = getSim2("height", "size", vocab, words, M, size);
//		printf("\ntest sim2 is %f", s);
//
//		Sentence s1 = getSentence("this is a test sentence", vocab, words, M, size);
//for(int i=0; i<s1.wordCount; i++){
//	for(int j=0; j<size; j++)
//	cout<<" @"<<i<<"  "<<s1.words[i].vector[j]<<"  ";
//	cout<<endl;
//}
//float* mvec = s1.getMeanVector();
//for(int j=0; j<size; j++)
//	cout<<" @"<<mvec[j]<<"  ";
//	return 0;
//	// end test new functions
//
//  fclose(f);
//  while (1) {
//    for (a = 0; a < N; a++) bestd[a] = 0;
//    for (a = 0; a < N; a++) bestw[a][0] = 0;
//    printf("Enter word or sentence (EXIT to break): ");
//    a = 0;
//    while (1) {
//      st1[a] = fgetc(stdin);
//      if ((st1[a] == '\n') || (a >= max_size - 1)) {
//        st1[a] = 0;
//        break;
//      }
//      a++;
//    }
//    if (!strcmp(st1, "EXIT")) break;
//    cn = 0;
//    b = 0;
//    c = 0;
//    while (1) {
//      st[cn][b] = st1[c];
//      b++;
//      c++;
//      st[cn][b] = 0;
//      if (st1[c] == 0) break;
//      if (st1[c] == ' ') {
//        cn++;
//        b = 0;
//        c++;
//      }
//    }
//    cn++;
//    for (a = 0; a < cn; a++) {
//      for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
//      if (b == words) b = -1;
//      bi[a] = b;
//      printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
//      if (b == -1) {
//        printf("Out of dictionary word!\n");
//        break;
//      }
//    }
//    if (b == -1) continue;
//    printf("\n                                              Word       Cosine distance\n------------------------------------------------------------------------\n");
//    for (a = 0; a < size; a++) vec[a] = 0;
//    for (b = 0; b < cn; b++) {
//      if (bi[b] == -1) continue;
//      for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];
//    }
//    len = 0;
//    for (a = 0; a < size; a++) len += vec[a] * vec[a];
//    len = sqrt(len);
//    for (a = 0; a < size; a++) vec[a] /= len;
//    for (a = 0; a < N; a++) bestd[a] = -1;
//    for (a = 0; a < N; a++) bestw[a][0] = 0;
//    for (c = 0; c < words; c++) {
//      a = 0;
//      for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
//      if (a == 1) continue;
//      dist = 0;
//      for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
//      for (a = 0; a < N; a++) {
//        if (dist > bestd[a]) {
//          for (d = N - 1; d > a; d--) {
//            bestd[d] = bestd[d - 1];
//            strcpy(bestw[d], bestw[d - 1]);
//          }
//          bestd[a] = dist;
//          strcpy(bestw[a], &vocab[c * max_w]);
//          break;
//        }
//      }
//    }
//    for (a = 0; a < N; a++) printf("%50s\t\t%f\n", bestw[a], bestd[a]);
//  }
//  return 0;
//}
