#include "log.h"

Log::Log() {};
Log::~Log() {};

void Log::setup(ofVec2f p, float h, unsigned int numE)
{
	maxItems = numE;
	pos = p;
	height = h;
	fontSize = 12;
	lineSize = 16;
}

void Log::update()
{
	for (iEntry itr = entries.begin(); itr != entries.end(); itr++)
	{
		itr->update();
	}
}

void Log::draw()
{
	for (iEntry itr = entries.begin(); itr != entries.end(); itr++)
	{
		itr->draw();
	}
}

void Log::addEntry(std::string s)
{
	if (entries.size() >= maxItems)
	{
		entries.erase(entries.begin());
	}

	shiftEntries();

	ofVec2f position;
	position.x = pos.x;
	position.y = pos.y + height - lineSize;

	entries.push_back(LogEntry());
	entries.back().setup(position, s, fontSize, lineSize);
}

void Log::shiftEntries()
{
	for (iEntry itr = entries.begin(); itr != entries.end(); itr++)
	{
		itr->setPosition(ofVec2f(itr->getPosition().x, itr->getPosition().y - lineSize));
	}
}