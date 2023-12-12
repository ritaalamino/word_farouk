/*
 * Graph.h
 *
 *  Created on: Oct 3, 2018
 *      Author: mamfarouk
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include<string>
#include<Util.h>
struct concept{
	string lemma;
	string code;
	string pos;
};

struct relation{
	string name;
	string code;
	string in;
	string ex;
};
class Graph{
public:
	int conceptCount=0;
	int edgeCount=0;
	int repeated=0;
	bool debug = false;
	concept* nodes;
	relation* edges;
	Util utility;
	Graph(char* sentence);
	void addConcept(string name, string code, string POS);
	void addRelationIn(string name, string code, string in);
	void addRelationEx(string name, string code, string ex);
	void addIsRelation(string name, string code);
	concept getNode(string code);
	string* expand(string word);
	static double  getWeight(string relation);
	//double matchConceptWithExpansion(Graph, const char* c1, Graph, const char* c2);
	double matchRelation(Graph* g1, relation r1, Graph* g2, relation r2);
	double matchGraph(Graph g);
	bool checkGraph();
	void finalize();
	void printNodes();
	void printEdges();
};

#endif /* GRAPH_H_ */
