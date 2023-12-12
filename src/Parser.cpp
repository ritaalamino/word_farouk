/*
 * Parser.cpp
 *
 *  Created on: Jun 3, 2018
 *      Author: mamfarouk
 */
#include "Parser.h"
#include <iostream>
#include<string.h>
#include<sstream>
#//include <chrono.h>
#include <unistd.h>

#include <cstdio>
#include <memory>
#include <stdexcept>

using namespace std;

string* split(char* str, char del, int max = 20) {
	string item;
	stringstream ss(str);
	string* res = new string[max];
	//cout<<"iner test "<< str<<endl;
	int i = 0;
	//int start =0;
	while (getline(ss, item, del) && i < 50) {
		//cout<<"iner test 00  "<< i<<endl;
		res[i++] = item;
		//start += item.size()+1;
		//cout<<"iner test "<<item<< i<<endl;
	}
	//cout<<i;
	string* final = new string[i];
	for (int j = 0; j < i; j++)
		final[j] = res[j];
	delete[] res;
	return final;
}
string* split(string str, char del, int max = 50) {
	string item;
	stringstream ss(str);
	string* res = new string[max];
	int i = 0;
	while (getline(ss, item, del) && i < 50) {
		res[i++] = item;
	}
	//cout<<i;
	//for(int j=0; j<i; j++)
	//cout<<res[j]<<endl;
	return res;
}
vector<Token> Parser::getTokens(char* st) {
	int i = 0, t;
	char* tokenstr = new char[100];
	vector<Token> toks;
	//const char temp;
	while (st[i] != '[')
		i++;
	i++;
	do {
		while (st[i] != '[' && st[i] != ']')
			i++;
		if (st[i] == ']')
			break;
		t = ++i;
		while (st[i] != ']')
			i++;
		//cout<<"test 1 "<<endl;
		memcpy(tokenstr, &st[t], i - t);
		tokenstr[i - t] = '\0';
		//cout<<"test 12 "<<tokenstr<<endl;
		string* list = split(tokenstr, ',', 20);
		Token tok;
		//cout<<"test 1 3 "<<endl;
		string* sublist = split(list[0], ':', 5);
		tok.str = sublist[1].c_str();
		sublist = split(list[1], ':', 5);
		tok.pos = sublist[1].c_str();
		sublist = split(list[2], ':', 5);
		tok.lemma = sublist[1].c_str();
		sublist = split(list[3], ':', 5);
		tok.ner = sublist[1].c_str();
		//cout<<"str  "<<tok.str<<"  pos  "<<tok.pos<<endl;
		toks.push_back(tok);
		//cout<<"    "<<tokenstr<<endl;
		i++;
		//	delete list;
		//	delete sublist;
	} while (st[i] != ']');

	delete tokenstr;

	return toks;
}
bool isNeglectable(const char* pos) {
	//cout<<pos<<endl;
	if (strcmp(pos, "CC") == 0 || strcmp(pos, "CD") == 0 || strcmp(pos, "DT")
			== 0 || strcmp(pos, "EX") == 0 || strcmp(pos, "IN") == 0 || strcmp(
			pos, "LS") == 0 || strcmp(pos, "MD") == 0 || strcmp(pos, "PDT")
			== 0 || strcmp(pos, "POS") == 0 || strcmp(pos, "SYM") == 0
			|| strcmp(pos, "TO") == 0 || strcmp(pos, "UH") == 0 || strcmp(pos,
			"VBZ") == 0 || strcmp(pos, "','") == 0 || strcmp(pos, "") == 0
			|| strcmp(pos, ".") == 0)
		return true;
	return false;
}
char* trimPr(const char* str) {
	int len = strlen(str);
	if (len == 0)
		return "";
	//cout<<str<<"  --"<<len<<" --  >  ";
	char* n = new char[len - 2];
	for (int i = 2; i < len - 1; i++)
		n[i - 2] = str[i];
	n[len - 2] = '\0';
	//cout<<n<<endl;
	return n;
}
char* trimQuotes(const char* str) {
	int len = strlen(str);
	if (len == 0)
		return "";
	//cout<<str<<"  --"<<len<<" --  >  ";
	char* n = new char[len - 1];
	for (int i = 1; i < len - 1; i++)
		n[i - 1] = str[i];
	n[len - 2] = '\0';
	//cout<<n<<endl;
	return n;
}
void Parser::parse(char* st) {
	//cout<<st;
	vector<Token> toks = getTokens(st);
	//cout<<toks.size()<<" - - - - -"<<endl;
	for (int i = 0; i < toks.size(); i++) {
		cout << trimQuotes(toks[i].pos) << "  ----- " << i << endl;
		if (isNeglectable(trimQuotes(toks[i].pos)))
			continue;
		cout << toks[i].str << "   " << toks[i].pos << endl;
		;
	}
}

std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	FILE* pipe = popen(cmd, "r");
	if (!pipe)
		throw std::runtime_error("popen() failed!");
	try {
		while (!feof(pipe)) {
			if (fgets(buffer, 128, pipe) != NULL)
				result += buffer;
		}
	} catch (...) {
		pclose(pipe);
		throw;
	}
	pclose(pipe);
	return result;
}
char* getLine2(FILE* f) {
	char* l = new char[500];
	int i = 0;
	while (1) {
		l[i] = fgetc(f);
		if (l[i] == '\n')
			break;
		i++;
	}
	l[i] = '\0';
	//cout<<i<<endl;
	return l;
}
void writeLine(FILE* f, const char*line) {
	fprintf(f, "%s\n", line);
	//cout<<i<<endl;
	//return l;
}
char* process(const char* s) {
	Parser p;
	char* ns = new char[strlen(s)];
	//cout<<"lplplplplpplpl"<<endl;
	strcpy(ns, s);
	//cout<<"lplplplplpplpl"<<endl;
	vector<Token> toks = p.getTokens(ns);
	//cout<<"lplplplplpplpl"<<endl;
	char* st = new char[300];

	//cout<<toks.size()<<" - - - - -"<<endl;
	for (int i = 0; i < toks.size(); i++) {
		cout << trimQuotes(toks[i].pos) << "  ----- " << i << endl;
		if (isNeglectable(trimQuotes(toks[i].pos)))
			continue;
		cout << toks[i].str << " ()()()()()()(  " << toks[i].pos << endl;
		if (toks[i].str[0] == ' ')
			strcat(st, trimPr(toks[i].str));
		else
			strcat(st, toks[i].str);
		strcat(st, " ");
		strcat(st, trimQuotes(toks[i].pos));
		strcat(st, " ");
		//cout<<st<<" =+ "<<endl;
	}
	//cout<<st<<" ******=+ "<<endl;
	return st;
}
void prepare() {

	FILE *ff;
	ff = fopen("/research/NLP/dataset", "rb");
	if (ff == NULL) {
		printf("Input file not found\n");
		return;
	}
	FILE *fout;
	fout = fopen("/research/NLP/dataset_Graph", "wb");
	if (fout == NULL) {
		printf("output file not found\n");
		return;
	}
	cout << endl;
	int i;
	for (i = 0; i < 65; i++) {
		getLine2(ff);
		char* line1 = getLine2(ff);
		writeLine(fout, line1);
		string
				cmd =
						string("curl -d '") + string(line1)
								+ string(
										"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline'");
		string s = exec(cmd.c_str());
		usleep(1200 * 1000);
		string* sl = split(s, '\n');
		int i = 0;
		while (sl[i][0] != 's')
			i++;
		//cout << endl << endl << sl[i] << endl << endl;
		writeLine(fout, process(sl[i].c_str()));
		writeLine(fout, sl[i].c_str());
		cmd
				= string("curl -d '") + string(line1)
						+ string(
								"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline?semantics=drg'");
		s = exec(cmd.c_str());
		usleep(1200 * 1000);
		cout << endl << endl << s << endl << endl;
		writeLine(fout, "!.");
		writeLine(fout, s.c_str());
		writeLine(fout, "!.");
		char* line2 = getLine2(ff);
		writeLine(fout, line2);
		cmd
				= string("curl -d '") + string(line2)
						+ string(
								"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline'");
		s = exec(cmd.c_str());
		usleep(1500 * 1000);
		string* sl2 = split(s, '\n');
		i = 0;
		while (sl2[i][0] != 's')
			i++;
		//cout << endl << endl << sl2[i] << endl << endl;
		//Rst = process(sl[i]);
		writeLine(fout, process(sl2[i].c_str()));
		writeLine(fout, sl2[i].c_str());
		cmd
				= string("curl -d '") + string(line2)
						+ string(
								"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline?semantics=drg'");
		s = exec(cmd.c_str());
		usleep(1500 * 1000);
		writeLine(fout, "!.");
		writeLine(fout, s.c_str());
		writeLine(fout, "!.");

		writeLine(fout, getLine2(ff));//<<", ";
		writeLine(fout, getLine2(ff));//<<endl;
	}
}
char** checkSentence(const char* str) {
	char ch = str[0];
	int total = 0, spaces = 0;
	char** res = new char*[3];
	res[0] = new char[160];
	res[1] = new char[160];
	res[2] = new char[160];
	int s = 0, i = 0;
	//cout<<"spaces: "<<spaces<<"      total:"<<total<<"    "<<str<<endl;
	while (ch != '\0') {
		//cout<<total<<"   "<<ch<<endl;
		total++;
		if (ch == ' ' || ch == ',')
			spaces++;

		if (total > 500)
			break;
		if (spaces >= 14) {
			spaces = 0;
			res[s][i] = '\0';
			s++;
			i = 0;
		} else {
			if (ch != '.')
				res[s][i++] = ch;
		}

		ch = str[total];

	}
	res[s][i] = '\0';
	//cout<<"spaces: "<<spaces<<"      total:"<<total<<"    "<<i<<endl;
	//for(int a=0; a<=s;a++)
	//cout<<res[a]<<endl;
	//cout<<endl;
	return res;
}

void prepareMSRP() {

	FILE *ff;
	ff = fopen("/research/NLP/MSRParaphraseCorpus/msr_paraphrase_test.txt",
			"rb");
	if (ff == NULL) {
		printf("Input file not found\n");
		return;
	}
	FILE *fout;
	fout = fopen(
			"/research/NLP/MSRParaphraseCorpus/msr_paraphrase_test_Graph4.txt",
			"a");
	if (fout == NULL) {
		printf("output file not found\n");
		return;
	}
	cout << "READYYYY..." << endl;
	getLine2(ff);
	//getLine2(ff);
	int i;
	for (i = 0; i < 1600; i++) {
		//getLine2(ff);
		char* line1 = getLine2(ff);
		if(i<1500)
			continue;
		string* subs = split(line1, 9);
		//writeLine(fout, " "+i);
		cout<<endl<<i<<endl;
		writeLine(fout, subs[0].c_str());
		writeLine(fout, subs[3].c_str());
	//	cout << subs[3] << endl;
		char** all = checkSentence(subs[3].c_str());
		cout << "out" << endl;
		if (strlen(all[0]) > 0) {
	//		cout << all[0] << endl;

			string
					cmd =
							string("curl -d '") + string(all[0])
									+ string(
											"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline?semantics=drg'");
			cout<<cmd<<endl;
			string s = exec(cmd.c_str());
			usleep(1200 * 1000);
		//	cout << endl << endl << s << endl << endl;
			//writeLine(fout, "!.");
			writeLine(fout, s.c_str());

		}
		if (strlen(all[1]) > 0) {
			cout << all[1] << endl;

			string
					cmd =
							string("curl -d '") + string(all[1])
									+ string(
											"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline?semantics=drg'");
			cout<<cmd<<endl;
			string s = exec(cmd.c_str());
			usleep(1200 * 1000);
	//		cout << endl << endl << s << endl << endl;
			//writeLine(fout, "!.");
			writeLine(fout, s.c_str());
			//writeLine(fout, "!.");

		}
		if (strlen(all[2]) > 0) {
			cout << all[2] << endl;

			string
					cmd =
							string("curl -d '") + string(all[2])
									+ string(
											"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline?semantics=drg'");
			cout<<cmd<<endl;
			string s = exec(cmd.c_str());
			usleep(1200 * 1000);
	//		cout << endl << endl << s << endl << endl;
			//writeLine(fout, "!.");
			writeLine(fout, s.c_str());
			//writeLine(fout, "!.");

		}
		writeLine(fout, "!!.");

		writeLine(fout, subs[4].c_str());
		delete all;
		char** all2 = checkSentence(subs[4].c_str());
				cout << "out" << endl;
				if (strlen(all2[0]) > 0) {
		//cout << subs[4] << endl;
					string cmd
				= string("curl -d '") + string(all2[0])
						+ string(
								"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline?semantics=drg'");
		string s = exec(cmd.c_str());
		usleep(1500 * 1000);
		//writeLine(fout, "!.");
		writeLine(fout, s.c_str());
		//writeLine(fout, "!.");
		}

		if (strlen(all2[1]) > 0) {
			//cout << subs[4] << endl;
			string cmd
					= string("curl -d '") + string(all2[1])
							+ string(
									"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline?semantics=drg'");
			string s = exec(cmd.c_str());
			usleep(1500 * 1000);
			//writeLine(fout, "!.");
			writeLine(fout, s.c_str());
			//writeLine(fout, "!.");
		}
		if (strlen(all2[2]) > 0) {
			//cout << subs[4] << endl;
			string cmd
					= string("curl -d '") + string(all2[2])
							+ string(
									"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline?semantics=drg'");
			string s = exec(cmd.c_str());
			usleep(1500 * 1000);
			//writeLine(fout, "!.");
			writeLine(fout, s.c_str());
			//writeLine(fout, "!!!.");
		}
		writeLine(fout, "!!!.");
		//	writeLine(fout, getLine2(ff));//<<", ";
		//	writeLine(fout, getLine2(ff));//<<endl;
	}
}

void prepareMSDataset() {

	FILE *ff;
	ff = fopen("/research/NLP/MSRParaphraseCorpus/msr_paraphrase_train.txt",
			"rb");
	if (ff == NULL) {
		printf("Input file not found\n");
		return;
	}
	FILE *fout;
	fout = fopen("/research/NLP/paper2/exp/dataset_train_POS", "a");
	if (fout == NULL) {
		printf("output file not found\n");
		return;
	}
	cout << endl;
	int ii;
	getLine2(ff);
	for (ii = 0; ii < 1000; ii++) {

		char* line1 = getLine2(ff);
		if (strlen(line1) < 2)
			break;
		if (ii < 333)
			continue;
		cout << ii << endl;

		string* sts = split(line1, 9, 70);
		string label = sts[0];
		char* st1 = new char[sts[3].length()];
		strcpy(st1, sts[3].c_str());
		char* st2 = new char[sts[4].length()];
		strcpy(st2, sts[4].c_str());
		writeLine(fout, label.c_str());
		writeLine(fout, st1);
		//remove .
		for (int x = 0; x < strlen(st1) - 2; x++)
			if (st1[x] == '.')
				st1[x] = ' ';
		for (int x = strlen(st1) - 15; x < strlen(st1) - 2; x++)
			if (st1[x] == ',')
				st1[x] = ' ';
		string
				cmd =
						string("curl -d '") + string(st1)
								+ string(
										"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline'");
		cout << cmd << endl;
		string s = exec(cmd.c_str());
		usleep(1200 * 1000);
		cout << s << endl;
		string* sl = split(s, '\n', 30);
		int i = 0;
		while (sl[i][0] != 's')
			i++;
		cout << endl << endl << sl[i] << endl << endl;
		writeLine(fout, sl[i].c_str());
		cout << endl << endl << sl[i] << endl << endl;
		writeLine(fout, process(sl[i].c_str()));
		cout << endl << endl << sl[i] << endl << endl;
		writeLine(fout, st2);
		//remove .
		for (int x = 0; x < strlen(st2) - 2; x++)
			if (st2[x] == '.')
				st2[x] = ' ';
		for (int x = strlen(st2) - 15; x < strlen(st2) - 2; x++)
			if (st2[x] == ',')
				st2[x] = ' ';
		cmd
				= string("curl -d '") + string(st2)
						+ string(
								"' 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline'");
		cout << cmd << endl;
		s = exec(cmd.c_str());
		usleep(1500 * 1000);
		string* sl2 = split(s, '\n');
		i = 0;
		while (sl2[i][0] != 's')
			i++;
		//cout << endl << endl << sl2[i] << endl << endl;
		//Rst = process(sl[i]);
		writeLine(fout, sl2[i].c_str());
		writeLine(fout, process(sl2[i].c_str()));
		//writeLine(fout, getLine2(ff));//<<", ";
		//writeLine(fout, getLine2(ff));//<<endl;
	}
}

int main0() {
	/*Parser p;
	 char* st1 = "sem(1,[1001:[tok:'A',pos:'DT',lemma:a,namex:'O'],1002:[tok:smile,pos:'NN',lemma:smile,namex:'O'],1003:[tok: (is),pos:'VBZ',lemma:be,namex:'O'],1004:[tok:the,pos:'DT',lemma:the,namex:'O'],1005:[tok:expression,pos:'NN',lemma:expression,namex:'O'],1006:[tok:that,pos:'IN',lemma:that,namex:'O'],1007:[tok:you,pos:'PRP',lemma:you,namex:'O'],1008:[tok:have,pos:'VBP',lemma:have,namex:'O'],1009:[tok:on,pos:'IN',lemma:on,namex:'O'],1010:[tok:your,pos:'PRP$',lemma:your,namex:'O'],1011:[tok:face,pos:'NN',lemma:face,namex:'O'],1012:[tok:when,pos:'WRB',lemma:when,namex:'O'],1013:[tok:you,pos:'PRP',lemma:you,namex:'O'],1014:[tok:are,pos:'VBP',lemma:be,namex:'O'],1015:[tok:pleased,pos:'JJ',lemma:pleased,namex:'O'],1016:[tok:or,pos:'CC',lemma:or,namex:'O'],1017:[tok:amused,pos:'JJ',lemma:amused,namex:'O'],1018:[tok: (','),pos: (','),lemma: (','),namex:'O'],1019:[tok:or,pos:'CC',lemma:or,namex:'O'],1020:[tok:when,pos:'WRB',lemma:when,namex:'O'],1021:[tok:you,pos:'PRP',lemma:you,namex:'O'],1022:[tok:are,pos:'VBP',lemma:be,namex:'O'],1023:[tok:being,pos:'VBG',lemma:be,namex:'O'],1024:[tok:friendly,pos:'JJ',lemma:friendly,namex:'O'],1025:[tok:'.',pos:'.',lemma:'.',namex:'O']],merge(drs([[]:B,[]:C,[]:D,[]:E,[]:F,[]:G,[]:H,[]:I,[]:J,[1004]:K],[[1021]:pred(B,person,n,1),[1011]:pred(C,face,n,0),[]:rel(C,D,of,1),[1010]:pred(D,person,n,1),[1007]:pred(E,person,n,1),[1013]:pred(F,person,n,1),[1013]:pred(G,person,n,1),[1011]:pred(H,face,n,0),[]:rel(H,I,of,1),[1010]:pred(I,person,n,1),[1007]:pred(J,person,n,1),[1005]:pred(K,expression,n,0)]),drs([[]:L,[1001]:M],[[]:prop(L,drs([],[[1003]:eq(M,K),[1019]:or(drs([[]:N,[]:O,[1006]:P],[[]:prop(N,drs([],[[1016]:or(drs([[]:Q],[[]:rel(Q,G,experiencer,0),[1015]:pred(Q,pleased,a,0)]),drs([[]:R],[[]:rel(R,F,experiencer,0),[1017]:pred(R,amused,a,0)]))])),[1012]:rel(O,N,when,0),[1009]:rel(O,H,on,0),[]:rel(O,P,theme,0),[]:rel(O,J,agent,0),[1008]:pred(O,have,v,0),[]:eq(K,P)]),drs([[]:S,[]:T,[1006]:U],[[]:prop(S,drs([[]:V],[[]:rel(V,B,experiencer,0),[1024]:pred(V,friendly,a,0)])),[1020]:rel(T,S,when,0),[1009]:rel(T,C,on,0),[]:rel(T,U,theme,0),[]:rel(T,E,agent,0),[1008]:pred(T,have,v,0),[]:eq(K,U)]))])),[1002]:pred(M,smile,n,0)]))).";
	 char* str = "sem(1,[1001:[tok:'A',pos:'DT',lemma:a,namex:'O'],1002:[tok:rooster,pos:'NN',lemma:rooster,namex:'O'],1003:[tok: (is),pos:'VBZ',lemma:be,namex:'O'],1004:[tok:an,pos:'DT',lemma:an,namex:'O'],1005:[tok:adult,pos:'NN',lemma:adult,namex:'O'],1006:[tok:male,pos:'NN',lemma:male,namex:'O'],1007:[tok:chicken,pos:'NN',lemma:chicken,namex:'O'],1008:[tok:'.',pos:'.',lemma:'.',namex:'O']],drs([[]:B,[1001]:C],[[]:prop(B,drs([[]:D,[]:E,[1004]:F],[[1003]:eq(C,F),[1007]:pred(F,chicken,n,0),[]:rel(F,D,of,0),[1006]:pred(D,male,n,0),[]:rel(F,E,of,0),[1005]:pred(E,adult,n,0)])),[1002]:pred(C,rooster,n,0)])).";
	 string s;
	 cout<<process(str);
	 return 0;
	 //split(str,':');
	 for(int i=0; i<15; i++){
	 p.parse(st1);
	 p.parse(str);
	 }
	 */
	//prepareMSDataset();
	prepareMSRP();
}

