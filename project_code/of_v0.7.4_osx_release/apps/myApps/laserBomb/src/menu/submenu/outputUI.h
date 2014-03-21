#pragma once

#include "ofxUI.h"
#include "config.h"
#include "UI.h"

class outputUI : public UI {
    
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
		gui1->addSlider("Line Red", 0.0, 1.0, ildaFrame->params.output.color.r);
		gui1->addSlider("Line Green", 0.0, 1.0, ildaFrame->params.output.color.g);
		gui1->addSlider("Line Blue", 0.0, 1.0, ildaFrame->params.output.color.b);
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