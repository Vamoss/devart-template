#pragma once

#include "ofMain.h"
#include "ofxMSAInteractiveObject.h"

class button : public ofxMSAInteractiveObject {
    
public:
	ofEvent<string> onClick;
	
	string name;
	bool enable;
	
	void setup(string name, int x, int y, int width, int height, string path, ofColor color)
	{
		this->name = name;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->color = color;
		
		image.loadImage(path);
		enable = false;
		
		enableMouseEvents();
	};
	
	void update()
	{
	
	};
	
	void draw()
	{
		ofPushMatrix();
			ofTranslate(this->x, this->y);
			ofPushStyle();
				ofFill();
				ofSetColor(color);
				ofRect(0, 0, this->width, this->height);
				ofSetColor(255, (enable||isMouseOver()) ? 255 : 125);
				image.draw(0, 0);
			ofPopStyle();
		ofPopMatrix();
	};
	
	void onRelease(int x, int y, int button)
	{
		ofNotifyEvent(onClick, name);
	}

	
private:
	ofColor color;
	ofImage image;
};