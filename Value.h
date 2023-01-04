#pragma once

class CValue :public CStackItem
{
	int m_Value;
public:
	CValue() { m_Value = 0; }
	virtual ~CValue();
	bool Create();
	void SetValue(int v) { m_Value = v; }
	virtual int GetValue() { return m_Value; }
	void Neg() { m_Value = -m_Value; }
	//--------------------------------
	//	Operations
	//--------------------------------
	void Add(CValue* pOperand) { m_Value += pOperand->GetValue(); }
	void Sub(CValue* pOperand) { m_Value -= pOperand->GetValue(); }
	void Mul(CValue* pOperand) { m_Value *= pOperand->GetValue(); }
	void Div(CValue* pOperand) { m_Value /= pOperand->GetValue(); }
	void Mod(CValue* pOperand) { m_Value %= pOperand->GetValue(); }
	void ShL(CValue* pOperand) { m_Value <<= pOperand->GetValue(); }
	void ShR(CValue* pOperand) { m_Value >>= pOperand->GetValue(); }
	void Or(CValue* pOperand) { m_Value |= pOperand->GetValue(); }
	void And(CValue* pOperand) { m_Value &= pOperand->GetValue(); }
	void ORlogical(CValue* pOperand) {
		bool bV = false;
		bV = (m_Value || pOperand->GetValue());
		m_Value = int(bV);
	}
	void ANDlogical(CValue* pOperand) {
		bool bV;
		bV = bool(m_Value);
		m_Value = int(bV && pOperand->GetValue());
	}
};

#define VALUE(x)	((CValue *)(x))