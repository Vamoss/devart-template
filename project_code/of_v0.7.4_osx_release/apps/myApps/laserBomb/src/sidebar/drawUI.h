#pragma once

#include "config.h"
#include "sidebarUI.h"

class drawUI : public sidebarUI {
    
public:
    void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
		sidebarUI::setup(220, 800, ildaFbo, ildaFrame);
		
        setGUI1();
        
        gui1->loadSettings("GUI/settings.xml");
    }
    
	
	void setGUI1()
    {
		gui1->addLabel("DRAW", OFX_UI_FONT_LARGE);
		
		names.push_back("WHITE");
		names.push_back("RED");
		names.push_back("YELLOW");
		names.push_back("GREEN");
		names.push_back("CYAN");
		names.push_back("BLUE");
		names.push_back("DARK BLUE");
		names.push_back("MAGENTA");
		
		colors.push_back(ofColor(255, 255, 255, 255));
		colors.push_back(ofColor(255, 0, 0, 255));
		colors.push_back(ofColor(255, 255, 0, 255));
		colors.push_back(ofColor(0, 255, 0, 255));
		colors.push_back(ofColor(0, 255, 255, 255));
		colors.push_back(ofColor(0, 0, 255, 255));
		colors.push_back(ofColor(0, 0, 200, 255));
		colors.push_back(ofColor(255, 0, 255, 255));
		
		ofxUIRadio* colorRadio = new ofxUIRadio("COLORS", names, OFX_UI_ORIENTATION_VERTICAL, 32, 32);
		
		//ofxUIToggleMatrix * colorToggle = new ofxUIToggleMatrix(dim*3.0, dim*3.0, 1, colors.size(), "MATRIX3");
		vector<ofxUIToggle *> toggles =  colorRadio->getToggles();
		for(int i = 0; i < toggles.size(); i++)
		{
			ofxUIToggle *t = toggles[i];
			t->setColorFill(colors[i]);
			t->setColorOutlineHighlight(colors[i]);
			t->setColorBack(ofColor(colors[i].r, colors[i].g, colors[i].b, 125));
		}
		
		gui1->addWidgetDown(colorRadio);
		brushThicknessSlider = (ofxUISlider *) gui1->addSlider("Brush Thickiness", 0.0, 255.0, 15, 200, 16);
		eraserToggle = (ofxUILabelToggle *) gui1->addLabelToggle("Eraser", false, 200);
		clearButton = (ofxUILabelButton *) gui1->addLabelButton("Clear", false, 200);
		gui1->addWidgetDown(new ofxUIFbo(200, 200, &ildaFbo->getFbo(), "ORIGINAL IMAGE"));
		
		
        ofAddListener(gui1->newGUIEvent,this,&drawUI::guiEvent);
    }
    
    
    void guiEvent(ofxUIEventArgs &e)
    {
        string name = e.widget->getName();
        int kind = e.widget->getKind();
        cout << "got event from: " << name << endl;
		
		for(int i=0; i<names.size(); i++){
			if(names[i]==name){
				ildaFrame->params.output.color = colors[i];
				return;
			}
		}
	}
    
    void save()
    {
        gui1->saveSettings("GUI/settings.xml");
    }
	
	vector<string> names;
	vector<ofColor> colors;
	
	ofxUISlider * brushThicknessSlider;
	ofxUILabelToggle * eraserToggle;
	ofxUILabelButton * clearButton;
	
    
};