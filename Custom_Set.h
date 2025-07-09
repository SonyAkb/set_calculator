#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
class Custom_Set {
private:
    std::vector<int> values;//множество

public:
    Custom_Set() : values() {}
    Custom_Set(std::vector<int> v) { values = v; }
    Custom_Set(const Custom_Set& v);//конструктор копирования
    ~Custom_Set() {};

    void add(int a);
    bool Is_In(int a);// проверка наличия элемента в множестве
    void Print() const;

    Custom_Set operator+(const Custom_Set& other) const;//объединение
    Custom_Set operator-(Custom_Set& other);//пересечение
    Custom_Set operator*(Custom_Set& other);//симметрическая разность
    Custom_Set operator/(Custom_Set& other);//разность
    Custom_Set& operator=(const Custom_Set& other);//приравнивание
    Custom_Set Addition();//дополнение

    int Number_Of_Elements();
};