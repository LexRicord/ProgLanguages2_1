#pragma once

#define ID_MAXSIZE 5 // max char. quant. in Identificator
#define TI_MAXSIZE 4096 // max quantity of str in TI
#define IT_INT_DEFAULT 0x00000000 // def. val. of integer
#define IT_STR_DEFAULT 0x00 // def. val. of string
#define TI_NULLIDX 0xffffffff // 
#define TI_STR_MAXSIZE 255 
#define PARM_ID L".id.txt"

namespace IT 
{
	enum ID_DATA_TYPE { DEF = 0, INT = 1, STR = 2 }; // default, integer, string
	enum ID_TYPE { D = 0, V = 1, F = 2, P = 3, L = 4 }; // variable, function, parameter, literal

	struct Entry								// string of IT
	{
		char parentFunc[ID_MAXSIZE + 5];
		char id[ID_MAXSIZE + 5];					// id(shortened to ID_MAXSIZE)
		ID_DATA_TYPE idDataType;					
		ID_TYPE idType;			
		int firstInput;
		int index;
		union
		{
			int valueInt;										
			struct
			{
				unsigned char len;					// quant of string
				char str[TI_STR_MAXSIZE - 55];			 // char-s of string
			}valueStr[TI_STR_MAXSIZE - 55];			 //  string
		}value;										// value of id
		int parmQuantity;
		Entry();
		Entry(const char* parrentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType);
		Entry(const char* parrentFunc, const char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, int firstInput , int index);
		Entry(char* parrentFunc, char* id, ID_DATA_TYPE idDataType, ID_TYPE idType);
		Entry(char* parrentFunc, char* id, ID_DATA_TYPE idDataType, ID_TYPE idType, int firstInput , int index);
	};

	struct IdentTable 
	{
		int maxSize;					//  < TI_MAXSIZE
		int size;						// current IT size < maxSize
		Entry* table;					// array of IT strings
		Entry GetEntry(					 // get a string of IT
			int n						// number of str
		);

		int IsId(						// returns : number of str or TI_NULLIDX
			const char id[ID_MAXSIZE]		
		);

		int IsId(const char id[ID_MAXSIZE], const char parentFunc[ID_MAXSIZE + 5]);

		void Add(							
			Entry entry						// str of IT
		);

		void PrintIdTable(const wchar_t* in);
		IdentTable();
	};

	void Delete(IdentTable& idtable);		// delete IT to free memory
};