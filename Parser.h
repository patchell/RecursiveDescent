#pragma once

class CParser
{
	CLexer m_Lexer;
	FILE* m_pOUT;
	CStack m_Stack;
public:
	CParser();
	virtual ~CParser();
	void Create(FILE* pIn, FILE* pOut);
	void Run();
	CLexer* GetLexer() { return &m_Lexer; }
	//-------------------------------------------
	// Stack Operations
	//-------------------------------------------
	CStack* GetStack() { return &m_Stack; }
	CValue* PopValue() {
		return ((CValue*)(GetStack()->Pop()));
	}
	void PushValue(CValue* pV) {
		printf("Pus Value %d Onto Stack\n", pV->GetValue());
		GetStack()->Push(pV);
	}
	//-------------------------------------------
	// Productions
	//-------------------------------------------
	int Calc(int LookaHeadToken);
	int Statements(int LookaHeadToken);
	int DeclList(int LookaHeadToken);
	int DeclList_1(int LookaHeadToken);
	int Decl(int LookaHeadToken);
	int IdentList(int LookaHeadToken);
	int IdentList_1(int LookaHeadToken);
	int Ident(int LookaHeadToken);
	int OptInit(int LookaHeadToken);
	int Expr(int LookaHeadToken);
	int IFstatement(int LookaHeadToken);
	int Expr1(int LookaHeadToken);
	int Term(int LookaHeadToken);
	int Term1(int LookaHeadToken);
	int Unary(int LookaHeadToken);
	int Factor(int LookaHeadToken);
	int NumericExpr(int LookaHeadToken);
	int NumericExpr1(int LookaHeadToken);
	int NumericTerm(int LookaHeadToken);
	int NumericTerm1(int LookaHeadToken);
	int NumericFactor(int LookaHeadToken);
};

