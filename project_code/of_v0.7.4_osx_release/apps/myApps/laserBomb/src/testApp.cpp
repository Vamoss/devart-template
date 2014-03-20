#include "testApp.h"
#include "ofxSimpleGuiToo.h"
#include "ofxIldaRenderTarget.h"


extern "C" {
	#include "macGlutfix.h"
}

// VARS
ofxIlda::RenderTarget ildaFbo;
ofxIlda::Frame ildaFrame;

ofVec2f mouseDownPos;   // position of mouse (normalized)
ofVec2f lastMouseDownPos; // last position of mouse (normalized)

// PARAMS
bool doFboClear;
bool doDrawErase;   // whether we are erasing (true) or drawing (erase)
int brushThickness;

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(100);
    
    etherdream.setup();
    etherdream.setPPS(20000);
    
    ildaFbo.setup(512, 512);
    
    gui.addTitle("INPUT");
    gui.addToggle("doFboClear c", doFboClear);
    gui.addToggle("doDrawErase x", doDrawErase);
    gui.addSlider("brushThickness", brushThickness, 1, 50);
    
    gui.addTitle("CV");
    gui.addSlider("cv.blurAmount", ildaFbo.params.cv.blurAmount, 0, 20);
    gui.addSlider("cv.bottomThreshold", ildaFbo.params.cv.bottomThreshold, 0, 20);
    gui.addSlider("cv.thresholdAmount", ildaFbo.params.cv.thresholdAmount, 0, 255);
    gui.addSlider("adaptiveThresholdAmount", ildaFbo.params.cv.adaptiveThresholdAmount, 0, 50);
    gui.addSlider("cv.adaptiveThresholdBlock", ildaFbo.params.cv.adaptiveThresholdBlock, 0, 10);
    gui.addSlider("cv.erodeAmount", ildaFbo.params.cv.erodeAmount, 0, 20);
    gui.addToggle("cv.doCanny", ildaFbo.params.cv.doCanny);
    gui.addSlider("cv.cannyThresh1", ildaFbo.params.cv.cannyThresh1, 0, 10);
    gui.addSlider("cv.cannyThresh2", ildaFbo.params.cv.cannyThresh2, 0, 10);
    gui.addSlider("cv.cannyWindow", ildaFbo.params.cv.cannyWindow, 1, 3);
    gui.addToggle("cv.doFindHoles", ildaFbo.params.cv.doFindHoles);
    
    gui.addTitle("PATH PROCESSING");
    gui.addSlider("path.smoothAmount", ildaFrame.polyProcessor.params.smoothAmount, 0, 100);
    gui.addToggle("path.contourCollapse", ildaFrame.polyProcessor.params.collapse);
    gui.addSlider("path.optimizeTolerance", ildaFrame.polyProcessor.params.optimizeTolerance, 0, 1);
    gui.addSlider("path.targetPointCount", ildaFrame.polyProcessor.params.targetPointCount, 0, 5000);
    gui.addSlider("path.spacing", ildaFrame.polyProcessor.params.spacing, 0, 1);
    gui.addSlider("stats.pointCountOrig", ildaFrame.stats.pointCountOrig, 0, 10000);
    gui.addSlider("stats.pointCountProcessed", ildaFrame.stats.pointCountProcessed, 0, 10000);
    
    gui.addTitle("DISPLAY");
    gui.addToggle("doDrawFbo", ildaFbo.params.draw.fbo);
    gui.addSlider("fboAlpha", ildaFbo.params.draw.fboAlpha, 0, 255);
    gui.addToggle("doDrawLineRaw", ildaFbo.params.draw.linesRaw);
    gui.addToggle("doDrawIldaLines", ildaFrame.params.draw.lines);
    gui.addToggle("doDrawIldaPoints", ildaFrame.params.draw.points);
    gui.addToggle("doDrawIldaPointNumbers", ildaFrame.params.draw.pointNumbers);
    
    gui.addTitle("OUTPUT");
    gui.addColorPicker("color", ildaFrame.params.output.color);
    gui.addSlider("blankCount", ildaFrame.params.output.blankCount, 0, 100);
    gui.addSlider("endCount", ildaFrame.params.output.endCount, 0, 100);
    gui.addToggle("doCapX", ildaFrame.params.output.doCapX);
    gui.addToggle("doCapY", ildaFrame.params.output.doCapY);
    
    gui.addTitle("");
    gui.addContent("fbo", ildaFbo.getFbo());
    gui.addContent("greyImage", ildaFbo.getGreyImage());
    
    gui.setDefaultKeys(true);
    gui.loadFromXML();
    gui.show();
    
    doFboClear = true;
	
	
	captureWidth = ildaFbo.getWidth();
	captureHeight = ildaFbo.getHeight();
	tex.allocate(captureWidth, captureHeight, GL_RGBA);
	
	ildaFrame.params.output.transform.doFlipX = true;
	ildaFrame.params.output.transform.doFlipY = true;
	
	//webServer
	server.start("httpdocs");
	server.addHandler(this, "actions*");

}

//--------------------------------------------------------------
void testApp::update(){
	unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(), ofGetWindowPositionY(), captureWidth, captureHeight);
	
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < captureWidth * captureHeight; i++){
		unsigned char r1 = data[i*4]; // mem A
		data[i*4]   = data[i*4+1];
		data[i*4+1] = data[i*4+2];
		data[i*4+2] = data[i*4+3];
		data[i*4+3] = r1;
	}
	
	
	if (data!= NULL) tex.loadData(data, captureWidth, captureHeight, GL_RGBA);
}



//--------------------------------------------------------------
void testApp::drawInFbo() {
    ofPushStyle();
    ildaFbo.begin();
    if(doFboClear) {
        doFboClear = false;
        ofClear(0);
    }
    if(ofGetMousePressed() &&  mouseDownPos.x >= 0) {
        //original
		/*ofPushMatrix();
        ofScale(ildaFbo.getWidth(), ildaFbo.getHeight(), 1);
        ofSetColor(doDrawErase ? 0 : 255);
        ofSetLineWidth(brushThickness);
        ofLine(lastMouseDownPos, mouseDownPos);
        ofEllipse(mouseDownPos, brushThickness/2.0f/ildaFbo.getWidth(), brushThickness/2.0f/ildaFbo.getHeight());
        ofPopMatrix();*/
		
		
		//screen capture
		//tex.draw(0,0, captureWidth, captureHeight);
		
		//custom draw
        /*ofPushMatrix();
        ofSetColor(doDrawErase ? 0 : 255);
		ofFill();
        ofCircle(mouseDownPos.x*ildaFbo.getWidth(), mouseDownPos.y*ildaFbo.getHeight(), brushThickness/2.0f);
		ofNoFill();
        //ofSetLineWidth(brushThickness*8.0f);
        //ofLine(mouseDownPos.x*ildaFbo.getWidth(),		mouseDownPos.y*ildaFbo.getHeight(),
		//	   lastMouseDownPos.x*ildaFbo.getWidth(),	lastMouseDownPos.y*ildaFbo.getHeight());
        ofPopMatrix();*/
    }
	
    ildaFbo.end();
    ofPopStyle();
}




//--------------------------------------------------------------
void testApp::draw() {
	/*
	// clear the current frame
    ildaFrame.clear();
    
    drawInFbo();    // draw stuff into the ildaRenderTarget
    ildaFbo.update(ildaFrame);  // vectorize and update the ildaFrame
    
    ildaFrame.update();
	 */
    
	
	//custom shape test using ildaFrame
	/*
	ildaFrame.clear();
	ofxIlda::Poly &poly = ildaFrame.addPoly(ofxIlda::Poly(ofColor(100,100,0)));
	poly.lineTo(0.1f,0.0f);
	poly.lineTo(0.1f,0.1f);
	poly.lineTo(0.0f,0.1f);
	poly.close();
	ofxIlda::Poly &poly2 = ildaFrame.addPoly(ofxIlda::Poly(ofColor(100,0,0)));
	poly2.lineTo(0.2f,0.0f);
	poly2.lineTo(0.2f,0.2f);
	poly2.lineTo(0.0f,0.2f);
	poly2.close();
	ofxIlda::Poly &poly3 = ildaFrame.addPoly(ofxIlda::Poly(ofColor(0,0,100)));
	poly3.lineTo(0.4f,0.0f);
	poly3.lineTo(0.4f,0.4f);
	poly3.lineTo(0.0f,0.4f);
	poly3.close();
	ofxIlda::Poly &poly4 = ildaFrame.addPoly(ofxIlda::Poly(ofColor(0,100,0)));
	poly4.lineTo(0.8f,0.0f);
	poly4.lineTo(0.8f,0.8f);
	poly4.lineTo(0.0f,0.8f);
	poly4.close();
	ildaFrame.update();
    etherdream.setPoints(ildaFrame);
	*/
	
	/*
	//NOT WORKING
	//custom shape test NOT using ildaFrame
	vector<ofxIlda::Point> origPolys;
	origPolys.push_back(ofxIlda::Point(ofPoint(0.1f,0.0f), ofColor(100,100,0)));
	origPolys.push_back(ofxIlda::Point(ofPoint(0.1f,0.1f), ofColor(100,100,0)));
	origPolys.push_back(ofxIlda::Point(ofPoint(0.0f,0.1f), ofColor(100,100,0)));
	origPolys.push_back(ofxIlda::Point(ofPoint(0.0f,0.0f), ofColor(100,100,0)));
	origPolys.push_back(ofxIlda::Point(ofPoint(0.2f,0.0f), ofColor(100,0,0)));
	origPolys.push_back(ofxIlda::Point(ofPoint(0.2f,0.2f), ofColor(100,0,0)));
	origPolys.push_back(ofxIlda::Point(ofPoint(0.0f,0.2f), ofColor(100,0,0)));
	origPolys.push_back(ofxIlda::Point(ofPoint(0.0f,0.0f), ofColor(100,0,0)));
	etherdream.setPoints(origPolys);
	*/
	
	//webService
	ildaFrame.clear();
	ildaFrame.addPolys(receivedData);
	ildaFrame.update();
	
    int dw = ofGetWidth()/2;
    int dh = dw;
    int dx = ofGetWidth() - dw;
    int dy = 0;

    ildaFbo.draw(dx, dy, dw, dh);
    
    ofSetColor(0, 255, 0);
    ildaFrame.draw(dx, dy, dw, dh);
    
    etherdream.setPoints(ildaFrame);
    
    // draw cursor
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(doDrawErase ? 0 : 255, 128);
    float r = brushThickness/2 * ofGetWidth() /2 / ildaFbo.getWidth();
    ofCircle(ofGetMouseX(), ofGetMouseY(), r);
    ofNoFill();
    ofSetColor(255, 128);
    ofCircle(ofGetMouseX(), ofGetMouseY(), r);
	 
	gui.draw();
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(key) {
        case 'f': ofToggleFullscreen(); break;
        case 'c': doFboClear ^= true; break;
        case 'x': doDrawErase ^= true; break;
            
        case '=':
        case '+': brushThickness++; break;
            
        case '-': if(brushThickness>1) brushThickness--; break;
        case 't': printf("mouse inside: %i\n", ildaFrame.getPoly(0).inside(mouseDownPos)); break; // test
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    lastMouseDownPos = mouseDownPos;
    mouseDownPos.x = ofMap(x, ofGetWidth()/2, ofGetWidth(), 0, 1);
    mouseDownPos.y = ofMap(y, 0, ofGetWidth()/2, 0, 1);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    mouseDownPos.x = ofMap(x, ofGetWidth()/2, ofGetWidth(), 0, 1);
    mouseDownPos.y = ofMap(y, 0, ofGetWidth()/2, 0, 1);
    lastMouseDownPos = mouseDownPos;
}



//webServer
void testApp::httpGet(string url) {
	string colorString = getRequestParameter("color");
	cout << colorString << endl;
	httpResponse("Color value: "
				 + colorString);
}

void testApp::httpPost(string url, char *data, int dataLength) {
	//cout << "url: " << url << endl;
	//cout << "data: " << data << endl;
	//cout << "dataLength: " << dataLength << endl;
	
	//protocol
	//r,g,b,x,y,x,y,x,y,x,y_r,g,b,x,y,x,y,x,y_r,g,b,x,y,x,y,x,y
	string str(data, data + dataLength);
	vector< string > groupValues = ofSplitString(str,"_");
	receivedData.clear();
	float x,y;
	for(int j=0;j<groupValues.size();j++){
		vector< string > values = ofSplitString(groupValues[j],",");
		if(values.size()<5) continue;
		ofxIlda::Poly poly = ofxIlda::Poly(ofColor(ofToInt(values[0]),ofToInt(values[1]),ofToInt(values[2])));
		for(int i=3;i<values.size();i+=2){
			x=ofToFloat(values[i]);
			y=ofToFloat(values[i+1]);
			poly.lineTo(x, y);
		}
		receivedData.push_back(poly);
	}
	
	httpResponse("OK");
}