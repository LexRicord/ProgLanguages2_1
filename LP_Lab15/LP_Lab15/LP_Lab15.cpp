#include "stdafx.h"
#include "Log.h"
#include "tokenAnalisys.h"

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "ru");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест: ", "без ошибок ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);

		LT::LexTable lexTable;
		IT::IdentTable idTable;

		SeparationOfTokens(in, lexTable, idTable);
		lexTable.PrintLexTable(parm.in, L".lex_1.txt");

		for (int iter = 0, lt_position; iter < lexTable.size; iter++)
		{
			if ((lexTable.table[iter - 1].lexToken == LEX_EQUAL_SIGN && lexTable.table[iter].lexToken == LEX_ID && lexTable.table[iter + 1].lexToken == 'v') ||
				((lexTable.table[iter - 1].lexToken == LEX_EQUAL_SIGN && lexTable.table[iter].lexToken == LEX_ID && lexTable.table[iter + (idTable.GetEntry(lexTable.table[iter].indexTI).parmQuantity) * 2 + 2].lexToken == 'v')) ||
				lexTable.table[iter].lexToken == LEX_LEFTHESIS)
			{
				if (PLN::PolishNotation(iter, lexTable, idTable))
				{
					std::cout << iter << ": Польская запись построена; Строка: " << lexTable.table[iter].sourceNumber << std::endl;
					int str = lexTable.table[iter].sourceNumber;
					std::cout << "Результат построения: ";
					for (iter; str == lexTable.table[iter].sourceNumber; iter++)
					{
						std::cout << " ";
						In::IN in_ex;
						if (in_ex.code[lexTable.table[iter].lexToken] != in_ex.D)
						{
							if (lexTable.table[iter].operation != '\0')
								std::cout << lexTable.table[iter].operation;
							else if (strcmp(idTable.GetEntry(lexTable.table[iter].indexTI).id, "\0") != 0 && idTable.GetEntry(lexTable.table[iter].indexTI).value.valueInt != 0)
								std::cout << idTable.GetEntry(lexTable.table[iter].indexTI).value.valueInt;
							else
								std::cout << idTable.GetEntry(lexTable.table[iter].indexTI).id;
						}
					}
					std::cout << std::endl;
				}
				else
					std::cout << iter << ": Польская запись не построена; Строка: " << lexTable.table[iter].sourceNumber << std::endl;
			}
		}


		lexTable.PrintLexTable(parm.in);
		idTable.PrintIdTable(parm.in);

		Delete(lexTable);
		Delete(idTable);

		Log::Close(log);

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;

}