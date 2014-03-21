#pragma once

#include "ofxUI.h"
#include "config.h"
#include "UI.h"

class viewUI : public UI {
    
public:
    
    void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		UI::setup(ildaFbo, ildaFrame);
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {
		gui1 = new ofxUIScrollableCanvas(0, 0, 200, 768);
		gui1->addToggle("Draw Line", ildaFbo->params.draw.linesRaw);
		gui1->addToggle("Draw Ilda Line", ildaFrame->params.draw.lines);
		gui1->addToggle("Draw Ilda Points", ildaFrame->params.draw.points);
		gui1->addToggle("Draw Ilda Point Numbers", ildaFrame->params.draw.pointNumbers);
        
        ofAddListener(gui1->newGUIEvent,this,&viewUI::guiEvent);
    }
    
    void guiEvent(ofxUIEventArgs &e)
    {
        string name = e.widget->getName();
        int kind = e.widget->getKind();
        cout << "got event from: " << name << endl;
        
        if(name == "Draw Line")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
			ildaFbo->params.draw.linesRaw = toggle->getValue();
        }
		else if(name == "Draw Ilda Line")
		{
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
			ildaFrame->params.draw.lines = toggle->getValue();
		}
        else if(name == "Draw Ilda Points")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
			ildaFrame->params.draw.points = toggle->getValue();
        }
	}
    
    void save()
    {
        gui1->saveSettings("GUI/settings.xml");
    }
    
};