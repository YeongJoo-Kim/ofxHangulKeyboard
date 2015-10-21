/********  Test sample for ofxInteractiveObject									********/
/********  Make sure you open your console to see all the events being output	********/


#pragma once

#include "ofxMSAInteractiveObject.h"

#define		IDLE_COLOR		0xFFFFFF
#define		OVER_COLOR		0x00FF00
#define		DOWN_COLOR		0xFF0000


class ofxKey : public ofxMSAInteractiveObject {
public:
	ofxKey() : ofxMSAInteractiveObject()
	{
		set(m_KeyboardPosition.x + 0, m_KeyboardPosition.y + 0, 0, 0);

		m_fKeyPosX		= 0;
		m_fKeyPosY		= 0;
		m_keyCode		= 0;

		m_bKeepPressed = false;
	}

	ofxKey(float _x, float _y, float _w, float _h, int _key) :ofxMSAInteractiveObject()
	{

		set(m_KeyboardPosition.x + _x, m_KeyboardPosition.y + _y, _w, _h);

		m_fKeyPosX		= _x;
		m_fKeyPosY		= _y;
		m_keyCode		= _key;

		m_bKeepPressed = false;
	}
	void setup() 
	{
		ofxKey::m_KeyboardPosition = ofPoint(0.0f, 0.0f);

	//	disableMouseEvents();
		disableAppEvents();
	}
	
	void exit() 
	{
	}
	
	void update() 
	{
	}

	void setKey(float x, float y, float w, float h, int key)
	{
		set(m_KeyboardPosition.x + x, m_KeyboardPosition.y + y, w, h);

		m_fKeyPosX		= x;
		m_fKeyPosY		= y;

		m_keyCode = key;
	}

	void setKeepPress(bool bPress = true)
	{
		m_bKeepPressed = bPress;
	}

	bool getKeepPress()
	{
		return m_bKeepPressed;
	}

	//--------------------------------------------------------------
//	bool ofxMSAInteractiveObject::hitTest(int tx, int ty) const {
//		return ((tx > m_KeyboardPosition.x + x) && (tx < m_KeyboardPosition.x + x + width) && (ty > m_KeyboardPosition.y + y) && (ty < m_KeyboardPosition.y + y + height));
//	}


	
	
	void draw() 
	{
		if(isMousePressed() || m_bKeepPressed)
		{
			_KeyBoardImage_Press.drawSubsection(x, y, width, height, m_fKeyPosX, m_fKeyPosY);
		}
		else if(isMouseOver())
		{

		}
		else
		{

		}
	}
	
	virtual void onRollOver(int x, int y) {
		//printf("MyTestObject::onRollOver(x: %i, y: %i)\n", x, y);
	}
	
	virtual void onRollOut() {
		//printf("MyTestObject::onRollOut()\n");
	}
	
	virtual void onMouseMove(int x, int y){
		//printf("MyTestObject::onMouseMove(x: %i, y: %i)\n", x, y);
	}
	
	virtual void onDragOver(int x, int y, int button) {
		//printf("MyTestObject::onDragOver(x: %i, y: %i, button: %i)\n", x, y, button);
	}
	
	virtual void onDragOutside(int x, int y, int button) {
		//printf("MyTestObject::onDragOutside(x: %i, y: %i, button: %i)\n", x, y, button);
	}
	
	virtual void onPress(int x, int y, int button) 
	{
	//	printf("MyTestObject::onPress(x: %i, y: %i, button: %i)\n", x, y, button);

		ofNotifyEvent(ofxKey::KeyEvent, *this);


	}
	
	virtual void onRelease(int x, int y, int button) {
		//printf("MyTestObject::onRelease(x: %i, y: %i, button: %i)\n", x, y, button);
		ofNotifyEvent(ofxKey::KeyUpEvent, *this);
	}
	
	virtual void onReleaseOutside(int x, int y, int button) {
		//printf("MyTestObject::onReleaseOutside(x: %i, y: %i, button: %i)\n", x, y, button);

		ofNotifyEvent(ofxKey::KeyUpEvent, *this);
	}

	static ofEvent<ofxKey>		KeyEvent;
	static ofEvent<ofxKey>		KeyUpEvent;
	static ofImage				_KeyBoardImage_Press;

	int getKeyCode() {return m_keyCode;};
	
	static void setKeyboardBasePosition(ofPoint &position) 
	{ 
		m_KeyboardPosition = position; 
	};

protected:
	int		m_keyCode;
	float	m_fKeyPosX;
	float	m_fKeyPosY;
	bool	m_bKeepPressed;
	static ofPoint		m_KeyboardPosition;
};