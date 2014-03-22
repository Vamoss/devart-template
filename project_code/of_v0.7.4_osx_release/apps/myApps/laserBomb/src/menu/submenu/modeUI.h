#pragma once

#include "config.h"
#include "UI.h"

class modeUI : public UI {
    
public:
    
    void setup(ofColor color, ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		UI::setup(220, 100, color, ildaFbo, ildaFrame);
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {
		vector<string> names;
		names.push_back("DRAW");
		names.push_back("SCREEN CAPTURE");
		names.push_back("RECEIVER");
		
		gui1->addRadio("MODE", names, OFX_UI_ORIENTATION_VERTICAL);
		
		
        ofAddListener(gui1->newGUIEvent,this,&modeUI::guiEvent);
    }
    
    void keyPressed(int key)
    {
        switch (key)
        {
            case ' ':
                gui1->toggleVisible();
                break;
            case 's':
                save();
                break;
        }
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