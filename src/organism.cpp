#include "organism.h"

/* The image that is displayed when this dies */
extern ofImage deathImage;
/* Current time this frame */
extern uint64_t curTime;
/* last frame */
extern uint64_t prevTime;
/* difference between current and last */
extern uint64_t delta;


Organism::Organism() :
	timerMove(0),
	timerRetarget(0),
	timerHunger(0),
	timerAnim(0),
	timerRemove(0)
{

}

Organism::~Organism()
{

}

void Organism::setup(ofVec2f p, uint32_t numSeg, GENDER setGender)
{
	pos.set(p);

	dying = false;
	resizeDir = 0;

	animIndex = 0;
	animDir = 0;

	removeFlag = false;

	/* 50% chance to be male or female if not specified */
	if (setGender == NULL_GENDER)
	{
		float ranGen = ofRandom(10.);
		if (ranGen < 5.)
		{
			gender = MALE;
		}
		else
		{
			gender = FEMALE;
		}
	}
	else
	{
		gender = setGender;
	}

	reproduceReady = false;

	matureStage = 4;

	rad = 16; // radius of segment
	inc = (rad + (rad / numSeg)) / numSeg; // how much to decrease radius by each seg
	for (size_t i = 0; i < numSeg; i++)
	{
		bool m = false;
		if (gender == MALE)
		{
			m = true;
		}
		segments.push_back(Segment());
		segments.back().setup(rad, ofVec2f(pos.x + (SEG_DISTANCE * i), pos.y), m);

		rad -= inc;
	}

	// To move, give the initial segment a target
	// the rest will follow one another in a line
	segments.begin()->setTarget(ofVec2f(500, 500)); // arbitrary position

	hungry = false;

	timerSex = 0;
	timerStarvation = 0;
	timerDeath = 0;

	starved = false;

	deathIm = deathImage;
}

void Organism::update(ofVec2f *t)
{

	timerMove			+= delta;
	timerRetarget		+= delta;

	
	/* death sequence if at end of life*/
	if (timerDeath >= maxTimeDeath || starved)
	{
		dying = true;

		timerRemove += delta;

		if (timerRemove >= MAX_TIME_REMOVE)
		{
			removeFlag = true;
		}

		for (iSeg itr = segments.begin(); itr != segments.end(); itr++)
		{
			itr->setTargetDist(1);
			itr->setTarget(segments.begin()->getPos());
			itr->update();
		}
	}
	else
	{
		timerDeath += delta;
		timerStarvation += delta;

		if (timerStarvation >= maxTimeStarvation)
		{
			starved = true;
		}

		if (timerMove >= MAX_TIME_MOVE)
		{
			timerMove = 0;
		}

		if (timerRetarget >= MAX_TIME_RETARGET)
		{
			timerRetarget = 0;

			/* if given explicit target by caller */
			if (t != nullptr)
			{
				segments.begin()->setTarget(*t);

			}
			else // choose random target
			{
				float xpmin = segments.begin()->getTarget().x - 100;
				float xpmax = segments.begin()->getTarget().x + 100;
				float ypmin = segments.begin()->getTarget().y - 100;
				float ypmax = segments.begin()->getTarget().y + 100;

				ofVec2f ranV(ofRandom(xpmin, xpmax),
					ofRandom(ypmin, ypmax));

				/* Constrain to bounds of petri dish*/
				if (ranV.distance(petriPos) > petriRad)
				{
					ranV.interpolate(petriPos, 0.4);
				}

				segments.begin()->setTarget(ranV);

			}
			for (iSeg itr = segments.begin() + 1; itr != segments.end(); itr++)
			{
				itr->setTarget((itr - 1)->getPos());
			}
		}

		/* HUNGER + GROWTH */
	
		timerHunger += delta;

		if (timerHunger >= MAX_TIME_HUNGER)
		{
			timerHunger = 0;
			hungry = true;
		}
		

		/* SEX */
		if (segments.size() >= matureStage && !reproduceReady)
		{
			timerSex += delta;

			if (timerSex >= maxTimeSex)
			{
				timerSex = 0;
				// ofApp will handle the reproduction
				// so just set flag
				reproduceReady = true;
			}
		}

		segments.begin()->update();

		/* Each segment follow the one before it */
		for (iSeg itr = segments.begin() + 1; itr != segments.end(); itr++)
		{
			itr->setTarget((itr - 1)->getPos());

			itr->update();
		}
	}


}

void Organism::draw()
{
	// A cross is displayed if dying
	if (dying)
	{
		std::cout << segments.begin()->getPos().x << " " << segments.begin()->getPos().y << std::endl;
		deathIm.draw(segments.begin()->getPos());
	}

	// An orgaism is made up of multiple segments
	for (iSeg itr = segments.begin(); itr != segments.end(); itr++)
	{
		itr->draw();
	}
}

void Organism::grow()
{
	/* Reset hnger cycle */
	hungry = false;
	timerHunger = 0;
	timerStarvation = 0;

	float newSize = segments.begin()->getSize() + inc;
	ofVec2f newPos = segments.begin()->getPos();

	bool m = false;
	if (gender == MALE)
	{
		m = true;
	}
	
	segments.insert(segments.begin(), Segment());
	segments[0].setup(newSize, newPos, m);
}

bool Organism::getHungry()
{
	return hungry;
}

ofVec2f Organism::getPos()
{
	return segments.begin()->getPos();
}

GENDER Organism::getGender()
{
	return gender;
}

bool Organism::getReproduce()
{
	return reproduceReady;
}

void Organism::reproduce()
{
	reproduceReady = false;
}

int Organism::getSize()
{
	return segments.size();
}

int Organism::getMatureStage()
{
	return matureStage;
}

bool Organism::getDying()
{
	return dying;
}

std::string Organism::getName()
{
	return name;
}