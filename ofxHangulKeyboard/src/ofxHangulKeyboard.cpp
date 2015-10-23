
#include "ofxHangulKeyboard.h"

ofPoint ofxKey::m_KeyboardPosition = ofPoint(.0f, .0f);
ofEvent<ofxKey>	ofxKey::KeyEvent;
ofEvent<ofxKey>	ofxKey::KeyUpEvent;
ofImage ofxKey::_KeyBoardImage_Press;

ofEvent<int> ofxHangulKeyboard::KeyboardPressEvent;

ofxHangulKeyboard::ofxHangulKeyboard()
{
	

	m_wstrKeyboardText = L"";
	ofAddListener(ofEvents().setup, this, &ofxHangulKeyboard::_setup);
//	enableAppEvents();
}

ofxHangulKeyboard::~ofxHangulKeyboard()
{

}
/*
void ofxHangulKeyboard::enableAppEvents() {
	
//	ofAddListener(ofEvents().setup, this, &ofxHangulKeyboard::_setup);
	ofAddListener(ofEvents().update, this, &ofxHangulKeyboard::_update);
	ofAddListener(ofEvents().draw, this, &ofxHangulKeyboard::_draw);
}

void ofxHangulKeyboard::disableAppEvents()
{
//	ofRemoveListener(ofEvents().setup, this, &ofxHangulKeyboard::_setup);
	ofRemoveListener(ofEvents().update, this, &ofxHangulKeyboard::_update);
	ofRemoveListener(ofEvents().draw, this, &ofxHangulKeyboard::_draw);
}
*/
void ofxHangulKeyboard::_setup(ofEventArgs &e)
{
	setup();
}



void ofxHangulKeyboard::setup()
{
	m_LocalPosition = ofPoint(0, 410, 0);
	float _x = m_LocalPosition.x;
	float _y = m_LocalPosition.y;

	m_enLanguage = EN_KL_ENGLISH;

	m_KeyboardImage[KEYBOARD_IMAGE_NORMAL].loadImage("normal.png");
	m_KeyboardImage[KEYBOARD_IMAGE_PRESS].loadImage("push.png");
	
	ofxKey::setKeyboardBasePosition(m_LocalPosition);
	ofxKey::_KeyBoardImage_Press = m_KeyboardImage[KEYBOARD_IMAGE_PRESS];
	
	//첫번째줄
	m_KeyMap[OF_KEY_BACKSPACE] = ofxKey(893, 12, 118, 59, OF_KEY_BACKSPACE); 

	//2nd line
	m_KeyMap['q'] = ofxKey(111, 81, 59, 59, 'q');
	m_KeyMap['w'] = ofxKey(179, 81, 59, 59, 'w');
	m_KeyMap['e'] = ofxKey(246, 81, 59, 59, 'e');
	m_KeyMap['r'] = ofxKey(314, 81, 59, 59, 'r');
	m_KeyMap['t'] = ofxKey(381 ,81, 59, 59, 't');
	m_KeyMap['y'] = ofxKey(449, 81, 59, 59, 'y');
	m_KeyMap['u'] = ofxKey(516, 81, 59, 59, 'u');
	m_KeyMap['i'] = ofxKey(584, 81, 59, 59, 'i');
	m_KeyMap['o'] = ofxKey(652, 81, 59, 59, 'o');
	m_KeyMap['p'] = ofxKey(719, 81, 59, 59, 'p');

	//3th line
	m_KeyMap['a'] = ofxKey(141, 149, 59, 59, 'a');
	m_KeyMap['s'] = ofxKey(209, 149, 59, 59, 's');
	m_KeyMap['d'] = ofxKey(277, 149, 59, 59, 'd');
	m_KeyMap['f'] = ofxKey(346, 149, 59, 59, 'f');
	m_KeyMap['g'] = ofxKey(414, 149, 59, 59, 'g');
	m_KeyMap['h'] = ofxKey(483, 149, 59, 59, 'h');
	m_KeyMap['j'] = ofxKey(551, 149, 59, 59, 'j');
	m_KeyMap['k'] = ofxKey(619, 149, 59, 59, 'k');
	m_KeyMap['l'] = ofxKey(688, 149, 59, 59, 'l');
	m_KeyMap[OF_KEY_RETURN] = ofxKey(893, 149, 118, 59, OF_KEY_RETURN);

	//4th line
	m_KeyMap[OF_KEY_LEFT_SHIFT] = ofxKey(13, 218, 147, 59, OF_KEY_LEFT_SHIFT);
	m_KeyMap['z'] = ofxKey(170, 218,  59, 59, 'z');
	m_KeyMap['x'] = ofxKey(236, 218, 59, 59, 'x');
	m_KeyMap['c'] = ofxKey(302, 218, 59, 59, 'c');
	m_KeyMap['v'] = ofxKey(369, 218, 59, 59, 'v');
	m_KeyMap['b'] = ofxKey(435, 218, 59, 59, 'b');
	m_KeyMap['n'] = ofxKey(501, 218, 59, 59, 'n');
	m_KeyMap['m'] = ofxKey(567, 218, 59, 59, 'm');
	m_KeyMap[OF_KEY_RIGHT_SHIFT] = ofxKey(834, 218, 177, 59, OF_KEY_RIGHT_SHIFT);
							
	m_KeyMap[' '] = ofxKey(262, 286, 415, 59 , ' ');
	m_KeyMap[OF_KEY_HANGUL] = ofxKey(687, 286, 73, 59 , ' ');


	ofAddListener(ofxKey::KeyEvent, this, &ofxHangulKeyboard::keyDownEvent);
	ofAddListener(ofxKey::KeyUpEvent, this, &ofxHangulKeyboard::keyUpEvent);

	showKeyboard(m_bShowKeyboard);
}

bool ofxHangulKeyboard::isShowKeyboard()
{
	return m_bShowKeyboard;
}

void ofxHangulKeyboard::showKeyboard(bool show)
{
	m_bShowKeyboard = show;

	for(auto it = m_KeyMap.begin() ; it != m_KeyMap.end() ; ++it)
	{
		if(m_bShowKeyboard)
			it->second.enableMouseEvents();
		else 
			it->second.disableMouseEvents();
	}

// 	if(m_bShowKeyboard)
// 		enableAppEvents();
// 	else 
// 		disableAppEvents();

	m_Tween.setParameters(0, m_easingCubic, ofxTween::easeOut, 0, 1.0 , 1000, 0);
}

void ofxHangulKeyboard::update()
{

}

void ofxHangulKeyboard::draw()
{
	if(!m_bShowKeyboard) return;

	ofSetColor(0xff, 0xff, 0xff);

	ofEnableAlphaBlending();
	
	m_KeyboardImage[KEYBOARD_IMAGE_NORMAL].draw(m_LocalPosition);


	if(m_bShowKeyboard) for(auto it = m_KeyMap.begin() ; it != m_KeyMap.end() ; ++it) it->second.draw();

}

void ofxHangulKeyboard::keyUpEvent(ofxKey &e)
{
	int iKeyCode = e.getKeyCode();
	switch (iKeyCode)
	{
	case OF_KEY_RETURN:
 		ofNotifyEvent(KeyboardPressEvent, iKeyCode);
		break;
	default:
		break;
	}
}

void ofxHangulKeyboard::keyDownEvent(ofxKey &e) {

	int iKeyCode = e.getKeyCode();

	switch (iKeyCode)
	{
	case OF_KEY_RETURN:
	//	m_keys[40].showPressImage();
	//	m_keys[41].showPressImage();
		break;
	case OF_KEY_LEFT_SHIFT:
	case OF_KEY_RIGHT_SHIFT:
		m_KeyMap[OF_KEY_LEFT_SHIFT].setKeepPress(true);
		m_KeyMap[OF_KEY_RIGHT_SHIFT].setKeepPress(true);
		break;
	default:
		if(m_KeyMap[OF_KEY_LEFT_SHIFT].getKeepPress() || m_KeyMap[OF_KEY_RIGHT_SHIFT].getKeepPress())
		{
			iKeyCode -= ('a' - 'A');
			m_KeyMap[OF_KEY_LEFT_SHIFT].setKeepPress(false);
			m_KeyMap[OF_KEY_RIGHT_SHIFT].setKeepPress(false);
		}

		ofNotifyEvent(KeyboardPressEvent, iKeyCode);
		break;
	}
}
