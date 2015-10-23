#include "AutomataKR.h"

const int BASE_CODE = 0xac00;		// 기초음성(가)
const int LIMIT_MIN = 0xac00;		// 음성범위 MIN(가)
const int LIMIT_MAX = 0xd7a3;		// 음성범위 MAX

// 음성 테이블
wchar_t SOUND_TABLE[68] =
{
	/* 초성 19자 0 ~ 18 */
	L'ㄱ', L'ㄲ', L'ㄴ', L'ㄷ', L'ㄸ',
	L'ㄹ', L'ㅁ', L'ㅂ', L'ㅃ', L'ㅅ',
	L'ㅆ', L'ㅇ', L'ㅈ', L'ㅉ', L'ㅊ',
	L'ㅋ', L'ㅌ', L'ㅍ', L'ㅎ',
	/* 중성 21자 19 ~ 39 */
	L'ㅏ', L'ㅐ', L'ㅑ', L'ㅒ', L'ㅓ',
	L'ㅔ', L'ㅕ', L'ㅖ', L'ㅗ', L'ㅘ',
	L'ㅙ', L'ㅚ', L'ㅛ', L'ㅜ', L'ㅝ',
	L'ㅞ', L'ㅟ', L'ㅠ', L'ㅡ', L'ㅢ',
	L'ㅣ',
	/* 종성 28자 40 ~ 67 */
	L' ' , L'ㄱ', L'ㄲ', L'ㄳ', L'ㄴ',
	L'ㄵ', L'ㄶ', L'ㄷ', L'ㄹ', L'ㄺ', 
	L'ㄻ', L'ㄼ', L'ㄽ', L'ㄾ', L'ㄿ',
	L'ㅀ', L'ㅁ', L'ㅂ', L'ㅄ', L'ㅅ',
	L'ㅆ', L'ㅇ', L'ㅈ', L'ㅊ', L'ㅋ',
	L'ㅌ', L'ㅍ', L'ㅎ'
};

// 초성 합성 테이블
int MIXED_CHO_CONSON[14][3] =
{
	{ 0, 0,15}, // ㄱ,ㄱ,ㅋ
	{15, 0, 1}, // ㅋ,ㄱ,ㄲ
	{ 1, 0, 0}, // ㄲ,ㄱ,ㄱ

	{ 3, 3,16}, // ㄷ,ㄷ,ㅌ
	{16, 3, 4}, // ㅌ,ㄷ,ㄸ
	{ 4, 3, 3}, // ㄸ,ㄷ,ㄷ

	{ 7, 7,17}, // ㅂ,ㅂ,ㅍ
	{17, 7, 8}, // ㅍ,ㅂ,ㅃ
	{ 8, 7, 7}, // ㅃ,ㅂ,ㅂ

	{ 9, 9,10}, // ㅅ,ㅅ,ㅆ
	{10, 9, 9}, // ㅆ,ㅅ,ㅅ

	{12,12,14}, // ㅈ,ㅈ,ㅊ
	{14,12,13}, // ㅊ,ㅈ,ㅉ
	{13,12,12}  // ㅉ,ㅈ,ㅈ
};

// 초성,중성 모음 합성 테이블
int MIXED_VOWEL[21][3] = 
{
	{19,19,21},	// ㅏ,ㅏ,ㅑ
	{21,19,19},	// ㅑ,ㅏ,ㅏ

	{19,39,20},	// ㅏ,ㅣ,ㅐ
	{21,39,22},	// ㅑ,ㅣ,ㅒ

	{23,23,25},	// ㅓ,ㅓ,ㅕ
	{25,23,23},	// ㅕ,ㅓ,ㅓ

	{23,39,24},	// ㅓ,ㅣ,ㅔ
	{25,39,26},	// ㅕ,ㅣ,ㅖ

	{27,27,31},	// ㅗ,ㅗ,ㅛ
	{31,27,27},	// ㅛ,ㅗ,ㅗ

	{27,19,28},	// ㅗ,ㅏ,ㅘ
	{28,39,29},	// ㅘ,ㅣ,ㅙ

	{27,39,30},	// ㅗ,ㅣ,ㅚ

	{32,32,36},	// ㅜ,ㅜ,ㅠ
	{36,32,32},	// ㅠ,ㅜ,ㅜ

	{32,23,33},	// ㅜ,ㅓ,ㅝ
	{33,39,34},	// ㅝ,ㅣ,ㅞ

	{32,39,35},	// ㅜ,ㅣ,ㅟ

	{39,39,37},	// ㅣ,ㅣ,ㅡ
	{37,39,38},	// ㅡ,ㅣ,ㅢ
	{38,39,39}	// ㅢ,ㅣ,ㅣ
};

// 종성 합성 테이블
int MIXED_JONG_CONSON[22][3] = 
{

	{41,59,43}, // ㄱ,ㅅ,ㄳ

	{44,62,45}, // ㄴ,ㅈ,ㄵ
	{44,67,46}, // ㄴ,ㅎ,ㄶ

	{48,41,49}, // ㄹ,ㄱ,ㄺ
	{48,56,50}, // ㄹ,ㅁ,ㄻ

	{48,57,51}, // ㄹ,ㅂ,ㄼ
	{51,57,54}, // ㄼ,ㅂ,ㄿ

	{48,59,52}, // ㄹ,ㅅ,ㄽ
	{48,65,53}, // ㄹ,ㅌ,ㄾ 
	{48,67,55}, // ㄹ,ㅎ,ㅀ

	{57,59,58}, // ㅂ,ㅅ,ㅄ

};

// 종성 분해 테이블
int DIVIDE_JONG_CONSON[13][3] = 
{
	{41,41,42}, // ㄱ,ㄱ,ㄲ
	{41,59,43}, // ㄱ,ㅅ,ㄳ
	{44,62,45}, // ㄴ,ㅈ,ㄵ
	{44,67,46}, // ㄴ,ㅎ,ㄶ
	{48,41,49}, // ㄹ,ㄱ,ㄺ
	{48,56,50}, // ㄹ,ㅁ,ㄻ
	{48,57,51}, // ㄹ,ㅂ,ㄼ
	{48,66,54}, // ㄹ,ㅍ,ㄿ
	{48,59,52}, // ㄹ,ㅅ,ㄽ
	{48,65,53}, // ㄹ,ㅌ,ㄾ	
	{48,67,55}, // ㄹ,ㅎ,ㅀ
	{57,59,58}, // ㅂ,ㅅ,ㅄ
	{59,59,60}  // ㅅ,ㅅ,ㅆ
};

CAutomataKR::CAutomataKR(void)
{
	m_HangulKeyTable['q'] = 7;
	m_HangulKeyTable['w'] = 12;
	m_HangulKeyTable['e'] = 3;
	m_HangulKeyTable['r'] = 0;
	m_HangulKeyTable['t'] = 9;
	m_HangulKeyTable['y'] = 31;
	m_HangulKeyTable['u'] = 25;
	m_HangulKeyTable['i'] = 21;
	m_HangulKeyTable['o'] = 20;
	m_HangulKeyTable['p'] = 24;
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

	Clear();
}

CAutomataKR::~CAutomataKR(void)
{
}

// 버퍼 초기화
void CAutomataKR::Clear()
{
	m_nStatus		= HS_FIRST;
	completeText	= L"";
	ingWord			= NULL;
	m_completeWord	= NULL;
}


// 키코드 입력 및 조합 (정해진 int 코드값을 입력 받아 한글조합)
wchar_t CAutomataKR::SetKeyCode(int nKeyCode)
{
	m_completeWord = NULL;

	// 특수키 입력
	if(nKeyCode < 0)
	{
		m_nStatus = HS_FIRST;

		if(nKeyCode == KEY_CODE_SPACE) // 띄어쓰기
		{
			if(ingWord != NULL)
				completeText += ingWord;
			else
				completeText += L' ';

			ingWord = NULL;
		}
		else if(nKeyCode == KEY_CODE_ENTER) // 내려쓰기
		{
			if(ingWord != NULL)
				completeText += ingWord;

			completeText += L"\r\n";

			ingWord = NULL;
		}
		else if(nKeyCode == KEY_CODE_BACKSPACE) // 지우기
		{
			if(ingWord == NULL)
			{
				if(completeText.length() > 0)
				{
					string::size_type n = completeText.find_last_of(L"\n");  
					if( n == string::npos )
						completeText = completeText.substr(0, completeText.length() - 1);  
					else
						completeText = completeText.substr(0, completeText.length() - 2);  
				}
			}
			else
			{
				m_nStatus = DownGradeIngWordStatus(ingWord);
			}
		}

		return m_completeWord;
	}



	switch(m_nStatus)
	{
	case HS_FIRST:
		// 초성
		m_nPhonemez[0]	= nKeyCode;
		ingWord			= SOUND_TABLE[m_nPhonemez[0]];
		m_nStatus		= nKeyCode > 18 ? HS_FIRST_C : HS_FIRST_V;
		break;

	case HS_FIRST_C:
		// 모음 + 모음
		if(nKeyCode > 18)	// 모음
		{
			//if(MixVowel(&m_nPhonemez[0], nKeyCode) == false)
			{
				m_completeWord = SOUND_TABLE[m_nPhonemez[0]];
				m_nPhonemez[0] = nKeyCode;
			}
		}
		else				// 자음
		{
			m_completeWord	= SOUND_TABLE[m_nPhonemez[0]];
			m_nPhonemez[0]	= nKeyCode;
			m_nStatus		= HS_FIRST_V;
		}
		break;

	case HS_FIRST_V:
		// 자음 + 자음
		if(nKeyCode > 18)	// 모음
		{
			m_nPhonemez[1]	= nKeyCode;
			m_nStatus		= HS_MIDDLE_STATE;
		}
		else				// 자음
		{
		//	if(!MixInitial(nKeyCode))
			{
				m_completeWord	= SOUND_TABLE[m_nPhonemez[0]];
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST_V;
			}
		}
		break;

	case HS_MIDDLE_STATE:
		// 초성 + 모음 + 모음
		if(nKeyCode > 18)
		{
			if(MixVowel(&m_nPhonemez[1], nKeyCode) == false)
			{
				m_completeWord	= CombineHangle(1);
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST_C;
			}
		}
		else
		{
			int jungCode = ToFinal(nKeyCode);

			if(jungCode > 0)
			{
				m_nPhonemez[2]	= jungCode;
				m_nStatus		= HS_END_STATE;
			}
			else
			{
				m_completeWord	= CombineHangle(1);
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST;
			}
		}
		break;

	case HS_END:
		// 초성 + 중성 + 종성
		if(nKeyCode > 18)  
		{
			m_completeWord	= CombineHangle(1);
			m_nPhonemez[0]	= nKeyCode;
			m_nStatus		= HS_FIRST;
		}
		else
		{
			int jungCode = ToFinal(nKeyCode);
			if(jungCode > 0)
			{
				m_nPhonemez[2]	= jungCode;
				m_nStatus		= HS_END_STATE;
			}
			else
			{
				m_completeWord	= CombineHangle(1);
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST;
			}  
		}
		break;

	case HS_END_STATE:
		// 초성 + 중성 + 자음(종) + 자음(종)
		if(nKeyCode > 18)
		{
			m_completeWord = CombineHangle(1);

			m_nPhonemez[0]	= ToInitial(m_nPhonemez[2]);
			m_nPhonemez[1]	= nKeyCode;
			m_nStatus		= HS_MIDDLE_STATE;
		}
		else
		{
			int jungCode = ToFinal(nKeyCode);
			if(jungCode > 0)
			{
				m_nStatus = HS_END_EXCEPTION;

				if(!MixFinal(jungCode))
				{
					m_completeWord	= CombineHangle(2);
					m_nPhonemez[0]	= nKeyCode;
					m_nStatus		= HS_FIRST_V;
				}
			}
			else
			{
				m_completeWord	= CombineHangle(2);
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST_V;
			}  
		}
		break;

	case HS_END_EXCEPTION:
		// 초성 + 중성 + 종성(곁자음)
		if(nKeyCode > 18)  
		{
			DecomposeConsonant();
			m_nPhonemez[1]	= nKeyCode;
			m_nStatus		= HS_MIDDLE_STATE;
		}
		else
		{
			int jungCode = ToFinal(nKeyCode);
			if(jungCode > 0)
			{
				m_nStatus = HS_END_EXCEPTION;

				//if(!MixFinal(jungCode))
				{
					m_completeWord	= CombineHangle(2);
					m_nPhonemez[0]	= nKeyCode;
					m_nStatus		= HS_FIRST_V;
				}
			}
			else
			{
				m_completeWord	= CombineHangle(2);
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST_V; 
			}
		}
		break;
	}

	// 현재 보이는 글자상태
	CombineIngWord(m_nStatus);

	// 완성 문자열 만들기
	if(m_completeWord != NULL) 
		completeText += m_completeWord;

	return m_completeWord;
}
/*
// 키코드 입력 및 조합 (정해진 int 코드값을 입력 받아 한글조합)
wchar_t CAutomataKR::SetKeyCode(int nKeyCode)
{
	m_completeWord = NULL;

	// 특수키 입력 
	if(nKeyCode < 0)
	{
		m_nStatus = HS_FIRST;

		if(nKeyCode == KEY_CODE_SPACE) // 띄어쓰기
		{
			if(ingWord != NULL)
				completeText += ingWord;
			else
				completeText += L' ';

			ingWord = NULL;
		}
		else if(nKeyCode == KEY_CODE_ENTER) // 내려쓰기
		{
			if(ingWord != NULL)
				completeText += ingWord;

			completeText += L"\r\n";

			ingWord = NULL;
		}
		else if(nKeyCode == KEY_CODE_BACKSPACE) // 지우기
		{
			if(ingWord == NULL)
			{
				if(completeText.length() > 0)
				{
					int b = 0;
					int a = 10 / b;

					string::size_type n = completeText.find_last_not_of(L"\n");  
					if( n == string::npos )
						completeText.substr(0, completeText.length() - 1);  
					else
						completeText.substr(0, completeText.length() - 2);  

					#if 0
					if(completeText.c_str()[completeText.length() - 1] == L"\n")
						completeText = completeText.Left(completeText.length() -2);
					else
						completeText = completeText.Left(completeText.length() -1);
					#endif
					
				}
			}
			else
			{
				m_nStatus = DownGradeIngWordStatus(ingWord);
			}
		}

		return m_completeWord;
	}



	switch(m_nStatus)
	{
	case HS_FIRST:
		// 초성
		m_nPhonemez[0]	= nKeyCode;
		ingWord			= SOUND_TABLE[m_nPhonemez[0]];
		m_nStatus		= nKeyCode > 18 ? HS_FIRST_C : HS_FIRST_V;
		break;

	case HS_FIRST_C:
		// 모음 + 모음
		if(nKeyCode > 18)	// 모음
		{
			if(MixVowel(&m_nPhonemez[0], nKeyCode) == false)
			{
				m_completeWord = SOUND_TABLE[m_nPhonemez[0]];
				m_nPhonemez[0] = nKeyCode;
			}
		}
		else				// 자음
		{
			m_completeWord	= SOUND_TABLE[m_nPhonemez[0]];
			m_nPhonemez[0]	= nKeyCode;
			m_nStatus		= HS_FIRST_V;
		}
		break;

	case HS_FIRST_V:
		// 자음 + 자음
		if(nKeyCode > 18)	// 모음
		{
			m_nPhonemez[1]	= nKeyCode;
			m_nStatus		= HS_MIDDLE_STATE;
		}
		else				// 자음
		{
			if(!MixInitial(nKeyCode))
			{
				m_completeWord	= SOUND_TABLE[m_nPhonemez[0]];
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST_V;
			}
		}
		break;

	case HS_MIDDLE_STATE:
		// 초성 + 모음 + 모음
		if(nKeyCode > 18)
		{
			if(MixVowel(&m_nPhonemez[1], nKeyCode) == false)
			{
				m_completeWord	= CombineHangle(1);
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST_C;
			}
		}
		else
		{
			int jungCode = ToFinal(nKeyCode);

			if(jungCode > 0)
			{
				m_nPhonemez[2]	= jungCode;
				m_nStatus		= HS_END_STATE;
			}
			else
			{
				m_completeWord	= CombineHangle(1);
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST;
			}
		}
		break;

	case HS_END:
		// 초성 + 중성 + 종성
		if(nKeyCode > 18)  
		{
			m_completeWord	= CombineHangle(1);
			m_nPhonemez[0]	= nKeyCode;
			m_nStatus		= HS_FIRST;
		}
		else
		{
			int jungCode = ToFinal(nKeyCode);
			if(jungCode > 0)
			{
				m_nPhonemez[2]	= jungCode;
				m_nStatus		= HS_END_STATE;
			}
			else
			{
				m_completeWord	= CombineHangle(1);
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST;
			}  
		}
		break;

	case HS_END_STATE:
		// 초성 + 중성 + 자음(종) + 자음(종)
		if(nKeyCode > 18)
		{
			m_completeWord = CombineHangle(1);

			m_nPhonemez[0]	= ToInitial(m_nPhonemez[2]);
			m_nPhonemez[1]	= nKeyCode;
			m_nStatus		= HS_MIDDLE_STATE;
		}
		else
		{
			int jungCode = ToFinal(nKeyCode);
			if(jungCode > 0)
			{
				m_nStatus = HS_END_EXCEPTION;

				if(!MixFinal(jungCode))
				{
					m_completeWord	= CombineHangle(2);
					m_nPhonemez[0]	= nKeyCode;
					m_nStatus		= HS_FIRST_V;
				}
			}
			else
			{
				m_completeWord	= CombineHangle(2);
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST_V;
			}  
		}
		break;

	case HS_END_EXCEPTION:
		// 초성 + 중성 + 종성(곁자음)
		if(nKeyCode > 18)  
		{
			DecomposeConsonant();
			m_nPhonemez[1]	= nKeyCode;
			m_nStatus		= HS_MIDDLE_STATE;
		}
		else
		{
			int jungCode = ToFinal(nKeyCode);
			if(jungCode > 0)
			{
				m_nStatus = HS_END_EXCEPTION;

				if(!MixFinal(jungCode))
				{
					m_completeWord	= CombineHangle(2);
					m_nPhonemez[0]	= nKeyCode;
					m_nStatus		= HS_FIRST_V;
				}
			}
			else
			{
				m_completeWord	= CombineHangle(2);
				m_nPhonemez[0]	= nKeyCode;
				m_nStatus		= HS_FIRST_V; 
			}
		}
		break;
	}

	// 현재 보이는 글자상태
	CombineIngWord(m_nStatus);

	// 완성 문자열 만들기
	if(m_completeWord != NULL) 
		completeText += m_completeWord;

	return m_completeWord;
}
*/

// 초성으로 변환
int CAutomataKR::ToInitial(int nKeyCode)
{
	switch(nKeyCode)
	{
	case 41: return 0;	// ㄱ
	case 42: return 1;	// ㄲ
	case 44: return 2;	// ㄴ
	case 47: return 3;	// ㄷ
	case 48: return 5;	// ㄹ
	case 56: return 6;	// ㅁ
	case 57: return 7;	// ㅂ
	case 59: return 9;	// ㅅ
	case 60: return 10;	// ㅆ
	case 61: return 11;	// ㅇ
	case 62: return 12;	// ㅈ
	case 63: return 14;	// ㅊ
	case 64: return 15;	// ㅋ
	case 65: return 16;	// ㅌ
	case 66: return 17;	// ㅍ
	case 67: return 18;	// ㅎ
	}
	return -1;
}

// 종성으로 변환
int CAutomataKR::ToFinal(int nKeyCode)
{
	switch(nKeyCode)
	{
	case 0: return 41;	// ㄱ
	case 1: return 42;	// ㄲ
	case 2: return 44;	// ㄴ
	case 3: return 47;	// ㄷ
	case 5: return 48;	// ㄹ
	case 6: return 56;	// ㅁ
	case 7: return 57;	// ㅂ
	case 9: return 59;	// ㅅ
	case 10: return 60;	// ㅆ
	case 11: return 61;	// ㅇ
	case 12: return 62;	// ㅈ
	case 14: return 63;	// ㅊ
	case 15: return 64;	// ㅋ
	case 16: return 65;	// ㅌ
	case 17: return 66;	// ㅍ
	case 18: return 67;	// ㅎ
	}
	return -1;
}

// 자음분해
void CAutomataKR::DecomposeConsonant()
{
	int i = 0;
	if(m_nPhonemez[3] > 40 || m_nPhonemez[4] > 40)
	{
		do
		{
			if(DIVIDE_JONG_CONSON[i][2] == m_nPhonemez[2])
			{
				m_nPhonemez[3] = DIVIDE_JONG_CONSON[i][0];
				m_nPhonemez[4] = DIVIDE_JONG_CONSON[i][1];

				m_completeWord = CombineHangle(3);
				m_nPhonemez[0]	 = ToInitial(m_nPhonemez[4]);
				return;
			}
		}
		while(++i< 13);
	}

	m_completeWord = CombineHangle(1);
	m_nPhonemez[0]	 = ToInitial(m_nPhonemez[2]);
}

// 초성합성
bool CAutomataKR::MixInitial(int nKeyCode)
{
	if(nKeyCode >= 19)
		return false;

	int i = 0;
	do
	{
		if(MIXED_CHO_CONSON[i][0] == m_nPhonemez[0] && MIXED_CHO_CONSON[i][1] == nKeyCode)
		{
			m_nPhonemez[0] = MIXED_CHO_CONSON[i][2];
			return true;
		}
	}
	while(++i < 14);

	return false;
}

// 종성합성
bool CAutomataKR::MixFinal(int nKeyCode)
{
	if(nKeyCode <= 40) return false;

	int i = 0;
	do
	{
		if(MIXED_JONG_CONSON[i][0] == m_nPhonemez[2] && MIXED_JONG_CONSON[i][1] == nKeyCode)
		{
			m_nPhonemez[3] = m_nPhonemez[2];
			m_nPhonemez[4] = nKeyCode;
			m_nPhonemez[2] = MIXED_JONG_CONSON[i][2];

			return true;
		}
	}
	while(++i < 22);

	return false;
}

// 모음합성
bool CAutomataKR::MixVowel(int * currentCode, int inputCode)
{
	int i = 0;
	do
	{
		if(MIXED_VOWEL[i][0] == * currentCode && MIXED_VOWEL[i][1] == inputCode)
		{
			* currentCode = MIXED_VOWEL[i][2];
			return true;
		}
	}
	while(++i< 21);

	return false;
}

// 한글조합
wchar_t CAutomataKR::CombineHangle(int cho, int jung, int jong)
{
	// 초성 * 21 * 28 + (중성 - 19) * 28 + (종성 - 40) + BASE_CODE;
	return BASE_CODE - 572 + jong + cho * 588 + jung * 28;
}

wchar_t CAutomataKR::CombineHangle(int status)
{
	switch(status)
	{
	//초성 + 중성
	case 1: return CombineHangle(m_nPhonemez[0], m_nPhonemez[1], 40);

	//초성 + 중성 + 종성
	case 2: return CombineHangle(m_nPhonemez[0], m_nPhonemez[1], m_nPhonemez[2]);
	
	//초성 + 중성 + 곁자음01
	case 3: return CombineHangle(m_nPhonemez[0], m_nPhonemez[1], m_nPhonemez[3]);
	}
	return ' ';
}

void CAutomataKR::CombineIngWord(int status)
{
	switch(m_nStatus)
	{
	case HS_FIRST:
	case HS_FIRST_V:
	case HS_FIRST_C:
		ingWord = SOUND_TABLE[m_nPhonemez[0]];
		break;

	case HS_MIDDLE_STATE:
	case HS_END:
		ingWord = CombineHangle(1);
		break;

	case HS_END_STATE:
	case HS_END_EXCEPTION:
		ingWord = CombineHangle(2);
		break;
	}
}

int CAutomataKR::DownGradeIngWordStatus(wchar_t word)
{
	int iWord = word;

	//초성만 있는 경우
	if(iWord < LIMIT_MIN || iWord > LIMIT_MAX)
	{
		ingWord = NULL;

		return HS_FIRST;
	}

	//문자코드 체계
	//iWord = firstWord * (21*28)
	//		+ middleWord * 28
	//		+ lastWord * 27
	//		+ BASE_CODE;
	//
	int totalWord	= iWord - BASE_CODE;
	int iFirstWord	= totalWord / 28 / 21;	//초성
	int iMiddleWord = totalWord / 28 % 21;	//중성
	int iLastWord	= totalWord % 28;		//종성

	m_nPhonemez[0] = iFirstWord; //초성저장

	if(iLastWord == 0)	//종성이 없는 경우
	{
		ingWord = SOUND_TABLE[m_nPhonemez[0]];

		return HS_FIRST_V;
	}

	m_nPhonemez[1] = iMiddleWord + 19; //중성저장

	iLastWord += 40;

	for(int i = 0; i < 13; i++)
	{
		if(iLastWord == DIVIDE_JONG_CONSON[i][2])
		{
			ingWord = CombineHangle(3);
			m_nPhonemez[2] = DIVIDE_JONG_CONSON[i][0]; // 종성저장
			return HS_END_EXCEPTION;
		}
	}

	ingWord = CombineHangle(1);

	return HS_MIDDLE_STATE;
}
