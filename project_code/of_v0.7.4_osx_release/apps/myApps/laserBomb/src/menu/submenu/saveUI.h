#pragma once

#include "ofxUI.h"
#include "config.h"
#include "UI.h"

class saveUI : public UI {
    
public:
    
    void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		UI::setup(ildaFbo, ildaFrame);
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {
		//TODO
		gui1 = new ofxUIScrollableCanvas(0, 0, 200, 768);
        
        ofAddListener(gui1->newGUIEvent,this,&saveUI::guiEvent);
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