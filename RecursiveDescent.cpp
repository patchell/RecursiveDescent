// RecursiveDescent.cpp : 
// This file contains the 'main' function. 
// Program execution begins and ends there.
//-----------------------------------------
// This program demonstrates a simple
// Recursive Descent parser.  The grammar
// is as follows:
// 
//       ** LR Grammar ****
// 
//	Calc	->ExprList
// 
//	ExprList	-> Expr ';' ExprList
//				-> .
// 
//	Expr	-> Expr '+' Term
//			-> Expr '-' Term
//			-> Term
// 
// Term		-> Term '*' Unary
//			-> Term	'/' Unary
//			-> Unary
// 
// Unary	-> '-' Unary
//			-> Factor
// 
// Factor	-> '(' expr ')'
//			-> NUM
//			-> ID
// 
// -------------------------------
//  ** Conversion LR->LL
// LR --
// A -> A B
//   -> C
// LL --
// A -> C A'
// 
// A' -> B A'
//    -> .	//empty
// 
// A = Expr
// B = '+' Term
// C = Ter,
// A' = Expr'
// 
// Expr	-> Term Expr'
//
// Expr'	-> '+' Term Expr'
//			-> '-' Term Expr'
//			-> . //empty
// //
// -----------------------------
//      *Transformed Grammar*
// 
// Calc     ->Exprlist
// Exprlist -> Expr ';' Exprlist
//          -> .
// Expr     -> Term expr1
// Expr1    -> '+' Term Expr1
//          -> '-' Term Expr1
//          -> .
// Term     -> Unary Term1
// Term1    -> '*' Unary Term1
//          -> '/' Unary Term1
//			-> .
// Unary    -> '-' Unary
//          -> Factor
// Factor   -> '(' Expr ')'
//          -> NUM
//          -> ID
//-----------------------------------------

#include "pch.h"

int main(int argc, char* argv[])
{
	FILE* pIN, * pOUT;
	CParser Parser;

	printf("Recursive Descent Demo\n");
	printf("Input File %s\n", argv[1]);
	printf("Output File %s\n", argv[2]);
	fopen_s(&pIN, argv[1], "r");
	fopen_s(&pOUT, argv[2], "w");
	Parser.Create(pIN, pOUT);
	Parser.Run();
}

