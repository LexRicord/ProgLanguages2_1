#pragma once
#include "LT.h"
#include "IT.h"
#include "PN.h"
#include "IN.h"
#include <stdlib.h>

#define BEGIN_SYMBOL '|'

namespace PN
{
	bool Stack::push(LT::Entry input)
	{
		if (this->current_size < this->max_count)
		{
			lexEntry* temp = new lexEntry(input, this->head);
			this->head = temp;
			this->current_size++;
		}
		else
			return false;
	}

	bool Stack::push(PN::lexEntry input)
	{
		if (this->current_size < this->max_count)
		{
			lexEntry* temp = new lexEntry(input, this->head);
			this->head = temp;
			this->current_size++;
		}
		else
			return false;
	}

	lexEntry* Stack::pop()
	{
		if (this->current_size != 0)
		{

			lexEntry temp(*this->head);
			delete this->head;
			this->head = temp.next;
			this->current_size--;

			return &temp;
		}
		else
			return 0;
	}

	char Stack::Last_element(IT::IdTable idTable)
	{
		if (this->head->lexToken == 'v')
			return idTable.table[this->head->indexTI].value.operation;
		return this->head->lexToken;
	}


	bool PolishNotation(int lt_position, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		PN::Stack* literals = new PN::Stack;
		PN::Stack* operators = new PN::Stack;

		operators->push({ BEGIN_SYMBOL, -1, -1 });

		bool flag = true;
		bool is_complete = false;
		int function_id_position = 0;
		LT::Entry temp;
		In::IN in_ex;

		for (int i = lt_position; flag;)
		{
			temp = lexTable.GetEntry(i);

			if (idTable.GetEntry(temp.indexTI).idType == IT::ID_TYPE::F)
			{
				LT::Entry temp_1;
				temp_1 = lexTable.GetEntry(i);
				temp_1.lexToken = '\@';
				char buffer[ID_MAXSIZE];
				int parm_quantity = 0;
				i++;
				for (; lexTable.GetEntry(i).lexToken != ')' && lexTable.GetEntry(i).lexToken != ';'; i++)
				{

					if (in_ex.code[lexTable.GetEntry(i).lexToken] != in_ex.D)
					{
						parm_quantity++;
						temp = lexTable.GetEntry(i);
						literals->push(temp);
					}
				}
				if (lexTable.GetEntry(i).lexToken == ';' && parm_quantity == 0)
				{
					break;
				}
				_itoa_s(parm_quantity, buffer, 10);
				literals->push(temp_1);
				literals->push({ buffer[0],temp_1.sourceNumber,temp_1.indexTI });
				i++;
				continue;
			}
			if (temp.lexToken == LEX_ID || temp.lexToken == LEX_LITERAL)
			{
				literals->push(temp);
				i++;
				continue;
			}
			switch (operators->Last_element(idTable))
			{


			case BEGIN_SYMBOL:
			{
				if (temp.indexTI != -1)
				{
					if (idTable.table[temp.indexTI].value.operation == PLUS ||
						idTable.table[temp.indexTI].value.operation == MINUS ||
						idTable.table[temp.indexTI].value.operation == STAR ||
						idTable.table[temp.indexTI].value.operation == DIRSLASH)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				else
				{
					if (temp.lexToken == LEX_LEFTHESIS)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				if (temp.lexToken == LEX_RIGHTHESIS) { flag = false; }
				if (temp.lexToken == LEX_SEMICOLON ||
					temp.lexToken == LEX_EQUALITY_SIGN ||
					temp.lexToken == LEX_LESS_SIGN ||
					temp.lexToken == LEX_MORE_SIGN ||
					temp.lexToken == LEX_NOTEQUALITY_SIGN) {
					is_complete = true; flag = false;
				}
				break;
			}
			case PLUS:
			case MINUS:
			{
				if (temp.indexTI != -1)
				{
					if (idTable.table[temp.indexTI].value.operation == PLUS ||
						idTable.table[temp.indexTI].value.operation == MINUS)
					{
						literals->push(*operators->pop());
						break;
					}
				}
				else
				{
					if (temp.lexToken == LEX_LEFTHESIS ||
						temp.lexToken == LEX_SEMICOLON ||
						temp.lexToken == LEX_EQUALITY_SIGN ||
						temp.lexToken == LEX_LESS_SIGN ||
						temp.lexToken == LEX_MORE_SIGN ||
						temp.lexToken == LEX_NOTEQUALITY_SIGN)
					{
						literals->push(*operators->pop());
						break;
					}
				}

				if (temp.indexTI != -1)
				{
					if (idTable.table[temp.indexTI].value.operation == STAR ||
						idTable.table[temp.indexTI].value.operation == DIRSLASH)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				else
				{
					if (temp.lexToken == LEX_LEFTHESIS)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
			}

			case STAR:
			case DIRSLASH:
			{
				if (temp.indexTI != -1)
				{
					if (idTable.table[temp.indexTI].value.operation == PLUS ||
						idTable.table[temp.indexTI].value.operation == MINUS ||
						idTable.table[temp.indexTI].value.operation == STAR ||
						idTable.table[temp.indexTI].value.operation == DIRSLASH )
					{
						literals->push(*operators->pop());
						break;
					}
				}
				else
				{
					if (temp.lexToken == LEX_RIGHTHESIS ||
						temp.lexToken == LEX_SEMICOLON ||
						temp.lexToken == LEX_EQUALITY_SIGN ||
						temp.lexToken == LEX_LESS_SIGN ||
						temp.lexToken == LEX_MORE_SIGN ||
						temp.lexToken == LEX_NOTEQUALITY_SIGN)
					{
						literals->push(*operators->pop());
						break;
					}
				}
				if (temp.lexToken == LEX_LEFTHESIS)
				{
					operators->push(temp);
					i++;
					break;
				}
			}
			case LEX_LEFTHESIS:
			{
				if (temp.lexToken == LEX_SEMICOLON ||
					temp.lexToken == LEX_EQUALITY_SIGN ||
					temp.lexToken == LEX_LESS_SIGN ||
					temp.lexToken == LEX_MORE_SIGN ||
					temp.lexToken == LEX_NOTEQUALITY_SIGN)
					flag = false;

				if (temp.indexTI != -1)
				{
					if (idTable.table[temp.indexTI].value.operation == PLUS ||
						idTable.table[temp.indexTI].value.operation == MINUS ||
						idTable.table[temp.indexTI].value.operation == STAR ||
						idTable.table[temp.indexTI].value.operation == DIRSLASH)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				else
				{
					if (temp.lexToken == LEX_LEFTHESIS)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				if (temp.lexToken == LEX_RIGHTHESIS)
				{
					operators->pop();
					i++;
					break;
				}
			}
			default:
				flag = false;
			}
		}

		if (is_complete)
		{
			PN::lexEntry* temp;
			int count = literals->getCount();
			LT::Entry* temp_array = new LT::Entry[count];

			for (int i = count - 1; i >= 0; i--)
			{
				temp = literals->pop();
				if (temp)
				{
					temp_array[i] = *temp;
				}
			}

			for (int i = lt_position, j = 0; lexTable.table[i].lexToken != LEX_SEMICOLON &&
				lexTable.table[i].lexToken != LEX_EQUALITY_SIGN &&
				lexTable.table[i].lexToken != LEX_LESS_SIGN &&
				lexTable.table[i].lexToken != LEX_MORE_SIGN &&
				lexTable.table[i].lexToken != LEX_NOTEQUALITY_SIGN; i++)
			{
				if ((i - count) < lt_position)
					lexTable.table[i] = temp_array[j++];
				else
					lexTable.table[i] = { '#', lexTable.table[i].sourceNumber, -1 };
			}

			delete[] temp_array;
			delete literals;
			delete operators;
			return true;
		}
		else
		{
			delete literals;
			delete operators;
			return false;
		}
	}
}

