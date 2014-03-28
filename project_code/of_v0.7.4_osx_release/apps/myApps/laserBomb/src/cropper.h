#ifndef CROPPER
#define CROPPER

#include "ofMain.h"

struct selectableButton
{
	int x, y;

	int hitArea, visibleArea;

	bool dragH, dragV;

	bool selected;

	selectableButton(bool dragH, bool dragV)
	{
		this->dragH = dragH;
		this->dragV = dragV;

		hitArea = 32;
		visibleArea = 20;
		selected = false;
	}

	void draw()
	{
		ofPushStyle();
			ofSetColor(0);
			ofRect(x-visibleArea+1, y-visibleArea+1, visibleArea+visibleArea, visibleArea+visibleArea);
			if(selected){
				ofSetColor(255, 255, 255);
			}else{
				ofSetColor(255, 125, 0);
			}
			ofRect(x-visibleArea, y-visibleArea, visibleArea+visibleArea, visibleArea+visibleArea);
		ofPopStyle();
	}

	bool checkHit(int xx, int yy)
	{
		return (xx>x-hitArea && xx<x+hitArea && yy>y-hitArea && yy< y+hitArea);
	}

	void select()
	{
		selected = true;
	}

	void unselect()
	{
		selected = false;
	}
};

class cropper : public ofRectangle
{
public:
	int minX, minY, maxX, maxY;
	
	float scale;

	void setup(int x, int y, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;

		scale = 1;
		
		minX = 0;
		minY = 0;
		maxX = width;
		maxY = height;

		selectableButton * b;
		
		//first is top left and other are clock wise
		buttons.push_back(new selectableButton(true, true));
		buttons.push_back(new selectableButton(false, true));
		buttons.push_back(new selectableButton(true, true));
		buttons.push_back(new selectableButton(true, false));
		buttons.push_back(new selectableButton(true, true));
		buttons.push_back(new selectableButton(false, true));
		buttons.push_back(new selectableButton(true, true));
		buttons.push_back(new selectableButton(true, false));

		updatePosition();
	}

	void update()
	{

	}

	void draw()
	{
		ofPushMatrix();
			ofScale(scale, scale);
			ofPushStyle();
				ofNoFill();
				ofSetColor(0);
				ofRect(x+1, y+1, width, height);
				ofSetColor(255, 125, 0);
				ofRect(*this);
				for(int i=0; i<buttons.size(); i++){
					buttons[i]->draw();
				}
			ofPopStyle();
		ofPopMatrix();
	}

	void keyPressed  (int key)
	{
		if(key==OF_KEY_LEFT){
			movePoints(-1, 0);
		}else if(key==OF_KEY_RIGHT){
			movePoints(1, 0);
		}else if(key==OF_KEY_UP){
			movePoints(0, -1);
		}else if(key==OF_KEY_DOWN){
			movePoints(0, 1);
		}
	}

	void mousePressed(int x, int y, int button)
	{
		x = x/scale;
		y = y/scale;
		
		for(int i=0; i<buttons.size(); i++){
			if(buttons[i]->checkHit(x, y)){
				buttons[i]->select();
			}else{
				buttons[i]->unselect();
			}
		}
		
		lastMouseX = x;
		lastMouseY = y;
	}

	void mouseDragged(int x, int y, int button)
	{
		x = x/scale;
		y = y/scale;
		
		movePoints(x-lastMouseX, y-lastMouseY);
		lastMouseX = x;
		lastMouseY = y;

		updatePosition();
	}

private:
	void movePoints(int xx, int yy)
	{
		if(buttons[0]->selected){
			if(x+xx>minX && x+xx<maxX){
				x += xx;
				width -= xx;
			}
			if(y+yy>minY && y+yy<maxY){
				y += yy;
				height -= yy;
			}
		}else if(buttons[1]->selected){
			if(y+yy>minY && y+yy<maxY){
				y += yy;
				height -= yy;
			}
		}else if(buttons[2]->selected){
			if(width+x+xx>minX && width+x+xx<maxX){
				width += xx;
			}
			if(y+yy>minY && y+yy<maxY){
				y += yy;
				height -= yy;
			}
		}else if(buttons[3]->selected){
			if(width+x+xx>minX && width+x+xx<maxX){
				width += xx;
			}
		}else if(buttons[4]->selected){
			if(width+x+xx>minX && width+x+xx<maxX){
				width += xx;
			}
			if(height+y+yy>minY && height+y+yy<maxY){
				height += yy;
			}
		}else if(buttons[5]->selected){
			if(height+y+yy>minY && height+y+yy<maxY){
				height += yy;
			}
		}else if(buttons[6]->selected){
			if(x+xx>minX && x+xx<maxX){
				x += xx;
				width -= xx;
			}
			if(height+y+yy>minY && height+y+yy<maxY){
				height += yy;
			}
		}else if(buttons[7]->selected){
			if(x+xx>minX && x+xx<maxX){
				x += xx;
				width -= xx;
			}
		}

		updatePosition();
	}

	void updatePosition()
	{
		buttons[0]->x = x;
		buttons[0]->y = y;

		buttons[1]->x = x+(width/2);
		buttons[1]->y = y;

		buttons[2]->x = x+width;
		buttons[2]->y = y;

		buttons[3]->x = x+width;
		buttons[3]->y = y+(height/2);

		buttons[4]->x = x+width;
		buttons[4]->y = y+height;

		buttons[5]->x = x+(width/2);
		buttons[5]->y = y+height;

		buttons[6]->x = x;
		buttons[6]->y = y+height;

		buttons[7]->x = x;
		buttons[7]->y = y+(height/2);
	}

	vector<selectableButton *> buttons;

	int lastMouseX;
	int lastMouseY;
};

#endif