#pragma once

#include "config.h"
#include "button.h"
#include "UI.h"
#include "modeUI.h"
#include "effectUI.h"
#include "outputUI.h"
#include "pathUI.h"
#include "viewUI.h"
#include "saveUI.h"

class menu {
    
public:
    
    void setup(ofxIlda::RenderTarget * ildaFbo, ofxIlda::Frame * ildaFrame)
    {
   		int buttonSize = 60;
		
		buttonMode = new button();
		buttonMode->setup("mode", 0, buttonSize*1,buttonSize,buttonSize,"gui/images/menu_mode.png",ofColor(12,56,64));
		buttons.push_back(buttonMode);
		
		buttonEffect = new button();
		buttonEffect->setup("effect", 0, buttonSize*2,buttonSize,buttonSize,"gui/images/menu_effect.png",ofColor(19,91,91));
		buttons.push_back(buttonEffect);
		
		buttonOutput = new button();
		buttonOutput->setup("output", 0, buttonSize*3,buttonSize,buttonSize,"gui/images/menu_output.png",ofColor(22,115,105));
		buttons.push_back(buttonOutput);
		
		buttonPath = new button();
		buttonPath->setup("path", 0, buttonSize*4,buttonSize,buttonSize,"gui/images/menu_path.png",ofColor(20,140,113));
		buttons.push_back(buttonPath);
		
		buttonView = new button();
		buttonView->setup("view", 0, buttonSize*5,buttonSize,buttonSize,"gui/images/menu_view.png",ofColor(23,154,113));
		buttons.push_back(buttonView);
		
		buttonSave = new button();
		buttonSave->setup("save", 0, buttonSize*6,buttonSize,buttonSize,"gui/images/menu_save.png",ofColor(134,203,113));
		buttons.push_back(buttonSave);
		
		for(int j=0; j<buttons.size(); j++){
			ofAddListener(buttons[j]->onClick, this, &menu::onButtonClick);
		}
		
		panelMode = new modeUI();
		panels.push_back(panelMode);
		
		panelEffect = new effectUI();
		panels.push_back(panelEffect);
		
		panelOutput = new outputUI();
		panels.push_back(panelOutput);
		
		panelPath = new pathUI();
		panels.push_back(panelPath);
		
		panelView = new viewUI();
		panels.push_back(panelView);
		
		panelSave = new saveUI();
		panels.push_back(panelSave);
		
		for(int i=0; i<panels.size(); i++) {
			panels[i]->setup(ildaFbo, ildaFrame);
			panels[i]->gui1->setVisible(false);
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
		for(int i=0; i<buttons.size(); i++) {
			buttons[i]->setPosition(x, buttons[i]->y);
			panels[i]->gui1->setPosition(x+60, buttons[i]->y);
		}
		
	}
	
	void onButtonClick(string & name)
	{
		bool state;
		for(int i=0; i<buttons.size(); i++) {
			state = buttons[i]->name==name && !buttons[i]->enable;
			buttons[i]->enable = state;
			panels[i]->gui1->setVisible(state);
		}
	}
	
private:
	
	button * buttonMode;
	button * buttonEffect;
	button * buttonOutput;
	button * buttonPath;
	button * buttonView;
	button * buttonSave;
	
	vector<button *> buttons;
	
	
	modeUI * panelMode;
	effectUI * panelEffect;
	outputUI * panelOutput;
	pathUI * panelPath;
	viewUI * panelView;
	saveUI * panelSave;
    
	vector<UI *> panels;
};