#pragma once

#include <ofVec2f.h>
#include <ofAppRunner.h>
#include <ofColor.h>

#include <vector>
#include <string>
#include <sstream>

#include "segment.h"

// use vectors for segments, because over time organisms grow 
// and add new segments
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

	/* A position! A size (number of segments)! and a gender! 
		gender should be set to either MALE or FEMALE. If it is 
		set to NULL_GENDER (the default) then the gender is randomised 
		between MALE and FEMALE
	*/
	void setup(ofVec2f p, uint32_t numSeg, GENDER setGen=NULL_GENDER);

	/* give the organism a target to move towards. make sure 
	to call this in the ofApp update fn.  */
	void update(ofVec2f *t);

	/* put in the ofApp draw fn */
	void draw();

	/* This makes the orgnism grow by one segment */
	void grow();

	/* am I hungry? */
	bool getHungry();

	/* am i ready to repoduce? */
	bool getReproduce();

	/* Where am i? */
	ofVec2f getPos();

	/* Set to indicate that this should be removed */
	bool removeFlag;

	/* What gender am I? */
	GENDER getGender();

	void reproduce();

	/* Am i dying? */
	bool getDying();

	/* How big am I? (in segments) */
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

	/* How far apart re segments? */
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

	/* How many segments are needed before the organism
		is considered mature?
	*/
	int matureStage;


};
