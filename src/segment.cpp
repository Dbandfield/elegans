#include "segment.h"

extern ofImage orgImage;
extern ofImage maleImage;

extern uint64_t curTime;
extern uint64_t prevTime;
extern uint64_t delta;

Segment::Segment() {}

Segment::~Segment() {}

void Segment::setup(float sz, ofVec2f p, bool male)
{

	size = sz;
	targetDist = size * 1.3;
	pos.set(p);
	heading = ofVec2f(1, 0);

	if (!male)
	{
		im = ofImage(orgImage);
	}
	else
	{
		im = ofImage(maleImage);
	}

	im.resize(size, size);
	im.setAnchorPoint(im.getWidth() / 2, im.getHeight() / 2);

	timer = 0;

	moveVel = 0; // movement velocity
	rotVel = 0;
	movAcc = 0.001;
	rotAcc = 0.1;
}

void Segment::update()
{
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
	else if(angleToTarget < 5)
	{

		if (rotVel < MAX_ROT_VEL)
		{
			rotVel += rotAcc;
		}

		heading.rotate(-(delta * rotVel));
	}
	else
	{
		//rotVel = 0;
	}

	if (pos.distance(target) > targetDist)
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

void Segment::draw()
{
	im.draw(pos.x, pos.y);
	//ofPolyline l;
	//l.addVertex(pos);
	//l.lineTo(target);
	//l.draw();
}

void Segment::pointAt(ofVec2f)
{

}

void Segment::setTarget(ofVec2f t)
{
	target.set(t);
}

ofVec2f Segment::getPos()
{
	return pos;
}

ofVec2f Segment::getTarget()
{
	return target;
}

float Segment::getSize()
{
	return size;
}

void Segment::setTargetDist(float f)
{
	targetDist = f;
}