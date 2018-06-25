#include "log-entry.h"

LogEntry::LogEntry(){}
LogEntry::~LogEntry() {};

void LogEntry::setup(ofVec2f p, std::string t, int fSize, int lSize)
{
	fontSize = fSize;
	lineSize = lSize;
	pos.set(p);
	font.load("consola.ttf", fontSize);
	height = lineSize;
	text = t;
}

void LogEntry::update()
{

}

void LogEntry::draw()
{
	ofSetColor(ofColor(255, 255, 255));
	font.drawString(text, pos.x, pos.y);
}

void LogEntry::setPosition(ofVec2f v)
{
	pos.set(v);
}

ofVec2f LogEntry::getPosition()
{
	return pos;
}
