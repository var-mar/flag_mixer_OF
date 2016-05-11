#include "flagDrawer.h"

flagDrawer::flagDrawer() {}

void flagDrawer::setup(flag* _flag, float _x, float _y, float _w, float _h)
{
	mixedFlag = _flag;
	x = _x; y = _y; w = _w; h = _h;
	canvas.allocate(w, h, GL_RGBA);
}

void flagDrawer::draw() {
	canvas.begin();
		ofClear(255, 255, 255);
		drawBackground(mixedFlag->getBackground());
		for (int i = 0; i < mixedFlag->getLayers().size(); i++) {
			drawLayer(mixedFlag->getLayers()[i]);
		}
		drawMotif(mixedFlag->getMotif());
	canvas.end();
	canvas.draw(x,y);
}

void flagDrawer::drawBackground(flagBackground _fB){
	int type = _fB.object.type;
	int strokeWeight = _fB.object.strokeWeight;
	ofColor strokeColor = _fB.object.strokeColor;
	vector<ofColor> colors = _fB.object.colors;
	vector<int> symmetry = _fB.symmetry;

	ofFill();
	int numStrips = symmetry.size();
	for (int i = 0; i < numStrips; i++) {
		static float step = 0;
		switch (type) {
		case 0: //HORIZONTAL
			if (i == 0) step = 0;
			ofSetColor(colors[i%colors.size()]);
			ofDrawRectangle(0, step, FLAG_WIDTH, FLAG_HEIGHT*(float)symmetry[i%symmetry.size()] / 100);
			step += FLAG_HEIGHT*(float)symmetry[i%symmetry.size()] / 100;
			break;
		case 1: //VERTICAL
			if (i == 0) step = 0;
			ofSetColor(colors[i%colors.size()]);
			ofDrawRectangle(step, 0, FLAG_WIDTH*(float)symmetry[i%symmetry.size()] / 100, FLAG_HEIGHT);
			step += FLAG_WIDTH*(float)symmetry[i%symmetry.size()] / 100;
			break;
		case 2: //DIAGONAL_A
		{
			ofSetColor(colors[(colors.size() - 1 - i) % colors.size()]);
			if (i == 0) step = 1;
			ofPoint a = ofPoint(0, FLAG_HEIGHT);
			ofPoint b = ofPoint(0, (float)FLAG_HEIGHT - 2 * FLAG_HEIGHT*step);
			ofPoint c = ofPoint((float)FLAG_WIDTH * 2 * step, FLAG_HEIGHT);
			ofDrawTriangle(a, b, c);
			step -= (float)symmetry[(symmetry.size() - 1 - i) % symmetry.size()] / 100;
			break;
		}
		case 3: //DIAGONAL_B
		{
			ofSetColor(colors[(colors.size() - 1 - i) % colors.size()]);
			if (i == 0) step = 1;
			ofPoint a = ofPoint(FLAG_WIDTH, FLAG_HEIGHT);
			ofPoint b = ofPoint(FLAG_WIDTH, (float)FLAG_HEIGHT - 2 * FLAG_HEIGHT*step);
			ofPoint c = ofPoint(FLAG_WIDTH - (float)FLAG_WIDTH * 2 * step, FLAG_HEIGHT);
			ofDrawTriangle(a, b, c);
			step -= (float)symmetry[(symmetry.size() - 1 - i) % symmetry.size()] / 100;
			break;
		}
		}
	}
	if (strokeWeight > 0) {
		ofFill();
		ofSetColor(strokeColor);
		ofDrawRectangle(0, 0, FLAG_WIDTH, strokeWeight); //Up border
		ofDrawRectangle(0, FLAG_HEIGHT - strokeWeight, FLAG_WIDTH, strokeWeight); //Down border
		ofDrawRectangle(0, 0, strokeWeight, FLAG_HEIGHT); //Left border
		ofDrawRectangle(FLAG_WIDTH - strokeWeight, 0, strokeWeight, FLAG_HEIGHT); //Right border
	}
}

void flagDrawer::drawLayer(flagLayer _fL) {

	int type = _fL.object.type;
	int strokeWeight = _fL.object.strokeWeight;
	ofColor strokeColor = _fL.object.strokeColor;
	vector<ofColor> colors = _fL.object.colors;
	int height = _fL.height;
	int scale = _fL.scale;
	ofPoint center = _fL.center;

	switch (type) {
	case 0: //SQUARE
		ofSetColor(strokeWeight > 0 ? strokeColor : colors[0]);
		ofRect(center.x - scale*.5f, center.y - (scale + height)*.5f, scale, scale + height);
		if (strokeWeight > 0) {
			ofSetColor(colors[0]);
			ofRect(center.x - scale*.5f + strokeWeight, center.y - (scale + height)*.5f + strokeWeight, scale - strokeWeight * 2, scale + height - strokeWeight * 2);
		}
		break;
	case 1: //TRIANGLE
	{
		ofPoint v1 = ofPoint(0, 1).normalize();
		float angle = (float)TWO_PI / 3; //120
		ofPoint v2 = ofPoint(v1.x*cos(angle) - v1.y*sin(angle), v1.x*sin(angle) + v1.y*cos(angle));
		angle = (float)(TWO_PI / 3) * 2; //240
		ofPoint v3 = ofPoint(v1.x*cos(angle) - v1.y*sin(angle), v1.x*sin(angle) + v1.y*cos(angle));
		ofPoint p1, p2, p3;
		p1 = v1; p2 = v2; p3 = v3;
		p1 *= scale + height; p2 *= scale; p3 *= scale;
		p1 += center; p2 += center; p3 += center;
		ofSetColor(strokeWeight > 0 ? strokeColor : colors[0]);
		ofDrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
		if (strokeWeight > 0) {
			ofSetColor(colors[0]);
			v1 = ofPoint(0, (float)(1 - (float)strokeWeight / 500));
			angle = (float)TWO_PI / 3; //120
			v2 = ofPoint(v1.x*cos(angle) - v1.y*sin(angle), v1.x*sin(angle) + v1.y*cos(angle));
			angle = (float)(TWO_PI / 3) * 2;
			v3 = ofPoint(v1.x*cos(angle) - v1.y*sin(angle), v1.x*sin(angle) + v1.y*cos(angle));
			p1 = v1; p2 = v2; p3 = v3;
			p1 *= scale + height; p2 *= scale; p3 *= scale;
			p1 += center; p2 += center; p3 += center;
			ofDrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
		}
		break;
	}
	case 2: //CIRCLE
		ofSetColor(strokeWeight > 0 ? strokeColor : colors[0]);
		ofEllipse(center, scale, scale + height);
		if (strokeWeight > 0) {
			ofSetColor(colors[0]);
			ofEllipse(center, scale - strokeWeight, scale + height - strokeWeight);
		}
		break;
	case 3: //CROSS
		ofSetColor(strokeWeight > 0 ? strokeColor : colors[0]);
		ofRect(center.x - scale*.5f, center.y - (scale + height)*.5f, scale, scale + height);
		ofPushMatrix();
		ofTranslate(center.x, center.y, 0);
		ofRotate(90);
		ofPushMatrix();
		ofTranslate(-center.x, -center.y, 0);
		ofSetColor(strokeWeight > 0 ? strokeColor : colors[0]);
		ofRect(center.x - scale*.5f, center.y - (scale + height)*.5f, scale, scale + height);
		ofPopMatrix();
		ofPopMatrix();
		if (strokeWeight > 0) {
			ofSetColor(colors[0]);
			ofRect(center.x - scale*.5f + strokeWeight, center.y - (scale + height)*.5f + strokeWeight, scale - strokeWeight * 2, scale + height - strokeWeight * 2);
		}
		ofPushMatrix();
		ofTranslate(center.x, center.y, 0);
		ofRotate(90);
		ofPushMatrix();
		ofTranslate(-center.x, -center.y, 0);
		if (strokeWeight > 0) {
			ofSetColor(colors[0]);
			ofRect(center.x - scale*.5f + strokeWeight, center.y - (scale + height)*.5f + strokeWeight, scale - strokeWeight * 2, scale + height - strokeWeight * 2);
		}
		ofPopMatrix();
		ofPopMatrix();
		break;
	}
}

void flagDrawer::drawMotif(ofxSVG _motif) {
	_motif.draw();
}

