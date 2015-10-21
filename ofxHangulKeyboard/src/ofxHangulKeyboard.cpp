
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
	m_LocalPosition = ofPoint(38, 686, 0);
	float _x = m_LocalPosition.x;
	float _y = m_LocalPosition.y;

	m_enLanguage = EN_KL_ENGLISH;

	m_KeyboardImage[KEYBOARD_IMAGE_NORMAL].loadImage("images/input_name/keybard_off.png");
	m_KeyboardImage[KEYBOARD_IMAGE_PRESS].loadImage("images/input_name/keybard_on.png");
	
	ofxKey::setKeyboardBasePosition(m_LocalPosition);
	ofxKey::_KeyBoardImage_Press = m_KeyboardImage[KEYBOARD_IMAGE_PRESS];
	

	//2nd line
	m_KeyMap['q'] = ofxKey(32, 22, 82, 86, 'q');
	m_KeyMap['w'] = ofxKey(135, 22, 82, 86, 'w');
	m_KeyMap['e'] = ofxKey(237, 22, 82, 86, 'e');
	m_KeyMap['r'] = ofxKey(340, 22, 82, 86, 'r');
	m_KeyMap['t'] = ofxKey(442 ,22, 82, 86, 't');
	m_KeyMap['y'] = ofxKey(545, 22, 82, 86, 'y');
	m_KeyMap['u'] = ofxKey(647, 22, 82, 86, 'u');
	m_KeyMap['i'] = ofxKey(750, 22, 82, 86, 'i');
	m_KeyMap['o'] = ofxKey(852, 22, 82, 86, 'o');
	m_KeyMap['p'] = ofxKey(955, 22, 82, 86, 'p');
	m_KeyMap[OF_KEY_BACKSPACE] = ofxKey(1059, 22, 117, 86, OF_KEY_BACKSPACE); 

	//3th line
	m_KeyMap[OF_KEY_LEFT_SHIFT] = ofxKey(58, 111, 117, 86, OF_KEY_LEFT_SHIFT);
	m_KeyMap['a'] = ofxKey(186, 111, 82, 86, 'a');
	m_KeyMap['s'] = ofxKey(289, 111, 82, 86, 's');
	m_KeyMap['d'] = ofxKey(391, 111, 82, 86, 'd');
	m_KeyMap['f'] = ofxKey(494, 111, 82, 86, 'f');
	m_KeyMap['g'] = ofxKey(596, 111, 82, 86, 'g');
	m_KeyMap['h'] = ofxKey(699, 111, 82, 86, 'h');
	m_KeyMap['j'] = ofxKey(801, 111, 82, 86, 'j');
	m_KeyMap['k'] = ofxKey(904, 111, 82, 86, 'k');
	m_KeyMap['l'] = ofxKey(1006, 111, 82, 86, 'l');
							
	//4th line
	m_KeyMap['z'] = ofxKey(31, 200,  82, 86, 'z');
	m_KeyMap['x'] = ofxKey(134, 200, 82, 86, 'x');
	m_KeyMap['c'] = ofxKey(236, 200, 82, 86, 'c');
	m_KeyMap['v'] = ofxKey(339, 200, 82, 86, 'v');
	m_KeyMap['b'] = ofxKey(441, 200, 82, 86, 'b');
	m_KeyMap['n'] = ofxKey(544, 200, 82, 86, 'n');
	m_KeyMap['m'] = ofxKey(646, 200, 82, 86, 'm');
							
	m_KeyMap[' '] = ofxKey(751, 200, 287, 86 , ' ');
	m_KeyMap[OF_KEY_RETURN] = ofxKey(1060, 200, 115, 86, OF_KEY_RETURN);

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
	
	if(!m_Tween.isCompleted())
	{
		float fTween = m_Tween.update();
		int iWindowsHeight = ofGetHeight();

		int _y  = iWindowsHeight - (float(iWindowsHeight - m_LocalPosition.y) *  fTween);

		m_KeyboardImage[KEYBOARD_IMAGE_NORMAL].draw(m_LocalPosition.x, _y);
	}
	else
	{
		m_KeyboardImage[KEYBOARD_IMAGE_NORMAL].draw(m_LocalPosition);		
	}


	if(m_bShowKeyboard) for(auto it = m_KeyMap.begin() ; it != m_KeyMap.end() ; ++it) it->second.draw();

	ofPushMatrix();
	ofTranslate(m_LocalPosition.x, m_LocalPosition.y);

	//

	//ofFill();
	//ofSetHexColor(backgroundColor);
	//rBox();

// 	ofNoFill();
// 	ofSetLineWidth(2);
// 	ofSetHexColor(foregroundColor);
// 	rBox();

	ofPopMatrix();
}
/*
void ofxHangulKeyboard::ClearKeyBuffer()
{
	m_wstrKeyboardText = L"";

	m_automataKr.Clear();
}
*/
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
		m_KeyMap[OF_KEY_LEFT_SHIFT].setKeepPress(true);
		break;
	default:
		if(m_KeyMap[OF_KEY_LEFT_SHIFT].getKeepPress())
		{
			iKeyCode -= ('a' - 'A');
			m_KeyMap[OF_KEY_LEFT_SHIFT].setKeepPress(false);
		}

		ofNotifyEvent(KeyboardPressEvent, iKeyCode);

			
		break;
	}
}
