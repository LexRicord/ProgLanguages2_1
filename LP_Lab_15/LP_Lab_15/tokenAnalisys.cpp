#pragma once

#include "In.h"
#include "Error.h"
#include "tokenAnalisys.h"
#include "LT.h"
#include "FST.h"
#include "IT.h"


void SeparationOfTokens(const In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	char* temp = new char[tokenSize] {};
	int str_number = 1;
	int str_position = 1;
	bool sign = false;
	In::IN in_ex;

	for (int i = 0, j = 0; i < source.size; i++)
	{
		if ((in_ex.code[(source.text[i])] != in_ex.D && in_ex.code[(source.text[i])] != in_ex.A && !sign) ||
			(in_ex.code[(source.text[i])] == in_ex.A && in_ex.code[(source.text[i + 1])] == in_ex.A) ||
			((source.text[i]) == '-' && in_ex.code[(source.text[i + 1])] == in_ex.N && in_ex.code[(source.text[i - 1])] != in_ex.N))
		{
			temp[j++] = source.text[i];
			str_position++;
			if ((in_ex.code[lexTable.table[lexTable.size - 1].lexToken] == in_ex.A || in_ex.code[lexTable.table[lexTable.size - 1].lexToken] == in_ex.D) &&
				((temp[j - 1]) == '-' && in_ex.code[(source.text[i + 1])] == in_ex.N))
			{
				i++;
				do
				{
					temp[j++] = source.text[i];
					str_position++;
					i++;
				} while ((in_ex.code[(source.text[i])] != in_ex.D) ||
					(in_ex.code[(source.text[i])] == in_ex.A && in_ex.code[(source.text[i + 1])] == in_ex.A));
				i--;
			}
			if (in_ex.code[(source.text[i])] == in_ex.A && in_ex.code[(source.text[i + 1])] == in_ex.A)
			{
				sign = true;
				i++;
				temp[j++] = source.text[i];
			}
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
				if (source.text[i] == '\"')
				{
					temp[j++] = source.text[i++];

					for (int c = 0; source.text[i] != '\"'; c++)
					{
						if (c <= TI_STR_MAXSIZE)
						{
							temp[j++] = source.text[i++];
						}
						else
							throw ERROR_THROW_IN(127, str_number, str_position);
					}

					if (source.text[i] == '\"')
					{
						temp[j++] = source.text[i];
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
						throw ERROR_THROW_IN(124, str_number, str_position);
				}
				if (source.text[i] == '\'')
				{
					temp[j++] = source.text[i++];
					for (int c = 0; source.text[i] != '\''; c++)
					{
						if (c <= TI_CHAR_MAXSIZE)
						{
							temp[j++] = source.text[i++];
						}
						else
							throw ERROR_THROW_IN(130, str_number, str_position);
					}

					if (source.text[i] == '\'')
					{
						temp[j++] = source.text[i];
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
			sign = false;
		}
		if (source.text[i] == '\n')
		{
			str_number++;
			str_position = 0;
		}
	}
	delete[] temp;
	bool main_flag = false;
	for (int iter = 0; iter < lexTable.size; iter++)
	{
		if (lexTable.GetEntry(iter).indexTI != -1)
			if (strcmp(idTable.table[lexTable.GetEntry(iter).indexTI].id, "main") == 0)
			{
				main_flag = true;
				break;
			}
	}
	if (!main_flag)
		throw ERROR_THROW_IN(131, -1, -1);
	for (int iter = 0; iter < lexTable.size; iter++)
	{
		if (lexTable.GetEntry(iter).indexTI != -1)
			if (idTable.table[lexTable.GetEntry(iter).indexTI].value.operation == '/')
			{
				if (lexTable.GetEntry(iter).indexTI != -1)
					if (idTable.table[lexTable.GetEntry(iter).indexTI].value.vInt == 0 && (idTable.table[lexTable.GetEntry(iter).indexTI].idDataType == IT::ID_DATA_TYPE::UINT ||
						idTable.table[lexTable.GetEntry(iter).indexTI].idDataType == IT::ID_DATA_TYPE::INT) &&
						(idTable.table[lexTable.GetEntry(iter).indexTI].idDataType == IT::ID_TYPE::L ||
							idTable.table[lexTable.GetEntry(iter).indexTI].idDataType == IT::ID_TYPE::P ||
							idTable.table[lexTable.GetEntry(iter).indexTI].idDataType == IT::ID_TYPE::V ||
							idTable.table[lexTable.GetEntry(iter).indexTI].idDataType == IT::ID_TYPE::VF))
					{
						//throw ERROR_THROW_IN(145, lexTable.GetEntry(iter).sourceNumber, -1);
					}
			}
	}

}

bool tokenAnalize(char* token, const int str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
{
	static varFlagType flag_type_variable;

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
		if (lexTable.table[lexTable.size - 1].lexToken == 't')
		{
			switch (flag_type_variable.type)
			{
			case varFlagType::UINT:
			{
				idTable.Add({ "\0", "\0", IT::ID_DATA_TYPE::DEF, IT::ID_TYPE::D, 'u' });
				lexTable.table[lexTable.size - 1].indexTI = idTable.size - 1;
				break;
			};
			case varFlagType::INT:
			{
				idTable.Add({ "\0", "\0", IT::ID_DATA_TYPE::DEF, IT::ID_TYPE::D, 'i' });
				lexTable.table[lexTable.size - 1].indexTI = idTable.size - 1;
				break;
			};
			}
		}
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
		idTable.Add({ "\0", "\0", IT::ID_DATA_TYPE::DEF, IT::ID_TYPE::D, '+' });
		Add(lexTable, { LEX_PLUS,str_number,idTable.size - 1 });
		return true;
	}

	case '-':
	{
		In::IN in_ex;
		if (lexTable.table[lexTable.size - 1].indexTI != -1)
		{
			if (idTable.table[lexTable.table[lexTable.size - 1].indexTI].idDataType != IT::ID_DATA_TYPE::UINT && idTable.table[lexTable.table[lexTable.size - 1].indexTI].idDataType != IT::ID_DATA_TYPE::BOOL && idTable.table[lexTable.table[lexTable.size - 1].indexTI].idDataType != IT::ID_DATA_TYPE::INT)
			{
				throw ERROR_THROW_IN(143, str_number, -1);
			}
		}
		if (in_ex.code[token[1]] == in_ex.N)
		{
			FST::FST* number_literal = new FST::FST(FST_INTEGER_LITERAL(token));
			if (FST::execute(*number_literal))
			{
				int i = idTable.IsId(token);
				if (i != LT_TI_NULLXDX)
					Add(lexTable, { LEX_LITERAL,str_number,i });
				else
				{
					if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexToken == '=')
					{
						if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).idDataType == IT::INT)
						{
							if (atoi(token) > pow(2, 31) - 1 || atoi(token) < -pow(2, 31))
							{
								//throw  ERROR_THROW_IN(146, lexTable.table[i].sourceNumber, -1);
							}
							idTable.table[lexTable.GetEntry(lexTable.size - 2).indexTI].value.vInt = atoi(token);
							char* name;
							name = idTable.GetLexemaName();
							idTable.Add({ "\0",name, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::L });
							idTable.table[idTable.size - 1].value.vInt = atoi(token);
						}
						else if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).idDataType == IT::UINT)
						{
							throw ERROR_THROW_IN(147, str_number, -1);
						}
					}
					else
					{
						char* name;
						name = idTable.GetLexemaName();
						idTable.Add({ "\0",name, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::L });
						idTable.table[idTable.size - 1].value.vInt = atoi(token);
					}
					Add(lexTable, { LEX_LITERAL,str_number, idTable.size - 1 });
				}
				delete number_literal;
				number_literal = NULL;
				return true;
			}
		}
		idTable.Add({ "\0", "\0", IT::ID_DATA_TYPE::DEF, IT::ID_TYPE::D, '-' });
		Add(lexTable, { LEX_MINUS,str_number,idTable.size - 1 });
		return true;
	}


	case '*':
	{
		if (lexTable.table[lexTable.size - 1].indexTI != -1)
		{
			if (idTable.table[lexTable.table[lexTable.size - 1].indexTI].idDataType != IT::ID_DATA_TYPE::UINT && idTable.table[lexTable.table[lexTable.size - 1].indexTI].idDataType != IT::ID_DATA_TYPE::BOOL && idTable.table[lexTable.table[lexTable.size - 1].indexTI].idDataType != IT::ID_DATA_TYPE::INT)
			{
				throw ERROR_THROW_IN(143, str_number, -1);
			}
		}
		idTable.Add({ "\0", "\0", IT::ID_DATA_TYPE::DEF, IT::ID_TYPE::D, '*' });
		Add(lexTable, { LEX_STAR,str_number,idTable.size - 1 });
		return true;
	}

	case '/':
	{
		if (lexTable.table[lexTable.size - 1].indexTI != -1)
		{
			if (idTable.table[lexTable.table[lexTable.size - 1].indexTI].idDataType != IT::ID_DATA_TYPE::UINT && idTable.table[lexTable.table[lexTable.size - 1].indexTI].idDataType != IT::ID_DATA_TYPE::BOOL && idTable.table[lexTable.table[lexTable.size - 1].indexTI].idDataType != IT::ID_DATA_TYPE::INT)
			{
				throw ERROR_THROW_IN(143, str_number, -1);
			}
		}
		idTable.Add({ "\0", "\0", IT::ID_DATA_TYPE::DEF, IT::ID_TYPE::D, '/' });
		Add(lexTable, { LEX_SLASH,str_number,idTable.size - 1 });
		return true;
	}
	case LEX_NOTEQUALITY_SIGN:
	{
		if (token[1] == '=')
		{
			Add(lexTable, { LEX_NOTEQUALITY_SIGN,str_number,LT_TI_NULLXDX });
			return true;
		}
		return false;
	}
	case LEX_EQUAL_SIGN:
	{
		if (token[1] == '=')
		{
			Add(lexTable, { LEX_EQUALITY_SIGN,str_number,LT_TI_NULLXDX });
			return true;
		}
		Add(lexTable, { LEX_EQUAL_SIGN,str_number,LT_TI_NULLXDX });
		return true;
	}
	case 'f':
	{
		FST::FST* function = new FST::FST(FST_FUNCTION(token));
		FST::FST* _for = new FST::FST(FOR(token));
		FST::FST* _false = new FST::FST(FALSE(token));
		if (FST::execute(*function))
		{
			Add(lexTable, { LEX_FUNCTION,str_number,LT_TI_NULLXDX });

			delete function;
			delete _for;
			delete _false;
			function = NULL;
			_for = NULL;
			_false = NULL;
			return true;
		}
		else if (FST::execute(*_for))
		{
			char* name = idTable.GetViewName();
			idTable.Add({ "\0", name, IT::ID_DATA_TYPE::DEF, IT::ID_TYPE::D });
			Add(lexTable, { LEX_FOR,str_number,idTable.size - 1 });

			delete function;
			delete _for;
			delete _false;
			function = NULL;
			_for = NULL;
			_false = NULL;
			return true;
		}
		else if (FST::execute(*_false))
		{

			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL, str_number, i });
			else
			{
				if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexToken == '=')
				{
					idTable.table[idTable.size - 1].value.vBool = false;
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::ID_DATA_TYPE::BOOL, IT::ID_TYPE::L });
					idTable.table[idTable.size - 1].value.vBool = false;
				}
				else
				{
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name , IT::ID_DATA_TYPE::BOOL, IT::ID_TYPE::L });
					idTable.table[idTable.size - 1].value.vBool = false;
				}
				Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
			}

			delete function;
			delete _for;
			delete _false;
			function = NULL;
			_for = NULL;
			_false = NULL;
			return true;

		}
		else
		{
			delete function;
			delete _for;
			delete _false;
			function = NULL;
			_for = NULL;
			_false = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'i':
	{
		FST::FST* integer = new FST::FST(INTEGER(token));
		if (FST::execute(*integer))
		{
			Add(lexTable, { LEX_INTEGER,str_number,LT_TI_NULLXDX });

			delete integer;
			integer = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			flag_type_variable.type = varFlagType::INT;
			return true;
		}
		else
		{
			delete integer;
			integer = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'u':
	{
		FST::FST* uinteger = new FST::FST(UINTEGER(token));
		if (FST::execute(*uinteger))
		{
			Add(lexTable, { LEX_UINTEGER,str_number,LT_TI_NULLXDX });

			delete uinteger;
			uinteger = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			flag_type_variable.type = varFlagType::UINT;
			return true;
		}
		else
		{
			delete uinteger;
			uinteger = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 't':
	{
		FST::FST* _true = new FST::FST(TRUE(token));
		if (FST::execute(*_true))
		{
			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL, str_number, i });
			else
			{
				if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexToken == '=')
				{
					idTable.table[idTable.size - 1].value.vBool = true;
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::ID_DATA_TYPE::BOOL, IT::ID_TYPE::L });
					idTable.table[idTable.size - 1].value.vBool = true;
				}
				else
				{
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::ID_DATA_TYPE::BOOL, IT::ID_TYPE::L });
					idTable.table[idTable.size - 1].value.vBool = false;
				}
				Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
			}

			delete _true;
			_true = NULL;
			return true;
		}
		else
		{
			delete _true;
			_true = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'b':
	{
		FST::FST* tbool = new FST::FST(BOOL(token));
		if (FST::execute(*tbool))
		{
			Add(lexTable, { LEX_BOOL,str_number,LT_TI_NULLXDX });

			delete tbool;
			tbool = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			flag_type_variable.type = varFlagType::BOOL;
			return true;
		}
		else
		{
			delete tbool;
			tbool = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'c':
	{
		FST::FST* t_char = new FST::FST(CHAR(token));
		if (FST::execute(*t_char))
		{
			Add(lexTable, { LEX_CHAR,str_number,LT_TI_NULLXDX });

			delete t_char;
			t_char = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			flag_type_variable.type = varFlagType::CHAR;
			return true;
		}
		else
		{
			delete t_char;
			t_char = NULL;
			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 's':
	{
		FST::FST* string = new FST::FST(STRING(token));
		if (FST::execute(*string))
		{
			Add(lexTable, { LEX_STRING,str_number,LT_TI_NULLXDX });

			delete string;
			string = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			flag_type_variable.type = varFlagType::STR;
			return true;
		}
		else
		{
			delete string;
			string = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'r':
	{
		FST::FST* _return = new FST::FST(RETURN(token));
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

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case 'o':
	{
		FST::FST* _out = new FST::FST(OUT(token));
		if (FST::execute(*_out))
		{
			Add(lexTable, { LEX_OUT,str_number,LT_TI_NULLXDX });

			delete _out;
			_out = NULL;
			return true;
		}
		else
		{
			delete _out;
			_out = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	case '\"':
	{
		FST::FST* string_literal = new FST::FST(FST_STRING_LITERAL(token));
		if (FST::execute(*string_literal))
		{
			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL, str_number, i });
			else
			{
				if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexToken == '=')
				{
					int j = 0;
					idTable.table[lexTable.GetEntry(lexTable.size - 2).indexTI].value.vStr.len = 0;

					for (; token[j] != '\0';)
					{
						idTable.table[lexTable.GetEntry(lexTable.size - 2).indexTI].value.vStr.str[idTable.table[idTable.size - 1].value.vStr.len] = token[j];
						idTable.table[lexTable.GetEntry(lexTable.size - 2).indexTI].value.vStr.len++;
						j++;
					}
					idTable.table[lexTable.GetEntry(lexTable.size - 2).indexTI].value.vStr.str[idTable.table[lexTable.GetEntry(lexTable.size - 2).indexTI].value.vStr.len++] = '\0';
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0", name, IT::ID_DATA_TYPE::STR, IT::ID_TYPE::L });
					j = 0;
					for (; token[j] != '\0';)
					{
						idTable.table[idTable.size - 1].value.vStr.str[idTable.table[idTable.size - 1].value.vStr.len] = token[j];
						idTable.table[idTable.size - 1].value.vStr.len++;
						j++;
					}
					idTable.table[idTable.size - 1].value.vStr.str[idTable.table[idTable.size - 1].value.vStr.len++] = '\0';
					Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
				}
				else
				{
					int j = 0;
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0", name, IT::ID_DATA_TYPE::STR, IT::ID_TYPE::L });
					i++;
					for (; token[i] != '\0'; i++)
					{
						idTable.table[idTable.size - 1].value.vStr.str[idTable.table[idTable.size - 1].value.vStr.len] = token[i];
						idTable.table[idTable.size - 1].value.vStr.len++;
						j++;
					}
					idTable.table[idTable.size - 1].value.vStr.str[j] = '\0';
					Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
				}
				;
			}

			delete string_literal;
			string_literal = NULL;
			return true;
		}
	}
	case '\'':
	{
		FST::FST* char_literal = new FST::FST(CHAR_LITERAL(token));
		if (FST::execute(*char_literal))
		{
			int i = idTable.IsId(token);
			if (i != LT_TI_NULLXDX)
				Add(lexTable, { LEX_LITERAL, str_number, i });
			else
			{
				if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexToken == '=')
				{
					if (token[1] > 128 || token[1] < -127)
					{
						//throw  ERROR_THROW_IN(148, lexTable.table[i].sourceNumber, -1);
					}
					idTable.table[lexTable.table[lexTable.size - 2].indexTI].value.vChar = token[1];
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::ID_DATA_TYPE::CHAR, IT::ID_TYPE::L });
					idTable.table[idTable.size - 1].value.vChar = token[1];
				}
				else
				{
					if (token[1] > 128 || token[1] < -127)
					{
						//throw  ERROR_THROW_IN(148, lexTable.table[i].sourceNumber, -1);
					}
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::ID_DATA_TYPE::CHAR, IT::ID_TYPE::L });
					idTable.table[idTable.size - 1].value.vChar = token[1];
				}
				Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
			}
			delete char_literal;
			char_literal = NULL;
			return true;
		}
	}
	case 'm':
	{
		FST::FST* _main = new FST::FST(MAIN(token));
		if (FST::execute(*_main))
		{
			for (int iter = 0; iter < idTable.size; iter++)
			{
				if (strcmp(idTable.GetEntry(iter).id, "main") == 0)
				{
					throw ERROR_THROW_IN(129, str_number, idTable.size - 1);
				}
			}
			idTable.Add({ "\0", token, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::F });
			Add(lexTable, { LEX_MAIN,str_number,idTable.size - 1 });
			delete _main;
			_main = NULL;
			flag_type_variable.LT_posititon = lexTable.size - 1;
			return true;
		}
		else
		{
			delete _main;
			_main = NULL;

			return func_var(token, str_number, lexTable, idTable, flag_type_variable);
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

				if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexToken == '=')
				{
					if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).idDataType == IT::INT || idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).idDataType == IT::BOOL)
					{
						if (atoi(token) > pow(2, 31) - 1 || atoi(token) < -pow(2, 31))
						{
							//throw  ERROR_THROW_IN(146, lexTable.table[i].sourceNumber, -1);
						}
						idTable.table[lexTable.GetEntry(lexTable.size - 2).indexTI].value.vInt = atoi(token);
						char* name;
						name = idTable.GetLexemaName();
						idTable.Add({ "\0",name, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::L });
						idTable.table[idTable.size - 1].value.vInt = atoi(token);
					}
					else if (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).indexTI).idDataType == IT::UINT)
					{
						if (atoi(token) > pow(2, 32) - 1 || atoi(token) < 0)
						{
							//throw  ERROR_THROW_IN(147, lexTable.table[i].sourceNumber, -1);
						}
						idTable.table[lexTable.GetEntry(lexTable.size - 2).indexTI].value.vUint = atoi(token);
						char* name;
						name = idTable.GetLexemaName();
						idTable.Add({ "\0",name, IT::ID_DATA_TYPE::UINT, IT::ID_TYPE::L });
						idTable.table[idTable.size - 1].value.vUint = atoi(token);
					}

				}
				else
				{
					if (atoi(token) > pow(2, 31) - 1 || atoi(token) < -pow(2, 31))
					{
						//throw  ERROR_THROW_IN(146, lexTable.table[i].sourceNumber, -1);
					}
					char* name;
					name = idTable.GetLexemaName();
					idTable.Add({ "\0",name, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::L });
					idTable.table[idTable.size - 1].value.vInt = atoi(token);
				}
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

			return  func_var(token, str_number, lexTable, idTable, flag_type_variable);
		}
	}
	}
}

bool func_var(char* token, const int str_number, LT::LexTable& lexTable, IT::IdTable& idTable, varFlagType& flag_type_variable)
{
	FST::FST* id = new FST::FST(FST_IDENTIFICATOR(token));
	if (FST::execute(*id))
	{
		bool Checked_id = false;

		//функция
		if (strcmp(token, "main") == 0 || strcmp(token, "strl") == 0 || strcmp(token, "random") == 0 ||
			((lexTable.GetEntry(lexTable.size - 1).lexToken == LEX_FUNCTION &&
				lexTable.GetEntry(lexTable.size - 2).lexToken == 't') &&
				flag_type_variable.LT_posititon == lexTable.size - 2))
		{
			int check = idTable.IsId(token);
			if (check == -1 || idTable.table[check].idDataType != flag_type_variable.type)
			{
				if (flag_type_variable.type == varFlagType::INT)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::F });
				}
				if (flag_type_variable.type == varFlagType::STR)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::STR, IT::ID_TYPE::F });
				}
				if (flag_type_variable.type == varFlagType::CHAR)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::CHAR, IT::ID_TYPE::F });
				}
				if (flag_type_variable.type == varFlagType::BOOL)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::BOOL, IT::ID_TYPE::F });
				}
				if (flag_type_variable.type == varFlagType::UINT)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::UINT, IT::ID_TYPE::F });
				}
				if (strcmp(token, "strl") == 0)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::F });
					idTable.table[idTable.size - 1].parmQuantity = 1;
				}
				if (strcmp(token, "random") == 0)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::F });
					idTable.table[idTable.size - 1].parmQuantity = 1;
				}
				flag_type_variable.LT_posititon = -1;
				flag_type_variable.type = varFlagType::DEF;

				if (strcmp(token, "strl") == 0)
				{
					Add(lexTable, { LEX_STRLEN, str_number, idTable.size - 1 });
				}
				else if (strcmp(token, "random") == 0)
				{
					Add(lexTable, { LEX_RANDOM, str_number, idTable.size - 1 });
				}
				else
				{
					Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
					idTable.table[idTable.size - 1].first_in = lexTable.size - 1;
				}
				Checked_id = true;
			}
			else if ((strcmp(token, "strl") == 0 || strcmp(token, "random") == 0) && idTable.IsId(token) != -1)
			{
				if (strcmp(token, "strl") == 0)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::F });
					idTable.table[idTable.size - 1].parmQuantity = 1;
					Add(lexTable, { LEX_STRLEN, str_number, idTable.size - 1 });
				}
				if (strcmp(token, "random") == 0)
				{
					idTable.Add({ "\0", token, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::F });
					idTable.table[idTable.size - 1].parmQuantity = 1;
					Add(lexTable, { LEX_RANDOM, str_number, idTable.size - 1 });
				}
				Checked_id = true;
			}
			else
				throw ERROR_THROW_IN(123, str_number, -1);
		}
		//параметр функции 
		if (!Checked_id &&
			(lexTable.GetEntry(lexTable.size - 1).lexToken == 't' && flag_type_variable.LT_posititon == lexTable.size - 1))
		{
			bool LeftBrace = false;
			for (int i = lexTable.size - 1; i > 0; i--)
			{
				LT::Entry entry = lexTable.GetEntry(i);
				if (entry.lexToken == LEX_LEFT_BRACE)
					LeftBrace = true;
				bool type_check = (idTable.GetEntry(entry.indexTI).idType == IT::ID_TYPE::F);
				if (lexTable.GetEntry(i).lexToken == LEX_ID && type_check)
				{
					if (lexTable.GetEntry(i - 1).lexToken == LEX_FUNCTION && lexTable.GetEntry(i - 2).lexToken == 't')
					{
						if (LeftBrace == true) break;
						if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).indexTI).id, i) == -1)
						{
							if (flag_type_variable.type == varFlagType::INT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,lexTable.GetEntry(i).indexTI,token , IT::ID_DATA_TYPE::INT, IT::ID_TYPE::P });
								idTable.table[(lexTable.GetEntry(i).indexTI)].parms[idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity] = IT::ID_DATA_TYPE::INT;
								idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity++;

							}
							if (flag_type_variable.type == varFlagType::STR)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,lexTable.GetEntry(i).indexTI,token  , IT::ID_DATA_TYPE::STR, IT::ID_TYPE::P });
								idTable.table[(lexTable.GetEntry(i).indexTI)].parms[idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity] = IT::ID_DATA_TYPE::STR;
								idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity++;
							}
							if (flag_type_variable.type == varFlagType::UINT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,lexTable.GetEntry(i).indexTI,token , IT::ID_DATA_TYPE::UINT, IT::ID_TYPE::P });
								idTable.table[(lexTable.GetEntry(i).indexTI)].parms[idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity] = IT::ID_DATA_TYPE::UINT;
								idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity++;
							}
							if (flag_type_variable.type == varFlagType::BOOL)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,lexTable.GetEntry(i).indexTI,token  , IT::ID_DATA_TYPE::BOOL, IT::ID_TYPE::P });
								idTable.table[(lexTable.GetEntry(i).indexTI)].parms[idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity] = IT::ID_DATA_TYPE::BOOL;
								idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity++;
							}
							if (flag_type_variable.type == varFlagType::CHAR)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,lexTable.GetEntry(i).indexTI,token  , IT::ID_DATA_TYPE::CHAR, IT::ID_TYPE::P });
								idTable.table[(lexTable.GetEntry(i).indexTI)].parms[idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity] = IT::ID_DATA_TYPE::BOOL;
								idTable.table[(lexTable.GetEntry(i).indexTI)].parmQuantity++;
							}
							flag_type_variable.LT_posititon = -1;
							flag_type_variable.type = varFlagType::DEF;

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

		//переменная(определена ли она уже?)
		if (!Checked_id && (lexTable.GetEntry(lexTable.size - 1).lexToken == 't' && flag_type_variable.LT_posititon == lexTable.size - 1))
		{
			bool LeftBrace = false;
			bool RightBrace = false;
			for (int i = lexTable.size - 1; i >= 0; i--)
			{
				char LEXEMA = lexTable.GetEntry(i).lexToken;
				if (LEXEMA == LEX_LEFT_BRACE)
				{
					LeftBrace = true;
				}
				if (LEXEMA == LEX_RIGHT_BRACE)
				{
					RightBrace = true;
				}
				if (LEXEMA == LEX_FOR && LeftBrace && RightBrace)
				{
					LeftBrace = false;
					RightBrace = false;
					continue;
				}
				if ((LeftBrace && !RightBrace &&
					((LEXEMA == LEX_ID && idTable.GetEntry(lexTable.GetEntry(i).indexTI).idType == IT::ID_TYPE::F && lexTable.table[i - 1].lexToken == 'f')) ||
					((LEXEMA == LEX_ID && strcmp(idTable.GetEntry(lexTable.GetEntry(i).indexTI).id, "main") == 0))) || (LEXEMA == LEX_FOR && (!LeftBrace && !RightBrace))
					)
				{
					if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).indexTI).id, i) == -1)
					{

						if (LEXEMA == LEX_FOR)
						{
							LeftBrace = false;
							for (int l = i; l >= 0; l--)
							{
								char LEXEMA = lexTable.GetEntry(l).lexToken;
								if (LEXEMA == LEX_LEFT_BRACE)
								{
									LeftBrace = true;
								}
								if (LEXEMA == LEX_ID && idTable.GetEntry(lexTable.GetEntry(l).indexTI).idType == IT::ID_TYPE::F && LeftBrace)
								{
									idTable.Add({ idTable.GetForName(idTable.GetEntry(lexTable.GetEntry(l).indexTI).id,flag_type_variable),token, (IT::ID_DATA_TYPE)flag_type_variable.type, IT::ID_TYPE::VF });
									break;
								}
								if (LEXEMA == LEX_FOR)
								{
									idTable.Add({ idTable.GetForName(idTable.GetEntry(lexTable.GetEntry(l).indexTI).id,flag_type_variable),token, (IT::ID_DATA_TYPE)flag_type_variable.type, IT::ID_TYPE::VF });
									break;
								}
							}

						}
						else
						{
							if (flag_type_variable.type == varFlagType::INT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,lexTable.GetEntry(i).indexTI,token, IT::ID_DATA_TYPE::INT, IT::ID_TYPE::V });
							}
							if (flag_type_variable.type == varFlagType::STR)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,lexTable.GetEntry(i).indexTI,token , IT::ID_DATA_TYPE::STR, IT::ID_TYPE::V });
							}
							if (flag_type_variable.type == varFlagType::CHAR)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,lexTable.GetEntry(i).indexTI,token, IT::ID_DATA_TYPE::CHAR, IT::ID_TYPE::V });
							}
							if (flag_type_variable.type == varFlagType::BOOL)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,lexTable.GetEntry(i).indexTI,token , IT::ID_DATA_TYPE::BOOL, IT::ID_TYPE::V });
							}
							if (flag_type_variable.type == varFlagType::UINT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).indexTI).id,lexTable.GetEntry(i).indexTI,token , IT::ID_DATA_TYPE::UINT, IT::ID_TYPE::V });
							}

						}
						flag_type_variable.LT_posititon = -1;
						flag_type_variable.type = varFlagType::DEF;

						Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
						Checked_id = true;
						break;
					}
					else
						throw ERROR_THROW_IN(125, str_number, -1);
				}


			}
		}


		//идентификаторы с учётом области видимости
		if (!Checked_id)
		{
			bool LeftBrace = false;
			bool RightBrace = false;
			bool LeftThesis = false;
			bool RightThesis = false;
			for (int i = lexTable.size - 1; i >= 0; i--)
			{
				char LEXEMA = lexTable.GetEntry(i).lexToken;
				if (LEXEMA == LEX_LEFT_BRACE)
				{
					LeftBrace = true;
				}
				if (LEXEMA == LEX_RIGHT_BRACE)
				{
					RightBrace = true;
				}
				if (LEXEMA == LEX_LEFTHESIS)
				{
					LeftThesis = true;
				}
				if (LEXEMA == LEX_RIGHTHESIS)
				{
					RightThesis = true;
				}
				if (LEXEMA == LEX_FOR && LeftBrace && RightBrace && LeftThesis && RightThesis)
				{
					LeftBrace = false;
					RightBrace = false;
					LeftThesis = false;
					RightThesis = false;
					continue;
				}
				if ((LeftBrace && !RightBrace && ((LEXEMA == LEX_ID && idTable.GetEntry(lexTable.GetEntry(i).indexTI).idType == IT::ID_TYPE::F))) ||
					(LEXEMA == LEX_FOR && (LeftBrace && !RightBrace) || (LEXEMA == LEX_FOR && (LeftThesis && !RightThesis))))
				{
					int temp = 0;
					IT::Entry id_f;
					id_f = idTable.GetEntry(lexTable.GetEntry(i).indexTI);
					if (LEXEMA == LEX_FOR)
					{
						temp = idTable.IsId(token, id_f);
					}
					if (temp == -1)
					{
						int iter = i;
						do
						{
							for (; lexTable.GetEntry(iter).lexToken != LEX_LEFT_BRACE && iter >= 0; iter--)
							{
							}
							for (; iter >= 0; iter--)
							{
								if (lexTable.GetEntry(iter).indexTI != -1 && iter >= 0)
									if (idTable.table[lexTable.GetEntry(iter).indexTI].idType == IT::F)
										break;
								if (iter >= 0)
									if (lexTable.GetEntry(iter).lexToken == LEX_FOR)
										break;
							}
							if (iter >= 0)
								temp = idTable.IsId(token, idTable.table[lexTable.GetEntry(iter).indexTI]);
						} while (temp == -1 && iter >= 0 && iter >= 0);
					}
					if (idTable.GetEntry(lexTable.GetEntry(i).indexTI).idType == IT::ID_TYPE::F)
					{
						temp = idTable.IsId(token, id_f, lexTable.GetEntry(i).indexTI);
					}
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
							token[256] = '\0';
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