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
        gui1->setVisible(true);
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
        
        if(name == "PARTICLES")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
			//server::send(name, slider->getScaledValue());
        }
		else if(name == "PROBABILITY")
		{
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			//server::send(name, slider->getScaledValue());
		}
        else if(name == "SPRING")
        {
			ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
			//server::send(name, toggle->getValue());
        }
        else if(name == "ATTRACT")
        {
			ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
			//server::send(name, toggle->getValue());
        }
		else if(name == "STRENGHT")
		{
			ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget;
			//server::send(name, slider->getScaledValueLow(), slider->getScaledValueHigh());
		}
		else if(name == "ORBIT")
		{
			ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget;
			//server::send(name, slider->getScaledValueLow(), slider->getScaledValueHigh());
		}
        else if(name == "SHAKE")
        {
			//server::send(name);
        }
        else if(name == "RESTART")
        {
			//server::send(name);
		}
		else if(name == "COLLISION")
		{
			ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
			//server::send(name, toggle->getValue());
		}
		else if(name == "MASS")
		{
			ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget;
			//server::send(name, slider->getScaledValueLow(), slider->getScaledValueHigh());
		}
		else if(name == "GRAVITY")
		{
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			//server::send(name, slider->getScaledValue());
		}
		else if(name == "BOUNCE")
		{
			ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget;
			//server::send(name, slider->getScaledValueLow(), slider->getScaledValueHigh());
		}
		else if(name == "CENTER")
		{
			((ofxUISlider *)gui1->getWidget("GRAVITY"))->setValue(0);
			//server::send("GRAVITY", 0.0f);
		}
        else if(name == "SAVE")
        {
            save();
        }
	}
	
	void setParticles(float percent)
	{
		ofxUISlider *slider = (ofxUISlider *) gui1->getWidget("PARTICLES");
		if(percent != slider->getValue()){
			slider->setValue(percent * slider->getMax());
			//server::send("PARTICLES", slider->getScaledValue());
		}
	}
    
    void save()
    {
        gui1->saveSettings("GUI/settings.xml");
    }
    
};