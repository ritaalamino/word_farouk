class WordModel{
public:
	int size;
	long long words;
	  float *M;
	  char *vocab;
	  int type;
	  float** mat;
	  char** voc;
	WordModel(char* modelFile, int type);
	float* getVector(char*, bool&) const;
	float* getDeepVector(char*, bool&) const;
	bool initialize(char*);
	bool load(char*);
};
