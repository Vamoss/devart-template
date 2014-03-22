#pragma once

#include "ofMain.h"

class config {
public:
	static int columnWidth;
	static int columnSpace;
	static int UISpace;
	static int UIHeight;
	static int UIWidth;
	
	static vector<ofColor> menuColors;
	
	static void setup();
};