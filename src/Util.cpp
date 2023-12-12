/*
 * Util.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: mamfarouk
 */
#include "Util.h"
#include<math.h>
#include<sstream>
char* Util::getLine(FILE* f){
	char* l = new char[850];
	int i=0;
	while(1){
		l[i] = fgetc(f);
		if(l[i] == '\n' || feof(f))
			break;
		i++;
	}
	l[i] = '\0';
	//cout<<i<<endl;
	//cout<<&l<<"    "<<*l<<endl;
	return l;
}
string Util::getStringLine(FILE* f){
	char* l = getLine(f);
//	int q = strlen(l);
//	char* tmp = new char[q];
//	for(int i=0; i< strlen(l); i++)
//		tmp[i] = l[i];
	string s = l;
	delete l;
	return s;
}
void Util::writeLine(FILE* f,const char*line ){
	fprintf(f,"%s\n",line);
	fflush(f);
}
void Util::writeToFile(FILE* f,const char*line ){
	fprintf(f,"%s",line);
}
string* Util::split(char* str, char del, int max=20){
	string item;
	//cout<<str<<endl;
	stringstream ss(str);
	string* res = new string[max];
	//cout<<"iner test "<< str<<endl;
	int i=0;
	//int start =0;
	while(std::getline(ss, item, del) && i<max)
	{
		//cout<<"iner test 00  "<< i<<endl;
		if(item.length() <= 0)
			continue;
		res[i++]=item;
		//start += item.size()+1;
		//cout<<"iner testp "<<item<< i<<"  ;;; "<<endl;
	}
	//cout<<i<<":::::;"<<endl;
	string* final = new string[i+1];
	for(int j=0; j<i; j++)
		final[j] = res[j];
	final[i][0]='\0';
	//cout<<endl<<i<<endl;
	delete[] res;
	//cout<<"kmkmk "<<final[0]<<endl;
	return final;
}
double Util::calcPearson(float x[], float y[], int size){
	double sumXY=0, sumX2=0, sumY2=0, sumX=0, sumY=0;
	for(int i=0; i< size; i++){
		sumXY += x[i]*y[i];
		sumX2 += x[i]*x[i];
		sumY2 += y[i]*y[i];
		sumX += x[i];
		sumY += y[i];
	}
	double p = (size*sumXY - sumX*sumY) / (sqrt(size*sumX2 - sumX*sumX) * sqrt(size*sumY2 - sumY*sumY));
	return p;
}
double Util::stringSim(const std::string &s1, const std::string &s2)
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
/*
string Util::exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
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
*/
