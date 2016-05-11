#pragma once
#include "flag.h"
#include "settings.h"

class flagDrawer {
public:
	flagDrawer();
	void setup(flag* _flag, float _x, float _y, float _w, float _h);
	void draw();
private:
	void drawBackground(flagBackground _flagBackground);
	void drawLayer(flagLayer _flagLayer);
	void drawMotif(ofxSVG _motif);
	flag* mixedFlag;
	flagBackground bg;
	ofFbo canvas;
	float x, y, w, h;
};