#pragma once

#include "ofMain.h"

#include <vector>
#include <string>
#include <sstream>

#include "organism.h"
#include "food.h"
#include "petri.h"

typedef std::vector<Organism> vOrg;
typedef std::vector<Organism>::iterator iOrg;
typedef std::vector<Food> vFood;
typedef std::vector<Food>::iterator iFood;

class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

private:

	unsigned int wormNum;

	void reproduce(Organism *o1);

	vOrg organisms;
	vFood food;
	Petri petri;

	const int NUM_START_ORGS = 4;
	const int NUM_START_FOOD = 7;
	const int MAX_FOOD = 7;
	const int MAX_ORG = 3;

	uint64_t timerRespawnFood;

	long long maxTimeRespawnFood = 5000;

	bool pause;

	struct NewOrgSettings
	{
		int createOrg;
		std::vector<ofVec2f> pos;
		std::vector<ofColor> col;
		std::vector<int> segs;
	} newOrgSettings;
		
};
