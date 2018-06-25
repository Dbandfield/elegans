#include "ofApp.h"

ofImage orgImage;
ofImage foodImage;
ofImage deathImage;
ofImage maleImage;

uint64_t curTime =0;
uint64_t prevTime = 0;
uint64_t delta = 0;
//--------------------------------------------------------------
void ofApp::setup()
{
	pause = false; 

	// Because I haven't had time to go back and refactor
	// since differentiating male and female organisms,
	// the image for femaile organisms is referred to as 
	// orgImage while the male image is maleImage
	orgImage.load("org.png");
	foodImage.load("food.png");
	maleImage.load("male.png");
	deathImage.load("death.png");

	deathImage.resize(128, 128);
	deathImage.setAnchorPoint(deathImage.getWidth() / 2, deathImage.getHeight() / 2);
	
	ofSetBackgroundColor(ofColor(20, 20, 20, 1));

	timerRespawnFood = 0;
	curTime = ofGetElapsedTimeMillis();
	prevTime = curTime;
	delta = 0;
	maxTimeRespawnFood = 5000;

	petri.setup();

	// Make equal number of male and female organisms
	for (size_t i = 0; i < NUM_START_ORGS/2; i++)
	{
		organisms.push_back(Organism());
		organisms.back().setup(petri.getPos(), 3, MALE);
	}
	for (size_t i = 0; i < NUM_START_ORGS / 2; i++)
	{
		organisms.push_back(Organism());
		organisms.back().setup(petri.getPos(), 3, FEMALE);
	}

	// put food in random positions, but shift towards
	// centre if they go outside petri bounds

	for (size_t i = 0; i < NUM_START_FOOD; i++)
	{
		food.push_back(Food());

		ofVec2f ranV(ofRandom(ofGetWidth()),
						ofRandom(ofGetHeight()));
		if (ranV.distance(petri.getPos()) > petri.getRad())
		{
			ranV.interpolate(petri.getPos(), 0.6);
		}

		food.back().setup(ranV);
	}

	newOrgSettings.createOrg = 0;


}

//--------------------------------------------------------------
void ofApp::update() 
{
	curTime = ofGetElapsedTimeMillis();
	delta = curTime - prevTime;
	prevTime = curTime;

	if (!pause)
	{
		
		petri.update();

		// One or less organisms??? The population will die out!
		if (organisms.size() <= 1)
		{
			// So we interfere with nature and add some more
			for (size_t i = 0; i < NUM_START_ORGS / 2; i++)
			{
				organisms.push_back(Organism());
				organisms.back().setup(petri.getPos(), 3, MALE);
			}
			for (size_t i = 0; i < NUM_START_ORGS / 2; i++)
			{
				organisms.push_back(Organism());
				organisms.back().setup(petri.getPos(), 3, FEMALE);
			}
		}

		/* respawn food if needed */
		if (food.size() < MAX_FOOD)
		{
			timerRespawnFood += delta;

			if (timerRespawnFood >= maxTimeRespawnFood + ofRandom(-(maxTimeRespawnFood / 2), (maxTimeRespawnFood / 2)))
			{
				timerRespawnFood = 0;
				food.push_back(Food());
				ofVec2f newPos;
				ofVec2f rDir(1, 0);
				newPos.set(petri.getPos());
				float rAngle = ofRandom(0, 360);
				float rDist = ofRandom(0, petri.getRad());
				rDir.rotate(rAngle);
				rDir *= rDist;
				newPos += rDir;
				food.back().setup(newPos);
			}
		}

		/* check if ready for removal. This happens after an organism has 
			gone through its dying phase */
		for (iOrg itro = organisms.begin(); itro != organisms.end(); itro++)
		{
			if (itro->removeFlag)
			{
				organisms.erase(itro);
				break;
			}
		}


		/* Go through each organism */
		for (iOrg itro = organisms.begin(); itro != organisms.end(); itro++)
		{
			/* if org is hungry */
			if (itro->getHungry())
			{
				/* If some food exists */
				if (food.size() > 0)
				{
					bool updated = false;
					/* go through each food */
					for (iFood itrf = food.begin(); itrf != food.end(); itrf++)
					{
						/* see if it is close enough to be targetted */
						float d = itro->getPos().distance(itrf->getPos());
						if (d < petri.getRad() / 2)
						{
							ofVec2f vc = itrf->getPos();
							itro->update(&vc);
							updated = true;

							// close enough to eat food!
							if (d < 50)
							{
								itro->grow(); // the organism grows ...
								itrf->consume(); // ... and the food is consumed ...
								food.erase(itrf); // .. and disappears
								
							}
							break;
						}
					}
					if(!updated) itro->update(nullptr); // no target
				}
				else
				{
					itro->update(nullptr); // no target
				}

			}
			/* if not hungry, check if ready to reproduce 
				(ie. an org won't reproduce if it is hungry.) */
			else if (itro->getReproduce())
			{
				bool updated = false;
				for (iOrg itro2 = organisms.begin(); itro2 != organisms.end(); itro2++)
				{
					if (itro != itro2 && // is different org
						itro->getGender() != itro2->getGender() && //is different gender
						itro2->getReproduce() && // is ready
						!itro2->getDying() //is not dying
						)
					{
						float d = itro->getPos().distance(itro2->getPos());
						if (d < petri.getRad() / 2)
						{
							if (itro2->getSize() >= itro2->getMatureStage())
							{
								ofVec2f vc = itro2->getPos();
								itro->update(&vc);
								updated = true;

								if (d < 50)
								{
									
									itro->reproduce();
									itro2->reproduce();
									reproduce(&(*itro));

								}
								break;
							}

						}
					}
				}

				if (!updated) itro->update(nullptr);
			}
			else
			{
				itro->update(nullptr);
			}
		}

		for (iFood itr = food.begin(); itr != food.end(); itr++)
		{
			itr->update();
		}
	}

	/* create orgs */

	if (newOrgSettings.createOrg > 0)
	{
		for (int i = 0; i < newOrgSettings.createOrg; i++)
		{
			organisms.push_back(Organism());
			organisms.back().setup(newOrgSettings.pos[i], 
									newOrgSettings.segs[i]);
		}

		newOrgSettings.createOrg = 0;
		newOrgSettings.segs.clear();
		newOrgSettings.pos.clear();
	}

}

//--------------------------------------------------------------
void ofApp::draw()
{
	petri.draw();

	for (iOrg itr = organisms.begin(); itr != organisms.end(); itr++)
	{
		itr->draw();
	}

	for (iFood itr = food.begin(); itr != food.end(); itr++)
	{
		itr->draw();
	}


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == 'p')
	{
		pause = !pause;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::reproduce(Organism *o1)
{

	ofVec2f posi = o1->getPos();

	newOrgSettings.createOrg++;
	newOrgSettings.pos.push_back(posi);
	newOrgSettings.segs.push_back(3);
}


