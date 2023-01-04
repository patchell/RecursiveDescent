#include "pch.h"

CStack::CStack()
{
	m_pHead = 0;
}

CStack::~CStack()
{
	CStackItem* pSI;

	while (m_pHead)
	{
		pSI = Look(1);
		delete m_pHead;
		m_pHead = pSI;
	}
}

bool CStack::Create()
{
	return true;
}

void CStack::Push(CStackItem* pItem)
{
	pItem->SetNext(GetHead());
	SetHead(pItem);
}

CStackItem* CStack::Pop()
{
	CStackItem* pRV = 0;

	if (GetHead())
	{
		pRV = GetHead();
		SetHead(GetHead()->GetNext());
	}
	return pRV;
}

CStackItem* CStack::Look(int Depth)
{
	int i = 0;
	CStackItem* pRV = 0;;
	bool Loop = true;

	for (i = 0, pRV = GetHead(); i < Depth && Loop; ++i)
	{
		if (pRV == 0)
		{
			Loop = false;
		}
		else
		{
			pRV = pRV->GetNext();
		}
	}
	return pRV;
}
