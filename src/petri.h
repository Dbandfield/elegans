#pragma once

#include <ofAppRunner.h>
#include <ofPath.h>
#include <ofVec2f.h>

/* Simple class to represent the background */

class Petri
{

public:

	Petri();
	~Petri();

	void setup();

	void draw();

	void update();

	ofVec2f getPos();

	float getRad();


private:

	ofPath circle;
	float circleRad;
	ofVec2f pos;

};
