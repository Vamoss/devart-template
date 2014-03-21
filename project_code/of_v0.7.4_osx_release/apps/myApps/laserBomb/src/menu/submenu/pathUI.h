#pragma once

#include "ofxUI.h"
#include "config.h"
#include "UI.h"

class pathUI : public UI {
    
public:
    
    void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		UI::setup(ildaFbo, ildaFrame);
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
		
		//gui.addSlider("stats.pointCountOrig", ildaFrame.stats.pointCountOrig, 0, 10000);
		//gui.addSlider("stats.pointCountProcessed", ildaFrame.stats.pointCountProcessed, 0, 10000);
    }
    
	
	void setGUI1()
    {	
		gui1 = new ofxUIScrollableCanvas(0, 0, 200, 768);
		gui1->addSlider("Smooth Amount", 0.0, 100.0, ildaFrame->polyProcessor.params.smoothAmount);
		gui1->addToggle("Contour Collapse", ildaFrame->polyProcessor.params.collapse);
		gui1->addSlider("Optimize Tolerance", 0.0, 1.0, ildaFrame->polyProcessor.params.optimizeTolerance);
		gui1->addSlider("Target Point Count", 0.0, 5000.0, ildaFrame->polyProcessor.params.targetPointCount);
		gui1->addSlider("Spacing", 0.0, 1.0, ildaFrame->polyProcessor.params.spacing);
        
        ofAddListener(gui1->newGUIEvent,this,&pathUI::guiEvent);
    }
    
    void guiEvent(ofxUIEventArgs &e)
    {
        string name = e.widget->getName();
        int kind = e.widget->getKind();
        cout << "got event from: " << name << endl;
        
        if(name == "Smooth Amount")
        {
            ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFrame->polyProcessor.params.smoothAmount = slider->getScaledValue();
        }
		else if(name == "Contour Collapse")
		{
			ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
			ildaFrame->polyProcessor.params.collapse = toggle->getValue();
		}
        else if(name == "Optimize Tolerance")
        {
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFrame->polyProcessor.params.optimizeTolerance = slider->getScaledValue();
        }
        else if(name == "Target Point Count")
        {
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFrame->polyProcessor.params.targetPointCount = slider->getScaledValue();
        }
		else if(name == "Spacing")
		{
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFrame->polyProcessor.params.spacing = slider->getScaledValue();
		}
	}
	
    void save()
    {
        gui1->saveSettings("GUI/settings.xml");
    }
    
};