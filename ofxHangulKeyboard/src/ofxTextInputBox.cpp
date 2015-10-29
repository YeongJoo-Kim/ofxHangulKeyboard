#include "ofxTextInputBox.h"

ofEvent<ofxTextInputBox>		ofxTextInputBox::TextInputBox_ClickDownEvent;

ofxTextInputBox::ofxTextInputBox() 
	: ofxMSAInteractiveObject()
{
	disableMouseEvents();
	disableAppEvents();

	m_strText		= L"";
	m_strControlID	= "";
	m_bSelected		= false;

	m_fCoursorDrawTime = 0.0f;

	m_HangulKeyTable['q'] = 7;
	m_HangulKeyTable['Q'] = 8;
	m_HangulKeyTable['w'] = 12;
	m_HangulKeyTable['W'] = 13;
	m_HangulKeyTable['e'] = 3;
	m_HangulKeyTable['E'] = 4;
	m_HangulKeyTable['r'] = 0;
	m_HangulKeyTable['R'] = 1;
	m_HangulKeyTable['t'] = 9;
	m_HangulKeyTable['T'] = 10;
	m_HangulKeyTable['y'] = 31;
	m_HangulKeyTable['u'] = 25;
	m_HangulKeyTable['i'] = 21;
	m_HangulKeyTable['o'] = 20;
	m_HangulKeyTable['O'] = 22;
	m_HangulKeyTable['p'] = 24;
	m_HangulKeyTable['P'] = 26;
	m_HangulKeyTable['a'] = 6;
	m_HangulKeyTable['s'] = 2;
	m_HangulKeyTable['d'] = 11;
	m_HangulKeyTable['f'] = 5;
	m_HangulKeyTable['g'] = 18;
	m_HangulKeyTable['h'] = 27;
	m_HangulKeyTable['j'] = 23;
	m_HangulKeyTable['k'] = 19;
	m_HangulKeyTable['l'] = 39;
	m_HangulKeyTable['z'] = 15;
	m_HangulKeyTable['x'] = 16;
	m_HangulKeyTable['c'] = 14;
	m_HangulKeyTable['v'] = 17;
	m_HangulKeyTable['b'] = 36;
	m_HangulKeyTable['n'] = 32;
	m_HangulKeyTable['m'] = 37;

	m_iAlphaValue = 0xff;


	ofAddListener(ofEvents().setup, this, &ofxTextInputBox::setup);

};

ofxTextInputBox::~ofxTextInputBox()
{

};

void ofxTextInputBox::keyDown(int iKey)
{
	if(iKey == OF_KEY_BACKSPACE)
	{
		m_Automata.SetKeyCode(KEY_CODE_BACKSPACE);
	}
	else if(iKey == ' ')
	{
		m_Automata.SetKeyCode(KEY_CODE_SPACE);
	}
	else
	{
		/*float fStringWidth = m_TextFont.getStringBoundingBox(m_strText, 0, 0).width;


		if(fStringWidth < width - 20)
		{
			auto it = m_HangulKeyTable.find(iKey);

			int code = m_HangulKeyTable[iKey];

			if(it != m_HangulKeyTable.end())
			{
				code = m_HangulKeyTable[iKey];

				m_Automata.SetKeyCode(code);
			}

		}
		*/

		auto it = m_HangulKeyTable.find(iKey);

		int code = m_HangulKeyTable[iKey];

		if(it != m_HangulKeyTable.end())
		{
			code = m_HangulKeyTable[iKey];
				 
			m_Automata.SetKeyCode(code);
		}

		wstring strText = m_Automata.completeText + m_Automata.ingWord;;
		float fStringWidth = m_TextFont.getStringBoundingBox(strText, 0, 0).width;
		if(fStringWidth > width + 10)
		{
			m_Automata.SetKeyCode(KEY_CODE_BACKSPACE);

		}
	}

	m_strText = m_Automata.completeText + m_Automata.ingWord;
}

void ofxTextInputBox::draw(ofEventArgs &e) 
{

	float fStringWidth = m_TextFont.getStringBoundingBox(m_strText, 0, 0).width;
	float fStringHeight = m_TextFont.getStringBoundingBox(m_strText, 0, 0).height;
	float fDrawX = x;
	float fDrawY = ((height - fStringHeight) * .5f) + fStringHeight + y;

	ofSetColor(0xb1, 0xb1, 0xb1, m_iAlphaValue);
	m_TextFont.drawString(m_strText, fDrawX + 2, fDrawY + 2);

	ofSetColor(0x49, 0x49, 0x49, m_iAlphaValue);
	m_TextFont.drawString(m_strText, fDrawX, fDrawY );

	//Draw Cursor
	if(m_bSelected)
	{
		//ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
		float fElapsedTime = ofGetElapsedTimef();
		if(fElapsedTime < m_fCoursorDrawTime)
		{

			ofSetColor(0x00, 0x00, 0x00, m_iAlphaValue);

			float fCursorHeight = height * .8f;

			float fCursorDrawY = ((height - fCursorHeight) * .5f);
			ofRect(x + fStringWidth + 3, y + fCursorDrawY, CURSOR_WIDTH, fCursorHeight);
		}
		else
		{
			if(fElapsedTime - m_fCoursorDrawTime > 0.5) //0.5초동안 쉬고
				m_fCoursorDrawTime = fElapsedTime + 0.5; //0.5초 동안 그려라
		}
		//ofDisableBlendMode();
	}

}