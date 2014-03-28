#pragma once

#include "config.h"
#include "menuUI.h"

class effectUI : public menuUI {
    
public:
    
    void setup(ofColor color, ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		menuUI::setup(220, 450, color, ildaFbo, ildaFrame);
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {	
		gui1->addLabel("EFFECT", OFX_UI_FONT_MEDIUM);
		gui1->addSlider("Blur", 0.0, 20.0, ildaFbo->params.cv.blurAmount);
		gui1->addSlider("Bottom Treshold", 0.0, 20.0, ildaFbo->params.cv.bottomThreshold);
		gui1->addSlider("Treshold Amount", 0.0, 255.0, ildaFbo->params.cv.thresholdAmount);
		gui1->addSlider("Adaptive Treshold Amount", 0.0, 50.0, ildaFbo->params.cv.adaptiveThresholdAmount);
		gui1->addSlider("Adaptive Threshold Block", 0.0, 10.0, ildaFbo->params.cv.adaptiveThresholdBlock);
		gui1->addSlider("Erode Amount", 0.0, 20.0, ildaFbo->params.cv.erodeAmount);
		gui1->addToggle("Edge Detect", ildaFbo->params.cv.doCanny);
		gui1->addSlider("Edge Tresh1", 0.0, 10.0, ildaFbo->params.cv.cannyThresh1);
		gui1->addSlider("Edge Tresh2", 0.0, 10.0, ildaFbo->params.cv.cannyThresh2);
		gui1->addSlider("Edge Window", 1.0, 3.0, ildaFbo->params.cv.doFindHoles);
		gui1->addToggle("Find Holes", ildaFbo->params.cv.doFindHoles);
        
        ofAddListener(gui1->newGUIEvent,this,&effectUI::guiEvent);
    }
	
	void guiEvent(ofxUIEventArgs &e)
    {
        string name = e.widget->getName();
        int kind = e.widget->getKind();
        cout << "got event from: " << name << endl;
        
        if(name == "Blur"){
            ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFbo->params.cv.blurAmount = slider->getScaledValue();
        }else if(name == "Bottom Treshold"){
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFbo->params.cv.bottomThreshold = slider->getScaledValue();
		}else if(name == "Treshold Amount"){
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFbo->params.cv.thresholdAmount = slider->getScaledValue();
        }else if(name == "Adaptive Treshold Amount"){
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFbo->params.cv.adaptiveThresholdAmount = slider->getScaledValue();
        }else if(name == "Adaptive Threshold Block"){
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFbo->params.cv.adaptiveThresholdBlock = slider->getScaledValue();
        }else if(name == "Erode Amount"){
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFbo->params.cv.erodeAmount = slider->getScaledValue();
        }else if(name == "Edge Detect"){
			ofxUIToggle *slider = (ofxUIToggle *) e.widget;
			ildaFbo->params.cv.doCanny = slider->getValue();
        }else if(name == "Edge Tresh1"){
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFbo->params.cv.cannyThresh1 = slider->getScaledValue();
        }else if(name == "Edge Tresh2"){
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFbo->params.cv.cannyThresh2 = slider->getScaledValue();
        }else if(name == "Edge Window"){
			ofxUISlider *slider = (ofxUISlider *) e.widget;
			ildaFbo->params.cv.cannyWindow = slider->getScaledValue();
        }else if(name == "Find Holes"){
			ofxUIToggle *slider = (ofxUIToggle *) e.widget;
			ildaFbo->params.cv.doFindHoles = slider->getValue();
        }
	}
    
    void save()
    {
        gui1->saveSettings("GUI/settings.xml");
    }
    
};