#pragma once

class CParser
{
	CLexer m_Lexer;
	FILE* m_pOUT;
public:
	CParser();
	virtual ~CParser();
	void Create(FILE* pIn, FILE* pOut);
	void Run();
	CLexer* GetLexer() { return &m_Lexer; }
	int Calc(int LookaHeadToken);
	int ExprList(int LookaHeadToken);
	int Expr(int LookaHeadToken);
	int Expr1(int LookaHeadToken);
	int Term(int LookaHeadToken);
	int Term1(int LookaHeadToken);
	int Unary(int LookaHeadToken);
	int Factor(int LookaHeadToken);
};

