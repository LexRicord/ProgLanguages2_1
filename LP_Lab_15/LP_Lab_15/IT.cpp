#pragma once
#include "IT.h"
#include "Error.h"
#include <iomanip>
#include <string.h>
#include "stdafx.h"
#include "tokenAnalisys.h"
namespace IT
{
	IT::IdTable::IdTable()
	{
		this->maxsize = TI_MAXSIZE;
		this->size = 0;
		this->table = new Entry[TI_MAXSIZE];
	}
	Entry::Entry()
	{
		this->parentFunc[0] = '\0';
		this->parentFunc_num = -1;
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
		this->parentFunc_num = -1;
		this->id[i] = '\0';
		this->idDataType = idDataType;
		this->idType = idType;
		this->parmQuantity = 0;
	}
	Entry::Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, int it)
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
		this->parentFunc_num = -1;
		this->id[i] = '\0';
		this->idDataType = idDataType;
		this->idType = idType;
		this->parmQuantity = 0;
		this->value.vInt = it;
	}
	Entry::Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, char it)
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
		this->parentFunc_num = -1;
		this->id[i] = '\0';
		this->idDataType = idDataType;
		this->idType = idType;
		this->parmQuantity = 0;
		this->value.vChar = it;
	}
	Entry::Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, unsigned int it)
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
		this->parentFunc_num = -1;
		this->id[i] = '\0';
		this->idDataType = idDataType;
		this->idType = idType;
		this->parmQuantity = 0;
		this->value.vUint = it;
	}
	Entry::Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, char* ch)
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
		this->parentFunc_num = -1;
		this->id[i] = '\0';
		this->idDataType = idDataType;
		this->idType = idType;
		this->parmQuantity = 0;
		strcpy_s(this->value.vStr.str, 255, ch);
		this->value.vStr.len = strlen(ch);
	}
	Entry::Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, const char* ch)
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
		this->parentFunc_num = -1;
		this->id[i] = '\0';
		this->idDataType = idDataType;
		this->idType = idType;
		this->parmQuantity = 0;
		strcpy_s(this->value.vStr.str, 255, ch);
		this->value.vStr.len = strlen(ch);
	}
	Entry::Entry(char* parentFunc, int parentFunc_number, char* id, ID_DATA_TYPE idDataType, ID_TYPE idType)
	{
		int i = 0;
		if (parentFunc)
			for (i = 0; parentFunc[i] != '\0'; i++)
				this->parentFunc[i] = parentFunc[i];
		this->parentFunc[i] = '\0';
		this->parentFunc_num = parentFunc_number;
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->id[i] = '\0';
		this->idDataType = idDataType;
		this->idType = idType;
		this->parmQuantity = 0;
	}
	Entry::Entry(const char* parentFunc, char* id, ID_DATA_TYPE idDataType, ID_TYPE idType)
	{
		int i = 0;
		if (parentFunc)
			for (i = 0; parentFunc[i] != '\0'; i++)
				this->parentFunc[i] = parentFunc[i];
		this->parentFunc[i] = '\0';
		this->parentFunc_num = -1;
		i = 0;
		if (id[0] != '\0')
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->id[i] = '\0';
		this->idDataType = idDataType;
		this->idType = idType;
		this->parmQuantity = 0;
	}

	IdTable Create(int size)
	{
		IdTable id_table;
		id_table.size = size;
		id_table.maxsize = TI_MAXSIZE;
		id_table.table = new Entry[TI_MAXSIZE];
		return id_table;
	}

	char* IdTable::GetLexemaName()
	{
		char buffer[5] = { "l" };
		char buffer_count[5];
		_itoa_s(this->noname_lexToken_count, buffer_count, 5);
		strcat_s(buffer, buffer_count);
		this->noname_lexToken_count++;
		return buffer;
	}

	char* IdTable::GetForName(char* id, varFlagType Type)
	{
		char buffer[255] = { "" };
		strcat_s(buffer, 255, id);
		return buffer;
	}
	char* IdTable::GetViewName()
	{
		char buffer[255] = { "for_" };
		char numberBuffer[3];
		_itoa_s(this->for_count, numberBuffer, 10);
		strcat_s(buffer, 255, numberBuffer);
		this->for_count++;
		return buffer;
	}
	void IdTable::Add(Entry entry)
	{
		if (strlen(entry.id) > ID_MAXSIZE && entry.idType != ID_TYPE::F)
			throw ERROR_THROW(121);

		if (this->size < this->maxsize)
		{
			if (entry.idType != ID_TYPE::F)
				entry.id[255] = '\0';
			this->table[this->size] = entry;

			switch (entry.idDataType)
			{
			case ID_DATA_TYPE::INT:
			{
				this->table[this->size].value.vInt = TI_INT_DEFAULT; break;
			}
			case ID_DATA_TYPE::STR:
			{
				this->table[this->size].value.vStr.str[0] = TI_STR_DEFAULT;
				this->table[this->size].value.vStr.len = 0; break;
			}
			case ID_DATA_TYPE::CHAR:
			{
				this->table[this->size].value.vChar = '\0'; break;
			}
			case ID_DATA_TYPE::BOOL:
			{
				this->table[this->size].value.vBool = false; break;
			}
			case ID_DATA_TYPE::UINT:
			{
				this->table[this->size].value.vUint = 0; break;
			}
			}
			this->size++;
		}
		else
			throw ERROR_THROW(122);

	}
	Entry IdTable::GetEntry(int n)
	{
		if (n < this->size && n >= 0)
			return this->table[n];
	}
	int IdTable::IsId(const char id[ID_MAXSIZE])
	{
		for (int iter = 0; iter < this->size; iter++)
		{
			if ((strcmp(this->table[iter].id, id) == 0))
				return iter;
		}
		return TI_NULLIDX;
	}
	int IdTable::IsId(const char id[ID_MAXSIZE], Entry ide, int parentFunc_number)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (strcmp(this->table[i].id, id) == 0 &&
				strcmp(this->table[i].parentFunc, ide.id) == 0 &&
				parentFunc_number == this->table[i].parentFunc_num
				)
				return i;
		}
		return TI_NULLIDX;
	}
	int IdTable::IsId(const char id[ID_MAXSIZE], Entry ide)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (strcmp(this->table[i].id, id) == 0 &&
				strcmp(this->table[i].parentFunc, ide.id) == 0
				)
				return i;
		}
		return TI_NULLIDX;
	}
	int IdTable::IsId(const char id[ID_MAXSIZE], const char parentFunc[ID_MAXSIZE + 5], int parentFunc_number)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (strcmp(this->table[i].id, id) == 0 &&
				strcmp(this->table[i].parentFunc, parentFunc) == 0 &&
				this->table[i].parentFunc_num == parentFunc_number
				)
				return i;
		}
		return TI_NULLIDX;
	}
	void Delete(IdTable& idTable)
	{
		delete[] idTable.table;
		idTable.table = nullptr;
	}

	void IdTable::PrintIdTable(const wchar_t* in)
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

			* (idStream) << "====================================================================================" << std::endl;
			*(idStream) << "| Литералы                                                                         |" << std::endl;
			*(idStream) << "====================================================================================" << std::endl;
			*(idStream) << '|' << std::setw(15) << "Идентификатор: " << std::setw(15) << "Тип данных: " << "|" << std::setw(50) << "Значение: " << '|' << std::setw(20) << "Длина строки: " << '|' << std::endl;
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
						*(idStream) << '|' << std::setw(24) << this->table[i].id << '|' << std::setw(24) << "INT " << '|' << std::setw(60) << this->table[i].value.vInt << '|' << std::setw(30) << "-" << '|' << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << '|' << std::setw(23) << this->table[i].id << '|' << std::setw(23) << "STR" << '|' << std::setw(60 - strlen(this->table[i].value.vStr.str)) << this->table[i].value.vStr.str << '|' << std::setw(30) << (int)this->table[i].value.vStr.len << '|' << std::endl;
						break;
					}
					case 3:
					{
						*(idStream) << '|' << std::setw(23) << this->table[i].id << '|' << std::setw(23) << "UINT" << '|' << std::setw(60) << this->table[i].value.vUint << '|' << std::setw(30) << "-" << '|' << std::endl;
						break;
					}
					case 4:
					{
						*(idStream) << '|' << std::setw(23) << this->table[i].id << '|' << std::setw(23) << "CHAR" << '|' << std::setw(60) << this->table[i].value.vChar << '|' << std::setw(30) << "-" << '|' << std::endl;
						break;
					}
					case 5:
					{
						*(idStream) << '|' << std::setw(23) << this->table[i].id << '|' << std::setw(23) << "BOOL" << '|' << std::setw(60) << this->table[i].value.vBool << '|' << std::setw(30) << "-" << '|' << std::endl;
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
			*(idStream) << "| Функции                                      |" << std::endl;
			*(idStream) << "=============================================================================" << std::endl;
			*(idStream) << '|' << std::setw(20) << "Идентификатор: " << '|' << std::setw(25) << "Тип данных возврата: " << '|' << std::setw(25) << "Количество переданных параметров: " << '|' << std::endl;
			*(idStream) << "=============================================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idType == IT::ID_TYPE::F)
				{

					switch (this->table[i].idDataType)
					{
					case 1:
					{
						*(idStream) << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(42) << "INT " << '|' << std::setw(68) << this->table[i].parmQuantity << '|' << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(42) << "STR " << '|' << std::setw(68) << this->table[i].parmQuantity << '|' << std::endl;
						break;
					}
					case 3:
					{
						*(idStream) << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(42) << "UINT " << '|' << std::setw(68) << this->table[i].parmQuantity << '|' << std::endl;
						break;
					}
					case 4:
					{
						*(idStream) << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(42) << "CHAR " << '|' << std::setw(68) << this->table[i].parmQuantity << '|' << std::endl;
						break;
					}
					case 5:
					{
						*(idStream) << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(42) << "BOOL " << '|' << std::setw(68) << this->table[i].parmQuantity << '|' << std::endl;
						break;
					}
					}

				}


			}

			*(idStream) << "=============================================================================" << std::endl;

#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Variables

			flagForFirst = false;

			*(idStream) << "==================================================================================================================================================================" << std::endl;
			*(idStream) << "| Переменные                                                                                                                                                     |" << std::endl;
			*(idStream) << "==================================================================================================================================================================" << std::endl;
			*(idStream) << '|' << std::setw(30) << "Имя родительского блока: " << '|' << std::setw(20) << "Идентификатор: " << '|' << std::setw(15) << "Тип данных: " << '|' << std::setw(25) << "Тип идентификатора: " << '|' << std::setw(50) << "Значение: " << '|' << std::setw(15) << "Длина строки: " << '|' << std::endl;
			*(idStream) << "==================================================================================================================================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idType == IT::ID_TYPE::V || this->table[i].idType == IT::ID_TYPE::VF)
				{


					switch (this->table[i].idDataType)
					{
					case 1:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "INT " << '|' << std::setw(45) << "V  " << '|' << std::setw(60) << this->table[i].value.vInt << '|' << std::setw(25) << "- " << '|' << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "STR " << '|' << std::setw(45) << "V  " << '|' << std::setw(60) << this->table[i].value.vStr.str << '|' << std::setw(25) << (int)this->table[i].value.vStr.len << '|' << std::endl;
						break;
					}
					case 3:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "UINT " << '|' << std::setw(45) << "V  " << '|' << std::setw(60) << this->table[i].value.vUint << '|' << std::setw(25) << "-" << '|' << std::endl;
						break;
					}
					case 4:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "CHAR " << '|' << std::setw(45) << "V  " << '|' << std::setw(60) << this->table[i].value.vChar << '|' << std::setw(25) << "-" << '|' << std::endl;
						break;
					}
					case 5:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "BOOL " << '|' << std::setw(45) << "V  " << '|' << std::setw(60) << this->table[i].value.vBool << '|' << std::setw(25) << "-" << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}
				if (this->table[i].idType == IT::ID_TYPE::VF)
				{


					switch (this->table[i].idDataType)
					{
					case 1:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "INT " << '|' << std::setw(45) << "VF  " << '|' << std::setw(60) << this->table[i].value.vInt << '|' << std::setw(25) << "- " << '|' << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "STR " << '|' << std::setw(45) << "VF  " << '|' << std::setw(60) << this->table[i].value.vStr.str << '|' << std::setw(25) << (int)this->table[i].value.vStr.len << '|' << std::endl;
						break;
					}
					case 3:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "UINT " << '|' << std::setw(45) << "VF  " << '|' << std::setw(60) << this->table[i].value.vUint << '|' << std::setw(25) << "-" << '|' << std::endl;
						break;
					}
					case 4:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "CHAR " << '|' << std::setw(45) << "VF  " << '|' << std::setw(60) << this->table[i].value.vChar << '|' << std::setw(25) << "-" << '|' << std::endl;
						break;
					}
					case 5:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "BOOL " << '|' << std::setw(45) << "VF  " << '|' << std::setw(60) << this->table[i].value.vBool << '|' << std::setw(25) << "-" << '|' << std::endl;
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
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "INT " << '|' << std::setw(45) << "P  " << '|' << std::setw(60) << this->table[i].value.vInt << '|' << std::setw(25) << "- " << '|' << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "STR " << '|' << std::setw(45) << "P  " << '|' << std::setw(60) << this->table[i].value.vStr.str << '|' << std::setw(25) << (int)this->table[i].value.vStr.len << '|' << std::endl;
						break;
					}
					case 3:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "UINT " << '|' << std::setw(45) << "P  " << '|' << std::setw(60) << this->table[i].value.vUint << '|' << std::setw(25) << "-" << '|' << std::endl;
						break;
					}
					case 4:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "CHAR " << '|' << std::setw(45) << "P  " << '|' << std::setw(60) << this->table[i].value.vChar << '|' << std::setw(25) << "-" << '|' << std::endl;
						break;
					}
					case 5:
					{
						*(idStream) << '|' << std::setw(52 - strlen(this->table[i].parentFunc)) << this->table[i].parentFunc << '|' << std::setw(37 - strlen(this->table[i].id)) << this->table[i].id << '|' << std::setw(25) << "BOOL " << '|' << std::setw(45) << "P  " << '|' << std::setw(60) << this->table[i].value.vBool << '|' << std::setw(25) << "-" << '|' << std::endl;
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
			throw ERROR_THROW(128);
		idStream->close();
		delete idStream;
	}
}