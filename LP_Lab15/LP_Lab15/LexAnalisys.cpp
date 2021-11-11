#include "stdafx.h"

///ка счит. вх. посл. симв.

FST::FST typeInt(MY_STATIC_STRING, 8, \
	FST::NODE(1, FST::RELATION('i', 1)), \
	FST::NODE(1, FST::RELATION('n', 2)), \
	FST::NODE(1, FST::RELATION('t', 3)), \
	FST::NODE(1, FST::RELATION('e', 4)), \
	FST::NODE(1, FST::RELATION('g', 5)), \
	FST::NODE(1, FST::RELATION('e', 6)), \
	FST::NODE(1, FST::RELATION('r', 7)), \
	FST::NODE());
FST::FST FST_typeString(MY_STATIC_STRING, 7, \
	FST::NODE(1, FST::RELATION('s', 1)), \
	FST::NODE(1, FST::RELATION('t', 2)), \
	FST::NODE(1, FST::RELATION('r', 3)), \
	FST::NODE(1, FST::RELATION('i', 4)), \
	FST::NODE(1, FST::RELATION('n', 5)), \
	FST::NODE(1, FST::RELATION('g', 6)), \
	FST::NODE());

FST::FST FST_typeFunc(MY_STATIC_STRING, 9, \
	FST::NODE(1, FST::RELATION('f', 1)), \
	FST::NODE(1, FST::RELATION('u', 2)), \
	FST::NODE(1, FST::RELATION('n', 3)), \
	FST::NODE(1, FST::RELATION('c', 4)), \
	FST::NODE(1, FST::RELATION('t', 5)), \
	FST::NODE(1, FST::RELATION('i', 6)), \
	FST::NODE(1, FST::RELATION('o', 7)), \
	FST::NODE(1, FST::RELATION('n', 8)), \
	FST::NODE());

FST::FST FST_strDeclare(MY_STATIC_STRING, 8, \
	FST::NODE(1, FST::RELATION('d', 1)), \
	FST::NODE(1, FST::RELATION('e', 2)), \
	FST::NODE(1, FST::RELATION('c', 3)), \
	FST::NODE(1, FST::RELATION('l', 4)), \
	FST::NODE(1, FST::RELATION('a', 5)), \
	FST::NODE(1, FST::RELATION('r', 6)), \
	FST::NODE(1, FST::RELATION('e', 7)), \
	FST::NODE());

FST::FST FST_strReturn(MY_STATIC_STRING, 7, \
	FST::NODE(1, FST::RELATION('r', 1)), \
	FST::NODE(1, FST::RELATION('e', 2)), \
	FST::NODE(1, FST::RELATION('t', 3)), \
	FST::NODE(1, FST::RELATION('u', 4)), \
	FST::NODE(1, FST::RELATION('r', 5)), \
	FST::NODE(1, FST::RELATION('n', 6)), \
	FST::NODE());
FST::FST FST_strMain(MY_STATIC_STRING, 5, \
	FST::NODE(1, FST::RELATION('m', 1)), \
	FST::NODE(1, FST::RELATION('a', 2)), \
	FST::NODE(1, FST::RELATION('i', 3)), \
	FST::NODE(1, FST::RELATION('n', 4)), \
	FST::NODE());

FST::FST FST_strPrint(MY_STATIC_STRING, 6, \
	FST::NODE(1, FST::RELATION('p', 1)), \
	FST::NODE(1, FST::RELATION('r', 2)), \
	FST::NODE(1, FST::RELATION('i', 3)), \
	FST::NODE(1, FST::RELATION('n', 4)), \
	FST::NODE(1, FST::RELATION('t', 5)), \
	FST::NODE());

FST::FST FST_expression(MY_STATIC_STRING, 2, \
	FST::NODE(4, FST::RELATION('+', 1), FST::RELATION('-', 1), FST::RELATION('*', 1), FST::RELATION('/', 1)), \
	FST::NODE());

FST::FST FST_space(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION(' ', 1)), \
	FST::NODE());

FST::FST FST_blockOpening(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION('{', 1)), \
	FST::NODE());

FST::FST FST_blockEnding(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION('}', 1)), \
	FST::NODE());

FST::FST FST_leftParenthesis(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION('(', 1)), \
	FST::NODE());

FST::FST FST_rightParenthesis(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION(')', 1)), \
	FST::NODE());

FST::FST FST_semicolon(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION(';', 1)), \
	FST::NODE());

FST::FST FST_comma(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION(',', 1)), \
	FST::NODE());

FST::FST FST_plus(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION('+', 1)), \
	FST::NODE());

FST::FST FST_minus(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION('-', 1)), \
	FST::NODE());

FST::FST FST_slash(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION('/', 1)), \
	FST::NODE());

FST::FST FST_asterisk(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION('*', 1)), \
	FST::NODE());

FST::FST FST_equalSigh(MY_STATIC_STRING, 2, \
	FST::NODE(1, FST::RELATION('=', 1)), \
	FST::NODE());

FST::FST FST_intLiteral(MY_STATIC_STRING, 2, \
	FST::NODE(20, \
		FST::RELATION('0', 0), FST::RELATION('1', 0), FST::RELATION('2', 0), \
		FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0), \
		FST::RELATION('6', 0), FST::RELATION('7', 0), FST::RELATION('8', 0), \
		FST::RELATION('9', 0), FST::RELATION('0', 1), FST::RELATION('1', 1), \
		FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), \
		FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), \
		FST::RELATION('8', 1), FST::RELATION('9', 1)), \
	FST::NODE());

FST::FST FST_fstIdentificator(MY_STATIC_STRING, 2, \
	FST::NODE(54, \
		FST::RELATION('a', 1), FST::RELATION('a', 0), FST::RELATION('b', 1), FST::RELATION('b', 0), \
		FST::RELATION('c', 1), FST::RELATION('c', 0), FST::RELATION('d', 1), FST::RELATION('d', 0), FST::RELATION('e', 1), FST::RELATION('e', 0), \
		FST::RELATION('f', 1), FST::RELATION('f', 0), FST::RELATION('g', 1), FST::RELATION('g', 0), FST::RELATION('h', 0), FST::RELATION('h', 1), FST::RELATION('i', 0), FST::RELATION('i', 1), \
		FST::RELATION('j', 0), FST::RELATION('j', 1), FST::RELATION('k', 0), FST::RELATION('k', 1), FST::RELATION('l', 0), FST::RELATION('l', 1), \
		FST::RELATION('m', 0), FST::RELATION('m', 1), FST::RELATION('n', 0), FST::RELATION('n', 1), FST::RELATION('o', 0), FST::RELATION('o', 1), \
		FST::RELATION('p', 0), FST::RELATION('p', 1), FST::RELATION('q', 0), FST::RELATION('q', 1), FST::RELATION('r', 0), FST::RELATION('r', 1), \
		FST::RELATION('s', 0), FST::RELATION('s', 1), FST::RELATION('t', 0), FST::RELATION('t', 1), FST::RELATION('u', 0), FST::RELATION('u', 1), \
		FST::RELATION('v', 0), FST::RELATION('v', 1), FST::RELATION('w', 0), FST::RELATION('w', 1), FST::RELATION('x', 0), FST::RELATION('x', 1), \
		FST::RELATION('y', 0), FST::RELATION('y', 1), FST::RELATION('z', 0), FST::RELATION('z', 1)), \
	FST::NODE());
LT::LexTable lextab = LT::Create(LT_MAXSIZE - 1);
IT::IdTable idtab = IT::Create(TI_MAXSIZE - 1);
std::fstream file;
namespace LexAnalisys
{
	bool checkUp(char* m, FST::FST fst)
	{
		fst.string = m;
		return FST::execute(fst);
	}
	

	void paste(int line, char m)
	{
		LT::Entry entry;
		entry.sn = line;
		if (m != 'i')
		{
			entry.idxTI = LT_TI_NULLIDX;
		}
		else
		{
			entry.idxTI = idtab.size;
		}
		memset(entry.lex_token, '\0', strlen(entry.lex_token) - 1);
		entry.lex_token[0] = m;
		LT::Add(lextab, entry);
	}

	void Lexis(Parm::PARM parm, In::IN in)
	{
		
		char word[255] = "";
		char word2[255] = "";
		bool flagfun2 = false;
		int m = 0;
		int line = 1;
		bool nai = false;		///флаг ключ слов, идент распозн
		bool povt_id = false;
		char ch;
		bool flag_s = false;
		bool flag_i = false;
		bool pflag = false;		///флаг параметра
		bool id = false;
		char lit = '0';
		bool flag_lit = false;
		int n = 0;
		IT::Entry entr;
		bool funflag = false;
		short odin = 0;			/// '
		char fun[10] = "global";
		char fun2[10] = "global";
		bool povt_lit = false;

		for (int i = 0; i < in.size; i++)
		{
			ch = in.text[i];
			nai = false;				///флаг ключ. слов
			if (ch == IN_CODE_ENDL)
			{
				line++;
				paste(line, '|');
				continue;
			}
			if (ch == '\'')
			{
				odin++;
				if (odin == 2)
					odin = 0;
			}
			if (odin == 1)
			{
				word[m] = ch;
				m++;
				continue;
			}


			if (ch != ' ' && ch != ';' && ch != '-' && ch != '+' && ch != '/' && ch != '*' && ch != '\''
				&& ch != ',' && ch != ')' && ch != '(' && ch != '}' && ch != '{' && ch != IN_CODE_ENDL && ch != '=')
			{
				word[m] = ch;
				m++;
				continue;
			}

			///проверка на ключевые слова
			else
			{
				word[m] = '\0';
				m = 0;

				if (ch == IN_CODE_ENDL)
				{
					line++;
					continue;
				}
				nai = checkUp(word, FST_typeString);	///проверка на string
				if (nai)
				{
					paste(line, LEX_STRING);
					flag_s = true;
				}
				if (!nai)
				{
					nai = checkUp(word, typeInt);	///проверка на int
					if (nai)
					{
						flag_i = true;
						paste(line, LEX_INTEGER);
					}
				}
				if (!nai)
				{
					nai = checkUp(word, FST_typeFunc);	///проверка на function
					if (nai)
						paste(line, LEX_FUNCTION);
				}
				if (!nai)
				{
					nai = checkUp(word, FST_strDeclare);	///проверка на declare
					if (nai)
						paste(line, LEX_DECLARE);
				}
				if (!nai)
				{
					nai = checkUp(word, FST_strReturn);	///проверка на return
					if (nai)
						paste(line, LEX_RETURN);
				}
				if (!nai)
				{
					nai = checkUp(word, FST_strMain);	///проверка на main
					if (nai)
					{
						paste(line, LEX_MAINFUNC);
						strcpy_s(fun, "main");

					}

				}
				if (!nai)
				{
					nai = checkUp(word, FST_strPrint);	///проверка на print
					if (nai)
						paste(line, LEX_PRINT);
				}

				///Строковый литерал
				if (word[0] == '\'')
				{
					paste(line, LEX_FST_intLiteral);/// l
					for (int i = 0; i < strlen(word); i++)
						word2[i] = word[i + 1];	///без кавычек
					word2[strlen(word)] = '\0';
					nai = true;					///распознан литерал - др. проверок не будет
					flag_lit = true;
					flag_s = true;
				}

				///Целочисленный литерал
				if (!nai)
				{
					nai = checkUp(word, FST_intLiteral);
					if (nai)
					{
						paste(line, LEX_FST_intLiteral);/// l
						flag_lit = true;
						flag_i = true;
					}

				}
				if (flag_lit && nai)
				{
					///Заполняем ТИ литералом
					entr.idxfirstLE = line;		///индекс первой строки в ТЛ
					entr.idtype = IT::L;
					strcpy_s(entr.fun, "");
					if (idtab.size > 0)
					{
						///ТИ не пуста - повтор?
						for (int u = 0; u < idtab.size && nai; u++)
						{
							if (idtab.table[u].idtype == 4)	///если это литерал
							{
								if (flag_i == true)
								{
									if (atoi(word) == idtab.table[u].value.vint)
									{
										lextab.table[lextab.size - 1].idxTI = u;
										nai = false;///цикл заканч.
										povt_lit = true;
										flag_lit = false;
										flag_i = false;
									}
								}
								if (flag_s == true)
								{
									if (strcmp(word2, idtab.table[u].value.vstr.str) == 0)
									{
										lextab.table[lextab.size].idxTI = u;
										nai = false;
										povt_lit = true;
										flag_lit = false;
										flag_s = false;
									}
								}
							}
						}
					}
					///нет повт - заполн новый литерал
					if (!povt_lit)
					{
						entr.id[0] = 'L';
						entr.id[1] = lit + 1;
						lit++;
						entr.id[2] = '\0';
						flag_lit = false;	///флаг: литерал распознан

						if (flag_s)
						{
							entr.iddatatype = IT::STR;				///выставляем тип данных
							strcpy_s(entr.value.vstr.str, word2);		///копируем значение строки
							entr.value.vstr.len = strlen(word2);	///длину
							flag_s = false;							///флаг: литерал распознан
						}
						if (flag_i)
						{
							entr.iddatatype = IT::INT;
							entr.value.vint = atoi(word);
							flag_i = false;
						}
						lextab.table[lextab.size - 1].idxTI = idtab.size;
						IT::Add(idtab, entr);
					}
					else
						povt_lit = false;
				}

				///Ничего не содержит, игнорируется
				if ((ch == ' ' && word[0] == '\0'))
				{
					memset(word, '\0', strlen(word));
					continue;
				}

				///если слово пусто, нет проверки на ид.
				if (word[0] == '\0')
					nai = true;

				///слово не ключевое, это строк. ид?
				if (!nai)
				{
					nai = checkUp(word, FST_fstIdentificator);	///abc
					if (nai)
						id = true;
				}
				///слово является идентификатором
				if (nai && id)
				{
					nai = false;
					id = false;
					paste(line, LEX_ID);/// i
					lextab.table[lextab.size].idxTI = idtab.size;

					if (lextab.table[lextab.size - 2].lex_token[0] != 'f')///проверяем на функцию
					{
						if (strlen(word) < ID_MAXSIZE)
							strcpy_s(entr.id, word);
						else
						{
							for (int i = 0; i < 4; i++)
							{
								entr.id[i] = word[i];
							}
						}
						entr.idxfirstLE = line;	///строка, на кот нах идент
						strcpy_s(entr.fun, fun);	///копируем область видимости
					}
					else///если функция
					{
						if (strcmp(word, "substr") == 0 || strcmp(word, "strlen") == 0)///если станд библ
						{
							strcpy_s(entr.fun, "External");
						}
						else
						{
							strcpy_s(entr.fun, fun);
						}
						strcpy_s(entr.functionname, word);
						strcpy_s(entr.id, "null");
						entr.idxfirstLE = line;
					}

					///проверка на повторение
					if (idtab.size > 0)
						for (int u = 0; u < idtab.size && !nai; u++)
						{
							if (strcmp(fun, idtab.table[u].fun) == 0 ||
								strcmp(idtab.table[u].fun, "global") == 0 ||
								strcmp(idtab.table[u].fun, "External") == 0)
							{
								if (strcmp(idtab.table[u].id, "null") == 0 &&
									strcmp(idtab.table[u].functionname, word) == 0)
								{
									lextab.table[lextab.size - 1].idxTI = u;

									if (idtab.table[u].iddatatype == IT::INT)
									{
										flag_i = false;
									}
									if (idtab.table[u].iddatatype == IT::STR)
									{
										flag_s = false;
									}
									nai = false;///повторов нету
									povt_id = true;
								}
								if (strcmp(entr.id, idtab.table[u].id) == 0 &&	///если такой ид уже есть в ТИ
									strcmp(idtab.table[u].id, "null") != 0)
								{
									lextab.table[lextab.size - 1].idxTI = u;
									if (idtab.table[u].iddatatype == IT::INT)
									{
										flag_i = false;
									}
									if (idtab.table[u].iddatatype == IT::STR)
									{
										flag_s = false;
									}
									nai = false;///повторов нету
									povt_id = true;
								}
							}
						}
					///тип идентификатора: V = 1, F = 2, P = 3, L = 4
					if (!povt_id)
					{
						entr.idtype = IT::V;///тип variable
						if (lextab.table[lextab.size - 2].lex_token[0] == 'f')
						{
							entr.idtype = IT::F;///тип func
						}
						if ((lextab.table[lextab.size - 3].lex_token[0] == '(' && lextab.table[lextab.size - 4].lex_token[0] != 'v') || pflag)
						{
							entr.idtype = IT::P;///,если скобка, и не вэраибл то параметр
							pflag = true;
						}

						if (!nai)
						{
							if (flag_s)
							{
								entr.iddatatype = IT::STR;			///если строка,то тип данных строка
								strcpy_s(entr.value.vstr.str, "");	///копируем пустую строку
								entr.value.vstr.len = 0;			///длину строки на ноль
								flag_s = false;						///флаг убираем
							}

							if (flag_i)
							{
								entr.iddatatype = IT::INT;
								entr.value.vint = 0;
								flag_i = false;
							}
						}
						IT::Add(idtab, entr);///в таблицу
					}
					else
						povt_id = false;
					nai = false;
				}
			}

			///Операции с целыми числами
			if (ch == '+' || ch == '*' || ch == '-' || ch == '/' || ch == '=')
			{
				char word2[5];
				nai = false;
				word2[0] = ch;
				word2[1] = '\0';

				nai = checkUp(word2, FST_asterisk);///проверка на *
				if (nai)
					paste(line, LEX_STAR);
				if (!nai)
				{
					nai = checkUp(word2, FST_equalSigh);///проверка на =
					if (nai)
						paste(line, LEX_RAV);
				}
				if (!nai)
				{
					nai = checkUp(word2, FST_minus);///проверка на -
					if (nai)
						paste(line, LEX_FST_minus);
				}
				if (!nai)
				{
					nai = checkUp(word2, FST_plus);///проверка на +
					if (nai)
						paste(line, LEX_FST_plus);
				}
				if (!nai)
				{
					nai = checkUp(word2, FST_slash);///проверка на /
					if (nai)
						paste(line, LEX_DIRSLASH);
				}


			}

			///Символы-сепараторы
			if (ch == LEX_FST_semicolon || ch == LEX_LEFTHESIS ||
				ch == LEX_RIGHTHESIS || ch == LEX_FST_blockOpening ||
				ch == LEX_BRACELET || ch == LEX_FST_comma)
			{
				nai = false;
				memset(word, '\0', strlen(word));
				word[0] = in.text[i];
				word[1] = '\0';
				nai = checkUp(word, FST_semicolon);///проверка на ;
				if (nai)
					paste(line, LEX_FST_semicolon);
				if (!nai)
				{
					nai = checkUp(word, FST_blockOpening);///проверка на {
					if (nai)
					{
						n = 1;
						paste(line, LEX_FST_blockOpening);
						///поиск последней ф-и перед '}' и этой обл видимости
						while (n < idtab.size + 1 && strcmp(fun, "main") != 0)
						{
							if (idtab.table[idtab.size - n].idtype == 2)
							{
								funflag = true;
								break;
							}
							n++;
						}
						if (funflag)
						{
							strcpy_s(fun2, fun);
							strcpy_s(fun, idtab.table[idtab.size - n].functionname);
							funflag = false;
						}
					}
				}
				if (!nai)
				{
					nai = checkUp(word, FST_blockEnding);///проверка на }
					if (nai)
					{
						paste(line, LEX_BRACELET);
						strcpy_s(fun, fun2);
					}
				}
				if (!nai)
				{
					nai = checkUp(word, FST_comma);///проверка на ,
					if (nai)
						paste(line, LEX_FST_comma);
				}
				if (!nai)
				{
					nai = checkUp(word, FST_leftParenthesis);///проверка на (
					if (nai)
					{
						paste(line, LEX_LEFTHESIS);
						if (idtab.table[idtab.size - 1].idtype == 2 && strcmp(fun, "global") == 0)
						{
							strcpy_s(fun2, fun);
							strcpy_s(fun, idtab.table[idtab.size - 1].functionname);///копируем обл видимости(имя функции в области)
							flagfun2 = true;
						}
					}
				}
				if (!nai)
				{
					nai = checkUp(word, FST_rightParenthesis);///проверка на )
					if (nai)
					{
						paste(line, LEX_RIGHTHESIS);
						pflag = false;
						if (flagfun2)
						{
							strcpy_s(fun, fun2);
							flagfun2 = false;
						}

					}
				}
			}
			memset(word, '\0', strlen(word));
		}

		std::fstream file;
		file.open(parm.log);
		if (file.fail())
		{
			throw ERROR_THROW(112);	///Ошибка при создании файла протокола
		}
		file << lextab.table[0].sn << ' ';


		for (int i = 0; i < lextab.size; i++)
		{
			if (lextab.table[i].lex_token[0] == '|')
			{
				file << '\n';
				if (i != (lextab.size - 1))
				{
					file << lextab.table[i].sn << ' ';
				}
				continue;
			}
			file << lextab.table[i].lex_token;

		}
		file << std::setw(15) << "|Name" << std::setw(2) << '|';
		file << std::setw(10) << "|Type" << std::setw(2) << '|';
		file << std::setw(15) << "|ID type" << std::setw(2) << '|';
		file << std::setw(15) << "|Line" << std::setw(2) << '|';
		file << std::setw(15) << "|Value" << std::setw(2) << '|';
		file << std::setw(12) << "|Length" << std::setw(2) << '|';
		file << std::setw(12) << "|Area" << std::setw(2) << '|' << '\n';
		for (int i = 0; i < idtab.size; i++)
		{
			if (strcmp(idtab.table[i].id, "null"))
				file << std::setw(15) << idtab.table[i].id << std::setw(2);
			else {
				file << std::setw(15) << idtab.table[i].functionname << std::setw(2);
			}
			if (idtab.table[i].iddatatype == IT::INT)
			{

				file << std::setw(15) << "integer" << std::setw(2);
			}
			if (idtab.table[i].iddatatype == IT::STR)
			{
				file << std::setw(15) << "string" << std::setw(2);
			}
			if (idtab.table[i].idtype == IT::F)
			{
				file << std::setw(15) << "function" << std::setw(2);
			}
			if (idtab.table[i].idtype == IT::P)
			{
				file << std::setw(15) << "parametr" << std::setw(2);
			}
			if (idtab.table[i].idtype == IT::L)
			{
				file << std::setw(15) << "FST_intLiteral" << std::setw(2);
			}
			if (idtab.table[i].idtype == IT::V)
			{
				file << std::setw(15) << "variable" << std::setw(2);
			}
			file << std::setw(15) << idtab.table[i].idxfirstLE << std::setw(2);

			if (idtab.table[i].iddatatype == IT::INT)
			{
				file << std::setw(15) << idtab.table[i].value.vint << std::setw(2) << std::setw(15) << " " << std::setw(2);
			}
			else
			{
				file << std::setw(15) << idtab.table[i].value.vstr.str << std::setw(2);
				file << std::setw(15) << idtab.table[i].value.vstr.len << std::setw(2);

			}
			if (strcmp(idtab.table[i].id, "strl") == 0)
				strcpy_s(idtab.table[i].fun, "External");
			file << std::setw(15) << idtab.table[i].fun << std::setw(2) << '\n';
		}
		file.close();
	}
};