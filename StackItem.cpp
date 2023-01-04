#include "pch.h"

CStackItem::CStackItem()
{
	m_pNext = 0;
}

CStackItem::~CStackItem()
{
	m_pNext = 0;
}

bool CStackItem::Create()
{
	return true;
}
