#pragma once
#define ID_MAXSIZE		255					// ������������ ���������� �������� � �������������� 
#define TI_MAXSIZE		4096				// ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT  0x00000000			// �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT  0x00				// �������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffffffff			// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE  255					// ������������ ����� ������
#define TI_CHAR_MAXSIZE  1					// ������������ ����� ����������� ��������
#define TI_MAX_PARM_Q	10
struct varFlagType
{
	int LT_posititon = -1;
	enum { DEF = 0, INT = 1, STR = 2, UINT = 3, CHAR = 4, BOOL = 5 }type = DEF;
};
#define PARM_ID L".id.txt"
namespace IT								// ������� ��������������� 
{
	enum ID_DATA_TYPE { DEF = 0, INT = 1, STR = 2, UINT = 3, CHAR = 4, BOOL = 5 };				// ���� ������ ���������������: integer, string
	enum ID_TYPE { D = 0, V = 1, F = 2, P = 3, L = 4, VF = 5 };			// ���� ���������������: ����������, �������, ��������, �������

	struct Entry							// ������ ������� ���������������
	{
		int first_in;
		ID_DATA_TYPE parms[TI_MAX_PARM_Q];
		char parentFunc[ID_MAXSIZE];
		int parentFunc_num;
		char id[ID_MAXSIZE + 1];							// ������������� (������������� ��������� �� ID_MAXSIZE)
		ID_DATA_TYPE idDataType;							// ��� ������
		ID_TYPE idType;									// ��� ��������������
		union
		{
			int vInt;
			char operation = '\0';
			char vChar;
			bool vBool;
			unsigned int vUint;
			struct
			{
				unsigned char len;							// ���������� �������� � string
				char str[TI_STR_MAXSIZE];					// ������� string
			}vStr;						// �������� string
		}value;	// �������� ��������������
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

	struct IdTable							// ��������� ������� ���������������
	{
		int noname_lexToken_count = 0;
		int for_count = 0;
		int maxsize;									// ������� ������� ��������������� < TI_MAXSIZE
		int size;										// ������� ������ ������� ��������������� < maxsize
		Entry* table;									// ������ ����� ������� ���������������
		Entry GetEntry(							// �������� ������ ������� ���������������
			int n											// ����� ���������� ������
		);

		void Add(								// ������� ������ � ������� ��������������� 
			Entry entry										// ������ ������� ��������������
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


	void Delete(IdTable& idTable);			// ������� ������� ������ (���������� ������)
};