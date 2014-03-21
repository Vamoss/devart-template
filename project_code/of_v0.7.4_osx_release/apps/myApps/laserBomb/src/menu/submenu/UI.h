#pragma once

#include "ofxUI.h"
#include "ofxIldaRenderTarget.h"

#undef OFX_UI_FONT_SMALL_SIZE
#define OFX_UI_FONT_SMALL_SIZE 4

#undef OFX_UI_FONT_MEDIUM_SIZE
#define OFX_UI_FONT_MEDIUM_SIZE 4

#undef OFX_UI_GLOBAL_WIDGET_SPACING
#define OFX_UI_GLOBAL_WIDGET_SPACING 40

#undef OFX_UI_FONT_RESOLUTION
#define OFX_UI_FONT_RESOLUTION 40

class UI {
    
public:
    
	ofxUIScrollableCanvas		*gui1;
	ofxIlda::RenderTarget * ildaFbo;
	ofxIlda::Frame * ildaFrame;
	
	virtual void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
	{
		this->ildaFbo = ildaFbo;
		this->ildaFrame = ildaFrame;
	};
	
	virtual void update(){};
	virtual void draw(){};
	virtual void keyPressed(int key){};
	virtual void mousePressed(int x, int y, int button){};
	virtual void mouseReleased(int x, int y, int button){};
};