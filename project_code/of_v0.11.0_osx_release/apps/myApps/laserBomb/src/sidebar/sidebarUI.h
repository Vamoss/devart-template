#pragma once

#include "ofxUI.h"
#include "ofxIldaRenderTarget.h"
#include "ofxUIFbo.h"

class sidebarUI {
    
public:
    
	ofxUICanvas		*gui1;
	ofxIlda::RenderTarget * ildaFbo;
	ofxIlda::Frame * ildaFrame;
	
	virtual void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
	{
		setup(200, 768, ildaFbo, ildaFrame);
	}
	
	virtual void setup(int width, int height, ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
	{
		this->ildaFbo = ildaFbo;
		this->ildaFrame = ildaFrame;
		
		gui1 = new ofxUICanvas(0, 0, width, height);
		gui1->setWidgetSpacing(10);
		gui1->setDrawBack(false);
	};
	
	virtual void update(){};
	virtual void draw(){};
	virtual void keyPressed(int key){};
	virtual void mousePressed(int x, int y, int button){};
	virtual void mouseReleased(int x, int y, int button){};

protected:
	ofColor color;
};