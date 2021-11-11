#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"

#define BEGIN_SYMBOL '|'

namespace PLN
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

	bool Stack::push(PLN::lexEntry input)
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

	char Stack::Last_element()
	{
		if (this->head->lexToken == 'v')
			return this->head->operation;
		return this->head->lexToken;
	}


	bool PolishNotation(int lt_position, LT::LexTable& lexTable, IT::IdentTable& idTable)
	{
		PLN::Stack* literals = new PLN::Stack;
		PLN::Stack* operators = new PLN::Stack;

		operators->push({ BEGIN_SYMBOL, -1, -1 });

		bool flag = true;
		bool is_complete = false;
		int function_id_position = 0;
		LT::Entry temp;

		for (int i = lt_position; flag;)
		{
			temp = lexTable.GetEntry(i);

			if (idTable.GetEntry(temp.indexTI).idType == IT::ID_TYPE::F)
			{
				for (; lexTable.GetEntry(i).lexToken != ')'; i++)
				{
					temp = lexTable.GetEntry(i);
					literals->push(temp);
				}
				temp = lexTable.GetEntry(i);
				literals->push(temp);
				i++;
				continue;
			}
			if (temp.lexToken == LEX_ID || temp.lexToken == LEX_LITERAL)
			{
				literals->push(temp);
				i++;
				continue;
			}

			switch (operators->Last_element())
			{
			case BEGIN_SYMBOL:
			{
				if (temp.operation == PLUS ||
					temp.operation == MINUS ||
					temp.operation == LEX_STAR ||
					temp.operation == LEX_SLASH ||
					temp.lexToken == LEX_LEFTHESIS)
				{
					operators->push(temp);
					i++;
					break;
				}
				if (temp.lexToken == LEX_RIGHTHESIS) { flag = false; }
				if (temp.lexToken == LEX_SEMICOLON) { is_complete = true; flag = false; }
				break;
			}
			case PLUS:
			case MINUS:
			{
				if (temp.operation == PLUS ||
					temp.operation == MINUS ||
					temp.lexToken == LEX_LEFTHESIS ||
					temp.lexToken == LEX_SEMICOLON)
				{
					literals->push(*operators->pop());
					break;
				}

				if (temp.operation == LEX_STAR ||
					temp.operation == LEX_SLASH ||
					temp.lexToken == LEX_LEFTHESIS)
				{
					operators->push(temp);
					i++;
					break;
				}
			}

			case LEX_STAR:
			case LEX_SLASH:
			{
				if (temp.operation == PLUS ||
					temp.operation == MINUS ||
					temp.operation == LEX_STAR ||
					temp.operation == LEX_SLASH ||
					temp.lexToken == LEX_RIGHTHESIS ||
					temp.lexToken == LEX_SEMICOLON)
				{
					literals->push(*operators->pop());
					break;
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
				if (temp.lexToken == LEX_SEMICOLON) flag = false;

				if (temp.operation == PLUS ||
					temp.operation == MINUS ||
					temp.operation == LEX_STAR ||
					temp.operation == LEX_SLASH ||
					temp.lexToken == LEX_LEFTHESIS)
				{
					operators->push(temp);
					i++;
					break;
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
			PLN::lexEntry* temp;
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

			for (int i = lt_position, j = 0; lexTable.table[i].lexToken != LEX_SEMICOLON; i++)
			{
				if ((i - count) < lt_position)
					lexTable.table[i] = temp_array[j++];
				else
					lexTable.table[i] = { ' ', lexTable.table[i].sourceNumber, -1 };
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
