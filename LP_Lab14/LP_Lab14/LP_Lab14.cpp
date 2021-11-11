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

		lexTable.PrintLexTable(parm.in);
		idTable.PrintIdTable(parm.in);
		int i = 0;
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