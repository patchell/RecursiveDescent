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
	GetStack()->Create();
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
	// calc     ->Decls Statements EOF
	//-----------------------------
	LookaHeadToken = DeclList(LookaHeadToken);
	LookaHeadToken = Statements(LookaHeadToken);
	if (GetLexer()->Accept(LookaHeadToken, EOF))
		printf("Done\n");
	else
		printf("Unexpected EOF\n");
	return LookaHeadToken;
}

int CParser::Statements(int LookaHeadToken)
{
	//--------------------------------------------------
	// Statements	-> IDENT '=' Expr ';' Statements
	//				-> IF IFstatement Statements
	//				-> .
	//--------------------------------------------------
	switch (LookaHeadToken)
	{
	case CLexer::IDENT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::IDENT);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, '=');
		LookaHeadToken = Expr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, ';');
		LookaHeadToken = Statements(LookaHeadToken);
		break;
	case CLexer::IF:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::IF);
		LookaHeadToken = IFstatement(LookaHeadToken);
		LookaHeadToken = Statements(LookaHeadToken);
		break;
	}
	return LookaHeadToken;
}

int CParser::DeclList(int LookaHeadToken)
{
	//-------------------------------------
	// DeclList	-> Decl DeclList_1
	//-------------------------------------
	LookaHeadToken = Decl(LookaHeadToken);
	LookaHeadToken = DeclList_1(LookaHeadToken);
	return LookaHeadToken;
}

int CParser::DeclList_1(int LookaHeadToken)
{
	switch (LookaHeadToken)
	{
	case ';':
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, ';');
		LookaHeadToken = Decl(LookaHeadToken);
		LookaHeadToken = DeclList_1(LookaHeadToken);
		break;
	}
	return LookaHeadToken;
}

int CParser::Decl(int LookaHeadToken)
{
	//--------------------------------------
	// Decl	->INT IdentList
	//		-> .
	//--------------------------------------
	switch (LookaHeadToken)
	{
	case CLexer::INT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::INT);
		LookaHeadToken = IdentList(LookaHeadToken);
		LookaHeadToken = Decl(LookaHeadToken);
		break;
	}
	return LookaHeadToken;
}

int CParser::IdentList(int LookaHeadToken)
{
	//-------------------------------------
	// IdentList	-> Ident IdentList_1
	//-------------------------------------
	
	LookaHeadToken = Ident(LookaHeadToken);
	LookaHeadToken = IdentList_1(LookaHeadToken);
	return LookaHeadToken;
}

int CParser::IdentList_1(int LookaHeadToken)
{
	//-------------------------------------
	// IdentList_1	-> ',' Ident IdentList_1
	//				-> .
	//-------------------------------------
	switch (LookaHeadToken)
	{
	case ',':
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, ',' );
		LookaHeadToken = Ident(LookaHeadToken);
		LookaHeadToken = IdentList_1(LookaHeadToken);
		break;
	}
	return LookaHeadToken;
}

int CParser::Ident(int LookaHeadToken)
{
	//-------------------------------------
	// Ident	-> IDENT OptInit
	//			-> .
	//-------------------------------------
	CSymbol* pSym;

	switch (LookaHeadToken)
	{
	case CLexer::IDENT:
		pSym = new CSymbol;
		pSym->Create();
		pSym->SetName(GetLexer()->GetLexBuff());
		GetLexer()->GetSymbolTable()->AddSymbol(pSym);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::IDENT);
		LookaHeadToken = OptInit(LookaHeadToken);
		break;
	}
	return LookaHeadToken;
}

int CParser::OptInit(int LookaHeadToken)
{
	//-------------------------------------
	// OptInit	-> '=' NumericExpr
	//			-> .
	//-------------------------------------
	switch (LookaHeadToken)
	{
	case '=':
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, '=');
		LookaHeadToken = NumericExpr(LookaHeadToken);
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

int CParser::IFstatement(int LookaHeadToken)
{
	printf("IF->");
	LookaHeadToken = Expr(LookaHeadToken);
	LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::THEN);
	LookaHeadToken = Statements(LookaHeadToken);
	printf("End IF\n");
	LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::FI);
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
	case CLexer::IDENT:
		printf("ID:%s\n", GetLexer()->GetSymbol()->GetName());
		LookaHeadToken = GetLexer()->Expect(
			LookaHeadToken,
			CLexer::IDENT
		);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

int CParser::NumericExpr(int LookaHeadToken)
{
	//--------------------------------------------
	// NumericExpr	->NumericTerm NumericExpr1
	//--------------------------------------------
	LookaHeadToken = NumericTerm(LookaHeadToken);
	LookaHeadToken = NumericExpr1(LookaHeadToken);
	return LookaHeadToken;
}

int CParser::NumericExpr1(int LookaHeadToken)
{
	//--------------------------------------------------
	// NumericExpr1	-> '+' NumericTerm NumericExpr1
	//				-> '-' NumericTerm NumericExpr1
	//				-> .
	//--------------------------------------------------
	CValue* pV1, * pV2;

	switch (LookaHeadToken)
	{
	case '+':
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, '+');
		LookaHeadToken = NumericTerm(LookaHeadToken);
		pV2 = PopValue();
		pV1 = PopValue();
		pV1->Add(pV2);
		delete pV2;
		PushValue(pV1);
		LookaHeadToken = NumericExpr1(LookaHeadToken);
		break;
	case '-':
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, '-');
		LookaHeadToken = NumericTerm(LookaHeadToken);
		pV2 = PopValue();
		pV1 = PopValue();
		pV1->Sub(pV2);
		delete pV2;
		PushValue(pV1);
		LookaHeadToken = NumericExpr1(LookaHeadToken);
		break;
	}
	return LookaHeadToken;
}

int CParser::NumericTerm(int LookaHeadToken)
{
	//--------------------------------------------
	// NumericTerm	->NumericFactor NumericTerm1
	//--------------------------------------------
	LookaHeadToken = NumericFactor(LookaHeadToken);
	LookaHeadToken = NumericTerm1(LookaHeadToken);
	return LookaHeadToken;
}

int CParser::NumericTerm1(int LookaHeadToken)
{
	//--------------------------------------------------
	// NumericTerm1	-> '*' NumericFactor NumericTerm1
	//				-> '/' NumericFactor NumericTerm1
	//				-> .
	//--------------------------------------------------
	CValue* pV1, * pV2;

	switch (LookaHeadToken)
	{
	case '*':
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, '*');
		LookaHeadToken = NumericFactor(LookaHeadToken);
		pV2 = PopValue();
		pV1 = PopValue();
		pV1->Mul(pV2);
		delete pV2;
		PushValue(pV1);
		LookaHeadToken = NumericTerm1(LookaHeadToken);
		break;
	case '/':
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, '/');
		LookaHeadToken = NumericFactor(LookaHeadToken);
		pV2 = PopValue();
		pV1 = PopValue();
		pV1->Div(pV2);
		delete pV2;
		PushValue(pV1);
		LookaHeadToken = NumericTerm1(LookaHeadToken);
		break;
	}
	return LookaHeadToken;
}

int CParser::NumericFactor(int LookaHeadToken)
{
	//------------------------------------------
	// NumericFactor	-> '(' NumericExpr ')'
	//					-> NUM
	//					-> .
	//------------------------------------------
	CValue* pVal = 0;

	switch (LookaHeadToken)
	{
	case '(':
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, '(');
		LookaHeadToken = NumericExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, ')');
		break;
	case CLexer::NUM:
		pVal = new CValue;
		pVal->Create();
		pVal->SetValue(GetLexer()->GetNumber());
		PushValue(pVal);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::NUM);
		break;
	}
	return LookaHeadToken;
}
