#pragma once
#include "ofMain.h"
#define		KEY_CODE_SPACE			-1		// 띄어쓰기
#define		KEY_CODE_ENTER			-2		// 내려쓰기
#define		KEY_CODE_BACKSPACE		-3		// 지우기

class CAutomataKR
{
public:
	CAutomataKR(void);
	~CAutomataKR(void);

public:
	void		Clear();					// 버퍼초기화
	wchar_t		SetKeyCode(int	nKeyCode);	// 키코드 받기 (정해진 int 코드값을 입력 받아 한글조합)

	wchar_t		ingWord;		// 작성중 글자
 	wstring		completeText;	// 완성 문자열

	map<char, int>			m_HangulKeyTable;

private:
	enum	HAN_STATUS		// 단어조합상태
	{
		HS_FIRST = 0,		// 초성
		HS_FIRST_V,			// 자음 + 자음 
		HS_FIRST_C,			// 모음 + 모음
		HS_MIDDLE_STATE,	// 초성 + 모음 + 모음
		HS_END,				// 초성 + 중성 + 종성
		HS_END_STATE,		// 초성 + 중성 + 자음 + 자음
		HS_END_EXCEPTION	// 초성 + 중성 + 종성(곁자음)
	};

	int			m_nStatus;		// 단어조합상태
	int			m_nPhonemez[5]; // 음소[초,중,종,곁자음1,곁자음2]

	wchar_t		m_completeWord;	// 완성글자


	// 변환 
	int			ToInitial(int nKeyCode);	// 초성으로
	int			ToFinal(int nKeyCode);		// 종성으로


	// 분해 
	void		DecomposeConsonant();		// 자음분해


	// 합성 
	bool		MixInitial(int nKeyCode);	// 초성합성
	bool		MixFinal(int nKeyCode);		// 종성합성

	bool		MixVowel(int * nCurCode, int nInCode);	// 모음합성


	// 조합(한글완성) 
	wchar_t		CombineHangle(int cho, int jung, int jong);
	wchar_t		CombineHangle(int status);
	void		CombineIngWord(int status);

	int			DownGradeIngWordStatus(wchar_t word);	//조합 문자 상태 낮추기
};
