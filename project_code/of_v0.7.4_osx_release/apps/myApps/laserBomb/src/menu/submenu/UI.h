#pragma once

#include "ofxUI.h"
#include "ofxIldaRenderTarget.h"

class UI {
    
public:
    
	ofxUICanvas		*gui1;
	ofxIlda::RenderTarget * ildaFbo;
	ofxIlda::Frame * ildaFrame;
	
	virtual void setup(ofColor color, ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
	{
		setup(200, 768, color, ildaFbo, ildaFrame);
	}
	
	virtual void setup(int width, int height, ofColor color, ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
	{
		this->color = color;
		this->ildaFbo = ildaFbo;
		this->ildaFrame = ildaFrame;
		
		gui1 = new ofxUICanvas(0, 0, width, height);
		gui1->setVisible(false);
		gui1->setWidgetSpacing(10);
		
        ofColor cb = color;
		cb.a = 200;
		ofColor co = ofColor( 225, 183, 237, 100 );
		ofColor coh = ofColor( 245, 225, 226, 255 );
		ofColor cf = ofColor( 255 );
		ofColor cfh = ofColor( 209, 227, 137, 255 );
		ofColor cp = ofColor( 224, 72, 145, 100 );
		ofColor cpo = ofColor( 255 );
		gui1->setUIColors( cb, co, coh, cf, cfh, cp, cpo );
	};
	
	virtual void update(){};
	virtual void draw(){};
	virtual void keyPressed(int key){};
	virtual void mousePressed(int x, int y, int button){};
	virtual void mouseReleased(int x, int y, int button){};

protected:
	ofColor color;
};