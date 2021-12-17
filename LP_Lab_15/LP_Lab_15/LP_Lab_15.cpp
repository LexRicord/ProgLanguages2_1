#include "stdafx.h"
#include "Log.h"
#include "tokenAnalisys.h"

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "ru");
	Log::LOG log = Log::INITLOG;
	try
	{
		clock_t sint, pn;
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест: ", "без ошибок ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);

		LT::LexTable lexTable;
		IT::IdTable idTable;

		SeparationOfTokens(in, lexTable, idTable);

		lexTable.PrintLexTable(parm.in, L".lex_1.txt");

		std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
		printf("Приведение выражений к записи в польской нотации.\n");

		*log.stream << "------ПОЛЬСКАЯ НОТАЦИЯ------" << std::endl;
		sint = clock();
		int PNnumberGenerated = 0;
		for (int iter = 0, lt_position; iter < lexTable.size; iter++)
		{
			if (lexTable.table[iter - 1].lexToken == LEX_EQUAL_SIGN ||
				lexTable.table[iter - 1].lexToken == LEX_MORE_SIGN ||
				lexTable.table[iter - 1].lexToken == LEX_LESS_SIGN ||
				lexTable.table[iter - 1].lexToken == LEX_NOTEQUALITY_SIGN ||
				lexTable.table[iter - 1].lexToken == LEX_EQUALITY_SIGN ||
				lexTable.table[iter - 1].lexToken == LEX_RETURN ||
				lexTable.table[iter - 1].lexToken == LEX_OUT ||
				(lexTable.table[iter - 3].lexToken == LEX_LEFTHESIS &&
					lexTable.table[iter - 2].lexToken == LEX_INTEGER &&
					lexTable.table[iter - 1].lexToken == LEX_RIGHTHESIS))
			{
				if (PN::PolishNotation(iter, lexTable, idTable))
				{
					PNnumberGenerated++;
				}
			}
		}
		*log.stream << "Выражений обработано успешно: " << PNnumberGenerated << std::endl;

		std::cout << "Выражений обработано успешно: " << PNnumberGenerated << std::endl;
		pn = clock();
		if (parm.printСT)
			printf("Преобразование выражений в польскую нотацию заняло %d миллисекунд\n", (pn - sint));
		std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
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
