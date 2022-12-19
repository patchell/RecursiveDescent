#include "pch.h"

CParser::CParser()
{
	m_pOUT = 0;
}

CParser::~CParser()
{
}

void CParser::Create(FILE* pIn, FILE* pOut)
{
	GetLexer()->Create(pIn);
	m_pOUT = pOut;
}

void CParser::Run()
{
	int LookaHeadToken;

	LookaHeadToken = GetLexer()->Lex();
	Calc(LookaHeadToken);
}

int CParser::Calc(int LookaHeadToken)
{
	//-----------------------------
	// calc     ->exprlist EOF
	//-----------------------------
	LookaHeadToken = ExprList(LookaHeadToken);
	if (GetLexer()->Accept(LookaHeadToken, EOF))
		printf("Done\n");
	else
		printf("Unexpected EOF\n");
	return LookaHeadToken;
}

int CParser::ExprList(int LookaHeadToken)
{
	//------------------------------
	// Exprlist -> Expr ';' Exprlist
	//          -> .
	//------------------------------
	
	LookaHeadToken = Expr(LookaHeadToken);
	switch (LookaHeadToken)
	{
	case ';':
		printf(";\n");
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken,
			';'
		);
		LookaHeadToken = ExprList(LookaHeadToken);
		break;
	case EOF:
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

int CParser::Expr(int LookaHeadToken)
{
	//-------------------------------
	// Expr     -> Term expr1
	//-------------------------------
 	LookaHeadToken = Term(LookaHeadToken);
	LookaHeadToken = Expr1(LookaHeadToken);
	return LookaHeadToken;
}

int CParser::Expr1(int LookaHeadToken)
{
	//-----------------------------------
	// Expr1    -> '+' Term Expr1
	//          -> '-' Term Expr1
	//          -> .
	//-----------------------------------

	switch (LookaHeadToken)
	{
	case '+':
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken, 
			'+'
		);
		LookaHeadToken = Term(LookaHeadToken);
		printf("+\n");
		LookaHeadToken = Expr1(LookaHeadToken);
		break;
	case '-':
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken,
			'-'
		);
		LookaHeadToken = Term(LookaHeadToken);
		printf("-\n");
		LookaHeadToken = Expr1(LookaHeadToken);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

int CParser::Term(int LookaHeadToken)
{
	//---------------------------------------
	// Term     -> Unary Term1
	//---------------------------------------
	LookaHeadToken = Unary(LookaHeadToken);
	LookaHeadToken = Term1(LookaHeadToken);
	return LookaHeadToken;
}

int CParser::Term1(int LookaHeadToken)
{
	//---------------------------------------
// Term1    -> '*' Unary Term1
//          -> '/' Unary Term1
//			-> .
	//---------------------------------------

	switch (LookaHeadToken)
	{
	case '*':
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken, '*'
		);
		LookaHeadToken = Unary(LookaHeadToken);
		printf("*\n");
		LookaHeadToken = Term1(LookaHeadToken);
		break;
	case '/':
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken, '/'
		);
		LookaHeadToken = Unary(LookaHeadToken);
		printf("/\n");
		LookaHeadToken = Term1(LookaHeadToken);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

int CParser::Unary(int LookaHeadToken)
{
	//------------------------------------
	// Unary    -> '-' Unary
	//          -> Factor
	//------------------------------------
	switch (LookaHeadToken)
	{
	case '-':
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken,
			'-'
		);
		LookaHeadToken = Unary(LookaHeadToken);
		printf("-");
		printf("NEG\n");
		break;
	default:
		LookaHeadToken = Factor(LookaHeadToken);
		break;
	}
	return LookaHeadToken;
}

int CParser::Factor(int LookaHeadToken)
{
	//-------------------------------------
	// Factor   -> '(' Expr ')'
	//          -> NUM
	//          -> ID
	//-------------------------------------
	switch (LookaHeadToken)
	{
	case '(':
		printf("(\n");
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken,
			'('
		);
		LookaHeadToken = Expr(LookaHeadToken);
		printf(")\n");
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken,
			')'
		);
		break;
	case CLexer::NUM:
		printf("NUM:%d\n", GetLexer()->GetNumber());
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken,
			CLexer::NUM
		);
		break;
	case CLexer::ID:
		printf("ID:%s\n", GetLexer()->GetSymbol()->GetName());
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken,
			CLexer::ID
		);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}
