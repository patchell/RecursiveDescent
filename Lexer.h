#pragma once

class CLexer
{
	FILE* m_pIn;
	CSymTab m_SymTab;
	CSymbol* m_pSym;
	char m_aLexBuff[128];
	int m_LexbuffIndex;
	int m_Number;
	int m_Line;
	int m_Col;
	int m_UnGetBuff;
public:
	enum Token {
		NUM = 256,
		ID
	};
public:
	CLexer();
	virtual ~CLexer();
	void Create(FILE* pIn);
	CSymTab* GetSymbolTable() { return &m_SymTab; }
	CSymbol* GetSymbol() { return m_pSym; }
	int GetNumber() { return m_Number; }
	int GetLineNumber() { return m_Line; }
	int GetColumnNumber() { return m_Col; }
	int Lex();
	int LexGetChar();
	void LexUngetChar(int c);
	CSymbol* Lookup(const char* pName);
	int Expect(int LookaHeadToken, int Token);
	int Accept(int LookaHeadToken, int Token);
	int IsANumber(int c);
};

