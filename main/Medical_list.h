#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Disease // ткуктура заболевания
{
    int disease_code; // Код заболевания
    string registration_date; // Дата регестрации заболевания
    Disease* next; // Указатель на следующую запись о заболевании
    Disease(int d, string r) : disease_code(d), registration_date(r), next(nullptr) {}
};

class List
{
private:
    Disease* head;
public:
    List();
    void push_front(int, string); 
    void delete_node(int);
    void output_list() const;
};

//----------------------------------------------------------------------------------------------

struct Medical_card_Node
{
    string medical_policy_number; // Номер мед. полиса (буквенно-цифровой)
    Disease* disease_list; // Указатель на линейный список заболеваний
    string surname; // Фамилия пациента
    Medical_card_Node* prev;
    Medical_card_Node* next;
};

class Medical_list
{
public:
    Medical_list(); // Конструктор
    ~Medical_list(); // Деструктор

    void insert_node(string medical_policy_number, string surname); // вставка узла
    void delete_node(Medical_card_Node* node); // удаление узла
    void print_list_forward() const; // вывод списка слева направо
    void print_list_backward() const; // вывод списка справа налево
    Medical_card_Node* search_node(string brand) const; // поиск узла по марке автомобиля

    // Методы по индивидуальному варианту


private:
    Medical_card_Node* head; // Головной
    Medical_card_Node* tail; // Хвостовой
};