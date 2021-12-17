#pragma once

#include "stdafx.h"
#include "LT.h"
#include "Error.h"
#include <fstream>
namespace LT
{
	LT::LexTable::LexTable()
	{
		this->maxSize = LT_MAXSIZE;
		this->size = 0;
		this->table = new Entry[LT_MAXSIZE];
	}

	void Add(LexTable& lexTable, Entry entry)
	{
		if (lexTable.size < lexTable.maxSize)
			lexTable.table[lexTable.size++] = entry;
		else
			throw ERROR_THROW(120);
	}
	Entry LexTable::GetEntry(int n)
	{
		if (n < this->maxSize && n >= 0)
			return this->table[n];
	}
	void Delete(LexTable& lexTable)
	{
		delete[] lexTable.table;
		lexTable.table = nullptr;
	}
	void LexTable::PrintLexTable(const wchar_t* in)
	{
		int i = 0;
		wchar_t lex[500];
		for (; in[i] != '\0'; i++)
			lex[i] = in[i];
		lex[i] = '\0';
		wcscat_s(lex, PARM_LEX);

		std::ofstream* lex_stream = new std::ofstream;
		lex_stream->open(lex);

		if (lex_stream->is_open())
		{
			int num_string = 0, t = 0;
			for (int i = 0; i < this->size;)
			{
				t = this->table[i].indexTI;
				if (num_string == this->table[i].sourceNumber) {
					if ((this->table[i].lexToken == 'i') || (this->table[i].lexToken == 'l')) {
						(*lex_stream) << this->table[i++].lexToken;
						(*lex_stream) << t;
					}
					else {
						(*lex_stream) << this->table[i++].lexToken;
					}
				}
				else
				{
					num_string++;
					if (this->table[i].sourceNumber != num_string)
					{
						continue;
					}
					(*lex_stream) << '\n' << num_string << '\t';

					if (num_string == this->table[i].sourceNumber)
						(*lex_stream) << this->table[i++].lexToken;
				}
			}
		}
		else
			throw ERROR_THROW(128);
		lex_stream->close();
		delete lex_stream;

	}
	void LexTable::PrintLexTable(const wchar_t* in, const wchar_t* name)
	{
		int i = 0;
		wchar_t lex[500];
		for (; in[i] != '\0'; i++)
			lex[i] = in[i];
		lex[i] = '\0';
		wcscat_s(lex, name);

		std::ofstream* lex_stream = new std::ofstream;
		lex_stream->open(lex);

		if (lex_stream->is_open())
		{
			int num_string = 0, t = 0;
			for (int i = 0; i < this->size;)
			{
				t = this->table[i].indexTI;
				if (num_string == this->table[i].sourceNumber) {
					if ((this->table[i].lexToken == 'i') || (this->table[i].lexToken == 'l')) {
						(*lex_stream) << this->table[i++].lexToken;
						(*lex_stream) << t;
					}
					else {
						(*lex_stream) << this->table[i++].lexToken;
					}
				}
				else
				{
					num_string++;
					if (this->table[i].sourceNumber != num_string)
					{
						continue;
					}
					(*lex_stream) << '\n' << num_string << '\t';

					if (num_string == this->table[i].sourceNumber)
						(*lex_stream) << this->table[i++].lexToken;
				}
			}
		}
		else
			throw ERROR_THROW(128);
		lex_stream->close();
		delete lex_stream;

	}

	LT::Entry::Entry()
	{
		this->lexToken = '\0';
		this->sourceNumber = LT_TI_NULLXDX;
		this->indexTI = LT_TI_NULLXDX;
	}

	LT::Entry::Entry(const char lex, int str_n, int indexTI)
	{
		this->lexToken = lex;
		this->sourceNumber = str_n;
		this->indexTI = indexTI;
	}
	LT::Entry::Entry(const char lex, int str_n, int indexTI, char operation_symbol)
	{
		this->lexToken = lex;
		this->sourceNumber = str_n;
		this->indexTI = indexTI;
		this->operation = operation_symbol;
	}
}