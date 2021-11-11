#include "stdafx.h"
#include "Error.h"

namespace Error
{
	// ошибки:  0 - 99 - системные ошибки
	//			100 - 109 - ошибки параметров
	//			110 - 119 - ошибки открытия и чтения файлов 
	ERROR errorTable[ERROR_MAX_ENTRY] =			//таблица ошибок
	{
		ERROR_ENTRY(0,"Недопустимый код ошибки"),			//код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1,"Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Ошибка при создании файла выхода (-out)"),
		ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "Таблица лексем переполнена"),
		ERROR_ENTRY(121, "Слишком большое имя переменной или недопустимое имя переменной"),
		ERROR_ENTRY(122, "Таблица идентификаторов переполнена."),
		ERROR_ENTRY(123, "Нераспознанная лексема"),
		ERROR_ENTRY(124, "Нарушен формат строкового литерала"),
		ERROR_ENTRY(125, "Перезапись идентификатора"),
		ERROR_ENTRY(126, "Неизвестная переменная"),
		ERROR_ENTRY(127, "Превышена длина строкового литерала"),
		ERROR_ENTRY(128, "Не удалось создать файл с лексемами или идентификаторами"),
		ERROR_ENTRY(129, "Повторное объявление main"),
		ERROR_ENTRY(130, "Отсутствие ключевого слова declare при объявлении переменной"),
		ERROR_ENTRY_NODEF(140),ERROR_ENTRY_NODEF(150),ERROR_ENTRY_NODEF(160),ERROR_ENTRY_NODEF(170),
		ERROR_ENTRY_NODEF(180),ERROR_ENTRY_NODEF(190),ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(200),ERROR_ENTRY_NODEF(300),
		ERROR_ENTRY_NODEF(400),ERROR_ENTRY_NODEF(500),ERROR_ENTRY_NODEF(600),ERROR_ENTRY_NODEF(700),
		ERROR_ENTRY_NODEF(800),ERROR_ENTRY_NODEF(900),
	};
	ERROR geterror(int id)
	{
		ERROR er;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			er = errorTable[0];						//Недопустимый код ошибки в случае привышения диап. [0..1000]
		else
			er = errorTable[id];
		return er;
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR er;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			er = errorTable[0];									//Вне диапазона, номер строки и позиция отсутствуют
		else
		{
			er = errorTable[id];
			er.inext.line = line;
			er.inext.col = col;
		}
		return er;
	}
};