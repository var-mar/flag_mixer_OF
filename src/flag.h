#pragma once
#include "ofMain.h"
#include "ofxSVG.h"
#include "settings.h"

struct flagObject{
	vector<ofColor> colors;
	ofColor strokeColor;
	int strokeWeight;
	int type;
};

struct flagBackground {
	flagObject object;
	vector<int>symmetry;
};

struct flagLayer {
	flagObject object;
	int angle;
	int height;
	int scale;
	ofPoint center;
};

class flag {
public:
	flag();
	void setup(flagBackground _background, vector<flagLayer> _layers, ofxSVG _motif);
	void setup(flagBackground _background, vector<flagLayer> _layers, string _name, int _count);
	flagBackground getBackground();
	vector<flagLayer> getLayers();
	ofxSVG getMotif();

private:
	flagBackground background;
	vector<flagLayer> layers;
	string country;
	int count;
	ofxSVG motif;
};