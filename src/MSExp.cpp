/*
 * MSExp.cpp
 *
 *  Created on: Jul 17, 2018
 *      Author: mamfarouk
 */
#include "Util.h"
//#include "WordModel.h"
#include "SemanticSimilarity.h"
#include <sstream>

#include "wn/wn.h"

#include "sentence_similarity.h"
#include "wordnet_extended.h"

typedef WordnetExtended we;

using namespace boost;

Util ut;
void prepareDataSet(char* fileName) {
	FILE *f;
	f = fopen("/research/NLP/MSRParaphraseCorpus/msr_paraphrase_test.txt","rb");
	if (f == NULL) {
		printf("Input file not found\n");
		return;
	}
	cout << ut.getLine(f) << endl;
	char* line;
	//cout << label << " " << st1 << "  **  " << st2 << endl;
	//WordModelwm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin");
	//SemanticSimilarity ss(&wm);
	//cout << ss.getWordOrderSim(st1, st2) << "  " << ss.getSentenceSim(st1, st2);

	FILE *fout, *fout2, *fout3;
	fout = fopen("/research/NLP/paper2/exp/dataset_testWN4", "a");
	if (fout == NULL) {
		printf("output file not found\n");
		return;
	}

	fout2 = fopen("/research/NLP/paper2/exp/dataset_testWN5", "a");
	if (fout2 == NULL) {
		printf("output file not found\n");
		return;
	}
	fout3 = fopen("/research/NLP/paper2/exp/dataset_testWN6", "a");
	if (fout3 == NULL) {
		printf("output file not found\n");
		return;
	}
	we we("/Programs/WordNet-3.0/dict/",
							"/research/NLP/tools/semantic-similarity-master/dicts/freq.txt");

			ostringstream ostr, ostr2, ostr3;
			double v1, v2, v3, v4 ,v5, v6, v7, v8;
			WordModel wm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin", 1);
			SemanticSimilarity ss(&wm);
	//loop
	for (int i = 0; i < 4200; i++) {
		//cout<<"testh h h h h h"<<endl;
		ostr.str("");
		ostr2.str("");
		ostr3.str("");
		cout<<i<<"    ";
		line = ut.getLine(f);
		cout<<strlen(line)<<endl;
		if (strlen(line) < 2)
			break;
		if(i<1051)
			continue;
		//cout << line << endl;
		string* sts = ut.split(line, 9, 70);
		string label = sts[0];
		char* st1 = new char[sts[3].length()];
		strcpy(st1, sts[3].c_str());
		char* st2 = new char[sts[4].length()];
		strcpy(st2, sts[4].c_str());

		Sentence s1(st1);
		s1.initVectors(wm);
		Sentence s2(st2);
		s2.initVectors(wm);
		//cout << "test" << endl;
		v1 = ss.getWordOrderSim(st1, st2);
		//cout << v1 << endl;
		we::UndirectedGraph g;
		SentenceSimilarityLi2006 ssWN(we);
		v2 = ssWN.compute_similarity(st1, st2, g);
		//cout << v2 << endl;
		v3 = ss.getSentenceSim_Mean(s1, s2);
		//cout << v3 << endl;
		v4 = ss.getSentenceSim_WordToSentMaxWN_WE(s1, s2);
		//cout << v4 << endl;
		//v5 = ss.getSentenceSim_WordToSentMax(s1, s2);
		//cout << v5 << endl;
		//v6 = ss.getSentenceSim_CommonWords(s1, s2, 0.47);
		//v7 = ss.getSentenceSim_CommonWords(s1, s2, 0.45);
		/*ss.getSentenceSim_Mean_POS(s1, s2);
		 cout<<v6<<endl;
		 v7 = ss.getSentenceSim_WordToSentMax_Tok(s1, s2);
		 cout<<v7<<endl;
		 v8 =
		 cout<<v8<<endl;
		 */
cout<<label<<endl<<ostr.str();
cout<<v3;
		ostr << label << " 1:" << v1 << " 2:" << v4;// << " 3:" << v1 << " 4:"<< v2 << " 5:" << v6 << " 6:" << v4/*<<" 7:"<<v7<<" 8:"<<v8*/;
		ostr2 << label << " 1:" << v1 << " 2:" << v3 << " 3:" << v2 << " 4:"<< v4;// << " 5:" << v6 << " 6:" << v1/*<<" 7:"<<v7<<" 8:"<<v8*/;
		ostr3 << label << " 1:" << v1 << " 2:" << v3 << " 3:" << v1 << " 4:"<< v4;// << " 5:" << v5 << " 6:" << v6/*<<" 7:"<<v7<<" 8:"<<v8*/;
		//cout<<label<<" 1:"<<v1<<" ;; "<<endl;
		char* strLine;
		//			strcpy(strLine,label.c_str());
		//			strcat(strLine, " 1:");
		//		strcat(strLine,v1);
		cout << i<<endl;//ostr.str();
		cout<<ostr2.str().c_str()<<endl;
		ut.writeLine(fout, ostr.str().c_str());
		ut.writeLine(fout2, ostr2.str().c_str());
		ut.writeLine(fout3, ostr3.str().c_str());
		//cout<<ostr3.str().c_str()<<endl;
		//ut.writeToFie(fout, strLine);
	}
}
void unsupervised() {
	int countAll =0;
	int tp=0, tn=0, fp=0, fn=0, tp2=0, tn2=0, fp2=0, fn2=0;
	double pre, recall, f1, acc;
	FILE *f;
	f = fopen("/research/NLP/MSRParaphraseCorpus/msr_paraphrase_test.txt","rb");
	if (f == NULL) {
		printf("Input file not found\n");
		return;
	}
	cout << ut.getLine(f) << endl;
	char* line;
	//cout << label << " " << st1 << "  **  " << st2 << endl;
	we we("/Programs/WordNet-3.0/dict/",
							"/research/NLP/tools/semantic-similarity-master/dicts/freq.txt");

			double m1, m2, v1, v2, v3, v4 ,v5, v6, v7, v8;
			WordModel wm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin", 1);
			SemanticSimilarity ss(&wm);
			int temp;
	//loop
	for (int i = 0; i < 4200; i++) {
		//cout<<"testh h h h h h"<<endl;
		//cout<<i<<"    ";
		line = ut.getLine(f);
		//cout<<strlen(line)<<endl;
		if (strlen(line) < 2)
			break;
		//if(i<=1395)
			//continue;
		//cout << line << endl;
		string* sts = ut.split(line, 9, 70);
		string label = sts[0];
		char* st1 = new char[sts[3].length()];
		strcpy(st1, sts[3].c_str());
		char* st2 = new char[sts[4].length()];
		strcpy(st2, sts[4].c_str());

		Sentence s1(st1);
		s1.initVectors(wm);
		Sentence s2(st2);
		s2.initVectors(wm);
		//cout << "test" << endl;
		v1 = ss.getWordOrderSim(st1, st2);
		//cout << v1 << endl;
		we::UndirectedGraph g;
		SentenceSimilarityLi2006 ssWN(we);
		v2 = ssWN.compute_similarity(st1, st2, g);
		//cout << v2 << endl;
		v3 = ss.getSentenceSim_Mean(s1, s2);
		//cout << v3 << endl;
		//v4 = ss.getSentenceSim_WordToSentMaxWN_WE(s1, s2);

		//m1 = (v2);
		//m2 = v3;
		m1 = (v2+v1+v3+v1)/4.0;
		m2 = (v2+v1+v3)/3.0;
		int lab = atoi(label.c_str());
		cout<<lab<<", "<<m2<<", "<<m1<<", "<<i<<", "<<st1<<endl;
		//if(i%300 == 0)
			//cin>>temp;
		countAll++;
		if(m1>=0.55){
			if(lab == 1)
				tp++;
			else
				fp++;
		}
		else{if(lab == 0)
			tn++;
		else
			fn++;
		}
		if (m2 >= 0.55) {
			if (lab == 1)
				tp2++;
			else
				fp2++;
		} else {
			if (lab == 0)
				tn2++;
			else
				fn2++;
		}

		//char* strLine;
		acc= (float)(tp+tn)/countAll;
		pre = (float)tp/(tp+fp);
		recall = (float)tp/(tp+fn);
		f1 = 2*(recall*pre)/(recall+pre);
//		cout << i<<endl;//ostr.str();
//		cout<<acc<<"  precision "<<pre<<"  recall "<<recall<<"  F1 "<<f1<<"   "<<endl;
//		cout<<tp<<"   "<<tn<<"   "<<fp<<"   "<<fn<<"   "<<endl;
		acc= (float)(tp2+tn2)/countAll;
				pre = (float)tp2/(tp2+fp2);
				recall = (float)tp2/(tp2+fn2);
				f1 = 2*(recall*pre)/(recall+pre);
//				cout<<tp2<<"   "<<tn2<<"   "<<fp2<<"   "<<fn2<<"   "<<endl;
//				cout<<acc<<"  precision2 "<<pre<<"  recall "<<recall<<"  F1 "<<f1<<"   "<<endl;

	}
}

void UsingWordNet(){
	FILE *f;
	f = fopen("/research/NLP/MSRParaphraseCorpus/msr_paraphrase_test.txt",
			"rb");
	if (f == NULL) {
		printf("Input file not found\n");
		return;
	}
	cout << ut.getLine(f) << endl;
	char* line;

	FILE *fout;
	fout = fopen("/research/NLP/paper2/exp/dataset_testingWN", "wb");
	if (fout == NULL) {
		printf("output file not found\n");
		return;
	}

	we we("/Programs/WordNet-3.0/dict/",
						"/research/NLP/tools/semantic-similarity-master/dicts/freq.txt");

	ostringstream ostr;
	double v1, v2, v3, v4, v5, v6, v7, v8;

	//loop
	for (int i = 0; i < 4100; i++) {
		//cout<<"testh h h h h h"<<endl;
		ostr.str("");
		cout << i << "    ";
		line = ut.getLine(f);
		cout << strlen(line) << endl;
		if (strlen(line) < 2)
			break;
		if(i<1430)
		continue;
		//cout << line << endl;
		string* sts = ut.split(line, 9, 70);
		string label = sts[0];
		char* st1 = new char[sts[3].length()];
		strcpy(st1, sts[3].c_str());
		char* st2 = new char[sts[4].length()];
		strcpy(st2, sts[4].c_str());
		//cout<< ss.compute_similarity("Duque will return to Earth Oct. 27 with the station's current crew, U.S. astronaut Ed Lu and Russian cosmonaut Yuri Malenchenko."
		//			, "Currently living onboard the space station are American astronaut Ed Lu and Russian cosmonaut Yuri Malenchenko.", g); //0.561
		we::UndirectedGraph g;
		SentenceSimilarityLi2006 ss(we);

		//cout<<st1<<"++++"<<endl;
		//cout<<st2<<"______"<<endl;
		v1 = ss.compute_similarity(st1, st2, g); //0.561

		cout << v1 << endl;

		ostr << label << " 1:" << v1 ;//<< " 2:" << v3 << " 3:" << v1 << " 4:"<< v2 << " 5:" << v6 << " 6:" << v4;
		cout << ostr.str().c_str() << endl;
		ut.writeLine(fout, ostr.str().c_str());

	}
}


int main14(){
	//char* str;
	unsupervised();
	//prepareDataSet("dffd");
	//prepareMSDataset();
	//UsingWordNet();
}
