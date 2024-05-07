#include "Medical_list.h"


List::List() :head(nullptr) {}

// Вставка в начало узла списка заболеваний пациента
void List::push_front(int newCode, string newDate) {
    // Создаем новый узел, присваиваем ему значение, указываем, что следующий элемент - текущее начало, обновляем начало списка
    Disease* newNode = new Disease(newCode, newDate);
    newNode->next = head;
    head = newNode;
}

void List::delete_node(int key) {
    // Начинаем обходить список, проверяем наличие узла и его значение, удаляем его и обновляем указатели
    Disease* temp = head;
    Disease* prev = nullptr;
    if (temp != nullptr && temp->disease_code == key) {
        head = temp->next;
        delete temp;
        return;
    }
    while (temp != nullptr && temp->disease_code != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) {
        return;
    }
    prev->next = temp->next;
    delete temp;
}


//-------------------------------------------------------------------------------------------------------------------------------

Medical_list::Medical_list() {
    head = nullptr;
    tail = nullptr;
}

Medical_list::~Medical_list() {
    Medical_card_Node* current = head;
    while (current != nullptr) {
        Medical_card_Node* next = current->next;
        delete current;
        current = next;
    }
}

// Вставка узла в конец списка
void Medical_list::insert_node(string medical_policy_number, string surname) {
    Medical_card_Node* newNode = new Medical_card_Node;
    newNode->medical_policy_number = medical_policy_number;
    newNode->surname = surname;
    newNode->disease_list = nullptr; // Пока не болеет

    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Удаление узла
void Medical_list::delete_node(Medical_card_Node* node)  {
    if (node == nullptr)
        return;
    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        tail = node->prev;
    delete node;
}

// Вывод списка слева направо
void Medical_list::print_list_forward() const {
    Medical_card_Node* current = head;
    while (current != nullptr) {
        cout << "Номер мед. полиса: " << current->medical_policy_number;
        if (current->disease_list != nullptr) { // Проверка, что список болезний не пустой
            cout << ", Болезни: ";
            Disease* tmp_disease = current->disease_list;
            while (tmp_disease) {
                cout << "Код заболеванияe: " << tmp_disease->disease_code << ", Дата регистрации заболевания: " << tmp_disease->registration_date << "\t";
                tmp_disease = tmp_disease->next;
            }
            cout << ", Фимилия больного: " << current->surname << endl;
        }
        else
            cout << ", Болезний нет" << ", Фимилия больного: " << current->surname << endl;
        current = current->next;
    }
}

// Вывод списка справа налево
void Medical_list::print_list_backward() const {
    Medical_card_Node* current = tail;
    while (current != nullptr) {
        cout << "Номер мед. полиса: " << current->medical_policy_number;
        if (current->disease_list != nullptr) { // Проверка, что список болезний не пустой
            cout << ", Болезни: ";
            Disease* tmp_disease = current->disease_list;
            while (tmp_disease) {
                cout << "Код заболеванияe: " << tmp_disease->disease_code << ", Дата регистрации заболевания: " << tmp_disease->registration_date << "\t";
                tmp_disease = tmp_disease->next;
            }
            cout << ", Фимилия больного: " << current->surname << endl;
        }
        else
            cout << ", Болезний нет" << ", Фимилия больного: " << current->surname << endl;
        current = current->prev;
    }
}

// Поиск узла по мед. карты по фамилии больного
Medical_card_Node* Medical_list::search_node(string surname) const {
    Medical_card_Node* current = head;
    while (current != nullptr) {
        if (current->surname == surname)
            return current;
        current = current->next;
    }
    return nullptr; // Узел с заданной маркой не найден
}