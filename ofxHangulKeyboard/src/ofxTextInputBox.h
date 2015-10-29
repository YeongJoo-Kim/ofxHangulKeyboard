#include "ofMain.h"
#include "ofxMSAInteractiveObject.h"
#include "ofxFTGLFont.h"
#include "..\libs\AutomataKR.h"
class ofxTextInputBox: public ofxMSAInteractiveObject {

public:

	ofxTextInputBox();
	~ofxTextInputBox();
	static const int CURSOR_WIDTH = 5;
	

	wstring MultiByteToWideCharString(const string multibyte)
	{
		wchar_t unicode[1024] = {0,};

		MultiByteToWideChar(CP_ACP, MB_COMPOSITE, (LPCSTR)multibyte.c_str(), multibyte.size() + 1, unicode, 1024);

		return wstring(unicode);
	}


	static ofEvent<ofxTextInputBox>		TextInputBox_ClickDownEvent;
	wstring	m_strText;
	string	m_strControlID;
	
	ofxFTGLFont		m_TextFont;
	CAutomataKR		m_Automata;
	map<char, int>	m_HangulKeyTable;

	float  m_fCoursorDrawTime;

	bool	m_bSelected;

	int		m_iAlphaValue;

	
	void enable(bool bEnable)
	{
		if(bEnable)
		{
			ofAddListener(ofEvents().draw, this, &ofxTextInputBox::draw);
			enableMouseEvents();
		}
		else
		{
			ofRemoveListener(ofEvents().draw, this, &ofxTextInputBox::draw);
			disableMouseEvents();

			m_strText = L"";
			m_Automata.Clear();
		}
	}

	void select(bool bSelect = true)
	{
		m_bSelected = bSelect;
	}

	void setup(ofEventArgs &e) 
	{
		m_TextFont.loadFont("NanumGothic.ttf", 20, true);

		m_TextFont.drawString(L" ", 0, 0);
	}

	void setText(string& strText)
	{
		m_strText = MultiByteToWideCharString(strText);
	}

	wstring getText()
	{
		return m_strText;
	}

	void keyDown(int iKey);
	
	void draw(ofEventArgs &e);

	virtual void onPress(int x, int y, int button) 
	{
		m_bSelected = true;
		ofNotifyEvent(ofxTextInputBox::TextInputBox_ClickDownEvent, *this);
	}

	virtual void onRelease(int x, int y, int button) {
		//ofNotifyEvent(ofxTextInputBox::TextInputBox_ClickDownEvent, *this);
	}

	virtual void onReleaseOutside(int x, int y, int button) {
		//ofNotifyEvent(ofxTextInputBox::TextInputBox_ClickDownEvent, *this);
	}

};
