/*
 * GraphSTS.h
 *
 *  Created on: Sep 3, 2019
 *      Author: mamfarouk
 */

#ifndef GRAPHSTS_H_
#define GRAPHSTS_H_

#include<string>
#include<Graph.h>

class GraphSTS: public Graph{
public:
	GraphSTS(char* sentence);
	double matchGraph(Graph g);
};


#endif /* GRAPHSTS_H_ */
