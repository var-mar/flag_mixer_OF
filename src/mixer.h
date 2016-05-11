#pragma once
#include "flag.h"

class mixer {
public:
	mixer();
	void setup(vector<flag>* _flag);
	flag* getMixedFlag();
private:
	vector<flag>* flags;
	flag* mixedFlag;
};
