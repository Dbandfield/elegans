#include "organism.h"

extern ofImage deathImage;
extern uint64_t curTime;
extern uint64_t prevTime;
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

	rad = 16;
	inc = (rad + (rad / numSeg)) / numSeg;
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

	segments.begin()->setTarget(ofVec2f(500, 500));

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

		//timerAnim	+= delta;
		timerRemove += delta;

		if (timerRemove >= MAX_TIME_REMOVE)
		{
			removeFlag = true;
		}
		/*
		if (timerAnim >= MAX_TIME_ANIM)
		{
			timerAnim = 0;
			//animation 
			if (animDir == 0)
			{
				animIndex++;
				if (animIndex >= 1)
				{
					animDir = 1;
				}
			}
			else
			{
				animIndex--;
				if (animIndex <= 1)
				{
					animDir = 0;
				}
			}
			deathIm = deathImage[animIndex];*/

			/*if (resizeDir == 0)
			{
				deathImSize++;
				deathIm = deathImage[animIndex];
				deathIm.resize(deathImSize, deathImSize);
				deathIm.setAnchorPoint(deathIm.getWidth() / 2, deathIm.getHeight() / 2);

				if (deathImSize >= deathImMaxSize)
				{
					resizeDir = 1;
				}
			}
			else
			{
				deathImSize--;
				deathIm = deathImage[animIndex];
				deathIm.resize(deathImSize, deathImSize);
				deathIm.setAnchorPoint(deathIm.getWidth() / 2, deathIm.getHeight() / 2);

				if (deathImSize <= 5)
				{
					resizeDir = 0;
				}
			}
		}*/

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

				/* Constrain */
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
				reproduceReady = true;
			}
		}

		segments.begin()->update();

		for (iSeg itr = segments.begin() + 1; itr != segments.end(); itr++)
		{
			itr->setTarget((itr - 1)->getPos());

			itr->update();
		}
	}


}

void Organism::draw()
{
	if (dying)
	{
		std::cout << segments.begin()->getPos().x << " " << segments.begin()->getPos().y << std::endl;
		deathIm.draw(segments.begin()->getPos());
	}
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
	ofVec2f newPos = segments.begin()->getPos();// *SEG_DISTANCE;

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