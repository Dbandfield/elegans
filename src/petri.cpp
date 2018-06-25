#include "petri.h"

Petri::Petri() {}
Petri::~Petri() {}

ofVec2f petriPos;
float petriRad;

void Petri::setup()
{
	circle.setCircleResolution(50);
	/*float w = ofGetWidth();
	float h = ofGetHeight();
	float min = h < w ? h : w;
	circleRad = (min / 2) - 20;*/
	circleRad = 300;
	circle.circle(ofVec2f(0, 0), circleRad);
	//pos = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
	pos = ofVec2f(300, 300);
	circle.setColor(ofColor(255, 255, 255, 255));

	petriPos.set(pos);
	petriRad = circleRad;
}

void Petri::update()
{

}

void Petri::draw()
{
	circle.draw(pos.x, pos.y);
}

ofVec2f Petri::getPos()
{
	return pos;
}

float Petri::getRad()
{
	return circleRad;
}