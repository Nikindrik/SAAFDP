#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Disease // �������� �����������
{
    int disease_code; // ��� �����������
    string registration_date; // ���� ����������� �����������
    Disease* next; // ��������� �� ��������� ������ � �����������
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
    string medical_policy_number; // ����� ���. ������ (��������-��������)
    Disease* disease_list; // ��������� �� �������� ������ �����������
    string surname; // ������� ��������
    Medical_card_Node* prev;
    Medical_card_Node* next;
};

class Medical_list
{
public:
    Medical_list(); // �����������
    ~Medical_list(); // ����������

    void insert_node(string medical_policy_number, string surname); // ������� ����
    void delete_node(Medical_card_Node* node); // �������� ����
    void print_list_forward() const; // ����� ������ ����� �������
    void print_list_backward() const; // ����� ������ ������ ������
    Medical_card_Node* search_node(string brand) const; // ����� ���� �� ����� ����������

    // ������ �� ��������������� ��������


private:
    Medical_card_Node* head; // ��������
    Medical_card_Node* tail; // ���������
};