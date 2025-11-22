#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"
// функція отримує лексеми з вхідного файлу F і записує їх у таблицю лексем TokenTable
// результат функції - кількість лексем
unsigned int GetTokens(FILE* F, Token TokenTable[])
{
	States state = Start;
	Token TempToken;
	// кількість лексем
	unsigned int NumberOfTokens = 0;
	char ch, buf[16];
	int line = 1;
	// читання першого символу з файлу
	ch = getc(F);
	// пошук лексем
	while (1)
	{
		switch (state)
		{
			// стан Start - початок виділення чергової лексеми
			// якщо поточний символ маленька літера, то переходимо до стану Letter
			// якщо поточний символ цифра, то переходимо до стану Digit
			// якщо поточний символ пробіл, символ табуляції або переходу на новий рядок, то переходимо до стану Separators

				// якщо поточний символ / то є ймовірність, що це коментар, переходимо до стану
				//SComment
				// якщо поточний символ EOF (ознака кінця файлу), то переходимо до стану
				//EndOfFile
				// якщо поточний символ відмінний від попередніх, то переходимо до стану Another
		case Start:
			{
				if (ch == EOF)
					state = EndOfFile;
				else
					if (ch <= 'z' && ch >= 'a')
						state = Letter;
					else
						if (ch <= '9' && ch >= '0')
							state = Digit;
						else
							if (ch == ' ' || ch == '\t' || ch == '\n')
								state = Separators;
							else
								if (ch == '/')
									state = SComment;
								else
									state = Another;
				break;
			}
			// стан Finish - кінець виділення чергової лексеми і запис лексеми у таблицю лексем
		case Finish:
		{
			if (NumberOfTokens < MAX_TOKENS)
			{
				TokenTable[NumberOfTokens++] = TempToken;
				if (ch != EOF)
					state = Start;
				else
					state = EndOfFile;
			}
			else
			{
				printf("\n\t\t\ttoo many tokens !!!\n");
				return NumberOfTokens - 1;
			}
			break;
		}
		// стан EndOfFile - кінець файлу, можна завершувати пошук лексем
		case EndOfFile:
		{
			return NumberOfTokens;
		}
		// стан Letter - поточний символ - маленька літера, поточна лексема - ключове слово або ідентифікатор
		case Letter:
		{
			buf[0] = ch;
			int j = 1;
			ch = getc(F);
			while (((ch <= 'z' && ch >= 'a') || (ch <= '9' && ch >= '0')) && j < 15)
			{
				buf[j++] = ch;
				ch = getc(F);
			}
			buf[j] = '\0';
			TypeOfTokens temp_type = Unknown;
			if (!strcmp(buf, "Body"))
				temp_type = StartProgram;
			else
				if (!strcmp(buf, "Variables"))
					temp_type = Variable;
				else
					if (!strcmp(buf, "Integer_16t"))
						temp_type = Type;
					else
						if (!strcmp(buf, "Stop"))
							temp_type = EndProgram;
						else
							if (!strcmp(buf, "Get"))
								temp_type = Input;
							else
								if (!strcmp(buf, "Put"))
									temp_type = Output;
								else
									if (!strcmp(buf, "if"))
										temp_type = If;
									else
										if (!strcmp(buf, "For"))
											temp_type = ForKW;
										else
											if (!strcmp(buf, "To"))
												temp_type = ToKW;
											else
												if (!strcmp(buf, "Next"))
													temp_type = NextKW;
													else
														if (!strcmp(buf, "Then Goto"))
															temp_type = Then;
																else
																	if (!strcmp(buf,
																		"Goto"))
																		temp_type =
																			Else;
																				else
																					if
																						(strlen(buf) < 5)
																						temp_type = Identifier;
			strcpy_s(TempToken.name, buf);	
			TempToken.type = temp_type;
			TempToken.value = 0;
			TempToken.line = line;
			state = Finish;
			break;
		}
		// стан Digit - поточний символ - цифра, поточна лексема - число
		case Digit:
		{
			buf[0] = ch;
			int j = 1;
			ch = getc(F);
			while ((ch <= '9' && ch >= '0') && j < 15)
			{
				buf[j++] = ch;
				ch = getc(F);
			}
			buf[j] = '\0';
			strcpy_s(TempToken.name, buf);
			TempToken.type = Number;
			TempToken.value = atoi(buf);
			TempToken.line = line;
			state = Finish;
			break;
		}
		// стан Separators - поточний символ пробіл, символ табуляції або переходу на новий
		//рядок - видаляємо їх
		case Separators:
		{
			if (ch == '\n')
				line++;
			ch = getc(F);
			state = Start;
			break;
		}
		// стан SComment - поточний символ , можливо це коментар
		case SComment:
		{
			ch = getc(F);
			if (ch == '#')
				state = Comment;
			else
			{
				strcpy_s(TempToken.name, "Div");
				TempToken.type = Div;
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
			}
			break;
		}
		// стан Comment - поточний символ #, отже це коментар, видаляємо усі символи до кінця
		//рядка
		case Comment:
		{
			while (ch != '\n' && ch != EOF)
			{
				ch = getc(F);
			}
			if (ch == EOF)
			{
				state = EndOfFile;
				break;
			}
			//line++;
			//ch = getc(F);
			state = Start;
			break;
		}
		
		case Another:
		{
			// Перевіряємо всі можливі одно- і двосимвольні оператори

			// 1) (  )
			if (ch == '(')
			{
				strcpy_s(TempToken.name, "(");
				TempToken.type = LBraket;
				TempToken.value = 0;
				TempToken.line = line;
				ch = getc(F);
				state = Finish;
				break;
			}
			if (ch == ')')
			{
				strcpy_s(TempToken.name, ")");
				TempToken.type = RBraket;
				TempToken.value = 0;
				TempToken.line = line;
				ch = getc(F);
				state = Finish;
				break;
			}

			// 2) ;  ,
			if (ch == ';')
			{
				strcpy_s(TempToken.name, ";");
				TempToken.type = Semicolon;
				TempToken.value = 0;
				TempToken.line = line;
				ch = getc(F);
				state = Finish;
				break;
			}
			if (ch == ',')
			{
				strcpy_s(TempToken.name, ",");
				TempToken.type = Comma;
				TempToken.value = 0;
				TempToken.line = line;
				ch = getc(F);
				state = Finish;
				break;
			}

			// 3) ++
			if (ch == '+')
			{
				char c2 = getc(F);
				if (c2 == '+')
				{
					strcpy_s(TempToken.name, "++");
					TempToken.type = Add;
					TempToken.value = 0;
					TempToken.line = line;
					ch = getc(F);
				}
				else
				{
					// повертаємо непрочитаний символ
					ungetc(c2, F);
					TempToken.name[0] = '+';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					TempToken.value = 0;
					TempToken.line = line;
					ch = getc(F);
				}
				state = Finish;
				break;
			}

			// 4) --  
			if (ch == '-')
			{
				char c2 = getc(F);
				if (c2 == '-')
				{
					strcpy_s(TempToken.name, "--");
					TempToken.type = Sub;
					ch = getc(F);
				}
				else
				{
					ungetc(c2, F);
					TempToken.name[0] = '-';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					ch = getc(F);
				}
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
				break;
			}

			// 5) **
			if (ch == '*')
			{
				char c2 = getc(F);
				if (c2 == '*')
				{
					strcpy_s(TempToken.name, "**");
					TempToken.type = Mul;
					ch = getc(F);
				}
				else
				{
					ungetc(c2, F);
					TempToken.name[0] = '*';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					ch = getc(F);
				}
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
				break;
			}

			// 6) &&
			if (ch == '&')
			{
				char c2 = getc(F);
				if (c2 == '&')
				{
					strcpy_s(TempToken.name, "&&");
					TempToken.type = And;
					ch = getc(F);
				}
				else
				{
					ungetc(c2, F);
					TempToken.name[0] = '&';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					ch = getc(F);
				}
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
				break;
			}

			// 7) ||
			if (ch == '|')
			{
				char c2 = getc(F);
				if (c2 == '|')
				{
					strcpy_s(TempToken.name, "||");
					TempToken.type = Or;
					ch = getc(F);
				}
				else
				{
					ungetc(c2, F);
					TempToken.name[0] = '|';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					ch = getc(F);
				}
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
				break;
			}

			// 8) !!
			if (ch == '!')
			{
				char c2 = getc(F);
				if (c2 == '!')
				{
					strcpy_s(TempToken.name, "!!");
					TempToken.type = Not;
					ch = getc(F);
				}
				else
				{
					ungetc(c2, F);
					TempToken.name[0] = '!';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					ch = getc(F);
				}
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
				break;
			}

			// 9) Ne
			if (ch == 'N')
			{
				char c2 = getc(F);
				if (c2 == 'e')
				{
					strcpy_s(TempToken.name, "Ne");
					TempToken.type = NotEquality;
					ch = getc(F);
				}
				else
				{
					ungetc(c2, F);
					TempToken.name[0] = 'N';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					ch = getc(F);
				}
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
				break;
			}

			// 10) Eg
			if (ch == 'E')
			{
				char c2 = getc(F);
				if (c2 == 'g')
				{
					strcpy_s(TempToken.name, "Eg");
					TempToken.type = Equality;
					ch = getc(F);
				}
				else
				{
					ungetc(c2, F);
					TempToken.name[0] = 'E';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					ch = getc(F);
				}
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
				break;
			}

			// 11) ~>
			if (ch == '~')
			{
				char c2 = getc(F);
				if (c2 == '>')
				{
					strcpy_s(TempToken.name, "~>");
					TempToken.type = Greate;
					ch = getc(F);
				}
				else
				{
					ungetc(c2, F);
					TempToken.name[0] = '~';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					ch = getc(F);
				}
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
				break;
			}

			// 12) <~
			if (ch == '<')
			{
				char c2 = getc(F);
				if (c2 == '~')
				{
					strcpy_s(TempToken.name, "<~");
					TempToken.type = Less;
					ch = getc(F);
				}
				else
				{
					ungetc(c2, F);
					TempToken.name[0] = '<';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					ch = getc(F);
				}
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
				break;
			}

			// 13) >>
			if (ch == '>')
			{
				char c2 = getc(F);
				if (c2 == '>')
				{
					strcpy_s(TempToken.name, ">>");
					TempToken.type = Assign;
					ch = getc(F);
				}
				else
				{
					ungetc(c2, F);
					TempToken.name[0] = '>';
					TempToken.name[1] = '\0';
					TempToken.type = Unknown;
					ch = getc(F);
				}
				TempToken.value = 0;
				TempToken.line = line;
				state = Finish;
				break;
			}

			// Якщо нічого не підійшло — Unknown символ
			TempToken.name[0] = ch;
			TempToken.name[1] = '\0';
			TempToken.type = Unknown;
			TempToken.value = 0;
			TempToken.line = line;
			ch = getc(F);
			state = Finish;
			break;
		}

		}
	}
}
// функція друкує таблицю лексем на екран
void PrintTokens(Token TokenTable[], unsigned int TokensNum)
{
	char type_tokens[16];
	printf("\n\n---------------------------------------------------------------------------\n");
	printf("| TOKEN TABLE |\n");
	printf("---------------------------------------------------------------------------\n");
	printf("| line number | token | value | token code | type of token |\n");
	printf("---------------------------------------------------------------------------");
	for (unsigned int i = 0; i < TokensNum; i++)
	{
		switch (TokenTable[i].type)
		{
		case StartProgram:
			strcpy_s(type_tokens, "StartProgram");
			break;
		case Variable:
			strcpy_s(type_tokens, "Variable");
			break;
		case Type:
			strcpy_s(type_tokens, "Integer");
			break;
		case Identifier:
			strcpy_s(type_tokens, "Identifier");
			break;
		case EndProgram:
			strcpy_s(type_tokens, "EndProgram");
			break;
		case Input:
			strcpy_s(type_tokens, "Input");
			break;
		case Output:
			strcpy_s(type_tokens, "Output");
			break;
		case If:
			strcpy_s(type_tokens, "If");
			break;
		case Then:
			strcpy_s(type_tokens, "Then");
			break;
		case Else:
			strcpy_s(type_tokens, "Else");
			break;
		case ForKW:
			strcpy_s(type_tokens, "For");
			break;
		case ToKW:
			strcpy_s(type_tokens, "To");
			break;
		case NextKW:
			strcpy_s(type_tokens, "Next");
			break;
		case Assign:
			strcpy_s(type_tokens, "Assign");
			break;
		case Add:
			strcpy_s(type_tokens, "Add");
			break;
		case Sub:
			strcpy_s(type_tokens, "Sub");
			break;
		case Mul:
			strcpy_s(type_tokens, "Mul");
			break;
		case Div:
			strcpy_s(type_tokens, "Div");
			break;
		case Equality:
			strcpy_s(type_tokens, "Equality");
			break;
		case NotEquality:
			strcpy_s(type_tokens, "NotEquality");
			break;
		case Greate:
			strcpy_s(type_tokens, "Greate");
			break;
		case Less:
			strcpy_s(type_tokens, "Less");
			break;
		case Not:
			strcpy_s(type_tokens, "Not");
			break;
		case And:
			strcpy_s(type_tokens, "And");
			break;
		case Or:
			strcpy_s(type_tokens, "Or");
			break;
		case LBraket:
			strcpy_s(type_tokens, "LBraket");
			break;
		case RBraket:
			strcpy_s(type_tokens, "RBraket");
			break;
		case Number:
			strcpy_s(type_tokens, "Number");
			break;
		case Semicolon:
			strcpy_s(type_tokens, "Semicolon");
			break;
		case Comma:
			strcpy_s(type_tokens, "Comma");
			break;
		case Unknown:
			strcpy_s(type_tokens, "Unknown");
			break;
		}
		printf("\n|%12d |%16s |%11d |%11d | %-13s |\n",
			TokenTable[i].line,
			TokenTable[i].name,
			TokenTable[i].value,
			TokenTable[i].type,
			type_tokens);
		printf("---------------------------------------------------------------------------");
	}
}
// функція друкує таблицю лексем у файл
void PrintTokensToFile(char* FileName, Token TokenTable[], unsigned int TokensNum)
{
	FILE* F;
	if ((fopen_s(&F, FileName, "wt")) != 0)
	{
		printf("Error: Can not create file: %s\n", FileName);
		return;
	}
	char type_tokens[16];
	fprintf(F, "---------------------------------------------------------------------------\n");
	fprintf(F, "| TOKEN TABLE |\n");
	fprintf(F, "---------------------------------------------------------------------------\n");
	fprintf(F, "| line number | token | value | token code | type of token |\n");
	fprintf(F, "---------------------------------------------------------------------------");
	for (unsigned int i = 0; i < TokensNum; i++)
	{
		switch (TokenTable[i].type)
		{
		case StartProgram:
			strcpy_s(type_tokens, "StartProgram");
			break;
		case Variable:
			strcpy_s(type_tokens, "Variable");
			break;
		case Identifier:
			strcpy_s(type_tokens, "Identifier");
			break;
		case Type:
			strcpy_s(type_tokens, "Integer");
			break;
		case EndProgram:
			strcpy_s(type_tokens, "EndProgram");
			break;
		case Input:
			strcpy_s(type_tokens, "Input");
			break;
		case Output:
			strcpy_s(type_tokens, "Output");
			break;
		case If:
			strcpy_s(type_tokens, "If");
			break;
		case Then:
			strcpy_s(type_tokens, "Then");
			break;
		case Else:
			strcpy_s(type_tokens, "Else");
		case ForKW:
			strcpy_s(type_tokens, "For");
			break;
		case ToKW:
			strcpy_s(type_tokens, "To");
			break;
		case NextKW:
			strcpy_s(type_tokens, "Next");
			break;
		case Assign:
			strcpy_s(type_tokens, "Assign");
			break;
		case Add:
			strcpy_s(type_tokens, "Add");
			break;
		case Sub:
			strcpy_s(type_tokens, "Sub");
			break;
		case Mul:
			strcpy_s(type_tokens, "Mul");
			break;
		case Div:
			strcpy_s(type_tokens, "Div");
			break;
		case Equality:
			strcpy_s(type_tokens, "Equality");
			break;
		case NotEquality:
			strcpy_s(type_tokens, "NotEquality");
			break;
		case Greate:
			strcpy_s(type_tokens, "Greate");
			break;
		case Less:
			strcpy_s(type_tokens, "Less");
			break;
		case Not:
			strcpy_s(type_tokens, "Not");
			break;
		case And:
			strcpy_s(type_tokens, "And");
			break;
		case Or:
			strcpy_s(type_tokens, "Or");
			break;
		case LBraket:
			strcpy_s(type_tokens, "LBraket");
			break;
		case RBraket:
			strcpy_s(type_tokens, "RBraket");
			break;
		case Number:
			strcpy_s(type_tokens, "Number");
			break;
		case Semicolon:
			strcpy_s(type_tokens, "Semicolon");
			break;
		case Comma:
			strcpy_s(type_tokens, "Comma");
			break;
		case Unknown:
			strcpy_s(type_tokens, "Unknown");
			break;
		}
		fprintf(F, "\n|%12d |%16s |%11d |%11d | %-13s |\n",
			TokenTable[i].line,
			TokenTable[i].name,
			TokenTable[i].value,
			TokenTable[i].type,
			type_tokens);
		fprintf(F, "---------------------------------------------------------------------------");
	}
	fclose(F);
}
int main(int argc, char* argv[])
{
	// таблиця лесем
	//Token TokenTable[MAX_TOKENS];
	Token* TokenTable = new Token[MAX_TOKENS];
	// кількість лексем
	unsigned int TokensNum;
	// таблиця ідентифікаторів
	char InputFile[32] = "";
	FILE* InFile;
	if (argc != 2)
	{
		printf("Input file name: ");
		gets_s(InputFile);
	}
	else
	{
		strcpy_s(InputFile, argv[1]);
	}
	if ((fopen_s(&InFile, InputFile, "rt")) != 0)
	{
		printf("Error: Can not open file: %s\n", InputFile);
		return 1;
	}
	TokensNum = GetTokens(InFile, TokenTable);
	char TokenFile[32];
	int i = 0;
	while (InputFile[i] != '.')
	{
		TokenFile[i] = InputFile[i];
		i++;
	}
	TokenFile[i] = '\0';
	strcat_s(TokenFile, ".token");
	PrintTokensToFile(TokenFile, TokenTable, TokensNum);
	fclose(InFile);
	printf("\nLexical analysis completed. List of tokens in the file %s\n", TokenFile);
	PrintTokens(TokenTable, TokensNum);
	delete[]TokenTable;
	return 0;
}