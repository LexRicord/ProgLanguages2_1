#pragma once
#include "stdafx.h"
#include "tokenAnalisys.h"

void SeparationOfTokens(const In::IN& source, LT::LexTable& lexTable, IT::IdentTable& idTable)
{
	char* temp = new char[tokenSize] {};
	int str_number = 1;
	int str_position = 1;
	In::IN in_ex;

	for (int i = 0, j = 0; i < source.size; i++)
	{
		if (in_ex.code[(source.text[i])] != in_ex.D && in_ex.code[(source.text[i])] != in_ex.A)
		{
			temp[j++] = source.text[i];
			str_position++;
			continue;
		}
		else
		{
			if (j != 0)
			{
				i--;
				temp[j] = '\0';
				if (tokenAnalize(temp, str_number, lexTable, idTable))
				{
					temp[0] = '\0'; j = 0;
					continue;
				}
				else
					throw ERROR_THROW_IN(123, str_number, str_position);
			}
			else
			{
				if (source.text[i] == '\'')
				{
					temp[j++] = source.text[i++];

					for (int c = 0; source.text[i] != '\''; c++)
					{
						if (c <= TI_STR_MAXSIZE)
						{
							temp[j++] = source.text[i++];
						}
						else
							throw ERROR_THROW_IN(127, str_number, str_position);
					}

					if (source.text[i] == '\'')
					{
						temp[j] = source.text[i];
						if (tokenAnalize(temp, str_number, lexTable, idTable))
						{
							temp[0] = '\0'; j = 0;
							continue;
						}
						else
							throw ERROR_THROW_IN(123, str_number, str_position);
					}
					else
						throw ERROR_THROW_IN(124, str_number, str_position);
				}

				if (source.text[i] != '\n')
				{
					if (source.text[i] == ' ' || source.text[i] == '\t')
					{
						str_position++;
						continue;
					}

					temp[0] = source.text[i]; temp[1] = '\0';
					if (tokenAnalize(temp, str_number, lexTable, idTable))
						str_position++;
					else
						throw ERROR_THROW_IN(123, str_number, str_position);

					temp[0] = '/0'; j = 0;
				}
			}
		}
		if (source.text[i] == '\n')
		{
			str_number++;
			str_position = 0;
		}
		
	}
	delete[] temp;
}

bool tokenAnalize(char* token, const int str_number, LT::LexTable& lexTable, IT::IdentTable& idTable)
{
	static varTypeFlag varTypeFlag;

	switch (token[0])
	{
	case LEX_COMMA:
	{
		Add(lexTable, { LEX_COMMA,str_number,LT_TI_NULLXDX });
		return true;
	}

	case LEX_LEFT_BRACE:
	{
		Add(lexTable, { LEX_LEFT_BRACE,str_number,LT_TI_NULLXDX });
		return true;
	}

	case LEX_RIGHT_BRACE:
	{
		Add(lexTable, { LEX_RIGHT_BRACE,str_number,LT_TI_NULLXDX });
		return true;
	}

	case LEX_LEFTHESIS:
	{
		Add(lexTable, { LEX_LEFTHESIS,str_number,LT_TI_NULLXDX });
		return true;
	}

	case LEX_RIGHTHESIS:
	{
		Add(lexTable, { LEX_RIGHTHESIS,str_number,LT_TI_NULLXDX });
		return true;
	}

	case LEX_SEMICOLON:
	{
		Add(lexTable, { LEX_SEMICOLON,str_number,LT_TI_NULLXDX });
		return true;
	}

	case '+':
	{
		Add(lexTable, { LEX_PLUS,str_number,LT_TI_NULLXDX,'+' });
		return true;
	}

	case '-':
	{
		Add(lexTable, { LEX_MINUS,str_number,LT_TI_NULLXDX,'-' });
		return true;
	}

	case '*':
	{
		Add(lexTable, { LEX_STAR,str_number,LT_TI_NULLXDX,'*' });
		return true;
	}

	case '/':
	{
		Add(lexTable, { LEX_SLASH,str_number,LT_TI_NULLXDX,'/' });
		return true;
	}

	case LEX_EQUAL_SIGN:
	{
		Add(lexTable, { LEX_EQUAL_SIGN,str_number,LT_TI_NULLXDX });
		return true;
	}

	case 'f':
	{
		FST::FST* function = new FST::FST(FST_FUNCTION(token));
		if (FST::execute(*function))
		{
			Add(lexTable, { LEX_FUNCTION,str_number,LT_TI_NULLXDX });

			delete function;
			function = NULL;
			return true;
		}
		else
		{
			delete function;
			function = NULL;

			return func_var(token, str_number, lexTable, idTable, varTypeFlag);
		}
	}
	case 'i':
	{
		FST::FST* integer = new FST::FST(FST_INTEGER(token));
		if (FST::execute(*integer))
		{
			Add(lexTable, { LEX_INTEGER,str_number,LT_TI_NULLXDX });

			delete integer;
			integer = NULL;
			varTypeFlag.LT_posititon = lexTable.size - 1;
			varTypeFlag.type = varTypeFlag::INT;
			return true;
		}
		else
		{
			delete integer;
			integer = NULL;

			return func_var(token, str_number, lexTable, idTable, varTypeFlag);
		}
	}
	case 's':
	{
		FST::FST* string = new FST::FST(FST_STRING(token));
		if (FST::execute(*string))
		{
			Add(lexTable, { LEX_STRING,str_number,LT_TI_NULLXDX });

			delete string;
			string = NULL;
			varTypeFlag.LT_posititon = lexTable.size - 1;
			varTypeFlag.type = varTypeFlag::STR;
			return true;
		}
		else
		{
			delete string;
			string = NULL;

			return func_var(token, str_number, lexTable, idTable, varTypeFlag);
		}
	}

	case 'd':
	{
		FST::FST* declare = new FST::FST(FST_DECLARE(token));
		if (FST::execute(*declare))
		{
			Add(lexTable, { LEX_DECLARE,str_number,LT_TI_NULLXDX });

			delete declare;
			declare = NULL;
			return true;
		}
		else
		{
			delete declare;
			declare = NULL;

			return func_var(token, str_number, lexTable, idTable, varTypeFlag);
		}
	}

	case 'r':
	{
		FST::FST* _return = new FST::FST(FST_RETURN(token));
		if (FST::execute(*_return))
		{
			Add(lexTable, { LEX_RETURN,str_number,LT_TI_NULLXDX });

			delete _return;
			_return = NULL;
			return true;
		}
		else
		{
			delete _return;
			_return = NULL;

			return func_var(token, str_number, lexTable, idTable, varTypeFlag);
		}
	}
	case 'p':
	{
		FST::FST* _print = new FST::FST(FST_PRINT(token));
		if (FST::execute(*_print))
		{
			Add(lexTable, { LEX_PRINT,str_number,LT_TI_NULLXDX });

			delete _print;
			_print = NULL;
			return true;
		}
		else
		{
			delete _print;
			_print = NULL;

			return func_var(token, str_number, lexTable, idTable, varTypeFlag);
		}
	}
	case '\'':
	{
		FST::FST* stringLiteral = new FST::FST(FST_STRING_LITERAL(token));
		if (FST::execute(*stringLiteral))
		{
			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL, str_number, i });
			else
			{
				idTable.Add({ "\0", (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexToken == '=') ? idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).id : "-" , IT::ID_DATA_TYPE::STR, IT::ID_TYPE::L });
				idTable.table[idTable.size - 1].value.valueStr->len = 0;
				int i = 0, j = 0;
				for (; token[i] != '\0'; i++)
				{
					idTable.table[idTable.size - 1].value.valueStr->str[j] = token[i];
					idTable.table[idTable.size - 1].value.valueStr->len++;
					j++;
				}
				idTable.table[idTable.size - 1].value.valueStr->str[j] = '\0';

				Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
			}

			delete stringLiteral;
			stringLiteral = NULL;
			return true;
		}
	}
	default:
	{
		FST::FST* number_literal = new FST::FST(FST_INTEGER_LITERAL(token));
		if (FST::execute(*number_literal))
		{
			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL,str_number,i });
			else
			{
				idTable.Add({ "\0", (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexToken == '=') ? idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).id : "-" , IT::ID_DATA_TYPE::INT, IT::ID_TYPE::L });
				idTable.table[idTable.size - 1].value.valueInt = atoi(token);
				Add(lexTable, { LEX_LITERAL,str_number, idTable.size - 1 });
			}
			delete number_literal;
			number_literal = NULL;
			return true;
		}
		else
		{
			delete number_literal;
			number_literal = NULL;

			return func_var(token, str_number, lexTable, idTable, varTypeFlag);
		}
	}

	}
}

bool func_var(char* token, const int str_number, LT::LexTable& lexTable, IT::IdentTable& idTable, varTypeFlag& varTypeFlag)
{
	FST::FST* id = new FST::FST(FST_IDENTIFICATOR(token));
	if (FST::execute(*id))
	{
		bool Checked_id = false;

		if (strcmp(token, "main") == 0 || ((lexTable.GetEntry(lexTable.size - 1).lexToken == LEX_FUNCTION &&
				lexTable.GetEntry(lexTable.size - 2).lexToken == 't') &&
				varTypeFlag.LT_posititon == lexTable.size - 2))
		{
			if (strcmp(token, "main") == 0)
			{
				for (int iter = 0; iter < idTable.size; iter++)
				{
					if (strcmp(idTable.GetEntry(iter).id, "main") == 0)
					{
						throw ERROR_THROW_IN(129, str_number, -1);
					}
				}
			}
			if (idTable.IsId(token) == -1)
			{
				if (varTypeFlag.type == varTypeFlag::INT)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::F });
				}
				if (varTypeFlag.type == varTypeFlag::STR)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::STR, IT::ID_TYPE::F });
				}
				if (strcmp(token, "main") == 0)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::F });
				}

				varTypeFlag.LT_posititon = -1;
				varTypeFlag.type = varTypeFlag::DEF;

				Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
				Checked_id = true;
			}
			else
				throw ERROR_THROW_IN(123, str_number, -1);
		}

		if (!Checked_id && (lexTable.GetEntry(lexTable.size - 1).lexToken == 't' && lexTable.GetEntry(lexTable.size - 2).lexToken == LEX_DECLARE && varTypeFlag.LT_posititon == lexTable.size - 1))
		{
			bool LeftBrace = false;
			for (int i = lexTable.size - 1; i >= 0; i--)
			{
				if (lexTable.GetEntry(i).lexToken == LEX_LEFT_BRACE)
					LeftBrace = true;
				if (LeftBrace &&
					lexTable.GetEntry(i).lexToken == LEX_ID &&
					idTable.GetEntry(lexTable.GetEntry(i).indexTI).idType == IT::ID_TYPE::F)
				{
					if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).indexTI).id) == -1)
					{
						if (varTypeFlag.type == varTypeFlag::INT)
						{
							idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,token, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::V });
						}
						if (varTypeFlag.type == varTypeFlag::STR)
						{
							idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,token , IT::ID_DATA_TYPE::STR, IT::ID_TYPE::V });
						}
						varTypeFlag.LT_posititon = -1;
						varTypeFlag.type = varTypeFlag::DEF;

						Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
						Checked_id = true;
						break;
					}
					else
						throw ERROR_THROW_IN(125, str_number, -1);
				}


			}
		}

		if (!Checked_id && //func par-s
			(lexTable.GetEntry(lexTable.size - 1).lexToken == 't' && varTypeFlag.LT_posititon == lexTable.size - 1))
		{
			for (int i = lexTable.size - 1; i > 0; i--)
			{
				LT::Entry entry_minus_one = lexTable.GetEntry(i - 1);
				LT::Entry entry_minus_two = lexTable.GetEntry(i - 2);
				LT::Entry entry = lexTable.GetEntry(i);
				bool type_check = (idTable.GetEntry(entry.indexTI).idType == IT::ID_TYPE::F);
				if (entry.lexToken == LEX_ID && type_check)
				{
					if (entry_minus_one.lexToken == LEX_FUNCTION && entry_minus_two.lexToken == 't')
					{
						if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).indexTI).id) == -1)
						{
							if (varTypeFlag.type == varTypeFlag::INT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,token , IT::ID_DATA_TYPE::INT, IT::ID_TYPE::P });
								idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity++;
							}
							if (varTypeFlag.type == varTypeFlag::STR)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,token , IT::ID_DATA_TYPE::STR, IT::ID_TYPE::P });
								idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity++;
							}
							varTypeFlag.LT_posititon = -1;
							varTypeFlag.type = varTypeFlag::DEF;

							Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
							Checked_id = true;
							break;
						}
						else
							throw ERROR_THROW_IN(125, str_number, -1);
					}
				}
			}
		}

		//scoped id
		if (!Checked_id)
		{
			bool LeftBrace = false;
			for (int i = lexTable.size - 1; i >= 0; i--)
			{
				if (lexTable.GetEntry(i).lexToken == LEX_LEFT_BRACE)
					LeftBrace = true;
				if (LeftBrace && lexTable.GetEntry(i).lexToken == LEX_ID &&
					idTable.GetEntry(lexTable.GetEntry(i).indexTI).idType == IT::ID_TYPE::F)
				{
					int temp = idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).indexTI).id);
					if (temp != -1)
					{
						Add(lexTable, { LEX_ID,str_number,temp });
						break;
					}
					else
					{
						temp = idTable.IsId(token);
						if (idTable.GetEntry(temp).idType != IT::ID_TYPE::F)
						{
							token[5] = '\0';
						}
						if (temp != -1 && idTable.GetEntry(temp).idType == IT::ID_TYPE::F)
						{
							Add(lexTable, { LEX_ID,str_number,temp });
							break;
						}

						else throw ERROR_THROW_IN(126, str_number, -1);
					}
				}
			}
		}

		delete id;
		id = NULL;
		return true;
	}
	else
	{
		delete id;
		id = NULL;
		return false;
	}
}