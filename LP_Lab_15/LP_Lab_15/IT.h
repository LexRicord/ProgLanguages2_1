#pragma once
#define ID_MAXSIZE		255					// максимальное количество символов в идентификаторе 
#define TI_MAXSIZE		4096				// максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT  0x00000000			// значение по умолчанию дл€ типа integer
#define TI_STR_DEFAULT  0x00				// значение по умолчанию дл€ типа string
#define TI_NULLIDX		0xffffffff			// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE  255					// максимальна€ длина строки
#define TI_CHAR_MAXSIZE  1					// максимальна€ длина символьного литерала
#define TI_MAX_PARM_Q	10
struct varFlagType
{
	int LT_posititon = -1;
	enum { DEF = 0, INT = 1, STR = 2, UINT = 3, CHAR = 4, BOOL = 5 }type = DEF;
};
#define PARM_ID L".id.txt"
namespace IT								// таблица идентификаторов 
{
	enum ID_DATA_TYPE { DEF = 0, INT = 1, STR = 2, UINT = 3, CHAR = 4, BOOL = 5 };				// типы данных идентификаторов: integer, string
	enum ID_TYPE { D = 0, V = 1, F = 2, P = 3, L = 4, VF = 5 };			// типы идентификаторов: переменна€, функци€, параметр, литерал

	struct Entry							// строка таблицы идентификаторов
	{
		int first_in;
		ID_DATA_TYPE parms[TI_MAX_PARM_Q];
		char parentFunc[ID_MAXSIZE];
		int parentFunc_num;
		char id[ID_MAXSIZE + 1];							// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		ID_DATA_TYPE idDataType;							// тип данных
		ID_TYPE idType;									// тип идентификатора
		union
		{
			int vInt;
			char operation = '\0';
			char vChar;
			bool vBool;
			unsigned int vUint;
			struct
			{
				unsigned char len;							// количество символов в string
				char str[TI_STR_MAXSIZE];					// символы string
			}vStr;						// значение string
		}value;	// значение идентификатора
		int parmQuantity;
		Entry();
		Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType);
		Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, int it);
		Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, char* str);
		Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, const char* str);
		Entry(char* parentFunc, int parentFunc_number, char* id, ID_DATA_TYPE idDataType, ID_TYPE idType);
		Entry(const char* parentFunc, char* id, ID_DATA_TYPE idDataType, ID_TYPE idType);
		Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, char it);
		Entry(const char* parentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, unsigned int it);

	};

	struct IdTable							// экземпл€р таблицы идентификаторов
	{
		int noname_lexToken_count = 0;
		int for_count = 0;
		int maxsize;									// емкость таблицы идентификаторов < TI_MAXSIZE
		int size;										// текущий размер таблицы идентификаторов < maxsize
		Entry* table;									// массив строк таблицы идентификаторов
		Entry GetEntry(							// получить строку таблицы идентификаторов
			int n											// номер получаемой строки
		);

		void Add(								// добавиь строку в таблицу идентификаторов 
			Entry entry										// строка таблицы идентификторов
		);
		int IsId(const char id[ID_MAXSIZE], Entry ide, int parentFunc_number);
		int IsId(const char id[ID_MAXSIZE]);
		int IsId(const char id[ID_MAXSIZE], Entry ide);
		int IsId(const char id[ID_MAXSIZE], const char parentFunc[ID_MAXSIZE + 5], int parentFunc_number);
		void PrintIdTable(const wchar_t* in);
		IdTable();
		char* GetLexemaName();
		char* GetForName(char* id, varFlagType Type);
		char* GetViewName();
	};


	void Delete(IdTable& idTable);			// удалить таблицу лексем (освободить пам€ть)
};