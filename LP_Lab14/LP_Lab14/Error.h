#pragma once
#include "stdafx.h"


#define ERROR_THROW(id) Error::geterror(id);     //Макрос генерирует ошибку с номером, который будет задан в качестве параметра.
#define ERROR_THROW_IN(id, line, col) Error::geterrorin(id, line, col); //Макрос генерирует ошибку. Параметры: id ошибки, l - номер строки, с - позиция в строке
#define ERROR_ENTRY(id, mes) {id, mes, {-1,-1}}     //{-1,-1} - значения по умолчанию, если значение не задано.
#define ERROR_MAXSIZE_MESSAGE 200
#define ERROR_ENTRY_NODEF(id)		ERROR_ENTRY(-id,"Неопределённая ошибка")   //1 неопр. эл. таблицы ошибок

#define  ERROR_ENTRY_NODEF10(id)	ERROR_ENTRY_NODEF(id+0),ERROR_ENTRY_NODEF(id+1),ERROR_ENTRY_NODEF(id+2),ERROR_ENTRY_NODEF(id+3),\
									ERROR_ENTRY_NODEF(id+4),ERROR_ENTRY_NODEF(id+5),ERROR_ENTRY_NODEF(id+6),ERROR_ENTRY_NODEF(id+7),\
									ERROR_ENTRY_NODEF(id+8),ERROR_ENTRY_NODEF(id+9)

#define  ERROR_ENTRY_NODEF100(id)	ERROR_ENTRY_NODEF10(id+ 0),ERROR_ENTRY_NODEF10(id+10),ERROR_ENTRY_NODEF10(id+20),ERROR_ENTRY_NODEF10(id+30),\
									ERROR_ENTRY_NODEF10(id+40),ERROR_ENTRY_NODEF10(id+50),ERROR_ENTRY_NODEF10(id+60),ERROR_ENTRY_NODEF10(id+70),\
									ERROR_ENTRY_NODEF10(id+80),ERROR_ENTRY_NODEF10(id+90)

#define ERROR_MAX_ENTRY 1000											//кол-во эл-тов таблицы ошибок

namespace Error
{
	struct ERROR											//тип исключения для throw ERROR_THROW/ERROR_THROW_IN/catch(error)
	{
		int id;
		char message[ERROR_MAXSIZE_MESSAGE];      //сообщение об ошибке
		struct IN									//расширение при обработке входящих данных 
		{
			short line;								//Номер строки (0, 1 ...)
			short col;								//Позиция в строке (0, 1 ...)
		} inext;
	};

	ERROR geterror(int id);						//сформировать ERROR для ERROR_THROW(для проверки обработки исключений)
	ERROR geterrorin(int id, int line, int col); //для ERROR_THROW_IN
}