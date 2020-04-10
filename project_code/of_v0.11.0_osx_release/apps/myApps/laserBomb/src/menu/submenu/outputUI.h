#pragma once

#include "config.h"
#include "menuUI.h"

class outputUI : public menuUI {
    
public:
    
    void setup(ofColor color, ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		menuUI::setup(220, 170, color, ildaFbo, ildaFrame);
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {
		gui1->addLabel("OUTPUT", OFX_UI_FONT_MEDIUM);
		gui1->addSlider("Blank Count", 0.0, 100.0, ildaFrame->params.output.blankCount);
		gui1->addSlider("End Count", 0.0, 100.0, ildaFrame->params.output.endCount);
		gui1->addToggle("Cap X", ildaFrame->params.output.doCapX);
		gui1->addToggle("Cap Y", ildaFrame->params.output.doCapY);
        
        ofAddListener(gui1->newGUIEvent,this,&outputUI::guiEvent);
    }
    
    void guiEvent(ofxUIEventArgs &e)
    {
        string name = e.widget->getName();
        int kind = e.widget->getKind();
        cout << "got event from: " << name << endl;
        
        if(name == "Draw Ilda Point Numbers")
        {
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
			ildaFrame->params.draw.pointNumbers = toggle->getValue();
        }
		else if(name == "Line Red")
		{
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFrame->params.output.color.r = slider->getScaledValue();
		}
		else if(name == "Line Green")
		{
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFrame->params.output.color.g = slider->getScaledValue();
		}
        else if(name == "Line Blue")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFrame->params.output.color.b = slider->getScaledValue();
        }
        else if(name == "Blank Count")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFrame->params.output.blankCount = slider->getScaledValue();
		}
		else if(name == "End Count")
		{
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFrame->params.output.endCount = slider->getScaledValue();
		}
		else if(name == "Cap X")
		{
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
			ildaFrame->params.output.doCapX = toggle->getValue();
		}
		else if(name == "Cap Y")
		{
            ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
			ildaFrame->params.output.doCapY = toggle->getValue();
		}
	}
    
    void save()
    {
        gui1->saveSettings("GUI/settings.xml");
    }
    
};