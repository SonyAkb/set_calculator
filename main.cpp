#include "All_Functions.h"

int main() {
    system("chcp 1251 > Null");
    srand(time(0));

    std::map<char, Custom_Set*> variables;
    std::string user_choice, formula;
    bool flag_continuation_of_work = true;
    int name_of_the_main_set = 65;

    Create_Multiple_Sets(variables, name_of_the_main_set);
    Print_Of_All_Sets(variables);

    while (flag_continuation_of_work) {
        Separate(60, "=");
        std::cout << "Выберите операцию\n1 - Показать доступные множества\n2 - Показать все доступные операции\n3 - Посчитать формулу\n4 - Добавить новое множесвто\n5 - Добавить несколько новых множеств\n6 - Забыть все множества\n0 - Завершить работу" << std::endl;
        std::cin >> user_choice;
        switch (user_choice[0])
        {
        case '1'://Показать доступные множества
            Separate(40);
            Print_Of_All_Sets(variables);
            break;
        case '2'://Показать все доступные операции
            Separate(40);
            Print_Info_About_Operations();
            break;
        case '3'://Посчитать формулу
            Separate(40);
            Print_Of_All_Sets(variables);
            Print_Info_About_Operations();
            if (get_formula(formula, variables)) {
                try {
                    Showing_The_Answer(Calculation(variables, formula));///////////////добавить исключение!!!!!!!!!!
                }
                catch (...){
                    std::cout << ">>> Ошибка!!!" << std::endl;
                }
            }
            else {
                std::cout << ">>> Ошибка! Введена некорректная формула!" << std::endl;
            }
            break;
        case '4'://Добавить новое множесвто
            Separate(40);
            Entering_A_Single_Set(variables, name_of_the_main_set);
            break;
        case '5'://Добавить несколько новых множест
            Separate(40);
            Create_Multiple_Sets(variables, name_of_the_main_set);
            break;
        case '6'://Забыть все множества
            variables.clear();
            name_of_the_main_set = 65;
            std::cout << "Все множества были забыты!\nДля продолжения работы калькулятора необходимо создать новые!" << std::endl;
            Create_Multiple_Sets(variables, name_of_the_main_set);
            break;
        case '0'://Завершить работу
            Separate(60, "=");
            std::cout << "Завершение работы ... ";
            flag_continuation_of_work = false;
            break;
        default:
            std::cout << ">>> Такой операции нет! Попробуйте еще раз" << std::endl;
            break;
        }
    }

    std::cout << "Работа завершена" << std::endl;
    return 0;
}
