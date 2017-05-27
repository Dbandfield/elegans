#include "food.h"

extern ofVec2f petriPos;
extern float petriRad;
extern ofImage foodImage;
extern uint64_t curTime;
extern uint64_t prevTime;
extern uint64_t delta;

Food::Food() {}

Food::~Food() {}

void Food::setup(ofVec2f p)
{
	pos.set(p);
	heading = ofVec2f(1, 0);

	im = ofImage(foodImage);;
	im.resize(16, 16);
	im.setAnchorPoint(im.getWidth() / 2, im.getHeight() / 2);

	timer1 = 0;

	moveVel = 0; // movement velocity
	rotVel = 0;
	movAcc = 0.001;
	rotAcc = 0.1;

	target.set(pos);
}

void Food::update()
{
	timer1 += delta;
	/* ----- FROM ORG -----*/
	if (timer1 >= MAX_TIME_1)
	{
		timer1 = 0;

		float xpmin = pos.x - 10;
		float xpmax = pos.x + 10;
		float ypmin = pos.y - 10;
		float ypmax = pos.y + 10;

		ofVec2f ranV(ofRandom(xpmin, xpmax),
			ofRandom(ypmin, ypmax));

		/* Constrain */
		if (ranV.distance(petriPos) > petriRad)
		{
			ranV.interpolate(petriPos, 0.4);
		}

		target.set(ranV);

	}

	/* ------------------ */

	ofVec2f vToTarget(0, 0);
	vToTarget = target - pos;
	float angleToTarget = heading.angle(vToTarget);

	if (angleToTarget > 5)
	{
		if (rotVel < MAX_ROT_VEL)
		{
			rotVel += rotAcc;
		}

		heading.rotate(delta * rotVel);
	}
	else if (angleToTarget < 5)
	{

		if (rotVel < MAX_ROT_VEL)
		{
			rotVel += rotAcc;
		}

		heading.rotate(-(delta * rotVel));
	}
	else
	{
		rotVel = 0;
	}

	if (pos.distance(target) > TARGET_DIST)
	{
		if (moveVel < MAX_MOV_VEL)
		{
			moveVel += movAcc;
		}

		pos += heading * delta * moveVel;
	}
	else
	{
		moveVel = 0;
	}


}

void Food::draw()
{
	ofSetColor(ofColor(0, 0, 0, 255));
	im.draw(pos.x, pos.y);
	//ofPolyline l;
	//l.addVertex(pos);
	//l.lineTo(target);
	//l.draw();
}


ofVec2f Food::getPos()
{
	return pos;
}

ofVec2f Food::getTarget()
{
	return target;
}

void Food::consume()
{

}