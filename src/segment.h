/* segment of an organism*/

#pragma once

/* of incldes */
#include <ofVec2f.h>
#include <ofPath.h>
#include <ofPolyline.h>
#include <ofGraphics.h>
#include <ofImage.h>
#include <ofColor.h>


class Segment
{
public:

	Segment();
	~Segment();

	void setup(float size, ofVec2f p, bool male);

	void update();

	void draw();

	void pointAt(ofVec2f);

	void setTarget(ofVec2f gt);
	void setTargetDist(float f);

	ofVec2f getPos();
	ofVec2f getTarget();
	float getSize();

private:

	uint64_t timer;

	ofVec2f pos;
	float size;
	float moveVel; // movement velocity
	float rotVel; // rotation velocity
	float MAX_MOV_VEL = 0.05;
	float MAX_ROT_VEL = 5;
	float movAcc;
	float rotAcc;

	ofVec2f target;
	ofVec2f heading;

	float targetDist;

	ofImage im;
};
