#pragma once

class CSymTab
{
	CSymbol* m_pTableHead;
	CSymbol* m_pTableTail;
public:
	CSymTab();
	virtual ~CSymTab();
	void Create();
	void AddSymbol(CSymbol* pSym);
	CSymbol* FindSymbol(const char* pName);
};

