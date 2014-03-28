#pragma once

#include "config.h"
#include "sidebarUI.h"
#include "captureUI.h"
#include "drawUI.h"
#include "receiveUI.h"

class sidebar {
    
public:
    
    void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
   		panelDraw = new drawUI();
		panels.push_back(panelDraw);
		
		panelCapture = new captureUI();
		panels.push_back(panelCapture);
		
		panelReceive = new receiveUI();
		panels.push_back(panelReceive);
		
		for(int i=0; i<panels.size(); i++) {
			panels[i]->setup(ildaFbo, ildaFrame);
		}
	}
	
	void update()
	{
		for(int i=0; i<panels.size(); i++) {
			panels[i]->update();
		}
	}
	
	void draw()
	{
		for(int i=0; i<panels.size(); i++) {
			panels[i]->draw();
		}
	}
	
	void setX(int x)
	{
		for(int i=0; i<panels.size(); i++) {
			panels[i]->gui1->setPosition(x, 60);
		}
		
	}
	
	drawUI * panelDraw;
	captureUI * panelCapture;
	receiveUI * panelReceive;
	
	vector<sidebarUI *> panels;
};