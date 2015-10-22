#include "AutomataKR.h"

const int BASE_CODE = 0xac00;		// ��������(��)
const int LIMIT_MIN = 0xac00;		// �������� MIN(��)
const int LIMIT_MAX = 0xd7a3;		// �������� MAX

// ���� ���̺�
wchar_t SOUND_TABLE[68] =
{
	/* �ʼ� 19�� 0 ~ 18 */
	L'��', L'��', L'��', L'��', L'��',
	L'��', L'��', L'��', L'��', L'��',
	L'��', L'��', L'��', L'��', L'��',
	L'��', L'��', L'��', L'��',
	/* �߼� 21�� 19 ~ 39 */
	L'��', L'��', L'��', L'��', L'��',
	L'��', L'��', L'��', L'��', L'��',
	L'��', L'��', L'��', L'��', L'��',
	L'��', L'��', L'��', L'��', L'��',
	L'��',
	/* ���� 28�� 40 ~ 67 */
	L' ' , L'��', L'��', L'��', L'��',
	L'��', L'��', L'��', L'��', L'��', 
	L'��', L'��', L'��', L'��', L'��',
	L'��', L'��', L'��', L'��', L'��',
	L'��', L'��', L'��', L'��', L'��',
	L'��', L'��', L'��'
};

// �ʼ� �ռ� ���̺�
int MIXED_CHO_CONSON[14][3] =
{
	{ 0, 0,15}, // ��,��,��
	{15, 0, 1}, // ��,��,��
	{ 1, 0, 0}, // ��,��,��

	{ 3, 3,16}, // ��,��,��
	{16, 3, 4}, // ��,��,��
	{ 4, 3, 3}, // ��,��,��

	{ 7, 7,17}, // ��,��,��
	{17, 7, 8}, // ��,��,��
	{ 8, 7, 7}, // ��,��,��

	{ 9, 9,10}, // ��,��,��
	{10, 9, 9}, // ��,��,��

	{12,12,14}, // ��,��,��
	{14,12,13}, // ��,��,��
	{13,12,12}  // ��,��,��
};

// �ʼ�,�߼� ���� �ռ� ���̺�
int MIXED_VOWEL[21][3] = 
{
	{19,19,21},	// ��,��,��
	{21,19,19},	// ��,��,��

	{19,39,20},	// ��,��,��
	{21,39,22},	// ��,��,��

	{23,23,25},	// ��,��,��
	{25,23,23},	// ��,��,��

	{23,39,24},	// ��,��,��
	{25,39,26},	// ��,��,��

	{27,27,31},	// ��,��,��
	{31,27,27},	// ��,��,��

	{27,19,28},	// ��,��,��
	{28,39,29},	// ��,��,��

	{27,39,30},	// ��,��,��

	{32,32,36},	// ��,��,��
	{36,32,32},	// ��,��,��

	{32,23,33},	// ��,��,��
	{33,39,34},	// ��,��,��

	{32,39,35},	// ��,��,��

	{39,39,37},	// ��,��,��
	{37,39,38},	// ��,��,��
	{38,39,39}	// ��,��,��
};

// ���� �ռ� ���̺�
int MIXED_JONG_CONSON[22][3] = 
{

	{41,59,43}, // ��,��,��

	{44,62,45}, // ��,��,��
	{44,67,46}, // ��,��,��

	{48,41,49}, // ��,��,��
	{48,56,50}, // ��,��,��

	{48,57,51}, // ��,��,��
	{51,57,54}, // ��,��,��

	{48,59,52}, // ��,��,��
	{48,65,53}, // ��,��,�� 
	{48,67,55}, // ��,��,��

	{57,59,58}, // ��,��,��

};

// ���� ���� ���̺�
int DIVIDE_JONG_CONSON[13][3] = 
{
	{41,41,42}, // ��,��,��
	{41,59,43}, // ��,��,��
	{44,62,45}, // ��,��,��
	{44,67,46}, // ��,��,��
	{48,41,49}, // ��,��,��
	{48,56,50}, // ��,��,��
	{48,57,51}, // ��,��,��
	{48,66,54}, // ��,��,��
	{48,59,52}, // ��,��,��
	{48,65,53}, // ��,��,��	
	{48,67,55}, // ��,��,��
	{57,59,58}, // ��,��,��
	{59,59,60}  // ��,��,��
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

// ���� �ʱ�ȭ
void CAutomataKR::Clear()
{
	m_nStatus		= HS_FIRST;
	completeText	= L"";
	ingWord			= NULL;
	m_completeWord	= NULL;
}


// Ű�ڵ� �Է� �� ���� (������ int �ڵ尪�� �Է� �޾� �ѱ�����)
wchar_t CAutomataKR::SetKeyCode(int nKeyCode)
{
	m_completeWord = NULL;

	// Ư��Ű �Է�
	if(nKeyCode < 0)
	{
		m_nStatus = HS_FIRST;

		if(nKeyCode == KEY_CODE_SPACE) // ����
		{
			if(ingWord != NULL)
				completeText += ingWord;
			else
				completeText += L' ';

			ingWord = NULL;
		}
		else if(nKeyCode == KEY_CODE_ENTER) // ��������
		{
			if(ingWord != NULL)
				completeText += ingWord;

			completeText += L"\r\n";

			ingWord = NULL;
		}
		else if(nKeyCode == KEY_CODE_BACKSPACE) // �����
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
		// �ʼ�
		m_nPhonemez[0]	= nKeyCode;
		ingWord			= SOUND_TABLE[m_nPhonemez[0]];
		m_nStatus		= nKeyCode > 18 ? HS_FIRST_C : HS_FIRST_V;
		break;

	case HS_FIRST_C:
		// ���� + ����
		if(nKeyCode > 18)	// ����
		{
			//if(MixVowel(&m_nPhonemez[0], nKeyCode) == false)
			{
				m_completeWord = SOUND_TABLE[m_nPhonemez[0]];
				m_nPhonemez[0] = nKeyCode;
			}
		}
		else				// ����
		{
			m_completeWord	= SOUND_TABLE[m_nPhonemez[0]];
			m_nPhonemez[0]	= nKeyCode;
			m_nStatus		= HS_FIRST_V;
		}
		break;

	case HS_FIRST_V:
		// ���� + ����
		if(nKeyCode > 18)	// ����
		{
			m_nPhonemez[1]	= nKeyCode;
			m_nStatus		= HS_MIDDLE_STATE;
		}
		else				// ����
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
		// �ʼ� + ���� + ����
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
		// �ʼ� + �߼� + ����
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
		// �ʼ� + �߼� + ����(��) + ����(��)
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
		// �ʼ� + �߼� + ����(������)
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

	// ���� ���̴� ���ڻ���
	CombineIngWord(m_nStatus);

	// �ϼ� ���ڿ� �����
	if(m_completeWord != NULL) 
		completeText += m_completeWord;

	return m_completeWord;
}
/*
// Ű�ڵ� �Է� �� ���� (������ int �ڵ尪�� �Է� �޾� �ѱ�����)
wchar_t CAutomataKR::SetKeyCode(int nKeyCode)
{
	m_completeWord = NULL;

	// Ư��Ű �Է� 
	if(nKeyCode < 0)
	{
		m_nStatus = HS_FIRST;

		if(nKeyCode == KEY_CODE_SPACE) // ����
		{
			if(ingWord != NULL)
				completeText += ingWord;
			else
				completeText += L' ';

			ingWord = NULL;
		}
		else if(nKeyCode == KEY_CODE_ENTER) // ��������
		{
			if(ingWord != NULL)
				completeText += ingWord;

			completeText += L"\r\n";

			ingWord = NULL;
		}
		else if(nKeyCode == KEY_CODE_BACKSPACE) // �����
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
		// �ʼ�
		m_nPhonemez[0]	= nKeyCode;
		ingWord			= SOUND_TABLE[m_nPhonemez[0]];
		m_nStatus		= nKeyCode > 18 ? HS_FIRST_C : HS_FIRST_V;
		break;

	case HS_FIRST_C:
		// ���� + ����
		if(nKeyCode > 18)	// ����
		{
			if(MixVowel(&m_nPhonemez[0], nKeyCode) == false)
			{
				m_completeWord = SOUND_TABLE[m_nPhonemez[0]];
				m_nPhonemez[0] = nKeyCode;
			}
		}
		else				// ����
		{
			m_completeWord	= SOUND_TABLE[m_nPhonemez[0]];
			m_nPhonemez[0]	= nKeyCode;
			m_nStatus		= HS_FIRST_V;
		}
		break;

	case HS_FIRST_V:
		// ���� + ����
		if(nKeyCode > 18)	// ����
		{
			m_nPhonemez[1]	= nKeyCode;
			m_nStatus		= HS_MIDDLE_STATE;
		}
		else				// ����
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
		// �ʼ� + ���� + ����
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
		// �ʼ� + �߼� + ����
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
		// �ʼ� + �߼� + ����(��) + ����(��)
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
		// �ʼ� + �߼� + ����(������)
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

	// ���� ���̴� ���ڻ���
	CombineIngWord(m_nStatus);

	// �ϼ� ���ڿ� �����
	if(m_completeWord != NULL) 
		completeText += m_completeWord;

	return m_completeWord;
}
*/

// �ʼ����� ��ȯ
int CAutomataKR::ToInitial(int nKeyCode)
{
	switch(nKeyCode)
	{
	case 41: return 0;	// ��
	case 42: return 1;	// ��
	case 44: return 2;	// ��
	case 47: return 3;	// ��
	case 48: return 5;	// ��
	case 56: return 6;	// ��
	case 57: return 7;	// ��
	case 59: return 9;	// ��
	case 60: return 10;	// ��
	case 61: return 11;	// ��
	case 62: return 12;	// ��
	case 63: return 14;	// ��
	case 64: return 15;	// ��
	case 65: return 16;	// ��
	case 66: return 17;	// ��
	case 67: return 18;	// ��
	}
	return -1;
}

// �������� ��ȯ
int CAutomataKR::ToFinal(int nKeyCode)
{
	switch(nKeyCode)
	{
	case 0: return 41;	// ��
	case 1: return 42;	// ��
	case 2: return 44;	// ��
	case 3: return 47;	// ��
	case 5: return 48;	// ��
	case 6: return 56;	// ��
	case 7: return 57;	// ��
	case 9: return 59;	// ��
	case 10: return 60;	// ��
	case 11: return 61;	// ��
	case 12: return 62;	// ��
	case 14: return 63;	// ��
	case 15: return 64;	// ��
	case 16: return 65;	// ��
	case 17: return 66;	// ��
	case 18: return 67;	// ��
	}
	return -1;
}

// ��������
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

// �ʼ��ռ�
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

// �����ռ�
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

// �����ռ�
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

// �ѱ�����
wchar_t CAutomataKR::CombineHangle(int cho, int jung, int jong)
{
	// �ʼ� * 21 * 28 + (�߼� - 19) * 28 + (���� - 40) + BASE_CODE;
	return BASE_CODE - 572 + jong + cho * 588 + jung * 28;
}

wchar_t CAutomataKR::CombineHangle(int status)
{
	switch(status)
	{
	//�ʼ� + �߼�
	case 1: return CombineHangle(m_nPhonemez[0], m_nPhonemez[1], 40);

	//�ʼ� + �߼� + ����
	case 2: return CombineHangle(m_nPhonemez[0], m_nPhonemez[1], m_nPhonemez[2]);
	
	//�ʼ� + �߼� + ������01
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

	//�ʼ��� �ִ� ���
	if(iWord < LIMIT_MIN || iWord > LIMIT_MAX)
	{
		ingWord = NULL;

		return HS_FIRST;
	}

	//�����ڵ� ü��
	//iWord = firstWord * (21*28)
	//		+ middleWord * 28
	//		+ lastWord * 27
	//		+ BASE_CODE;
	//
	int totalWord	= iWord - BASE_CODE;
	int iFirstWord	= totalWord / 28 / 21;	//�ʼ�
	int iMiddleWord = totalWord / 28 % 21;	//�߼�
	int iLastWord	= totalWord % 28;		//����

	m_nPhonemez[0] = iFirstWord; //�ʼ�����

	if(iLastWord == 0)	//������ ���� ���
	{
		ingWord = SOUND_TABLE[m_nPhonemez[0]];

		return HS_FIRST_V;
	}

	m_nPhonemez[1] = iMiddleWord + 19; //�߼�����

	iLastWord += 40;

	for(int i = 0; i < 13; i++)
	{
		if(iLastWord == DIVIDE_JONG_CONSON[i][2])
		{
			ingWord = CombineHangle(3);
			m_nPhonemez[2] = DIVIDE_JONG_CONSON[i][0]; // ��������
			return HS_END_EXCEPTION;
		}
	}

	ingWord = CombineHangle(1);

	return HS_MIDDLE_STATE;
}
