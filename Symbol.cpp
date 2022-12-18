#include "pch.h"

CSymbol::CSymbol()
{
	m_pNext = 0;
	m_pPrev = 0;
	for (int i = 0; i < 32; ++i)
		m_aName[i] = 0;
}

CSymbol::~CSymbol()
{
}

void CSymbol::Create()
{
}

void CSymbol::SetName(const char* pName)
{
	strcpy_s(m_aName, 32, pName);
}

bool CSymbol::CompareName(const char* pName)
{
	bool rV = false;

	if (strcmp(m_aName, pName) == 0)
		rV = true;
	return rV;
}
