#include "testApp.h"


extern "C" {
	#include "macGlutfix.h"
}

//--------------------------------------------------------------
void testApp::setup(){
	
	//UI
	ofEnableAlphaBlending();
    ofBackground(78);
	logoX = 0;
	logo.loadImage("gui/images/logo.png");
	fboPosition.y = 60;
    
    etherdream.setup();
    etherdream.setPPS(20000);
    
    ildaFbo.setup(512, 512);
	
	m_menu = new menu();
	m_menu->setup(&ildaFbo, &ildaFrame);
    
    doFboClear = true;
	
	
	captureWidth = ildaFbo.getWidth();
	captureHeight = ildaFbo.getHeight();
	tex.allocate(captureWidth, captureHeight, GL_RGBA);
	
	
	ildaFbo.params.draw.fbo = true;
    ildaFbo.params.draw.fboAlpha = 255;
	
	ildaFrame.params.output.transform.doFlipX = true;
	ildaFrame.params.output.transform.doFlipY = true;
	
	//webServer
	server.start("httpdocs");
	server.addHandler(this, "actions*");
	
	layoutResize();
	
	
	brushThickness = 10;//50

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
	
	m_menu->update();
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
        ofPushMatrix();
        ofPushStyle();
		ofSetColor(doDrawErase ? 0 : 255);
		ofFill();
        ofCircle(mouseDownPos.x*ildaFbo.getWidth(), mouseDownPos.y*ildaFbo.getHeight(), brushThickness/2.0f);
		ofNoFill();
        //ofSetLineWidth(brushThickness*8.0f);
        //ofLine(mouseDownPos.x*ildaFbo.getWidth(),		mouseDownPos.y*ildaFbo.getHeight(),
		//	   lastMouseDownPos.x*ildaFbo.getWidth(),	lastMouseDownPos.y*ildaFbo.getHeight());
		ofPopStyle();
        ofPopMatrix();
    }
	
    ildaFbo.end();
    ofPopStyle();
}




//--------------------------------------------------------------
void testApp::draw() {
	
	ofSetColor(255);
	logo.draw(logoX,10);
	
	// clear the current frame
    ildaFrame.clear();
    
    drawInFbo();    // draw stuff into the ildaRenderTarget
    ildaFbo.update(ildaFrame);  // vectorize and update the ildaFrame
    
    ildaFrame.update();
	
	
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
	/*ildaFrame.clear();
	ildaFrame.addPolys(receivedData);
	ildaFrame.update();*/
	
    int dw = fboPosition.width;
    int dh = fboPosition.height;
    int dx = fboPosition.x;
    int dy = fboPosition.y;

    ildaFbo.draw(dx, dy, dw, dh);
    
    ofSetColor(0, 255, 0);
    ildaFrame.draw(dx, dy, dw, dh);
    
    etherdream.setPoints(ildaFrame);
    
    // draw cursor
    ofPushStyle();
    ofFill();
    ofSetColor(doDrawErase ? 0 : 255, 128);
    float r = brushThickness/2 * ofGetWidth() /2 / ildaFbo.getWidth();
    ofCircle(ofGetMouseX(), ofGetMouseY(), r);
    ofNoFill();
    ofSetColor(255, 128);
    ofCircle(ofGetMouseX(), ofGetMouseY(), r);
	ofPopStyle();
	
	m_menu->draw();
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
    mouseDownPos.x = ofMap(x, fboPosition.x, fboPosition.x+fboPosition.width, 0, 1);
    mouseDownPos.y = ofMap(y, fboPosition.y, fboPosition.y+fboPosition.height, 0, 1);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    mouseDownPos.x = ofMap(x, fboPosition.x, fboPosition.x+fboPosition.width, 0, 1);
    mouseDownPos.y = ofMap(y, fboPosition.y, fboPosition.y+fboPosition.height, 0, 1);
    lastMouseDownPos = mouseDownPos;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	layoutResize();
}

//--------------------------------------------------------------
void testApp::layoutResize(){
	int w = ofGetWidth();
	int h = ofGetHeight();
	
	fboPosition.height = h-60;
	fboPosition.width = fboPosition.height;
	
	int subPanelWidth = ofMap(ofGetWidth(), 800, 1920, 200, 400);
	
	int finalWidth = 60 + fboPosition.width + subPanelWidth;
	if(finalWidth>w){
		fboPosition.width = w - 60 - subPanelWidth;
		fboPosition.height = fboPosition.width;
		finalWidth = 60 + fboPosition.width + subPanelWidth;
	}
	
	logoX = (w-finalWidth)/2;
	m_menu->setX(logoX);
	
	fboPosition.x = logoX+60;
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