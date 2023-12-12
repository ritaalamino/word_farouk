/*
 * Parser.h
 *
 *  Created on: Jun 3, 2018
 *      Author: mamfarouk
 */
#include<vector>

#ifndef PARSER_H_
#define PARSER_H_
struct Token{
	const char* str;
	const char* lemma;
	const char* pos;
	const char* ner;
};
class Parser{
public:
	void parse(char*);
	std::vector<Token> getTokens(char*);
};

#endif /* PARSER_H_ */
