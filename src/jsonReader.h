#pragma once
#include "ofxJSON.h"
#include "flag.h"

struct country {
	string name;
	int count;
};

class jsonReader {
public:
	jsonReader();
	vector<flag>getData();
private:
	bool setCountryData();
	void setFlags();
	flag createFlag(country _country);
	bool openFile(ofxJSONElement& _file, string _name, string _path);
	flagBackground loadFlagBackground(country _country);
	flagLayer loadFlagLayer(country _country, int _index = -1);
	flagObject loadFlagObject(country _country, int _index = -1);
	ofColor getColorFromInt(int _int);
	void clearData();
	
	ofxJSONElement countriesFile, flagsFile;
	vector<country> countryData;
	vector<flag> flags;
};