#include "config.h"

int config::columnWidth = 330;
int config::columnSpace = 10;
int config::UISpace = 5;
int config::UIHeight = 16;
int config::UIWidth = config::columnWidth - 40;
vector<ofColor> config::menuColors;

void config::setup(){
	config::menuColors.push_back(ofColor(12,56,64));
	config::menuColors.push_back(ofColor(19,91,91));
	config::menuColors.push_back(ofColor(22,115,105));
	config::menuColors.push_back(ofColor(20,140,113));
	config::menuColors.push_back(ofColor(23,154,113));
	config::menuColors.push_back(ofColor(134,203,113));
};