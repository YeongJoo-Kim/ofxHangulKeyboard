#ifndef _ofxKEYBOARD
#define _ofxKEYBOARD

#include <iostream>
#include <fstream>
#include "ofxKey.h"
#define OF_KEY_HANGUL	0xF2

class ofxHangulKeyboard
{
public:
	ofxHangulKeyboard();
	~ofxHangulKeyboard();

	enum enKeyboardLanauage
	{
		EN_KL_ENGLISH = 0,
		EN_KL_HANGUL
	};
	
	enum KEYBOARD_IMAGE
	{
		KEYBOARD_IMAGE_NORMAL = 0,
		KEYBOARD_IMAGE_PRESS,
		KEYBOARD_IMAGE_MAX,
	};

	map<int , ofxKey> m_KeyMap;

	wstring getText() {return m_wstrKeyboardText;};
	void setText(wstring text) {m_wstrKeyboardText = text;}

	void _setup(ofEventArgs &e);
	void _update(ofEventArgs &e);
	void _draw(ofEventArgs &e);

	void setup();
	void update();
	void draw();

	void keyDownEvent(ofxKey &e);
	void keyUpEvent(ofxKey &e);

	void showKeyboard(bool show);
	bool isShowKeyboard();

	static ofEvent<int>	KeyboardPressEvent;

protected:

	wstring MultiByteToWideByteString(const string multibyte)
	{
		wchar_t unicode[1024] = {0,};

		MultiByteToWideChar(CP_ACP, MB_COMPOSITE, (LPCSTR)multibyte.c_str(), multibyte.size() + 1, unicode, 1024);

		return wstring(unicode);
	}

	string WideCharToMultibyteString(const wchar_t* unicode)
	{
		char multibyte[1024] = {0,};

		WideCharToMultiByte(CP_ACP, 0, unicode, wcslen(unicode) + 1, multibyte, 1024, 0, NULL);

		return string(multibyte);
	}

	//void enableAppEvents();
	//void disableAppEvents();

	enKeyboardLanauage	m_enLanguage;
	bool		m_bShowKeyboard;
	ofPoint		m_LocalPosition;

	wstring m_wstrKeyboardText;

	string m_strKeyboardText;
	
	ofImage		m_KeyboardImage[KEYBOARD_IMAGE_MAX];
};

#endif
