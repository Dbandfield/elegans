#pragma once

#include <ofVec2f.h>
#include <ofAppRunner.h>
#include <ofColor.h>

#include <vector>
#include <string>
#include <sstream>

#include "segment.h"

typedef std::vector<Segment> vSeg;
typedef std::vector<Segment>::iterator iSeg;

extern ofVec2f petriPos;
extern float petriRad;

enum GENDER
{
	NULL_GENDER,
	FEMALE,
	MALE
};

class Organism
{
public:

	Organism();
	~Organism();

	void setup(ofVec2f p, uint32_t numSeg, GENDER setGen=NULL_GENDER);

	void update(ofVec2f *t);

	void draw();

	void grow();

	bool getHungry();

	bool getReproduce();

	ofVec2f getPos();

	bool removeFlag;

	GENDER getGender();

	void reproduce();

	bool getDying();

	int getSize();

	int getMatureStage();

	std::string getName();

private:

	std::string name;

	bool starved;

	GENDER gender;
	float rad;
	float inc;

	ofVec2f pos;

	vSeg segments;

	float SEG_DISTANCE = 30;

	uint64_t timerMove;
	uint64_t timerRetarget;
	uint64_t timerHunger;
	uint64_t timerAnim;
	uint64_t timerRemove;
	uint64_t timerSex;
	uint64_t timerStarvation;
	uint64_t timerDeath;

	uint64_t MAX_TIME_MOVE = 1000;
	uint64_t MAX_TIME_RETARGET = 1000;
	uint64_t MAX_TIME_HUNGER = 10000;
	uint64_t MAX_TIME_ANIM = 50;
	uint64_t MAX_TIME_REMOVE = 5000;
	uint64_t maxTimeSex = 20000;
	uint64_t maxTimeStarvation = 20000;
	uint64_t maxTimeDeath = 120000;

	bool hungry;
	bool reproduceReady;


	ofImage deathIm;
	float deathImSize;
	float deathImMaxSize = 256;
	bool dying;

	int animIndex;
	int animDir;
	int resizeDir;

	int matureStage;


};
