#pragma once

class CStackItem
{
	CStackItem* m_pNext;
public:
	CStackItem();
	virtual ~CStackItem();
	bool Create();
	void SetNext(CStackItem* pSI) { m_pNext = pSI; }
	CStackItem* GetNext() { return m_pNext; }
};

