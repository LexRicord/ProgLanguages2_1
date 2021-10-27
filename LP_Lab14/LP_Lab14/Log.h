#pragma once

#include "stdafx.h"
#include "In.h"
#include "Parm.h"	
#include "Error.h"	

namespace Log   //работа с файлом протокола 
{
	struct LOG	//польз. тип - Протокол.
	{
		wchar_t logfile[PARM_MAX_SIZE]; //Имя файла
		std::ofstream* stream;			//выходной поток протокола
	};

	static const LOG INITLOG = { L"", NULL };		//структура для начальн. иниц. LOG
	LOG getlog(wchar_t logfile[]);					//сформировать стр. LOG
	void WriteLine(LOG log, const char* c, ...);	//Вывести конкатенацию в файл
	void WriteLine(LOG log, const wchar_t* c, ...);	//Вывести конкатенацию в файл
	void WriteLog(LOG log);							//вывести заголовок 
	void WriteParm(LOG log, Parm::PARM parm);		//вывысти инфо о входных пар-рах
	void WriteIn(LOG log, In::IN in);				//вывести инфо о входном потоке
	void WriteError(LOG log, Error::ERROR error);	//вывести инфо об ошибке
	void Close(LOG log);							//закрыть протокол
};