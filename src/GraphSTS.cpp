/*
 * GraphSTS.cpp
 *
 *  Created on: Sep 3, 2019
 *      Author: mamfarouk
 */

#include<iostream>
#include<regex>
#include<string>
#include<iomanip>
#include<Util.h>
#include<GraphSTS.h>
#include<SemanticSimilarity.h>


//#include<WordModel.h>
using namespace std;
//WordnetExtended wenn("/Programs/WordNet-3.0/dict/","/research/NLP/tools/semantic-similarity-master/dicts/freq.txt");
//	WordnetExtended::UndirectedGraph gg;
//	SentenceSimilarityLi2006 ssWn(wenn);

//WordModel wm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin");
//SemanticSimilarity ss(&wm);


GraphSTS::GraphSTS(char* sentence):Graph(sentence){

}
double GraphSTS::matchGraph(Graph g) {

	double matrix[edgeCount][g.edgeCount];

if(debug)	cout<<"     "<<setw(12)<<"  ";
	for (int j = 0; j < g.edgeCount && debug; j++)
		if(debug)cout<<setw(12)<<g.edges[j].name<<"     ";
if(debug)	cout<<endl;

	for (int i = 0; i < edgeCount; i++) {
		if(debug)		cout<<setw(12)<<edges[i].name<<"    ";
		for (int j = 0; j < g.edgeCount; j++) {
			matrix[i][j] = matchRelation(this, edges[i], &g, g.edges[j]);
			if(debug)			cout<<setw(12)<<matrix[i][j] <<"     ";
		}
		if(debug)		cout<<endl;
	}

	double sum =0;
	double max;
	int nanCount =0;
	string rel;
	double weightSum =0;
	double w =0;
	for(int i=0; i< edgeCount; i++){
		max =0;
		for (int j = 0; j < g.edgeCount; j++) {
			if(matrix[i][j] > max)
				{
				max = matrix[i][j];
				rel = g.edges[j].name;
			}
		}
		if(max ==0) nanCount++;//cout<<max<<"   "<<i<<endl;

			w = getWeight(rel);
			sum  += max*w;
			weightSum +=w;

	}
//	cout<<nanCount<<endl;
	double d1;
	if(g.edgeCount-nanCount == 0)
		d1 = 0;
	else
		d1 = sum / weightSum;
	 //d1 = sum / (edgeCount-nanCount);
	sum = 0;
	weightSum=0;
	nanCount =0;
	for (int j = 0; j < g.edgeCount; j++) {
		max = 0;
		for (int i = 0; i < edgeCount; i++) {
			if (matrix[i][j] > max)
			{
				max = matrix[i][j];
				rel = edges[i].name;
			}
		}
		if(max == 0)
			nanCount++;
		//sum += max;
		w = getWeight(rel);
		sum += max * w;
		weightSum += w;
	}
//	cout<<nanCount<<endl;
	if(g.edgeCount-nanCount == 0)
		return 0;
	double d2 = sum/ weightSum;// /(g.edgeCount-nanCount);
	cout<<endl<<"dddd"<< d1<<"   "<<d2<<"   "<<(d1+d2)/2<<endl;
//	if(edgeCount < g.edgeCount)
//		return d1;
//	else
//		return d2;
	return (d1+d2)/2;
}


int odds =0;
//computing similarity based on graph for STS dataset
int graph_STS(){
	Util utility;
	int tt = 0;
	cout << "sts Graph " << endl;
	FILE *fres;
	fres = fopen("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.gs.images.txt", "rb");
		if (fres == NULL) {
			printf("output file not found\n");
			return 0;
		}
		FILE *fresult;
		fresult = fopen("/research/NLP/sts datasets/2015/WTWRes_SL999/STS.rs.images3Test.txt", "w");
				if (fresult == NULL) {
					printf("output file not found\n");
					return 0;
				}
		string resLine;
/*		FILE *fOldres;
		fOldres = fopen("/research/NLP/sts datasets/2012/test-gold/STS.input.MSRvid_Result.txt", "rb");
		if (fOldres == NULL) {
			printf("output file not found 2\n");
			return 0;
		}
*/	FILE *fout;
	fout = fopen("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.input.images.txt-graph2.txt", "rb");
	if (fout == NULL) {
		printf("output file not found 3\n");
		return 0;
	}

	string line;

	regex conceptReg("c[[:digit:]]+:(.+?):.+instance (.+?) ");
	regex argReg("c[[:digit:]]+:(.+?):.+arg (.+?) ");
	regex inRelReg("(.*?):(.*?):.* int (.*?) ");
	regex exRelReg("(.*?):(.*?):.* ext (.*?) ");
	regex inEqRelReg("(.*?):equality int (.*?) ");
	regex exEqRelReg("(.*?):equality ext (.*?) ");
	regex isReg(".* (.*?):equality [[:digit:]]+ . is ");
	regex refReg(".+referent (.+?) .* (.+?) ");
	float prop[2000];
	float origin[2000];
	for (int i = 0; i+odds < 1500; i++) {
		cout<<utility.getStringLine(fout);
		line = utility.getStringLine(fout);
		//cout<<i<<endl;
		cout<<line<<endl;
		GraphSTS g1((char*) line.c_str());
		//cout << line << endl;
		line[0] = '\0';
		smatch match;
		while (line[0] != '!') {
			line = utility.getStringLine(fout);
			cout<<line<<endl;
			//if(i<tt)
			//continue;
			if(line[0] == '%')
			{}
			else
			if (regex_search(line, match, conceptReg)) {
				g1.addConcept(match.str(1), match.str(2), "");
			} else if (regex_search(line, match, argReg)) {
				g1.addConcept(match.str(1), match.str(2), "jj");
			} else if (regex_search(line, match, inRelReg)) {

				g1.addRelationIn(match.str(2), match.str(1), match.str(3));
			} else if (regex_search(line, match, exRelReg)) {

				g1.addRelationEx(match.str(2), match.str(1), match.str(3));
			} else if (regex_search(line, match, inEqRelReg)) {

				g1.addRelationIn("equality", match.str(1), match.str(2));
			} else if (regex_search(line, match, exEqRelReg)) {
				//cout<<endl<<match.str(1)<<endl;
				g1.addRelationEx("equality", match.str(1), match.str(2));
			}else if(regex_search(line, match, isReg)){
				//cout<<endl<<match.str(1)<<"    is relation"<<endl;
				g1.addIsRelation("is", match.str(1));
			} else if (regex_search(line, match, refReg)) {
				//cout<<"Referent "<<endl;
				string temp = match.str(2);
				if( temp.length() > 3)
				g1.addConcept(match.str(2), match.str(1), "ref");
			}


			//cout << line << endl;
		}
		//cout<<"test "<<endl;
		//g1.printNodes();
		//g1.printEdges();
		//cout << endl;

		g1.checkGraph();
		//continue;
		line = utility.getStringLine(fout);
		cout<<line<<endl;
		GraphSTS g2((char*) line.c_str());
		//cout << line << endl;

		line[0] = '\0';
		while (line[0] != '!') {
			line = utility.getStringLine(fout);
			//if(i<tt)
			//			continue;
			if (regex_search(line, match, conceptReg)) {
				//cout<<match.str(1)<<"    "<< match.str(2)<<endl;
				g2.addConcept(match.str(1), match.str(2), "");
			} else if (regex_search(line, match, argReg)) {
				g2.addConcept(match.str(1), match.str(2), "jj");
			} else if (regex_search(line, match, inRelReg)) {

				g2.addRelationIn(match.str(2), match.str(1), match.str(3));
			} else if (regex_search(line, match, exRelReg)) {

				g2.addRelationEx(match.str(2), match.str(1), match.str(3));
			} else if (regex_search(line, match, inEqRelReg)) {

				g2.addRelationIn("equality", match.str(1), match.str(2));
			} else if (regex_search(line, match, exEqRelReg)) {

				g2.addRelationEx("equality", match.str(1), match.str(2));
			}else if (regex_search(line, match, refReg)) {
				//cout<<"referent "<<match.str(2)<<"   "<< match.str(1)<<endl;
				string temp = match.str(2);
				if( temp.length() > 3)
				g2.addConcept(match.str(2), match.str(1), "ref");
			}else if(regex_search(line, match, isReg)){
				//cout<<endl<<match.str(1)<<"    is relation"<<endl;
				//cout<<g2.edges[g2.edgeCount-1].name<<"    "<<g2.edges[g2.edgeCount-1].code<<endl;
				g2.addIsRelation("is", match.str(1));
				//cout<<g2.edges[g2.edgeCount-1].name<<"    "<<g2.edges[g2.edgeCount-1].code<<endl;
		}

			//cout << line << endl;
		}
		g2.checkGraph();
		//resLine = utility.getStringLine(fOldres);
	//	if(i+odds>1500)
		{
			cout<<"**************************************"<<endl;
		//double old = stod(resLine);
		//printWordMatrix(g1, g2);
		prop[i] = g1.matchGraph(g2)*5; //*/(g1.matchGraph(g2)*0.65+old*0.35)*5;
		cout<<"+++++  "<<prop[i]<<endl;
		char* te = new char[8];
		sprintf(te, "%f", prop[i]);
		utility.writeLine(fresult, te);
		}
		line = utility.getLine(fres);
		origin[i] = atof(line.c_str());
		cout<<origin[i]<<endl;
//		line = utility.getLine(fout);
		if(g1.conceptCount <=1 || g2.conceptCount<=1)
			{odds++;cout<<i--;}
		cout<<"odds  :"<<odds<<"   i "<<i<<endl;
	//	if(i + odds >= 1500)
		//	break;

	}
	cout<<"GO  "<<odds<<endl;
	cout<<"result is  "<<utility.calcPearson(prop, origin, 1430)<<endl;

}
// this fuction converts graph to text 31/1/2022
int convertGraphToText(){
	Util utility;
	int tt = 0;
	cout << "sts Graph " << endl;
/*		FILE *fresult;
		fresult = fopen("/research/NLP/sts datasets/2015/WTWRes_SL999/STS.rs.images3Test.txt", "w");
				if (fresult == NULL) {
					printf("output file not found\n");
					return 0;
				}
*/		string resLine;
	FILE *fout;
	fout = fopen("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.input.images.txt-graph2.txt", "rb");
	if (fout == NULL) {
		printf("output file not found 3\n");
		return 0;
	}

	string line;

	regex conceptReg("c[[:digit:]]+:(.+?):.+instance (.+?) ");
	regex argReg("c[[:digit:]]+:(.+?):.+arg (.+?) ");
	regex inRelReg("(.*?):(.*?):.* int (.*?) ");
	regex exRelReg("(.*?):(.*?):.* ext (.*?) ");
	regex inEqRelReg("(.*?):equality int (.*?) ");
	regex exEqRelReg("(.*?):equality ext (.*?) ");
	regex isReg(".* (.*?):equality [[:digit:]]+ . is ");
	regex refReg(".+referent (.+?) .* (.+?) ");

	for (int i = 0; i+odds < 40; i++) {
		cout<<utility.getStringLine(fout);
		line = utility.getStringLine(fout);
		//cout<<i<<endl;
		cout<<line<<endl;
		GraphSTS g1((char*) line.c_str());
		//cout << line << endl;
		line[0] = '\0';
		smatch match;
		while (line[0] != '!') {
			line = utility.getStringLine(fout);
		//	cout<<line<<endl;
			if(line[0] == '%')
			{}
			else
			if (regex_search(line, match, conceptReg)) {
				g1.addConcept(match.str(1), match.str(2), "");
			} else if (regex_search(line, match, argReg)) {
				g1.addConcept(match.str(1), match.str(2), "jj");
			} else if (regex_search(line, match, inRelReg)) {

				g1.addRelationIn(match.str(2), match.str(1), match.str(3));
			} else if (regex_search(line, match, exRelReg)) {

				g1.addRelationEx(match.str(2), match.str(1), match.str(3));
			} else if (regex_search(line, match, inEqRelReg)) {

				g1.addRelationIn("equality", match.str(1), match.str(2));
			} else if (regex_search(line, match, exEqRelReg)) {
				//cout<<endl<<match.str(1)<<endl;
				g1.addRelationEx("equality", match.str(1), match.str(2));
			}else if(regex_search(line, match, isReg)){
				//cout<<endl<<match.str(1)<<"    is relation"<<endl;
				g1.addIsRelation("is", match.str(1));
			} else if (regex_search(line, match, refReg)) {
				//cout<<"Referent "<<endl;
				string temp = match.str(2);
				if( temp.length() > 3)
				g1.addConcept(match.str(2), match.str(1), "ref");
			}
		}
		cout << "  +++++++++ \n";
		for(int as = 0; as < g1.edgeCount; as++){
			cout<<g1.edges[as].name <<" ";
			cout<<g1.getNode(g1.edges[as].in).code<<":"<<g1.getNode(g1.edges[as].in).lemma;
			cout<<" "<<g1.getNode(g1.edges[as].ex).code<<":"<<g1.getNode(g1.edges[as].ex).lemma<<endl;

		}

		line = utility.getStringLine(fout);
		//cout<<line<<endl;
		GraphSTS g2((char*) line.c_str());
		cout << line << endl;

		line[0] = '\0';
		while (line[0] != '!') {
			line = utility.getStringLine(fout);
			//if(i<tt)
			//			continue;
			if (regex_search(line, match, conceptReg)) {
				//cout<<match.str(1)<<"    "<< match.str(2)<<endl;
				g2.addConcept(match.str(1), match.str(2), "");
			} else if (regex_search(line, match, argReg)) {
				g2.addConcept(match.str(1), match.str(2), "jj");
			} else if (regex_search(line, match, inRelReg)) {

				g2.addRelationIn(match.str(2), match.str(1), match.str(3));
			} else if (regex_search(line, match, exRelReg)) {

				g2.addRelationEx(match.str(2), match.str(1), match.str(3));
			} else if (regex_search(line, match, inEqRelReg)) {

				g2.addRelationIn("equality", match.str(1), match.str(2));
			} else if (regex_search(line, match, exEqRelReg)) {

				g2.addRelationEx("equality", match.str(1), match.str(2));
			}else if (regex_search(line, match, refReg)) {
				//cout<<"referent "<<match.str(2)<<"   "<< match.str(1)<<endl;
				string temp = match.str(2);
				if( temp.length() > 3)
				g2.addConcept(match.str(2), match.str(1), "ref");
			}else if(regex_search(line, match, isReg)){
				g2.addIsRelation("is", match.str(1));
				//cout<<g2.edges[g2.edgeCount-1].name<<"    "<<g2.edges[g2.edgeCount-1].code<<endl;
		}

			//cout << line << endl;
		}
//		g2.checkGraph();
		cout << "  +++++++++ \n";
				for(int as = 0; as < g2.edgeCount; as++){
					cout<<g2.edges[as].name <<" ";
					cout<<g2.getNode(g2.edges[as].in).code<<":"<<g2.getNode(g2.edges[as].in).lemma;
					cout<<" "<<g2.getNode(g2.edges[as].ex).code<<":"<<g2.getNode(g2.edges[as].ex).lemma<<endl;

				}
			//	break;
	}

}
int main() {
	//graph_STS();
	convertGraphToText();
	return 0;


}
