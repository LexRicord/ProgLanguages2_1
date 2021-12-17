#pragma once

#include "stdafx.h"

#define SPACE ' '
#define VERTICAL_BAR '|'
#define LINE_FEED '\n'
#define POST_PRE_SPACE_SYMBOLS ";,}{()=+-/*"

#define tokenSize 256


bool func_var(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, varFlagType& varTypeFlag);
void SeparationOfTokens(const In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable);
bool tokenAnalize(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable); ;