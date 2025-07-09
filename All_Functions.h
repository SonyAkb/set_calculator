#pragma once

#include "Custom_Set.h"

void Separate(int num, std::string symbol = "-");

bool Is_Brackets(std::string str);//в строке остались скобки или нет
char Calculating_Two_Sets(std::map<char, Custom_Set*>& variables, std::string formula, int& count_new_letter);//вычисление между двумя множествами

bool Is_Additions(std::string str, int& index);//есть ли в формуле отрицание
char Kill_Of_Addition(std::map<char, Custom_Set*>& variables, std::string formula, int& count_new_letter, int& index);//переворачиваю очередное дополнение
std::string Kill_Of_The_All_Additions(std::map<char, Custom_Set*>& variables, std::string formula, int& count_new_letter);

std::string Calculating_A_String_Without_Parentheses(std::map<char, Custom_Set*>& variables, std::string formula, int& count_new_letter);//подсчет строки множеств, где нет скобок
void Index_Of_Brackets(std::string formula, int& brackets_ind_one, int& brackets_ind_two);

Custom_Set Calculation(std::map<char, Custom_Set*> variables, std::string formula);

void Print_Info_About_Operations();//вывод обозначений операций множеств

std::string Str_Without_Spaces(std::string& formula);//убираю из формулы ВСЕ пробелы
std::string Without_Double_Negation(std::string& formula);//убираю двойное отрицание из формулы
std::string Formatting_Formula(std::string& formula);
bool Are_Brackets_Correct(std::string& formula);//скобки последовательно закрыты/открыты
std::string Valid_Characters(std::map<char, Custom_Set*>& variables);//нахожу все допустимые символы в строки формул
bool Is_This_Symbol_Allowed(char& symbol, std::string& all_allowed);
bool Are_Names_And_Signs_Correct(std::string& formula, std::map<char, Custom_Set*>& variables);
bool Last_And_First_Characters_Are_Correct(std::string formula);
bool There_Are_No_Two_Consecutive_Operations(std::string formula);
bool Is_Formula_Correct(std::string& formula, std::map<char, Custom_Set*>& variables);

bool is_String_Convert_To_Int_With_Interval(const std::string& input, int left_board = -100, int right_board = 100);

bool Is_There_Such_An_Element(std::vector<int>& set_1, int& number);

void Create_A_Random_Set(int& length, int& name_set, std::map<char, Custom_Set*>& variables);
void Create_Set_With_Hands(int& length, int& name_set, std::map<char, Custom_Set*>& variables);

void Enter_Two_Numbers(int& left_board, int& right_board);
int Enter_One_Number(int& number);

bool Is_Prime(int number);

void Create_Set_With_Conditions(int& length, int& name_set, std::map<char, Custom_Set*>& variables);

void Entering_A_Single_Set(std::map<char, Custom_Set*>& variables, int& name_of_the_main_set);

void Create_Multiple_Sets(std::map<char, Custom_Set*>& variables, int& name_of_the_main_set);

void Print_Of_All_Sets(std::map<char, Custom_Set*>& variables);

void Showing_The_Answer(Custom_Set set);

bool get_formula(std::string& formula, std::map<char, Custom_Set*>& variables);