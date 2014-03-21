#pragma once

#include "ofMain.h"
#include "ofxEtherdream.h"
#include "ofxWebServer.h"
#include "menu.h"
#include "ofxSimpleGuiToo.h"
#include "ofxIldaRenderTarget.h"

class testApp : public ofBaseApp, public ofxWSRequestHandler{
    
public:
    void setup();
    void update();
    void draw();
	
    void drawInFbo();
    
    void keyPressed  (int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
	void windowResized(int w, int h);
	void layoutResize();

    ofxEtherdream etherdream;
	
	//screenCapture
	ofTexture	tex;
	int captureWidth;
	int captureHeight;
	
	//UI
	menu * m_menu;
	ofImage logo;
	int logoX;
	ofRectangle fboPosition;
	
	
	//webServer
	ofxWebServer server;
	void httpGet(string url);
	void httpPost(string url, char *data, int dataLength);
	vector<ofxIlda::Poly> receivedData;
	
	
	//Ilda
	ofxIlda::RenderTarget ildaFbo;
	ofxIlda::Frame ildaFrame;
	
	//Draw Mode
	ofVec2f mouseDownPos;   // position of mouse (normalized)
	ofVec2f lastMouseDownPos; // last position of mouse (normalized)
	
	// PARAMS
	bool doFboClear;
	bool doDrawErase;   // whether we are erasing (true) or drawing (erase)
	int brushThickness;
};
