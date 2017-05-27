#pragma once

#include <ofVec2f.h>
#include <ofPath.h>
#include <ofAppRunner.h>
#include <ofImage.h>
#include <ofGraphics.h>



class Food
{
public:

	Food();
	~Food();

	void setup(ofVec2f p);

	void update();

	void draw();

	ofVec2f getPos();
	ofVec2f getTarget();

	void consume();

private:

	float SIZE = 10;

	uint64_t timer1;

	uint64_t MAX_TIME_1 = 10;

	ofVec2f pos;
	float size;
	float moveVel; // movement velocity
	float rotVel; // rotation velocity
	float MAX_MOV_VEL = 0.1;
	float MAX_ROT_VEL = 5;
	float movAcc;
	float rotAcc;

	ofVec2f target;
	ofVec2f heading;

	ofImage im;

	float TARGET_DIST = 0;

};
