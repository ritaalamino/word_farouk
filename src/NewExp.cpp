/*
 * NewExp.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: mamfarouk
 */
#include <iostream>
#include<string.h>
#include<sstream>
#include <cstdio>
#include <unistd.h>
#include <Util.h>

using namespace std;
/*
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
*/


std::string exec22(const char* cmd) {
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

Util utt;

//generate graph for new datasets sts
void generateGraph(char* fileName, int rowsNum){
cout<<"Start  **** \n"<<fileName;
	FILE *ff;
	ff = fopen(fileName, "rb");
	if (ff == NULL) {
		printf("Input file not found\n");
		return;
	}
	FILE *fout;
	char* oFileName = new char[200];
	strcpy(oFileName, fileName);
	strcat(oFileName, "-graph2.txt");
	fout = fopen( oFileName, "a");
	if (fout == NULL) {
		printf("output file not found\n");
		return;
	}
	FILE *gs;
	gs = fopen("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.gs.answers-forums.txt", "rb");
		if (gs == NULL) {
			printf("Input file not found\n");
			return;
		}

	cout << "READYYYY..." << endl;
	//getLine2(ff);
	//getLine2(ff);
	int i;
	char* num= new char[5];
	for (i = 0; i < rowsNum; i++) {
		//getLine2(ff);
		//cout<<i<<endl;

		char* line1 = utt.getLine(ff);
		char* str = utt.getLine(gs);
		if(strlen(str)<=0)
			continue;
	//	if(i<1000)
		//	continue;
		cout<<"results.... "<<i+1<<"  "<<line1<<endl;
		//continue;
		sprintf(num, "%d", i+1);
		utt.writeLine(fout, num);
		string* subs = utt.split(line1, 9, 20);
//		cout<<endl<<i<<endl;
		utt.writeLine(fout, subs[0].c_str());
	//	writeLine(fout, subs[1].c_str());
	//	cout << subs[3] << endl;
	//	char** all = chec6phkjkSentence(subs[3].c_str());
		cout << "out" << endl;
		if (strlen(subs[0].c_str()) > 0) {
	//		cout << all[0] << endl;
			string cmd =
							string("curl -d \"") + string(subs[0])
									+ string(
											"\" 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline?semantics=drg'");
			cout<<cmd<<endl;
			string s = exec22(cmd.c_str());
			usleep(1200 * 1000);
		//	cout << endl << endl << s << endl << endl;
			//writeLine(fout, "!.");
			utt.writeLine(fout, s.c_str());



		}
		utt.writeLine(fout, "!!.");

		utt.writeLine(fout, subs[1].c_str());
		//delete all;
		//char** all2 = checkSentence(subs[1].c_str());
				cout << "out" << endl;
				if (strlen(subs[1].c_str()) > 0) {
		//cout << subs[4] << endl;
					string cmd
				= string("curl -d \"") + string(subs[1])
						+ string(
								"\" 'http://gingerbeard.alwaysdata.net/candcapi/proxy.php/raw/pipeline?semantics=drg'");
		string s = exec22(cmd.c_str());
		usleep(1500 * 1000);
		//writeLine(fout, "!.");
		utt.writeLine(fout, s.c_str());
		//writeLine(fout, "!.");
		}
		utt.writeLine(fout, "!!!.");
		//	writeLine(fout, getLine2(ff));//<<", ";
		//	writeLine(fout, getLine2(ff));//<<endl;


	}

}
int maint(){
	cout<<"Start  ****00 \n";
	generateGraph("/research/NLP/sts datasets/2015/test_evaluation_task2a/STS.input.answers-forums.txt", 2000);
}
