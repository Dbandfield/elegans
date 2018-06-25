#pragma once

#include "log-entry.h"

#include <vector>
#include <string>

#include <ofVec2f.h>

typedef std::vector<LogEntry> vEntry;
typedef std::vector<LogEntry>::iterator iEntry;

class Log
{
public:

	Log();
	~Log();

	void setup(ofVec2f p, float h, unsigned int numE);
	void update();
	void draw();

	void addEntry(std::string s);

private:

	void shiftEntries();

	int maxItems;
	vEntry entries;
	ofVec2f pos;
	float height;
	int fontSize;
	int lineSize;
};
