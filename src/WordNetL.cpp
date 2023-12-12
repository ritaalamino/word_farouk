/*
 * WordNetL.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: mamfarouk
 */

//=======================================================================
// Copyright 2013
// Authors: Xin Liu tonyxliu@hotmail.co.uk
//
// Distributed under GPL v2
//=======================================================================

#include <string>
#include <iostream>
#include "wn/wn.h"

#include "sentence_similarity.h"
#include "wordnet_extended.h"

typedef WordnetExtended we;

using namespace boost;

// this defined in wn.h
//int OpenDB = 0;

//void print_graph(we::UndirectedGraph & g);
//void print_sim(std::string s1, std::string s2, float sim, float paper_sim = -1);

int main4(int argc, char **argv) {

	std::cout<<"test ------ "<<std::endl;
	we we("/Programs/WordNet-3.0/dict/",
			"/research/NLP/tools/semantic-similarity-master/dicts/freq.txt");
	we::UndirectedGraph g;

	SentenceSimilarityLi2006 ss(we);

	double s = ss.compute_similarity("boy", "girl", g);
	//s = ss.compute_similarity("hammer", "nail", g);
	//print_graph(g);
	for(int i=0; i<120; i++){
	s = ss.compute_similarity("Duque will return to Earth Oct. 27 with the station's current crew, U.S. astronaut Ed Lu and Russian cosmonaut Yuri Malenchenko."
			, "Currently living onboard the space station are American astronaut Ed Lu and Russian cosmonaut Yuri Malenchenko.", g); //0.561
	std::cout<<i<<" :   "<<s<<std::endl;
	}
	return 1;
}
/*
void print_sim(std::string s1, std::string s2, float sim, float paper_sim)
{
	std::cout << s1 << " * " << s2 << "(sim:" << sim << ", paper-sim:" << paper_sim <<")\n";
}

void print_graph(we::UndirectedGraph & g)
{
	typedef boost::property_map<we::UndirectedGraph, boost::vertex_index_t>::type VertexIndex;
	VertexIndex index = get(boost::vertex_index, g);

	std::cout << "vertices(g) = ";
	boost::graph_traits < we::UndirectedGraph >::vertex_iterator vi, vend;
	for (boost::tie(vi, vend) = boost::vertices(g); vi != vend; ++vi)
	{
		std::cout << "(" << g[*vi]->words[0] << " " << *vi << " " << g[*vi]->depth << "), ";
	}
	std::cout << "\n\n" << std::endl;


	std::cout << "edges(g) = ";
	boost::graph_traits<we::UndirectedGraph>::edge_iterator ei, ei_end;
	for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
	{
		std::cout << "(" << g[index[source(*ei, g)]]->words[0]<<source(*ei, g)
		<< "," << g[index[target(*ei, g)]]->words[0] << target(*ei, g) << ","
		<< g[index[target(*ei, g)]]->depth << "), ";
	}
	std::cout << "\n\n"  << std::endl;


	//graph_traits < we::UndirectedGraph >::out_edge_iterator out, out_end;
 // graph_traits < we::UndirectedGraph >::in_edge_iterator in, in_end;
	//std::cout << "out_edges(1): ";
 // for (boost::tie(out, out_end) = out_edges(1, g); out != out_end; ++out)
 //   std::cout << *out;
 // std::cout << std::endl << "in_edges(0): ";
 // for (boost::tie(in, in_end) = in_edges(1, g); in != in_end; ++in)
 //   std::cout << *in;
 // std::cout << "\n\n" << std::endl;
}
*/
