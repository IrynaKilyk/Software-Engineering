#pragma once
#define MAX_TOKENS 1000
#define MAX_IDENTIFIER 10
// перерахування, яке описує всі можливі типи лексем
enum TypeOfTokens
{
	StartProgram, // Body
	Variable, // Variables
	Type, // Integer_16t
	EndProgram, // Stop
	Input, // Get
	Output, // Put
	If, // If
	Then, // Then Goto
	Else, // Goto
	ForKW,// For
	ToKW, // To
	NextKW,// Next
	Identifier, // Up_low8 rule: starts with '_' max len 8
	Number, // number
	Assign, // >>
	Add, // ++
	Sub, // --
	Mul, // Mul
	Div, // Div
	Equality, // Eg
	NotEquality, // Ne
	Greate, // ~>
	Less, // <~
	Not, // !!
	And, // &&
	Or, // ||
	LBraket, // (
	RBraket, // )
	Semicolon, // ;
	Comma, // ,
	Unknown
};
// структура для зберігання інформації про лексему
struct Token
{
	char name[MAX_IDENTIFIER + 2]; // ім'я лексеми
	int value; // значення лексеми (для цілих констант)
	int line; // номер рядка
	TypeOfTokens type; // тип лексеми
};
typedef char Id[5];
// перерахування, яке описує стани лексичного аналізатора
enum States
{
	Start, // початок виділення чергової лексеми
	Finish, // кінець виділення чергової лексеми
	Letter, // опрацювання слів (ключові слова і ідентифікатори)
	Digit, // опрацювання цифри
	Separators, // видалення пробілів, символів табуляції і переходу на новий рядок
	Another, // опрацювання інших символів
	EndOfFile, // кінець файлу
	SComment, // початок коментаря
	Comment // видалення коментаря
};