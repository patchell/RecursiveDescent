#pragma once

class CSymbol
{
	char m_aName[32];
	CSymbol* m_pNext;
	CSymbol* m_pPrev;
public:
	CSymbol();
	virtual ~CSymbol();
	void Create();
	char* GetName() { return m_aName; }
	void SetName(const char* pName);
	bool CompareName(const char* pName);
	CSymbol* GetNext() { return m_pNext; }
	void SetNext(CSymbol* pN) { m_pNext = pN; }
	CSymbol*  GetPrev() { return m_pPrev; }
	void SetPrev(CSymbol* pP) { m_pPrev = pP; }
};

