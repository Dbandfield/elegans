#pragma once

#include <ofTrueTypeFont.h>
#include <ofVec2f.h>
#include <ofGraphics.h>
#include <ofColor.h>

#include <string>

class LogEntry
{
public:
	LogEntry();
	~LogEntry();

	void setup(ofVec2f p, std::string t, int fSize, int lSize);
	void update();
	void draw();

	void setPosition(ofVec2f v);
	ofVec2f getPosition();

private:

	ofTrueTypeFont font;
	std::string text;
	ofVec2f pos;
	float height;
	float fontSize;
	float lineSize;

};
