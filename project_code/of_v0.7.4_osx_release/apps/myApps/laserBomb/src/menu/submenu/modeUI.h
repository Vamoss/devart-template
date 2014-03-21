#pragma once

#include "ofxUI.h"
#include "config.h"
#include "UI.h"

class modeUI : public UI {
    
public:
    
    void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		UI::setup(ildaFbo, ildaFrame);
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {
		int buttonSize = 60;
		
		vector<string> names;
		names.push_back("DRAW");
		names.push_back("SCREEN CAPTURE");
		names.push_back("RECEIVER");
		
		gui1 = new ofxUIScrollableCanvas(0, 0, 200, 768);
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