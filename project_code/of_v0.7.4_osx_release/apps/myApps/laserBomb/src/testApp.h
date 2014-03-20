#pragma once

#include "ofMain.h"
#include "ofxEtherdream.h"
#include "ofxWebServer.h"

class testApp : public ofBaseApp, public ofxWSRequestHandler{
    
public:
    void setup();
    void update();
    void draw();
	
    void drawInFbo();
    
    void keyPressed  (int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);

    ofxEtherdream etherdream;
	
	ofTexture	tex;
	int captureWidth;
	int captureHeight;
	
	
	//webServer
	ofxWebServer server;
	void httpGet(string url);
	void httpPost(string url, char *data, int dataLength);
	vector<ofxIlda::Poly> receivedData;
};
