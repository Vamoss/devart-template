#include "ofApp.h"


extern "C" {
    #include "macGlutfix.h"
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    config::setup();
    
    //UI
    ofEnableAlphaBlending();
    ofBackground(78);
    logoX = 0;
    logo.load("gui/images/logo.png");
    fboPosition.y = 60;
    
    m_menu = new menu();
    m_menu->setup(&ildaFbo, &ildaFrame);
    ofAddListener(m_menu->panelMode->onChange, this, &ofApp::onModeChange);
    
    m_sidebar = new sidebar();
    m_sidebar->setup(&ildaFbo, &ildaFrame);
    
    string initalMode = "DRAW";
    onModeChange(initalMode);
    
    etherdream.setup();
    etherdream.setPPS(20000);
    
    ildaFbo.setup(512, 512);
    
    doFboClear = true;
    
    
    captureWidth = ofGetScreenWidth();
    captureHeight = ofGetScreenHeight();
    tex.allocate(captureWidth, captureHeight, GL_RGBA);
    
    
    ildaFbo.params.draw.fbo = true;
    ildaFbo.params.draw.fboAlpha = 255;
    
    ildaFrame.params.output.transform.doFlipX = true;
    ildaFrame.params.output.transform.doFlipY = true;
    
    //webServer
    server.start("httpdocs", config::receiverPort);
    server.addHandler(this, "actions*");
    
    layoutResize();
    layoutResize();
    
    brushThickness = 10;//50

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(mode==DRAW){
        brushThickness = m_sidebar->panelDraw->brushThicknessSlider->getScaledValue();
        doDrawErase = m_sidebar->panelDraw->eraserToggle->getValue();
        doFboClear = m_sidebar->panelDraw->clearButton->getValue();
    }else if(mode==CAPTURE && (m_sidebar->panelCapture->buttonCapture->getValue() || m_sidebar->panelCapture->toggleAutoCapture->getValue())){
        m_sidebar->panelCapture->m_cropper->update();
        
        unsigned char * data;
        ofRectangle tempRect;
        if(m_sidebar->panelCapture->buttonCrop->getValue()){
            tempRect.x = 0;
            tempRect.y = 0;
            tempRect.width = captureWidth;
            tempRect.height = captureHeight;
        }else{
            tempRect.x = m_sidebar->panelCapture->m_cropper->x;
            tempRect.y = m_sidebar->panelCapture->m_cropper->y;
            tempRect.width = m_sidebar->panelCapture->m_cropper->width;
            tempRect.height = m_sidebar->panelCapture->m_cropper->height;
        }
        data = pixelsBelowWindow(tempRect.x, tempRect.y, tempRect.width, tempRect.height);

        /* if using macbook retina, set to true */
        bool retina = true;
        int pixelSize = retina ? 2 : 1;
        
        // now, let's get the R and B data swapped, so that it's all OK:
        for (int i = 0; i < pixelSize * pixelSize * tempRect.width * tempRect.height; i++){
            unsigned char r1 = data[i*4]; // mem A
            data[i*4]   = data[i*4+1];
            data[i*4+1] = data[i*4+2];
            data[i*4+2] = data[i*4+3];
            data[i*4+3] = r1;
        }
    
        if (data!= NULL) tex.loadData(data, tempRect.width*pixelSize, tempRect.height*pixelSize, GL_RGBA);
    }else if(mode == RECEIVE){
        processReceivedData();
    }
    
    m_menu->update();
    m_sidebar->update();
}



//--------------------------------------------------------------
void ofApp::drawInFbo() {
    ofPushStyle();
    ildaFbo.begin();
    
    if(doFboClear) {
        doFboClear = false;
        ofClear(0);
    }
    
    if(mode==DRAW && ofGetMousePressed() &&  mouseDownPos.x >= 0) {
        ofPushMatrix();
        ofScale(ildaFbo.getWidth(), ildaFbo.getHeight(), 1);
        ofSetColor(doDrawErase ? 0 : 255);
        ofSetLineWidth(brushThickness);
        ofDrawLine(lastMouseDownPos, mouseDownPos);
        ofDrawEllipse(mouseDownPos, brushThickness/2.0f/ildaFbo.getWidth(), brushThickness/2.0f/ildaFbo.getHeight());
        ofPopMatrix();
    }else if(mode==CAPTURE){
        ofRectangle sourceRect;
        if(m_sidebar->panelCapture->buttonCrop->getValue()){
            sourceRect.x = 0;
            sourceRect.y = 0;
            sourceRect.width = captureWidth;
            sourceRect.height = captureHeight;
        }else{
            sourceRect.x = m_sidebar->panelCapture->m_cropper->x;
            sourceRect.y = m_sidebar->panelCapture->m_cropper->y;
            sourceRect.width = m_sidebar->panelCapture->m_cropper->width;
            sourceRect.height = m_sidebar->panelCapture->m_cropper->height;
        }
        captureDrawPosition.width=ildaFbo.getWidth();
        captureDrawPosition.height=sourceRect.height*(ildaFbo.getWidth()/sourceRect.width);
        if(captureDrawPosition.height>ildaFbo.getHeight()){
            captureDrawPosition.height=ildaFbo.getHeight();
            captureDrawPosition.width=sourceRect.width*ildaFbo.getHeight()/sourceRect.height;
        }
        captureDrawPosition.x = (ildaFbo.getWidth()-captureDrawPosition.width)/2;
        captureDrawPosition.y = (ildaFbo.getHeight()-captureDrawPosition.height)/2;
        m_sidebar->panelCapture->m_cropper->scale = (fboPosition.width/captureWidth)*(captureDrawPosition.width/ildaFbo.getWidth());
        tex.draw(captureDrawPosition.x, captureDrawPosition.y, captureDrawPosition.width, captureDrawPosition.height);
    }
    
    ildaFbo.end();
    ofPopStyle();
}




//--------------------------------------------------------------
void ofApp::draw() {
    
    ofSetColor(255);
    logo.draw(logoX,10);
    
    // clear the current frame
    ildaFrame.clear();
    
    if(mode==DRAW || mode==CAPTURE){
        drawInFbo();    // draw stuff into the ildaRenderTarget
        ildaFbo.update(ildaFrame);  // vectorize and update the ildaFrame
    }else if(mode==RECEIVE){
        ildaFrame.addPolys(receivedData);
    }
    ildaFrame.update();
    etherdream.setPoints(ildaFrame);
    
    ofPushMatrix();
        ofTranslate(fboPosition.x, fboPosition.y);
        ildaFbo.getGreyImage().draw(0, 0, fboPosition.width, fboPosition.height);
        
        ofSetColor(0, 255, 0);
        ildaFrame.draw(0, 0, fboPosition.width, fboPosition.height);
        
        if(mode==CAPTURE){
            if(m_sidebar->panelCapture->buttonCrop->getValue()){
                ofPushMatrix();
                
                cout << fboPosition.y << " " << captureDrawPosition.y << " " << fboPosition.height << " " << m_sidebar->panelCapture->m_cropper->scale << " " << fboScale << endl;
                    ofTranslate(captureDrawPosition.x*fboScale, captureDrawPosition.y*fboScale);
                    m_sidebar->panelCapture->m_cropper->draw();
                ofPopMatrix();
            }
            
        }
    ofPopMatrix();
    
    if(mode==DRAW){
        // draw cursor
        ofPushStyle();
        ofFill();
        ofSetColor(doDrawErase ? 0 : 255, 128);
        float r = brushThickness/2 * ofGetWidth() /2 / ildaFbo.getWidth();
        ofDrawCircle(ofGetMouseX(), ofGetMouseY(), r);
        ofNoFill();
        ofSetColor(255, 128);
        ofDrawCircle(ofGetMouseX(), ofGetMouseY(), r);
        ofPopStyle();
    }
    
    m_menu->draw();
    m_sidebar->draw();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'f': ofToggleFullscreen(); break;
        case 'c': doFboClear ^= true; break;
            
        case '-': if(brushThickness>1) brushThickness--; break;
        case 't': printf("mouse inside: %i\n", ildaFrame.getPoly(0).inside(mouseDownPos.x, mouseDownPos.y)); break; // test
    }
    m_sidebar->panelCapture->m_cropper->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(m_menu->isHit(x, y)) return;
    if(mode==DRAW){
        lastMouseDownPos = mouseDownPos;
        mouseDownPos.x = ofMap(x, fboPosition.x, fboPosition.x+fboPosition.width, 0, 1);
        mouseDownPos.y = ofMap(y, fboPosition.y, fboPosition.y+fboPosition.height, 0, 1);
    }else if(mode==CAPTURE){
        m_sidebar->panelCapture->m_cropper->mouseDragged(x-fboPosition.x-(captureDrawPosition.x*fboScale), y-fboPosition.y-(captureDrawPosition.y*fboScale), button);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(m_menu->isHit(x, y)) return;
    if(mode==DRAW){
        mouseDownPos.x = ofMap(x, fboPosition.x, fboPosition.x+fboPosition.width, 0, 1);
        mouseDownPos.y = ofMap(y, fboPosition.y, fboPosition.y+fboPosition.height, 0, 1);
        lastMouseDownPos = mouseDownPos;
    }else if(mode==CAPTURE){
        m_sidebar->panelCapture->m_cropper->mousePressed(x-fboPosition.x-(captureDrawPosition.x*fboScale), y-fboPosition.y-(captureDrawPosition.y*fboScale), button);
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    layoutResize();
}

//--------------------------------------------------------------
void ofApp::layoutResize(){
    int w = ofGetWidth();
    int h = ofGetHeight();
    
    fboPosition.height = h-60;
    fboPosition.width = fboPosition.height;
    fboScale = fboPosition.width/ildaFbo.getWidth();
    
    int subPanelWidth = ofMap(ofGetWidth(), 800, 1920, 200, 400);
    
    int finalWidth = 60 + fboPosition.width + subPanelWidth;
    if(finalWidth>w){
        fboPosition.width = w - 60 - subPanelWidth;
        fboPosition.height = fboPosition.width;
        finalWidth = 60 + fboPosition.width + subPanelWidth;
    }
    
    logoX = (w-finalWidth)/2;
    m_menu->setX(logoX);
    m_sidebar->setX(fboPosition.x+fboPosition.width);
    
    fboPosition.x = logoX+60;
}



//--------------------------------------------------------------
void ofApp::onModeChange(string & name)
{
    if(name=="DRAW"){
        mode = DRAW;
    }else if(name=="SCREEN CAPTURE"){
        mode = CAPTURE;
    }else if(name=="HTTP RECEIVER"){
        mode = RECEIVE;
    }
    
    m_sidebar->panelDraw->gui1->setVisible(mode==DRAW);
    m_sidebar->panelCapture->gui1->setVisible(mode==CAPTURE);
    m_sidebar->panelReceive->gui1->setVisible(mode==RECEIVE);
}



//webServer
void ofApp::httpGet(string url) {
    string colorString = getRequestParameter("color");
    cout << colorString << endl;
    httpResponse("Color value: " + colorString);
}

void ofApp::httpPost(string url, char *data, int dataLength) {
    //cout << "url: " << url << endl;
    //cout << "data: " << data << endl;
    //cout << "dataLength: " << dataLength << endl;
    dataReceived = string(data);
    httpResponse("OK");
}

void ofApp::processReceivedData(){
    if(dataReceived!=""){
        try {
            //protocol
            //r,g,b,x,y,x,y,x,y,x,y_r,g,b,x,y,x,y,x,y_r,g,b,x,y,x,y,x,y
            vector< string > groupValues = ofSplitString(dataReceived,"_");
            receivedData.clear();
            for(int j=0;j<groupValues.size();j++){
                vector< string > values = ofSplitString(groupValues[j],",");
                if(values.size()<5) continue;
                ofxIlda::Poly poly = ofxIlda::Poly(ofColor(ofToInt(values[0]),ofToInt(values[1]),ofToInt(values[2])));
                for(int i=3;i+1<values.size();i+=2){
                    float x=atof(values[i].c_str());
                    float y=atof(values[i+1].c_str());
                    poly.lineTo(x, y);
                }
                receivedData.push_back(poly);
            }
            
            m_sidebar->panelReceive->incomingDataCounter++;
            m_sidebar->panelReceive->incomingDataCounterLabel->setLabel("Received: " + ofToString(m_sidebar->panelReceive->incomingDataCounter));
        }
        catch(...) {
            cout << "error parsing received data" << endl;
        }
        dataReceived = "";
    }
}
