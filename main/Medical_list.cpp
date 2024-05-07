#include "Medical_list.h"


List::List() :head(nullptr) {}

// ������� � ������ ���� ������ ����������� ��������
void List::push_front(int newCode, string newDate) {
    // ������� ����� ����, ����������� ��� ��������, ���������, ��� ��������� ������� - ������� ������, ��������� ������ ������
    Disease* newNode = new Disease(newCode, newDate);
    newNode->next = head;
    head = newNode;
}

void List::delete_node(int key) {
    // �������� �������� ������, ��������� ������� ���� � ��� ��������, ������� ��� � ��������� ���������
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

// ������� ���� � ����� ������
void Medical_list::insert_node(string medical_policy_number, string surname) {
    Medical_card_Node* newNode = new Medical_card_Node;
    newNode->medical_policy_number = medical_policy_number;
    newNode->surname = surname;
    newNode->disease_list = nullptr; // ���� �� ������

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

// �������� ����
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

// ����� ������ ����� �������
void Medical_list::print_list_forward() const {
    Medical_card_Node* current = head;
    while (current != nullptr) {
        cout << "����� ���. ������: " << current->medical_policy_number;
        if (current->disease_list != nullptr) { // ��������, ��� ������ �������� �� ������
            cout << ", �������: ";
            Disease* tmp_disease = current->disease_list;
            while (tmp_disease) {
                cout << "��� �����������e: " << tmp_disease->disease_code << ", ���� ����������� �����������: " << tmp_disease->registration_date << "\t";
                tmp_disease = tmp_disease->next;
            }
            cout << ", ������� ��������: " << current->surname << endl;
        }
        else
            cout << ", �������� ���" << ", ������� ��������: " << current->surname << endl;
        current = current->next;
    }
}

// ����� ������ ������ ������
void Medical_list::print_list_backward() const {
    Medical_card_Node* current = tail;
    while (current != nullptr) {
        cout << "����� ���. ������: " << current->medical_policy_number;
        if (current->disease_list != nullptr) { // ��������, ��� ������ �������� �� ������
            cout << ", �������: ";
            Disease* tmp_disease = current->disease_list;
            while (tmp_disease) {
                cout << "��� �����������e: " << tmp_disease->disease_code << ", ���� ����������� �����������: " << tmp_disease->registration_date << "\t";
                tmp_disease = tmp_disease->next;
            }
            cout << ", ������� ��������: " << current->surname << endl;
        }
        else
            cout << ", �������� ���" << ", ������� ��������: " << current->surname << endl;
        current = current->prev;
    }
}

// ����� ���� �� ���. ����� �� ������� ��������
Medical_card_Node* Medical_list::search_node(string surname) const {
    Medical_card_Node* current = head;
    while (current != nullptr) {
        if (current->surname == surname)
            return current;
        current = current->next;
    }
    return nullptr; // ���� � �������� ������ �� ������
}