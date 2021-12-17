#pragma once

#define LEX_TOKEN_FIXSIZE 1 
#define LT_MAXSIZE 4096 
#define LT_TI_NULLXDX -1 // don't have elem in IT

#define	LEX_INTEGER				't'			// лексема для int
#define	LEX_UINTEGER			't'			// лексема для uint
#define	LEX_BOOL				't'			// лексема для bool
#define	LEX_STRING				't'			// лексема для string
#define	LEX_CHAR				't'			// лексема для char

#define	LEX_FOR					'c'			// лексема для for

#define	LEX_RANDOM				'i'			// лексема для random
#define LEX_MAIN				'i'			// лексема для main
#define LEX_STRLEN				'i'			// лексема для strlen

#define	LEX_RETURN				'r'			// лексема для return
#define	LEX_OUT					'o'			// лексема для out 

#define LEX_ID 'i' 
#define LEX_LITERAL 'l' 
#define LEX_FUNCTION 'f' 
#define LEX_DECLARE 'd' 
#define LEX_RETURN 'r' 
#define LEX_PRINT 'p' 
#define LEX_STRLEN 'e' 
#define LEX_SEMICOLON ';' 
#define LEX_COMMA ',' 
#define LEX_LEFT_BRACE '{' 
#define LEX_RIGHT_BRACE '}' 
#define LEX_LEFTHESIS '(' 
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS 'v'
#define LEX_MINUS 'v'
#define LEX_STAR 'v' 
#define LEX_SLASH 'v' 
#define LEX_EQUAL_SIGN '='
#define	LEX_NOTEQUALITY_SIGN	'!'			// лексема для !=
#define	LEX_EQUALITY_SIGN		'~'			// лексема для ==
#define	LEX_LESS_SIGN			'<'			// лексема для =
#define	LEX_MORE_SIGN			'>'			// лексема для =' 

#define DIRSLASH '/'
#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define SLASH '/'

#define PARM_LEX L".lex.txt"

namespace LT
{
	struct Entry
	{
		char lexToken;
		int sourceNumber; // str number in source code
		int indexTI; // or LT_TI_NULLIDX
		char operation = '\0';
		Entry();
		Entry(const char lex, int str_n, int indexTI);
		Entry(const char lex, int str_n, int indexTI, char operation_symbol);
	};

	struct LexTable
	{
		int maxSize; //  < LT_MAXSIZE
		int size; // current < maxSize
		Entry* table; // array of LT Enrties

		Entry GetEntry( //get a str 
			int n   //number of str
		);

		void PrintLexTable(const wchar_t* in); // output to file
		void PrintLexTable(const wchar_t* in, const wchar_t* name);
		LexTable();
	};

	void Add( // добавить строку в таблицу лексем
		LexTable& lexTable, // экземпляр таблицы лексем
		Entry entry // строка таблицы лексем
	);

	void Delete(LexTable& lexTable); // удалить таблицу лексем (освободить память)
};