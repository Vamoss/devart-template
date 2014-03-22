#pragma once

#include "config.h"
#include "UI.h"

class saveUI : public UI {
    
public:
    
    void setup(ofColor color, ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		UI::setup(220, 150, color, ildaFbo, ildaFrame);
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {
		//TODO
		gui1->addLabel("SAVE", OFX_UI_FONT_MEDIUM);
		
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