/*
 * Graph.cpp
 *
 *  Created on: Oct 1, 2018
 *      Author: mamfarouk
 */
#include<iostream>
#include<regex>
#include<string>
#include<iomanip>
#include<Util.h>
#include<Graph.h>
#include<SemanticSimilarity.h>


//#include<WordModel.h>
using namespace std;
bool debug = false;
int autoInc =0;
int gLen =0;
WordnetExtended wenn("/Programs/WordNet-3.0/dict/","/research/NLP/tools/semantic-similarity-master/dicts/freq.txt");
	WordnetExtended::UndirectedGraph gg;
	SentenceSimilarityLi2006 ssWn(wenn);

//WordModel wm("/research/NLP/word embedding/GoogleNews-vectors-negative300.bin/GoogleNews-vectors-negative300.bin", 1);
	WordModel wm("/Users/mamfarouk/Downloads/paragram_300_sl999/paragram_300_sl999.txt",-1);
SemanticSimilarity ss(&wm);
string getCode(){
	stringstream ss;
	ss<<"ma"<<autoInc++;
	//cout<<ss.str()<<endl;
	return ss.str();
}

double  Graph::getWeight(string relation){
	if(relation.compare("equality") == 0)
		return 1;
	else if(relation.compare("is") == 0)
		return 4;
	else if(relation.compare("rep") == 0)
		return 1;
	else if(relation.compare("for") == 0)
		return 1;
	else if(relation.compare("on") == 0)
		return 1;
	else if(relation.compare("of") == 0)
		return 1;
	else if(relation.compare("in") == 0)
			return 3;
	// modify  24-2-2019 for using structural only

	else if(relation.compare("experiencer") == 0)
		return 6;
	else if(relation.compare("agent") == 0)
		return 8;
	else if(relation.compare("theme") == 0)
		return 8;

	// end of modify
	else
		return 1;
}

Graph::Graph(char* str) {
	string* words = utility.split(str, ' ', 60);
	int count = 0;
//	bool test = false;
//	if(strcmp(str, "The increase reflects lower credit losses and favorable interest rates.") == 0)
//		test = true;
	if(debug) cout<<str<<endl;
	while (words[count].length() > 0) {
	//	cout<<words[count]<<endl;
		count++;
	}
	gLen = count;
//	cout<<str<<"    num of words is "<<count<<endl;
	nodes = new concept[count * 2];
	edges = new relation[count * 2];
}
void Graph::addConcept(string name, string code, string pos) {
	//nodes[conceptCount] = new concept;
	//cout<<conceptCount<<endl;
	for(int i=0; i< conceptCount; i++){
		if(nodes[i].code == code){
			string nCode = getCode();
			//cout<<nCode<<endl;
			addConcept(name, nCode, pos);
			string rName = getCode();
			//cout<<rName<<endl;
			addRelationIn("equality", rName, code);
			addRelationEx("equality", rName, nCode);
			return;
		}
	}
	nodes[conceptCount].lemma = name;
	nodes[conceptCount].code = code;
	nodes[conceptCount].pos = pos;
	conceptCount++;

}
void Graph::addRelationIn(string name, string code, string in) {
	bool found = false;
	int i;
	//cout<<"code is "<<code<<endl;
	for (i = 0; i < edgeCount; i++) {//cout<<edges[i].code<<endl;
		if (edges[i].code.compare(code) == 0) {
			found = true;
			break;

		}
	}
	if (found)
		edges[i].in = in;
	else {
		edges[edgeCount].code = code;
		edges[edgeCount].name = name;
		edges[edgeCount].in = in;
		edgeCount++;
	}
}
void Graph::addRelationEx(string name, string code, string ex) {
	bool found = false;
	int i;
	//cout<<"code is "<<code<<endl;
	for (i = 0; i < edgeCount; i++) {//cout<<edges[i].code<<endl;
		if (edges[i].code.compare(code) == 0) {
			found = true;
			break;

		}
	}
	if (found)
		edges[i].ex = ex;
	else {
		edges[edgeCount].code = code;
		edges[edgeCount].name = name;
		edges[edgeCount].ex = ex;
		edgeCount++;
	}
}
void Graph::addIsRelation(string name, string code) {
	bool found = false;
		int i;
		//cout<<"code is "<<code<<endl;
		for (i = 0; i < edgeCount; i++) {//cout<<edges[i].code<<endl;
			if (edges[i].code.compare(code) == 0) {
				edges[i].name = name;
				return;

			}
		}
//cout<<"*****\n**********\n*************\n********\n***********\n************************"<<endl;
		edges[edgeCount].code = code;
		edges[edgeCount].name = name;
		edgeCount++;

}
void Graph::printNodes() {
	for (int i = 0; i < conceptCount; i++)
		cout << nodes[i].code << "   " << nodes[i].lemma << "   "
				<< nodes[i].pos << endl;
}
void Graph::printEdges() {
	for (int i = 0; i < edgeCount; i++) {
		//cout<<edges[i].code<<"   ";
		cout << edges[i].name <<"\t"<<edges[i].in<<"\t"<<edges[i].ex<<endl;
	}
}
concept Graph::getNode(string code) {
	for (int i = 0; i < conceptCount; i++)
		if (nodes[i].code == code)
			return nodes[i];
	for (int i = 0; i < edgeCount; i++)
		if (edges[i].name == "equality" && (edges[i].ex == code))
			return getNode(edges[i].in);
	concept c;
	c.lemma = code;
	return c;
}
void Graph::finalize(){
	for (int i = 0; i < edgeCount; i++) {
			if(edges[i].name == "is" ){
				for (int j = 0; j < edgeCount; j++) {
					if(edges[i].code == edges[j].code)
					{
						edges[i].ex = edges[j].ex;
						edges[i].in = edges[j].in;
						cout<<"found  "<<endl;
						break;
					}
				}
			}
	}
}
bool Graph::checkGraph() {
	for(int i=0; i< conceptCount; i++)
		if(debug)
		cout<<nodes[i].code<<"   "<<nodes[i].lemma<<endl;
	for (int i = 0; i < edgeCount; i++) {
		cout<<getNode(edges[i].in).lemma<<"  "<<edges[i].name<<"   "<< getNode(edges[i].ex).lemma<<endl;
		if(edges[i].name == "equality" && getNode(edges[i].in).lemma == getNode(edges[i].ex).lemma)
		{
		//					edges[i].name = "rep";
							repeated++;
							}
		for(int j=i+1; j<edgeCount; j++){
			if(edges[i].name == edges[j].name){
				if(getNode(edges[i].in).lemma == getNode(edges[j].in).lemma &&
						getNode(edges[i].ex).lemma == getNode(edges[j].ex).lemma)
					{
					edges[j].name = "rep";

					repeated++;
					}
			}
		}
		//cout<<getNode(edges[i].in).lemma<<"     ";
		//cout<<edges[i].code << edges[i].name << "     "<<getNode(edges[i].ex).lemma<<endl;
	}
}
double matchRelationNameSTS(const char* r1, const char* r2) {
	//cout<<r1<<"    "<<r2<<endl;
//	if(strcmp(r1, "rep") == 0  || strcmp(r2, "rep") == 0 )     // added   24/11/2018
	//	return 0.5;
//	if(strcmp(r1, "topic") == 0  || strcmp(r2, "topic") == 0 )   // added   26/11/2018
//			return 0.3;
	if(strcmp(r1, "is") == 0 && strcmp(r2, "is") == 0)
			return 0.7;
	if(strcmp(r1, "equality") == 0 && strcmp(r2, "equality") == 0)
		return 0.7;
	if(strcmp(r1, "rep") == 0 )
			return 0.0;
	if (strcmp(r1, r2) == 0)
		return 1;
//	else if (strcmp(r1, "experiencer") == 0 && strcmp(r2, "of") == 0)
//		return 0.8;
//	else if (strcmp(r1, "of") == 0 && strcmp(r2, "experiencer") == 0)
//		return 0.8;
/*	else if (strcmp(r1, "theme") == 0 && strcmp(r2, "agent") == 0)
		return 0.6;
	else if (strcmp(r1, "agent") == 0 && strcmp(r2, "theme") == 0)
		return 0.6;
*/
	else
		return 0.79-(0.01*(Graph::getWeight(r1)+Graph::getWeight(r2)));
}

double matchRelationName(const char* r1, const char* r2) {
/*	char* t1 = new char[strlen(r1)];
		char* t2 = new char[strlen(r2)];
		strcpy(t1, r1);
		strcpy(t2, r2);
	double s1 = ss.getWordSim(t1, t2);
*/
	//cout<<r1<<"    "<<r2<<endl;
//	if(strcmp(r1, "rep") == 0  || strcmp(r2, "rep") == 0 )     // added   24/11/2018
	//	return 0.5;
//	if(strcmp(r1, "topic") == 0  || strcmp(r2, "topic") == 0 )   // added   26/11/2018
//			return 0.3;
	if(strcmp(r1, "is") == 0 && strcmp(r2, "is") == 0)
			return 0.7;
	if(strcmp(r1, "equality") == 0 && strcmp(r2, "equality") == 0)
		return 0.7;
	if(strcmp(r1, "rep") == 0 )
			return 0.0;
	if (strcmp(r1, r2) == 0)
		return 1;
//	else if (strcmp(r1, "experiencer") == 0 && strcmp(r2, "of") == 0)
//		return 0.8;
//	else if (strcmp(r1, "of") == 0 && strcmp(r2, "experiencer") == 0)
//		return 0.8;
	/*else if (strcmp(r1, "theme") == 0 && strcmp(r2, "recipient") == 0)
		return 0.75;
	else if (strcmp(r1, "recipient") == 0 && strcmp(r2, "theme") == 0)
		return 0.75;
*/
	else
		return 0.73;
}
double stringSim(const std::string &s1, const std::string &s2)
	{
	  const size_t m(s1.size());
	  const size_t n(s2.size());

	  if( m==0 ) return n;
	  if( n==0 ) return m;

	  size_t *costs = new size_t[n + 1];

	  for( size_t k=0; k<=n; k++ ) costs[k] = k;

	  size_t i = 0;
	  for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
	  {
	    costs[0] = i+1;
	    size_t corner = i;

	    size_t j = 0;
	    for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
	    {
	      size_t upper = costs[j+1];
	      if( *it1 == *it2 )
	      {
			  costs[j+1] = corner;
		  }
	      else
		  {
			size_t t(upper<corner?upper:corner);
	        costs[j+1] = (costs[j]<t?costs[j]:t)+1;
		  }

	      corner = upper;
	    }
	  }

	  size_t result = costs[n];
	  delete [] costs;
	  double r = (double)result/std::max(m, n);
	  return 1-r;

}
double matchConcept(const char* c1, const char* c2) {
	//cout<<c1<<"   "<<c2<<"   ";
	if(strcmp(c1, c2) == 0)
		return 1;
	char* t1 = new char[strlen(c1)];
	char* t2 = new char[strlen(c2)];
	strcpy(t1, c1);
	strcpy(t2, c2);
	double d1;
	d1 = /*ssWn.compute_similarity(t1, t2,gg);//*/ss.getWordSim(t1, t2);
	//if(d1<=0)
		//cout<<d1<<endl;
		if(isnan(d1) && isalpha(c2[strlen(c2)-1]) && isalpha(c1[strlen(c1)-1]))
	 {d1 = /*stringSim(t1, t2);//*/ssWn.compute_similarity(t1, t2,gg);
	 //cout<<"****  "<<d1<<endl;
	 }
		//else d1 = (d1*0.75 + ssWn.compute_similarity(t1, t2,gg)*0.25 );
	delete t1;
	delete t2;
	//use word expansion based on equality relation
	//cout<<d1<<"    "<<endl;
	return d1;
}
double matchConceptWithExpansion(Graph* g1, const char* c1, Graph* g2, const char* c2) {
	//return matchConcept(c1, c2);
	//cout<<c1<<"  ----  "<< c2<<endl;
	string* all1 = g1->expand(c1);
	string* all2 = g2->expand(c2);
	double w=0;
	double d, max =0;
	for(int i=0; !all1[i].empty(); i++)
		for(int j=0; !all2[j].empty(); j++){
			d = matchConcept(all1[i].c_str(), all2[j].c_str());
			w = ss.getIdf(all1[i], g1)*ss.getIdf(all2[j], g2);
			cout<<" W-- "<<w<<endl;
			if(w > 0)
				d = d/w;
			//cout<<all1[i].c_str()<<"  --  "<< all2[j].c_str()<<"    "<<d<<endl;
			if(d > max)
				max = d;
		}
	delete[] all1;
	delete[] all2;
	return max;
}
double Graph::matchRelation(Graph* g1, relation r1, Graph* g2, relation r2) {
	//cout<<g1->getNode(r1.in).lemma<<"   "<<r1.name<<"   "<< g1->getNode(r1.ex).lemma<<endl;
	//cout<<g2->getNode(r2.in).lemma<<"   "<<r2.name<<"   "<< g2->getNode(r2.ex).lemma<<endl;
	double d1 = matchConceptWithExpansion(g1, g1->getNode(r1.in).lemma.c_str(), g2, g2->getNode(r2.in).lemma.c_str());
	double d2 = matchConceptWithExpansion(g1, g1->getNode(r1.ex).lemma.c_str(), g2, g2->getNode(r2.ex).lemma.c_str());
//	double d1 = matchConcept(g1->getNode(r1.in).lemma.c_str(), g2->getNode(r2.in).lemma.c_str());
//	double d2 = matchConcept(g1->getNode(r1.ex).lemma.c_str(), g2->getNode(r2.ex).lemma.c_str());
//	double d3 = matchRelationName(r1.name.c_str(), r2.name.c_str());
	double d3 = matchRelationNameSTS(r1.name.c_str(), r2.name.c_str());
	//cout<<(d2 + d1) / 2.0*d3<<endl;
	return (d2 + d1) / 2.0*d3;

}
string* Graph::expand(string word){
	string* ewords = new string[15];
	ewords[0] = word;
	int c =1;
	for(int i =0; i< edgeCount; i++)
		if(strcmp(edges[i].name.c_str(), "equality") == 0 || strcmp(edges[i].name.c_str(), "is") == 0 || strcmp(edges[i].name.c_str(), "of") == 0){
			if(getNode(edges[i].ex).lemma == word)
				ewords[c++] = getNode(edges[i].in).lemma;
			else if(getNode(edges[i].in).lemma == word)
				ewords[c++] = getNode(edges[i].ex).lemma;
		}
	return ewords;
}

double Graph::matchGraph(Graph g) {

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
	//cout<<endl<<"dddd"<< d1<<"   "<<d2<<"   "<<(d1+d2)/2<<endl;
	return (d1+d2)/2;
}

float* get30(float arr[]){
	int c=0;
	cout<<"start   "<<endl;
	float* NewArr = new float[30];
	NewArr[c++] = arr[0];
	NewArr[c++] = arr[4];
	NewArr[c++] = arr[8];
	NewArr[c++] = arr[12];
	cout<<NewArr[c-1]<<endl;
	NewArr[c++] = arr[16];
	NewArr[c++] = arr[20];
	NewArr[c++] = arr[24];
	NewArr[c++] = arr[28];
	NewArr[c++] = arr[32];
	NewArr[c++] = arr[36];
	NewArr[c++] = arr[40];
	for(int i=46; i< 65; i++)
		{
		NewArr[c++] = arr[i];
		//cout<<NewArr[c-1];
		}
	for(int i=0; i< 30; i++)
			{
			//NewArr[c++] = arr[i];
			cout<<NewArr[i];
			}
	return NewArr;
}
float* get60(float arr[]){
	int c=0;
	//cout<<"start   "<<endl;
	float* NewArr = new float[60];
	for(int i=0; i< 65; i++)
		{
		if(i==16 || i==23 || i==29 || i==32 || i==38)
			continue;
		NewArr[c++] = arr[i];
		//cout<<NewArr[c-1];
		}
	for(int i=0; i< 30; i++)
			{
			//NewArr[c++] = arr[i];
	//		cout<<NewArr[i];
			}
	return NewArr;
}
void printWordMatrix(Graph g1, Graph g2){
	for(int j=0; j<g2.conceptCount; j++)
		cout<<g2.nodes[j].lemma<<"   &   ";
	for(int i=0; i< g1.conceptCount; i++){
		cout<<g1.nodes[i].lemma<<"   &   ";
		for(int j=0; j<g2.conceptCount; j++){
			cout<<g1.nodes[i].lemma.c_str()<<"  "<<g2.nodes[j].lemma.c_str()<<"  "<<matchConcept(g1.nodes[i].lemma.c_str(), g2.nodes[j].lemma.c_str())<<"  &  ";
		}
		cout<<endl;
	}
}
int graph_MSRP(){
	Util utility;
	int tt = 00;
	cout << "test Graph MSRP" << endl;

	FILE *fout;
	fout = fopen("/research/NLP/MSRParaphraseCorpus/msr_paraphrase_test_Graph3.txt", "rb");
	if (fout == NULL) {
		printf("output file not found\n");
		return 0;
	}
	string line, res;

	regex conceptReg("c[[:digit:]]+:(.+?):.+instance (.+?) ");
	regex argReg("c[[:digit:]]+:(.+?):.+arg (.+?) ");
	regex inRelReg("(.*?):(.*?):.* int (.*?) ");
	regex exRelReg("(.*?):(.*?):.* ext (.*?) ");
	regex inEqRelReg("(.*?):equality int (.*?) ");
	regex exEqRelReg("(.*?):equality ext (.*?) ");
	regex isReg(".* (.*?):equality [[:digit:]]+ . is ");
	regex refReg(".+referent (.+?) .* (.+?) ");
	smatch match;
	for (int i = 0; i < 350; i++) {
		res = utility.getStringLine(fout);

//		cout<<i<<endl;
	//	cout<<line<<endl;
		line = utility.getStringLine(fout);
//		cout<<"sent  "<<line<<endl;
		gLen =0;
		Graph g1((char*) line.c_str());
		int len1 = gLen;
		line = utility.getLine(fout);
		//cout<<line<<endl;
		line = utility.getLine(fout);
		//cout<<line<<endl;
		line = utility.getLine(fout);
		//cout << line << endl;
		line[0] = '\0';

//		cout<<"start g g "<<endl;
		while (line[0] != '!') {
			line = utility.getStringLine(fout);
			//cout<<line<<endl;
//			if(i<tt)
//			continue;
//			cout<<"test test 5555"<<endl;
			if (regex_search(line, match, conceptReg)) {
				//cout<<match.str(1)<<"    "<< match.str(2)<<endl;
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
//		cout<<"end of first sent g "<<endl;
		//cout<<"test "<<endl;
		//g1.printNodes();
		//g1.printEdges();
		//cout << endl;
		//continue;
//		g1.checkGraph();
		//continue;
		line = utility.getStringLine(fout);
		//cout<<"sec sent g "<<line<<endl;
		gLen =0;
		Graph g2((char*) line.c_str());
		line = utility.getLine(fout);
		line = utility.getLine(fout);
		line = utility.getLine(fout);
		//cout << line << endl;
		int len2 = gLen;
		line[0] = '\0';
//		cout<<"start  g2 "<<g2.conceptCount<<"   "<<g2.edgeCount<<endl;
		int iii=0;
		while (line[0] != '!') {
			line = utility.getStringLine(fout);
			//cout<<line<<endl;
			if(i<tt)
						continue;
//			cout<<"test test "<<iii++<<endl;
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
				g1.addConcept(match.str(2), match.str(1), "ref");
			}else if(regex_search(line, match, isReg)){
				//cout<<endl<<match.str(1)<<"    is relation"<<endl;
				//cout<<g2.edges[g2.edgeCount-1].name<<"    "<<g2.edges[g2.edgeCount-1].code<<endl;
				g2.addIsRelation("is", match.str(1));
				//cout<<g2.edges[g2.edgeCount-1].name<<"    "<<g2.edges[g2.edgeCount-1].code<<endl;
		}

		//	cout<<"start  g2 "<<g2.conceptCount<<"   "<<g2.edgeCount<<endl;
		}

//		if(i >= 31)
//			continue;
			//cout<<i;
//		g2.checkGraph();
//		resLine = utility.getStringLine(fres);
		//cout<<res<<", " <<" "<<i+1150<<", "<<g1.nodes[0].lemma<<endl;
		if(i>=tt)
		if((g1.conceptCount) > len1/2 && (g2.conceptCount) > len2/2)
		{
//		double old = stod(resLine);
		double sim = g1.matchGraph(g2); //*/(g1.matchGraph(g2)*0.5+old*0.5);
		cout<<res<<", "<<sim <<" "<<endl;
		}
		else{
		//	cout<<len1<<"    "<<g1.conceptCount<<"    "<<g1.nodes[0].lemma<<"   "<<len2<<"    "<<g2.conceptCount<<g2.nodes[0].lemma<<"     ";
		//	cout<<"eroorrrrrr  "<<endl;
			//writeLine(error, )
		}
//		line = utility.getLine(fout);
//		origin[i] = atof(line.c_str());
		//cout<<origin[i]<<endl;
//		line = utility.getLine(fout);
//g1 = NULL;
//delete g2;
	}
	cout<<"end o o o o o ";
return 3;
}
//int odds =0;
//computing similarity based on graph for STS dataset
int graph_STS_old(){
	Util utility;
	int tt = 0;
	cout << "sts Graph " << endl;
	FILE *fres;
	fres = fopen("/research/NLP/sts datasets/2012/test-gold/STS.gs.surprise.SMTnews.txt", "rb");
		if (fres == NULL) {
			printf("output file not found\n");
			return 0;
		}
		string resLine;

	FILE *fout;
	fout = fopen("/research/NLP/sts datasets/2012/test-gold/STS.input.surprise.SMTnews.txt-graph.txt", "rb");
	if (fout == NULL) {
		printf("output file not found\n");
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
	float prop[750];
	float origin[750];
	for (int i = 0; i < 399; i++) {
		cout<<utility.getStringLine(fout);
		line = utility.getStringLine(fout);
		//cout<<i<<endl;
		cout<<line<<endl;
		Graph g1((char*) line.c_str());
		//cout << line << endl;
		line[0] = '\0';
		smatch match;
		while (line[0] != '!') {
			line = utility.getStringLine(fout);
			//cout<<line<<endl;
			//if(i<tt)
			//continue;
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
		Graph g2((char*) line.c_str());
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
				g1.addConcept(match.str(2), match.str(1), "ref");
			}else if(regex_search(line, match, isReg)){
				//cout<<endl<<match.str(1)<<"    is relation"<<endl;
				//cout<<g2.edges[g2.edgeCount-1].name<<"    "<<g2.edges[g2.edgeCount-1].code<<endl;
				g2.addIsRelation("is", match.str(1));
				//cout<<g2.edges[g2.edgeCount-1].name<<"    "<<g2.edges[g2.edgeCount-1].code<<endl;
		}

			//cout << line << endl;
		}
		//g1.finalize();
		//g2.finalize();
		//g2.printNodes();
		//g2.printEdges();
		//cout << "ssdddddd" <<endl;
//		if(i >= 31)
//			continue;
			//cout<<i;
		g2.checkGraph();
		resLine = utility.getStringLine(fres);
		//if(i>=0)
		{
		//double old = stod(resLine);
		//printWordMatrix(g1, g2);
		prop[i] = g1.matchGraph(g2)*5; //*/(g1.matchGraph(g2)*0.65+old*0.35);
		cout<<prop[i]<<endl;
		}
		//line = utility.getLine(fres);
		origin[i] = atof(resLine.c_str());
		cout<<origin[i]<<endl;
//		line = utility.getLine(fout);
//		if(g1.conceptCount <=1 || g2.conceptCount<=1)
//			{odds++;cout<<i--;}

	}
	cout<<"GO  "<<endl;
	cout<<"result is  "<<utility.calcPearson(prop, origin, 399)<<endl;
/*
	float* Mprop = get30(prop);
	cout<<"GO2"<<endl;
	float* Morigin = get30(origin);
	cout<<"GO3"<<endl;
	for(int i=0; i< 30;i++)
	{
		cout<<Mprop[i]<<endl;
	}
	cout<<"result is  "<<utility.calcPearson(prop, origin, 65)<<endl;
	cout<<"30 result is  "<<utility.calcPearson(Morigin, Mprop, 30)<<endl;
	delete Mprop;
	delete Morigin;
	Mprop = get60(prop);
	Morigin = get60(origin);
		cout<<"60 result is  "<<utility.calcPearson(Morigin, Mprop, 60)<<endl;
	*/


}
int main11() {
	//Graph g("The increase reflects lower credit losses and favorable interest rates.");
	//cout<<gLen;
	//graph_STS_old();
	graph_MSRP();
//	cout<<endl<<matchConcept("higher", "thing");
	return 0;
	//wenn wes("/Programs/WordNet-3.0/dict/",
	//										"/research/NLP/tools/semantic-similarity-master/dicts/freq.txt");
	// test  =-=-==-==-=-=-=-=-=-
	/*
	double x = ss.getWordSim("body", "people");
	double y = ss.getWordSim("cemetery", "graveyard");
	double z = ss.getWordSim("area", "place");
	cout<<x<<"   "<<y<<"   "<<z<<endl;



	SentenceSimilarityLi2006 ssWN(we);
	double a = ssWN.compute_similarity("body","people",g);
	double a2 = ssWN.compute_similarity("cemetery","graveyard",g);
	double a3 = ssWN.compute_similarity("area","place",g);
	cout<<a<<"   "<<a2<<"   "<<a3<<endl;
	return 0;
	*/
	//    -= -= -= -= -=- =-= -= -= -= -=
	Util utility;
	int tt = 0;
	cout << "test Graph " << endl;
	FILE *fres;
	fres = fopen("/research/NLP/result65-2.txt", "rb");
		if (fres == NULL) {
			printf("output file not found\n");
			return 0;
		}
		string resLine;


	FILE *fout;
	fout = fopen("/research/NLP/dataset_Graph", "rb");
	if (fout == NULL) {
		printf("output file not found\n");
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
	float prop[65];
	float origin[65];
	for (int i = 0; i < 65; i++) {
		line = utility.getStringLine(fout);
		//cout<<i<<endl;
		cout<<line<<endl;
		Graph g1((char*) line.c_str());
		line = utility.getLine(fout);
		line = utility.getLine(fout);
		line = utility.getLine(fout);
		//cout << line << endl;
		line[0] = '\0';
		smatch match;
		while (line[0] != '!') {
			line = utility.getStringLine(fout);
			//cout<<line<<endl;
			//if(i<tt)
			//continue;
			if (regex_search(line, match, conceptReg)) {
				//cout<<match.str(1)<<"    "<< match.str(2)<<endl;
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
		Graph g2((char*) line.c_str());
		line = utility.getLine(fout);
		line = utility.getLine(fout);
		line = utility.getLine(fout);
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
				g1.addConcept(match.str(2), match.str(1), "ref");
			}else if(regex_search(line, match, isReg)){
				//cout<<endl<<match.str(1)<<"    is relation"<<endl;
				//cout<<g2.edges[g2.edgeCount-1].name<<"    "<<g2.edges[g2.edgeCount-1].code<<endl;
				g2.addIsRelation("is", match.str(1));
				//cout<<g2.edges[g2.edgeCount-1].name<<"    "<<g2.edges[g2.edgeCount-1].code<<endl;
		}

			//cout << line << endl;
		}
		//g1.finalize();
		//g2.finalize();
		//g2.printNodes();
		//g2.printEdges();
		//cout << "ssdddddd" <<endl;
//		if(i >= 31)
//			continue;
			//cout<<i;
		g2.checkGraph();
		resLine = utility.getStringLine(fres);
		if(i>=0)
		{
		double old = stod(resLine);
		printWordMatrix(g1, g2);
		//prop[i] = /*g1.matchGraph(g2); //*/(g1.matchGraph(g2)*0.65+old*0.35);
		cout<<prop[i]<<endl;
		}
		line = utility.getLine(fout);
		origin[i] = atof(line.c_str());
		//cout<<origin[i]<<endl;
		line = utility.getLine(fout);

	}
	cout<<"GO"<<endl;
	float* Mprop = get30(prop);
	cout<<"GO2"<<endl;
	float* Morigin = get30(origin);
	cout<<"GO3"<<endl;
	for(int i=0; i< 30;i++)
	{
		cout<<Mprop[i]<<endl;
	}
	cout<<"result is  "<<utility.calcPearson(prop, origin, 65)<<endl;
	cout<<"30 result is  "<<utility.calcPearson(Morigin, Mprop, 30)<<endl;
	delete Mprop;
	delete Morigin;
	Mprop = get60(prop);
	Morigin = get60(origin);
		cout<<"60 result is  "<<utility.calcPearson(Morigin, Mprop, 60)<<endl;


}
