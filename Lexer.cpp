#include "pch.h"

CLexer::CLexer()
{
	m_pSym = 0;
	m_Col = 1;
	m_Line = 1;
	m_LexbuffIndex = 0;
	m_Number = 0;
	m_pIn = 0;
	m_UnGetBuff = -1;
	for (size_t i = 0; i < 128; i++)
	{
		m_aLexBuff[i] = 0;
	}
}

CLexer::~CLexer()
{
}

void CLexer::Create(FILE* pIn)
{
	m_pIn = pIn;
	GetSymbolTable()->Create();
}

int CLexer::Lex()
{
	int Token = 0;
	int c = 0;
	bool Loop = true;
	bool auxLoop = true;

	m_LexbuffIndex = 0;
	while (Loop)
	{
		c = LexGetChar();
		switch (c)
		{
		case EOF:
			Token = EOF;
			Loop = false;
			break;
		case '\n':		//consume whitespace
			m_Line++;
			m_Col = 1;
		case ' ':
		case '\r':
		case '\t':
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		case';':
			Token = c;
			Loop = false;
			break;
		case '0': case '1': case'2': case'3': case '4':
		case '5': case '6': case '7': case'8': case '9':
			m_aLexBuff[m_LexbuffIndex++] = c;
			auxLoop = true;
			while (auxLoop)
			{
				c = LexGetChar();
				if (IsANumber(c))
				{
					m_aLexBuff[m_LexbuffIndex++] = c;
				}
				else
				{
					m_aLexBuff[m_LexbuffIndex] = 0;
					LexUngetChar(c);
					auxLoop = false;
				}
				Token = NUM;
				m_Number = atoi(m_aLexBuff);
				Loop = 0;
			}
			break;
		default:
			m_aLexBuff[m_LexbuffIndex++] = c;
			auxLoop = true;
			while (auxLoop)
			{
				c = LexGetChar();
				if (isalnum(c))
				{
					m_aLexBuff[m_LexbuffIndex++] = c;
				}
				else
				{
					m_aLexBuff[m_LexbuffIndex] = 0;
					LexUngetChar(c);
					auxLoop = false;
				}
				m_pSym = GetSymbolTable()->FindSymbol(m_aLexBuff);
				if (m_pSym == 0)
				{
					m_pSym = new CSymbol;
					m_pSym->Create();
					m_pSym->SetName(m_aLexBuff);
					Token = ID;
				}
			}
			Loop = false;
			break;
		}
	}
	return Token;
}

int CLexer::LexGetChar()
{
	int c;

	if (m_UnGetBuff >= 0)
	{
		c = m_UnGetBuff;
		m_UnGetBuff = -1;
	}
	else
	{
		c = fgetc(m_pIn);
	}
	return c;
}

void CLexer::LexUngetChar(int c)
{
	m_UnGetBuff = c;
}

CSymbol* CLexer::Lookup(const char* pName)
{
	CSymbol* pSym;;

	pSym = GetSymbolTable()->FindSymbol(pName);
	return pSym;
}

int CLexer::Expect(int LookaHeadToken, int Token)
{
	int rToken;

	if (Accept(LookaHeadToken, Token))
	{
		rToken = Lex();
	}
	else
	{
		throw("Undexpected Tocken");
	}
	return rToken;
}

int CLexer::Accept(int LookaHeadToken, int Token)
{
	int rV = 0;

	if (LookaHeadToken == Token)
		rV = 1;
	return rV;
}

int CLexer::IsANumber(int c)
{
	int rV = 0;
	switch (c)
	{
	case '0': case '1': case'2': case'3': case '4':
	case '5': case '6': case '7': case'8': case '9':
		rV = 1;
		break;
	default:
		rV = 0;
		break;
	}
	return rV;
}
