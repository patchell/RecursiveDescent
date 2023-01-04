#pragma once

class CStack
{
	CStackItem* m_pHead;
public:
	CStack();
	virtual ~CStack();
	bool Create();
	virtual void Push(CStackItem* pItem);
	virtual CStackItem* Pop();
	virtual CStackItem* Look(int Depth);
	virtual CStackItem* GetHead() { return m_pHead; }
	virtual void SetHead(CStackItem* pSI) { m_pHead = pSI; }
};

