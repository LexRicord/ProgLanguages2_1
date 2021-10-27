#pragma once

#include <string.h>
#include "stdafx.h"


namespace IT
{
	IT::IdentTable::IdentTable()
	{
		this->maxSize = TI_MAXSIZE;
		this->size = 0;
		this->table = new Entry[TI_MAXSIZE];
	}
	Entry::Entry()
	{
		this->parentFunc[0] = '\0';
		this->id[0] = '\0';
		this->idDataType = IT::ID_DATA_TYPE::DEF;
		this->idType = IT::ID_TYPE::D;
		this->parmQuantity = 0;
	}
	Entry::Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType)
	{
		int i = 0;
		if (parentFunc)
			for (i = 0; parentFunc[i] != '\0'; i++)
				this->parentFunc[i] = parentFunc[i];
		this->parentFunc[i] = '\0';

		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];
		this->id[i] = '\0';

		this->idDataType = idDataType;
		this->idType = idType;
		this->parmQuantity = 0;
	}
	Entry::Entry(char* parentFunc, char* id, ID_DATA_TYPE idDataType, ID_TYPE idType)
	{
		int i = 0;
		if (parentFunc)
			for (i = 0; parentFunc[i] != '\0'; i++)
				this->parentFunc[i] = parentFunc[i];
		this->parentFunc[i] = '\0';

		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];
		this->id[i] = '\0';

		this->idDataType = idDataType;
		this->idType = idType;
		this->parmQuantity = 0;
		this->value.valueStr->len = 0;
	}

	IdentTable Create(int size)
	{
		IdentTable id_table;
		id_table.size = size;
		id_table.maxSize = TI_MAXSIZE;
		id_table.table = new Entry[TI_MAXSIZE];
		return id_table;
	}
	void IdentTable::Add(Entry entry)
	{
		if (strlen(entry.id) > ID_MAXSIZE && entry.idType != ID_TYPE::F)
			throw ERROR_THROW(121);

		if (this->size < this->maxSize)
		{
			if (entry.idType != ID_TYPE::F)
				entry.id[5] = '\0';
			this->table[this->size] = entry;

			switch (entry.idDataType)
			{
			case ID_DATA_TYPE::INT:
			{
				this->table[this->size].value.valueInt = IT_INT_DEFAULT;
			}
			case ID_DATA_TYPE::STR:
			{
				this->table[this->size].value.valueStr->str[0] = IT_STR_DEFAULT;
				this->table[this->size].value.valueStr->len = 0;
			}
			}
			this->size++;
		}
		else
			throw ERROR_THROW(122);

	}
	Entry IdentTable::GetEntry(int n)
	{
		if (n < this->size && n >= 0)
			return this->table[n];
	}
	int IdentTable::IsId(const char id[ID_MAXSIZE])
	{
		for (int iter = 0; iter < this->size; iter++)
		{
			if (strcmp(this->table[iter].id, id) == 0)
				return iter;
		}
		return TI_NULLIDX;
	}
	int IdentTable::IsId(const char id[ID_MAXSIZE], const char parentFunc[ID_MAXSIZE + 5])
	{
		for (int i = 0; i < this->size; i++)
		{
			if ((strcmp(this->table[i].id, id) == 0) &&
				(strcmp(this->table[i].parentFunc, parentFunc) == 0))
				return i;
		}
		return TI_NULLIDX;
	}
	void Delete(IdentTable& idtable)
	{
		delete[] idtable.table;
		idtable.table = nullptr;
	}

	void IdentTable::PrintIdTable(const wchar_t* in)
	{
		int i = 0;
		wchar_t id[300];
		for (; in[i] != '\0'; i++)
			id[i] = in[i];
		id[i] = '\0';
		wcscat_s(id, PARM_ID);

		std::ofstream* idStream = new std::ofstream;
		idStream->open(id);

		if (idStream->is_open())
		{
			bool flagForFirst = false;

#pragma region Literals

			*(idStream) << "====================================================================================" << std::endl;
			*(idStream) << "| Литералы |" << std::endl;
			*(idStream) << "====================================================================================" << std::endl;
			*(idStream) << '|' << std::setw(15) << "Идентификатор: " << std::setw(15) << "Тип данных: " << "|" << std::setw(20) << "Значение: " << '|' << std::setw(20) << "Длина строки: " << '|' << std::endl;
			*(idStream) << "===================================================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idType == IT::ID_TYPE::L)
				{
					std::cout.width(25);
					switch (this->table[i].idDataType)
					{
					case 1:
					{
						*(idStream) << '|' << std::setw(15) << this->table[i].id << '|' << std::setw(15) << "INT " << '|' << std::setw(20) << this->table[i].value.valueInt << '|' << std::setw(15) << "-" << '|' << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << '|' << std::setw(15) << this->table[i].id << '|' << std::setw(15) << "STR " << '|' << std::setw(20) << this->table[i].value.valueStr->str << '|' << std::setw(15) << (int)this->table[i].value.valueStr->len << '|' << std::endl;
						break;
					}
					}
				}
			}

			*(idStream) << "====================================================================================" << std::endl;


#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Functions

			flagForFirst = false;

			*(idStream) << "=============================================================================" << std::endl;
			*(idStream) << "| Функции |" << std::endl;
			*(idStream) << "=============================================================================" << std::endl;
			*(idStream) << '|' << std::setw(20) << "Идентификатор: " << '|' << std::setw(25) << "Тип данных возврата: " << '|' << std::setw(35) << "Количество переданных параметров: " << '|' << std::endl;
			*(idStream) << "=============================================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idType == IT::ID_TYPE::F)
				{

					switch (this->table[i].idDataType)
					{
					case 1:
					{
						*(idStream) << '|' << std::setw(20) << this->table[i].id << '|' << std::setw(25) << "INT " << '|' << std::setw(35) << this->table[i].parmQuantity << '|' << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << '|' << std::setw(20) << this->table[i].id << '|' << std::setw(25) << "STR " << '|' << std::setw(35) << this->table[i].parmQuantity << '|' << std::endl;
						break;
					}
					}

				}


			}

			*(idStream) << "=============================================================================" << std::endl;

#pragma endregion
			*(idStream) << "\n\n\n";
#pragma region Variables

			flagForFirst = false;

			*(idStream) << "==================================================================================================================================================================" << std::endl;
			*(idStream) << "| Переменные |" << std::endl;
			*(idStream) << "==================================================================================================================================================================" << std::endl;
			*(idStream) << '|' << std::setw(30) << "Имя родительского блока: " << '|' << std::setw(30) << "Идентификатор: " << '|' << std::setw(25) << "Тип данных: " << '|' << std::setw(25) << "Тип идентификатора: " << '|' << std::setw(25) << "Значение: " << '|' << std::setw(25) << "Длина строки: " << '|' << std::endl;
			*(idStream) << "==================================================================================================================================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idType == IT::ID_TYPE::V)
				{


					switch (this->table[i].idDataType)
					{
					case 1:
					{
						*(idStream) << '|' << std::setw(30) << this->table[i].parentFunc << '|' << std::setw(30) << this->table[i].id << '|' << std::setw(25) << "INT " << '|' << std::setw(25) << "V  " << '|' << std::setw(25) << this->table[i].value.valueInt << '|' << std::setw(25) << "- " << '|' << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << '|' << std::setw(30) << this->table[i].parentFunc << '|' << std::setw(30) << this->table[i].id << '|' << std::setw(25) << "STR " << '|' << std::setw(25) << "V  " << '|' << std::setw(25) << this->table[i].value.valueStr->str << '|' << std::setw(25) << (int)this->table[i].value.valueStr->len << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}

				if (this->table[i].idType == IT::ID_TYPE::P)
				{

					switch (this->table[i].idDataType)
					{
					case 1:
					{
						*(idStream) << '|' << std::setw(30) << this->table[i].parentFunc << '|' << std::setw(30) << this->table[i].id << '|' << std::setw(25) << "INT " << '|' << std::setw(25) << "P  " << '|' << std::setw(25) << this->table[i].value.valueInt << '|' << std::setw(25) << "- " << '|' << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << '|' << std::setw(30) << this->table[i].parentFunc << '|' << std::setw(30) << this->table[i].id << '|' << std::setw(25) << "STR " << '|' << std::setw(25) << "P  " << '|' << std::setw(25) << this->table[i].value.valueStr->str << '|' << std::setw(25) << (int)this->table[i].value.valueStr->len << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}

			}
			*(idStream) << "==================================================================================================================================================================" << std::endl;
#pragma endregion
			* (idStream) << "\n\n\n";

		}
		else
			throw ERROR_THROW(125);
		idStream->close();
		delete idStream;
	}
}