#include "flag.h"

flag::flag() {}

void flag::setup(flagBackground _background, vector<flagLayer> _layers, string _country, int _count) {
	background = _background;
	layers = _layers;
	country = _country;
	count = _count;
	motif.load(MOTIFS_PATH + country + ".svg");
}

void flag::setup(flagBackground _background, vector<flagLayer> _layers, ofxSVG _motif) {
	background = _background;
	layers = _layers;
	motif = _motif;
}

flagBackground flag::getBackground() {
	return background;
}

vector<flagLayer> flag::getLayers() {
	return layers;
}

ofxSVG flag::getMotif() {
	return motif;
}