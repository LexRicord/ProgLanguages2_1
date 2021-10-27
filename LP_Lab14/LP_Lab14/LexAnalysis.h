#pragma once
#include "stdafx.h"
#include <string.h>
namespace LexAnalisys
{
	struct obl
	{
		char function[5];
		LT::LexTable lextab;
		IT::IdentTable idtab;
	};
	bool checkUp(char* m, FST::FST fst);
	void paste(int line, char m);
	void Lexis(Parm::PARM parm, In::IN in);
};
