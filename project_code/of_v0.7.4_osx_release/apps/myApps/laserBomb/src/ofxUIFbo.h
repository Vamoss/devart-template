#ifndef OFXUI_FBO
#define OFXUI_FBO

#include "ofxUIWidgetWithLabel.h"

class ofxUIFbo : public ofxUIWidgetWithLabel
{
public:
    ofxUIFbo(float x, float y, float w, float h, ofFbo *_fbo, string _name) : ofxUIWidgetWithLabel()
    {
        rect = new ofxUIRectangle(x,y,w,h);
        init(w, h, _fbo, _name);
    }
    
    ofxUIFbo(float x, float y, float w, float h, ofFbo *_fbo, string _name, bool _showLabel) : ofxUIWidgetWithLabel()
    {
        rect = new ofxUIRectangle(x,y,w,h);
        init(w, h, _fbo, _name);
        showLabel = _showLabel;
    }
    
    ofxUIFbo(float w, float h, ofFbo *_fbo, string _name) : ofxUIWidgetWithLabel()
    {
        rect = new ofxUIRectangle(0,0,w,h);
        init(w, h, _fbo, _name);
    }
	
    ofxUIFbo(float w, float h, ofFbo *_fbo, string _name, bool _showLabel) : ofxUIWidgetWithLabel()
    {
        rect = new ofxUIRectangle(0,0,w,h);
        init(w, h, _fbo, _name);
        showLabel = _showLabel;
    }
    
    void init(float w, float h, ofFbo *_fbo, string _name)
    {
		name = string(_name);
		kind = OFX_UI_WIDGET_IMAGE;
        showLabel = true;
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect);
        
        draw_back = false;
        draw_fill = true;
        
		fbo = _fbo;
        
		label = new ofxUILabel(0,h+padding,(name+" LABEL"),name, OFX_UI_FONT_SMALL);
		label->setParent(label);
		label->setRectParent(rect);
        label->setEmbedded(true);
    }
    
    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect;
        label->setDrawPadding(false);
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline;
        label->setDrawPaddingOutline(false);
	}
    
    virtual void drawFill()
    {
        if(draw_fill)
        {
			if(fbo != NULL)
			{
				ofFill();
				ofSetColor(255);
				fbo->draw(rect->getX(), rect->getY(), rect->width, rect->height);
			}
        }
    }
	
    virtual void setVisible(bool _visible)
    {
        visible = _visible;
        label->setVisible(showLabel);
    }
	
	ofxUILabel *getLabel()
	{
		return label;
	}
    
    void setFbo(ofFbo *_fbo)
    {
        fbo = _fbo;
    }
	
	virtual void setParent(ofxUIWidget *_parent)
	{
		parent = _parent;
        if(showLabel)
        {
            paddedRect->height += label->getPaddingRect()->height;
        }
        else
        {
            paddedRect->height += padding;
        }
        label->setVisible(showLabel);
	}
	
    virtual bool isDraggable()
    {
        return false;
    }
    
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent;
	ofFbo *fbo;
    bool showLabel;
};

#endif
