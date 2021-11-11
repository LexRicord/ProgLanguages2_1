#pragma once

#include "stdafx.h"


#define PARM_IN		L"-in:"				//ключ для файла с исходным кодом
#define	PARM_OUT	L"-out:"			//ключ для выходящего файла (объектного модуля)
#define	PARM_LOG	L"-log:"			//ключ для файла протоколов работы транслятора
#define	PARM_MAX_SIZE	300				//максимальная длина строки параметра
#define	PARM_OUT_DEFAULT_EXIT	L".out"		//расширение выходного файла (объектного кода) по умолчанию
#define	PARM_LOG_DEFAULT_EXIT	L".log"		//расширение файла протокола по умолчанию

namespace Parm			//пространство имен, в котором происходит обработка входных параметров Parm::
{
	struct PARM			//пользовательский тип, принимающих входные параметры
	{
		wchar_t in[PARM_MAX_SIZE];		//-in: исх. файл
		wchar_t out[PARM_MAX_SIZE];		//-out: об. файл
		wchar_t log[PARM_MAX_SIZE];		//-log: файл прот.
	};
	PARM getparm(int argc, wchar_t* argv[]);	//getparm(пар-ры ф-ции main) Формирует struct PARM на основе main.
}
