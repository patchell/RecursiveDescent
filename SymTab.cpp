#include "pch.h"

CSymTab::CSymTab()
{
	m_pTableHead = 0;
	m_pTableTail = 0;
}

CSymTab::~CSymTab()
{
}

void CSymTab::Create()
{
}

void CSymTab::AddSymbol(CSymbol* pSym)
{
	if (m_pTableHead)
	{
		pSym->SetNext(m_pTableHead);
		m_pTableHead->SetPrev(pSym);
		m_pTableHead = pSym;
	}
	else
	{
		m_pTableHead = pSym;
		m_pTableTail = pSym;
	}
}

CSymbol* CSymTab::FindSymbol(const char* pName)
{
	CSymbol* pSym = m_pTableHead;
	bool Loop = true;

	while (pSym && Loop)
	{
		if (pSym->CompareName(pName))
			Loop = false;
		else
			pSym = pSym->GetNext();
	}
	return pSym;
}
