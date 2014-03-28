#pragma once

#include "config.h"
#include "sidebarUI.h"

class receiveUI : public sidebarUI {
    
public:
	
	ofxUILabel * incomingDataCounterLabel;
	double incomingDataCounter;
    
    void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		sidebarUI::setup(220, 800, ildaFbo, ildaFrame);
		
		incomingDataCounter = 0;
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {
		gui1->addLabel("RECEIVE", OFX_UI_FONT_LARGE);
		gui1->addWidgetDown(new ofxUILabel("Send to port " + ofToString(config::receiverPort), OFX_UI_FONT_SMALL));
		incomingDataCounterLabel = (ofxUILabel *) gui1->addWidgetDown(new ofxUILabel("Received: " + ofToString(incomingDataCounter), OFX_UI_FONT_SMALL));
		
		
        
        ofAddListener(gui1->newGUIEvent,this,&receiveUI::guiEvent);
    }
    
    void guiEvent(ofxUIEventArgs &e)
    {
        string name = e.widget->getName();
        int kind = e.widget->getKind();
        cout << "got event from: " << name << endl;
	}
    
    void save()
    {
        gui1->saveSettings("GUI/settings.xml");
    }
    
};