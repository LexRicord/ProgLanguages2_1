#pragma once

#include "stdafx.h"

#define SPACE ' '
#define VERTICAL_BAR '|'
#define LINE_FEED '\n'
#define POST_PRE_SPACE_SYMBOLS ";,}{()=+-/*"

#define tokenSize 256

struct varTypeFlag
{
	int LT_posititon = -1;
	enum { DEF = 0, INT = 1, STR = 2 } type = DEF;
};

bool func_var(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdentTable& idTable, varTypeFlag& varTypeFlag);
void SeparationOfTokens(const In::IN& source, LT::LexTable& lexTable, IT::IdentTable& idTable);
bool tokenAnalize(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdentTable& idTable);