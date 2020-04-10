#pragma once

#include "config.h"
#include "menuUI.h"

class modeUI : public menuUI {
    
public:
	ofEvent<string> onChange;
    
    void setup(ofColor color, ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		menuUI::setup(220, 100, color, ildaFbo, ildaFrame);
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {
		vector<string> names;
		names.push_back("DRAW");
		names.push_back("SCREEN CAPTURE");
		names.push_back("HTTP RECEIVER");
		
		gui1->addRadio("MODE", names, OFX_UI_ORIENTATION_VERTICAL);
		
		
        ofAddListener(gui1->newGUIEvent,this,&modeUI::guiEvent);
    }
    
    
    void guiEvent(ofxUIEventArgs &e)
    {
        string name = e.widget->getName();
        int kind = e.widget->getKind();
        cout << "got event from: " << name << endl;
		
		ofNotifyEvent(onChange, name);
	}
    
    void save()
    {
        gui1->saveSettings("GUI/settings.xml");
    }
    
};