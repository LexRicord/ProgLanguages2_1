#include "stdafx.h"


namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[]) {
		PARM p;
		bool in_check = 0, out_check = 0, log_check = 0;
		for (int iter = 1; iter < argc; iter++) {
				if (wcslen(argv[iter]) > PARM_MAX_SIZE) //Returns the length of the C wide string wcs.(Число расширених эл-тов строки(2 байта)[0; до первого null)
				throw ERROR_THROW(104);
				if (wcsstr(argv[iter], PARM_IN)) //Returns a pointer to the first occurrence of wcs2 in wcs1, or a null pointer if wcs2 is not part of wcs1.
				{
					wcscpy_s(p.in, (argv[iter] + wcslen(PARM_IN))); 
					in_check = 1;
				}
				if (wcsstr(argv[iter], PARM_OUT))
				{
					wcscpy_s(p.out, (argv[iter] + wcslen(PARM_OUT)));
					out_check = 1;
				}
				if (wcsstr(argv[iter], PARM_LOG))
				{
					wcscpy_s(p.log, (argv[iter] + wcslen(PARM_LOG)));
					log_check = 1;
				}
		}
		if (!in_check) throw ERROR_THROW_IN(100,0,0);
		if (!out_check)
		{
			wcscpy_s(p.out, p.in);
			wcscat_s(p.out, PARM_OUT_DEFAULT_EXIT);             //Конкатенация: The wide character replaces the null terminator at the end of p.out
		}
		if (!log_check)
		{
			wcscpy_s(p.log, p.in);
			wcscat_s(p.log, PARM_LOG_DEFAULT_EXIT);
		}
		return p;
	}
}