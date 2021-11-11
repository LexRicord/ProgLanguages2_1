#pragma once
#include "LT.h"
#include "IT.h"
#include "stdafx.h"

namespace PLN
{
	bool PolishNotation(int  lt_position, LT::LexTable& lextTable, IT::IdentTable& idTable);

	struct lexEntry : LT::Entry
	{
		lexEntry* next;

		lexEntry()
		{
			this->next = nullptr;
		}

		lexEntry(LT::Entry input, lexEntry* next)
		{
			this->operation = input.operation;
			this->lexToken = input.lexToken;
			this->indexTI = input.indexTI;
			this->sourceNumber = input.sourceNumber;
			this->next = next;
		}

		operator LT::Entry()
		{
			return LT::Entry(this->lexToken, this->sourceNumber, this->indexTI);
		}
	};




	struct Stack
	{
		lexEntry* head;
		int current_size;
		const int max_count = 200;

		Stack()
		{
			this->current_size = 0;
			this->head = nullptr;
		}
		~Stack()
		{
			while (this->current_size != 0)
			{
				this->pop();
			}
		}

		bool push(LT::Entry input);
		bool push(PLN::lexEntry input);
		lexEntry* pop();
		char Last_element();
		int getCount() {
			return this->current_size;
		}
	};
}