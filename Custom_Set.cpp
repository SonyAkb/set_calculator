#include "Custom_Set.h"

Custom_Set::Custom_Set(const Custom_Set& v) {//конструктор копирования
    for (size_t i = 0; i < v.values.size(); ++i) {
        values.push_back(v.values[i]);
    }
}

void Custom_Set::add(int a) {
    values.push_back(a);
}

bool Custom_Set::Is_In(int a) { // проверка наличия элемента в множестве
    for (const auto& value : values) {
        if (value == a) {
            return true;
        }
    }
    return false;
}

void Custom_Set::Print() const {
    std::cout << "[";
    if (values.size() == 0) {
        std::cout << "Пустое множество";
    }
    else {
        for (size_t i = 0; i < values.size(); ++i) {
            std::cout << values[i];
            if (i < values.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << "]" << std::endl;
}

Custom_Set Custom_Set::operator+(const Custom_Set& other) const {//объединение
    Custom_Set result(*this);//копирую левое множество
    for (const auto& value : other.values) {//проход по элементам правого множесва
        if (!result.Is_In(value)) {//такого элемента еще нет в новом множестве
            result.values.push_back(value);
        }
    }
    return result;
}

Custom_Set Custom_Set::operator-(Custom_Set& other) {//пересечение
    Custom_Set result;
    for (const auto& value : other.values) {//проход по элементам правого множесва
        if (Is_In(value) && other.Is_In(value)) {//такой элемент есть в обоих множествах
            result.add(value);
        }
    }
    return result;
}

Custom_Set Custom_Set::operator*(Custom_Set& other) { //симметрическая разность
    Custom_Set result;
    for (const auto& value : values) {//проход по элементам левого множества
        if (!other.Is_In(value)) {//такого элемента нет в правом множестве
            result.values.push_back(value);
        }
    }
    for (const auto& value : other.values) {//проход по элементам правого множества
        if (!Is_In(value)) {//такого элемента нет в левом множестве
            result.values.push_back(value);
        }
    }
    return result;
}

Custom_Set Custom_Set::operator/(Custom_Set& other) { //разность
    Custom_Set result;
    for (const auto& value : values) {//проход по элементам левого множества
        if (!other.Is_In(value)) {//такого элемента нет в правом множестве
            result.add(value);
        }
    }
    return result;
}

Custom_Set& Custom_Set::operator=(const Custom_Set& other) {//приравнивание
    this->values = other.values;
    return *this;
}

Custom_Set Custom_Set::Addition() {//дополнение
    Custom_Set result;
    for (int value = -100; value <= 100; value++) {//проход по всем возможным элементам
        if (!Is_In(value)) {//если такого элемента нет в множестве
            result.add(value);
        }
    }
    return result;
}

int Custom_Set::Number_Of_Elements() {
    return values.size();
}