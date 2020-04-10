#pragma once

#include "config.h"
#include "sidebarUI.h"
#include "cropper.h"

class captureUI : public sidebarUI {
    
public:
	ofxUILabelToggle * buttonCrop;
	ofxUILabelButton * buttonCapture;
	ofxUIToggle * toggleAutoCapture;
	cropper * m_cropper;
    
    void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		sidebarUI::setup(220, 800, ildaFbo, ildaFrame);
		
		m_cropper = new cropper();
		m_cropper->setup(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {	
		gui1->addLabel("CAPTURE", OFX_UI_FONT_LARGE);
		buttonCapture = (ofxUILabelButton *) gui1->addLabelButton("CAPTURE", false, 200);
		toggleAutoCapture = (ofxUIToggle*) gui1->addToggle("AUTO CAPTURE", false, 16, 16);
		buttonCrop = (ofxUILabelToggle *) gui1->addLabelToggle("SELECT AREA", false, 200);
		gui1->addWidgetDown(new ofxUIFbo(200, 200, &ildaFbo->getFbo(), "ORIGINAL IMAGE"));
        
        ofAddListener(gui1->newGUIEvent,this,&captureUI::guiEvent);
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