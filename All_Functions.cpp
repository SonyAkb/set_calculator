#include "All_Functions.h"

void Separate(int num, std::string symbol)
{
    for (int i = 0; i < num; i++) { std::cout << symbol; }
    std::cout << std::endl;
}

bool Is_Brackets(std::string str) {//в строке остались скобки или нет
    for (const auto& value : str) {
        if (value == '(') {
            return true;
        }
    }
    return false;
}

char Calculating_Two_Sets(std::map<char, Custom_Set*>& variables, std::string formula, int& count_new_letter) {//вычисление между двумя множествами
    char sign = formula[1];//операция между двумя множествами
    char code = count_new_letter;
    Custom_Set new_set;//новое множество - результат операции над данными двумя множествами
    switch (sign) {
    case '+':
        new_set = *variables[formula[0]] + *variables[formula[2]];
        break;
    case '^':
        new_set = *variables[formula[0]] - *variables[formula[2]];
        break;
    case '*':
        new_set = *variables[formula[0]] * *variables[formula[2]];
        break;
    case '/':
        new_set = *variables[formula[0]] / *variables[formula[2]];
        break;
    }
    variables[code] = new Custom_Set(new_set);//заношу множество в словарь
    count_new_letter++;//сдвигаю очередной новый символ для другого множества
    return code;//новое множество на основе двух старых
}

bool Is_Additions(std::string str, int& index) {//есть ли в формуле отрицание
    int count = 0;
    for (const auto& value : str) {
        if (value == '!') {
            index = count;
            return true;
        }
        count++;
    }
    return false;
}

char Kill_Of_Addition(std::map<char, Custom_Set*>& variables, std::string formula, int& count_new_letter, int& index) {//переворачиваю очередное дополнение
    Custom_Set new_set;
    char code = count_new_letter;
    new_set = variables[formula[index + 1]]->Addition();//создаю перевернутое множество
    variables[code] = new Custom_Set(new_set);//заношу множество в словарь
    count_new_letter++;
    return code;
}

std::string Kill_Of_The_All_Additions(std::map<char, Custom_Set*>& variables, std::string formula, int& count_new_letter) {
    int index;
    while (Is_Additions(formula, index)) {//пока в строке есть дополнение
        char new_set = Kill_Of_Addition(variables, formula, count_new_letter, index);
        formula = formula.substr(0, index) + new_set + formula.substr(index + 2);//пересобираю строку
    }
    return formula;
}

std::string Calculating_A_String_Without_Parentheses(std::map<char, Custom_Set*>& variables, std::string formula, int& count_new_letter) {//подсчет строки множеств, где нет скобок
    char result_calculating_two;
    formula = Kill_Of_The_All_Additions(variables, formula, count_new_letter);//убираю из строки все отрицания
    while (formula.size() != 1) {//пока не посчитаю всю строку и не останеться одно множество
        result_calculating_two = Calculating_Two_Sets(variables, formula.substr(0, 3), count_new_letter);
        formula = result_calculating_two + formula.substr(3);
    }
    return formula;
}

void Index_Of_Brackets(std::string formula, int& brackets_ind_one, int& brackets_ind_two) {
    int count = 0;//счетчик по строке
    brackets_ind_one = 0, brackets_ind_two = 0;
    while (brackets_ind_two == 0) {//пока не дойду до самых внутренних скобок
        if (formula[count] == '(') {
            brackets_ind_one = count;//индекс левой внутренней скобки
        }
        else if (formula[count] == ')') {
            brackets_ind_two = count;//индекс правой внутренней скобки
        }
        count++;//увеличиваю счетчик по строке
    }
}

Custom_Set Calculation(std::map<char, Custom_Set*> variables, std::string formula) {
    bool flag_brackets = Is_Brackets(formula), flag_brackets_two = false;
    int brackets_ind_one = 0, brackets_ind_two = 0;//индексы внутренник скобок
    std::string result_of_calculation_brackets; //резултат вычислений выражения в скобках

    Custom_Set finally;//финальный результат подсчетов
    int name_of_the_new_set = 97;//первое имя промежуточных множеств

    while (flag_brackets) {//пока в строке есть скобки
        Index_Of_Brackets(formula, brackets_ind_one, brackets_ind_two);//нахожу индексы внутренних скобок
        int len_of_formula = formula.length();//длина формулы
        result_of_calculation_brackets = Calculating_A_String_Without_Parentheses(variables, formula.substr(brackets_ind_one + 1, brackets_ind_two - brackets_ind_one - 1), name_of_the_new_set);//высчитываю выражение внутри скобок
        formula = formula.substr(0, brackets_ind_one) + result_of_calculation_brackets + formula.substr(brackets_ind_two + 1);
        flag_brackets = Is_Brackets(formula); //проверка наличия скобок в строке
    }
    formula = Calculating_A_String_Without_Parentheses(variables, formula, name_of_the_new_set);
    finally = *variables[formula[0]];
    return finally;
}

void Print_Info_About_Operations() {//вывод обозначений операций множеств
    std::cout << "Обозначения операций между множествами\n  +      Пересечение (между двумя множествами)\n  ^     Объединение (между двумя множествами)\n  *     Симметрическая разность (между двумя множествами)\n  /     Разность (между двумя множествами)\n  !     Дополнение (перед множеством)\n";
}

std::string Str_Without_Spaces(std::string& formula) {//убираю из формулы ВСЕ пробелы
    std::string new_formula = "";
    for (const auto& value : formula) {
        if (value != ' ') {
            new_formula += value;
        }
    }
    return new_formula;
}

std::string Without_Double_Negation(std::string& formula) {//убираю двойное отрицание из формулы
    std::string new_formula = "";
    for (size_t i = 0; i < formula.size(); i++) {
        if (i != formula.size() - 1 && (formula[i] == '!' && formula[i + 1] == '!')) {
            i++;
        }
        else {
            new_formula += formula[i];
        }
    }
    return new_formula;
}

std::string Formatting_Formula(std::string& formula) {
    std::string new_formula = Str_Without_Spaces(formula);//убираю из формулы ВСЕ пробелы
    new_formula = Without_Double_Negation(new_formula);//убираю двойное отрицание из формулы
    return new_formula;
}

bool Are_Brackets_Correct(std::string& formula) {//скобки последовательно закрыты/открыты
    int count = 0;
    for (const auto& value : formula) {
        if (value == '(') {
            count++;
        }
        else if (value == ')') {
            count--;
        }
        if (count < 0) {
            return false;
        }
    }
    if (count != 0) {
        return false;
    }
    return true;
}

std::string Valid_Characters(std::map<char, Custom_Set*>& variables) {//нахожу все допустимые символы в строки формул
    std::string all_valid = "+^/*!()";
    for (auto iter = variables.begin(); iter != variables.end(); ++iter) {
        all_valid += iter->first;
    }
    return all_valid;
}

bool Is_This_Symbol_Allowed(char& symbol, std::string& all_allowed) {
    for (const auto& value : all_allowed) {
        if (symbol == value) {
            return true;
        }
    }
    return false;
}

bool Are_Names_And_Signs_Correct(std::string& formula, std::map<char, Custom_Set*>& variables) {
    std::string all_valid_characters = Valid_Characters(variables);

    for (auto& value : formula) {
        if (!Is_This_Symbol_Allowed(value, all_valid_characters)) {
            return false;
        }
    }

    return true;
}

bool Last_And_First_Characters_Are_Correct(std::string formula) {
    int last_index = formula.size() - 1;
    if (formula[0] == '+' || formula[0] == '^' || formula[0] == '/' || formula[0] == '*' || formula[last_index] == '+' || formula[last_index] == '^' || formula[last_index] == '/' || formula[last_index] == '*' || formula[last_index] == '!') {
        return false;
    }
    return true;
}

bool There_Are_No_Two_Consecutive_Operations(std::string formula) {
    if (formula.size() == 1) { return true; }


    for (int j = 0; j < formula.size() - 1; j++) {
        if (formula[j] == formula[j + 1] && formula[j] != '!' && formula[j] != '(' && formula[j] != ')') {
            return false;
        }
    }
    return true;
}

bool Is_Formula_Correct(std::string& formula, std::map<char, Custom_Set*>& variables) {
    if (!Are_Brackets_Correct(formula)) {
        return false;
    }
    if (!Are_Names_And_Signs_Correct(formula, variables)) {
        return false;
    }
    if (!Last_And_First_Characters_Are_Correct(formula)) {
        return false;
    }
    if (!There_Are_No_Two_Consecutive_Operations(formula)) {
        return false;
    }
    return true;
}

bool is_String_Convert_To_Int_With_Interval(const std::string& input, int left_board, int right_board) {
    try {
        int new_num = std::stoi(input);
        if (left_board <= new_num && new_num <= right_board) {// Попытка преобразовать строку в число
            return true;
        }
        return false;
    }
    catch (const std::exception& e) {
        return false;// Если возникло исключение, значит строка не может быть преобразована
    }
}

bool Is_There_Such_An_Element(std::vector<int>& set_1, int& number) {
    for (auto& value : set_1) {
        if (number == value) {
            return true;
        }
    }
    return false;
}

void Create_A_Random_Set(int& length, int& name_set, std::map<char, Custom_Set*>& variables) {
    std::vector<int> set_1;
    int tmp;
    for (int i = 0; i < length; i++) {
        do {
            tmp = (rand() % 201) - 100;
        } while (Is_There_Such_An_Element(set_1, tmp));
        set_1.push_back(tmp);
    }
    char code = name_set;
    variables[code] = new Custom_Set(set_1);
    ++name_set;
}

void Create_Set_With_Hands(int& length, int& name_set, std::map<char, Custom_Set*>& variables) {
    std::vector<int> set_1;
    std::string element_of_set_string;
    int element_of_set_int;
    bool flag_tmp;

    for (int i = 0; i < length; i++) {
        std::cout << "Введите элемент: ";
        std::cin >> element_of_set_string;
        do {

            while (!is_String_Convert_To_Int_With_Interval(element_of_set_string, -100, 100)) {
                std::cout << ">>> Ошибка! Попробуйте еще раз" << std::endl;
                std::cout << "Введите элемент (число int от -100 до 100, элементы не должны повторяться!): ";
                std::cin >> element_of_set_string;
            }
            element_of_set_int = std::stoi(element_of_set_string);
            flag_tmp = Is_There_Such_An_Element(set_1, element_of_set_int);
            if (flag_tmp) {
                std::cout << ">>> Ошибка! Попробуйте еще раз" << std::endl;
                std::cout << "Введите элемент (число int от -100 до 100, элементы не должны повторяться!): ";
                std::cin >> element_of_set_string;
            }
        } while (flag_tmp);
        set_1.push_back(std::stoi(element_of_set_string));
    }
    char code = name_set;
    variables[code] = new Custom_Set(set_1);
    ++name_set;
}

void Enter_Two_Numbers(int& left_board, int& right_board) {
    std::string board_of_set_string;
    int element_of_set_int;
    bool flag_tmp;

    std::cout << "Введите ЛЕВУЮ границу: ";
    std::cin >> board_of_set_string;

    while (!is_String_Convert_To_Int_With_Interval(board_of_set_string, -100, 100)) {
        std::cout << ">>> Ошибка! Попробуйте еще раз" << std::endl;
        std::cout << "Введите ЛЕВУЮ границу диапазона (число int от -100 до 100): ";
        std::cin >> board_of_set_string;
    }
    left_board = std::stoi(board_of_set_string);

    std::cout << "Введите ПРАВУЮ границу: ";
    std::cin >> board_of_set_string;

    while (!is_String_Convert_To_Int_With_Interval(board_of_set_string, -100, 100)) {
        std::cout << ">>> Ошибка! Попробуйте еще раз" << std::endl;
        std::cout << "Введите ПРАВУЮ границу диапазона (число int от -100 до 100): ";
        std::cin >> board_of_set_string;
    }
    right_board = std::stoi(board_of_set_string);

    if (left_board > right_board) {
        element_of_set_int = left_board;
        left_board = right_board;
        right_board = element_of_set_int;
    }
}

int Enter_One_Number(int& number) {
    std::string number_string;
    bool flag_tmp;

    std::cout << "Введите число, которому будут кратны элементы: ";
    std::cin >> number_string;

    while (!is_String_Convert_To_Int_With_Interval(number_string, 1, 100)) {
        std::cout << ">>> Ошибка! Попробуйте еще раз" << std::endl;
        std::cout << "Введите число (число int от 1 до 100): ";
        std::cin >> number_string;
    }

    number = std::stoi(number_string);
    return number;
}

bool Is_Prime(int number) {
    number = abs(number);
    if (number <= 1) return false; // Числа 0 и 1 не являются простыми

    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) return false;
    }

    return true;
}

void Create_Set_With_Conditions(int& length, int& name_set, std::map<char, Custom_Set*>& variables) {
    bool flag_bad_input = false, flag_prime_number = false;
    int left_board = -100, right_board = 100, tmp, multiples = 1;
    std::string user_choice;

    do {
        std::cout << "У множества есть диапазон?\n1 - Да\n2 - Нет" << std::endl;
        std::cin >> user_choice;
        switch (user_choice[0])
        {
        case '1':
            Enter_Two_Numbers(left_board, right_board);
            flag_bad_input = false;
            break;
        case '2':
            flag_bad_input = false;
            break;

        default:
            flag_bad_input = true;
            std::cout << ">>> Такой операции нет, попробуйте еще раз" << std::endl;
            break;
        }
    } while (flag_bad_input);

    do {
        std::cout << "Элементы множества должны быть обязательно кратны к-л числу?\n1 - Да\n2 - Нет\n3 - Элементы множества это простые числа" << std::endl;
        std::cin >> user_choice;
        switch (user_choice[0])
        {
        case '1':
            Enter_One_Number(multiples);
            flag_bad_input = false;
            break;
        case '2':
            flag_bad_input = false;
            break;
        case '3':
            flag_prime_number = true;//необходимо проверять числа на простоту
            flag_bad_input = false;
            break;
        default:
            flag_bad_input = true;
            std::cout << ">>> Такой операции нет, попробуйте еще раз" << std::endl;
            break;
        }
    } while (flag_bad_input);

    std::vector<int> set_1;

    for (int i = left_board; i <= right_board && set_1.size() < length; i++) {
        if (i % multiples == 0) {
            if (flag_prime_number) {
                if (Is_Prime(i)) {
                    set_1.push_back(i);
                }
            }
            else {
                set_1.push_back(i);
            }
        }
    }

    char code = name_set;
    variables[code] = new Custom_Set(set_1);
    ++name_set;
}

void Entering_A_Single_Set(std::map<char, Custom_Set*>& variables, int& name_of_the_main_set) {
    std::string user_choice, length_set_string;
    int length_set_int;
    bool flag_bad_input = false;

    std::cout << "Введите количество элементов в множестве -  " << (char)name_of_the_main_set << " : ";
    std::cin >> length_set_string;

    while (!is_String_Convert_To_Int_With_Interval(length_set_string, 0, 200)) {
        std::cout << ">>> Ошибка! Попробуйте еще раз" << std::endl;
        std::cout << "Введите количество элементов в множестве -  " << (char)name_of_the_main_set << " (положительное число int): ";
        std::cin >> length_set_string;
    }
    length_set_int = std::stoi(length_set_string); //конвектирую в числовой тип
    do {
        std::cout << "Выберите, каким образом необходимо создать множество\n1 - создать случайно\n2 - ввести с клавиатуры\n3 - создать по условиям" << std::endl;
        std::cin >> user_choice;
        Separate(40);
        switch (user_choice[0])
        {
        case '1':
            Create_A_Random_Set(length_set_int, name_of_the_main_set, variables);
            flag_bad_input = false;
            break;
        case '2':
            Create_Set_With_Hands(length_set_int, name_of_the_main_set, variables);
            flag_bad_input = false;
            break;
        case '3':
            Create_Set_With_Conditions(length_set_int, name_of_the_main_set, variables);
            flag_bad_input = false;
            break;
        default:
            flag_bad_input = true;
            std::cout << ">>> Такой операции нет, попробуйте еще раз" << std::endl;
            break;
        }
    } while (flag_bad_input);

}

void Create_Multiple_Sets(std::map<char, Custom_Set*>& variables, int& name_of_the_main_set) {
    std::string number_of_sets;
    int number_of_sets_int;
    std::cout << "Введите количество множеств, которые необходимо создать ";
    std::cin >> number_of_sets;

    while (!is_String_Convert_To_Int_With_Interval(number_of_sets, 2, 26)) {
        std::cout << ">>> Ошибка! Попробуйте еще раз" << std::endl;
        std::cout << "Введите число (число int от 2 до 26): ";
        std::cin >> number_of_sets;
    }
    number_of_sets_int = std::stoi(number_of_sets);
    for (int i = 0; i < number_of_sets_int; i++) {
        Entering_A_Single_Set(variables, name_of_the_main_set);
    }
}

void Print_Of_All_Sets(std::map<char, Custom_Set*>& variables) {
    std::cout << "Все доступные множества" << std::endl;
    for (auto iter = variables.begin(); iter != variables.end(); ++iter) {
        std::cout << iter->first << ": ";
        iter->second->Print();
    }
}

void Showing_The_Answer(Custom_Set set) {
    std::cout << "Ответ: ";
    if (set.Number_Of_Elements() == 0) {
        std::cout << "[Пустое пножество]" << std::endl;
    }
    else {
        set.Print();
    }
}

bool get_formula(std::string& formula, std::map<char, Custom_Set*>& variables) {
    Separate(40);
    std::cout << "Введите формулу" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, formula);
    formula = Formatting_Formula(formula);//устраняю лишние пробелы
    return Is_Formula_Correct(formula, variables);
}