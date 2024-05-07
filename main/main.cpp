#include <iostream>
#include "Medical_list.h"
using namespace std;


int main()
{
    setlocale(LC_ALL, "RUS");
    Medical_list medical_list;
    int Choice, choose;
    string medical_policy_number, surname, registration_date;
    int disease_code;
    // Меню выбора типа ввода данных
    cout << "Выберите тип ввода данных." << endl;
    cout << "1. Ввод данных с клавиатуры" << endl;
    cout << "2. Использовать уже заготовленные данные" << endl;

    cout << "Введите номер выбранного типа ввода данных: ";
    cin >> Choice;

    switch (Choice) {
    case 1:
        int n; // Количество пациентов
        cout << "Введите количество автомобилей: ";
        cin >> n;

        for (int i = 0; i < n; ++i) {
            cout << "Введите данные для медецинской карты " << i + 1 << ":" << endl;
            cout << "Номер мед. полиса (буквенно-цифровой): ";
            cin >> medical_policy_number;
            cout << "Фамилия пациента: ";
            cin >> surname;
            medical_list.insert_node(medical_policy_number, surname);
        }
        break;

    case 2:
        // Создание списка
        medical_list.insertNode("Toyota", "Япония", 2019, 25000.0);
        medical_list.insertNode("BMW", "Германия", 2018, 35000.0);
        medical_list.insertNode("Honda", "Япония", 2020, 22000.0);
        medical_list.insertNode("Mercedes", "Германия", 2017, 40000.0);
        medical_list.insertNode("Ford", "США", 2016, 18000.0);
        break;

    default:
        cout << "Ошибка" << endl;
        return 0;
    }
    cout << "Исходный список:" << endl;
    medical_list.printListForward();
    cout << endl;
    int choice_method;

    do {
        cout << "Меню:" << endl;
        cout << "1. Вывод списка вперед на экран" << endl;
        cout << "2. Вывод списка назад на экран" << endl;
        cout << "3. Вставка нового узла в конец подсписка" << endl;
        cout << "4. Вставка нового узла в начало подсписка" << endl;
        cout << "5. Удаление узла" << endl;
        cout << "6. Упорядочивание списка по марке автомобиля" << endl;
        cout << "7. Упорядочивание списка по стране автомобиля" << endl;
        cout << "8. Поиск автомобиля по бренду, дата продажи и удаление проданных машин из списка" << endl;
        cout << "9. Выход из программы" << endl;
        cout << "Введите пункт от 1 до 9: ";

        cin >> choice_method;

        switch (choice_method) {

        case 1:
            cout << "Список вперед:" << endl;
            medical_list.printListForward();
            cout << endl;
            break;

        case 2:
            cout << "Список назад:" << endl;
            medical_list.printListBackward();
            cout << endl;
            break;

        case 3:
            // Вставка нового узла в конец подсписка
            medical_list.insertNode("Audi", "Германия", 2021, 45000.0);
            cout << "Список после добавления Audi в конец списка немецких автомобилей:" << endl;
            medical_list.printListForward();
            cout << endl;
            break;

        case 4:
            // Вставка нового узла в начало подсписка
            medical_list.insertNodeAtBeginning("Audi", "Германия", 2021, 45000.0);
            cout << "Список после добавления Audi в начало списка немецких автомобилей:" << endl;
            medical_list.printListForward();
            cout << endl;
            break;

        case 5:
            CarNode * nodeToDelete = medical_list.searchNode("Audi");
            if (nodeToDelete != nullptr)
                medical_list.deleteNode(nodeToDelete);
            else
                cout << "Узел с указанными данными не найден." << endl;
            break;

        case 6:
            // Упорядочивание списка по стране автомобиля
            medical_list.orderListByBrand();
            cout << "Список после сортировки по брендам:" << endl;
            medical_list.printListForward();
            cout << endl;

        case 7:
            // Упорядочивание списка по стране изготовителю
            medical_list.orderListByCountry();
            cout << "List after ordering by country:" << endl;
            medical_list.printListForward();
            cout << endl;
            break;

        case 8:
            cout << "Выберите тип ввода данных для нахождения автомобиля." << endl;
            // Меню выбора типа ввода данных
            cout << "1. Ввод данных с клавиатуры" << endl;
            cout << "2. Использовать уже существующее данные " << endl;

            cout << "Тип ввода: ";
            cin >> choose;

            if (choose == 1) {
                // Ввод марки автомобиля для поиска
                cout << "Введите бренд для поиска: ";
                cin >> brand;
                {
                    CarNode* searchResult = medical_list.searchNode(brand);
                    if (searchResult != nullptr) {
                        cout << "Найденный автомобиль: " << searchResult->brand << " " << searchResult->country << " " << searchResult->year << " " << searchResult->price << endl;
                    }

                    else {
                        cout << "Автомобиль не найден." << endl;
                    }

                    // Ввод даты продажи для установки
                    if (searchResult != nullptr) {
                        cout << "Введите дату продажи автомобиля: ";
                        cin >> saleDate;
                        medical_list.setSaleDate(searchResult, saleDate);
                    }
                }
            }

            else if (choose == 2) {
                // Поиск узла по марке автомобиля
                {
                    CarNode* searchResult = medical_list.searchNode("Honda");
                    if (searchResult != nullptr) {
                        cout << "Найденный автомобиль: " << searchResult->brand << " " << searchResult->country << " " << searchResult->year << " " << searchResult->price << endl;
                    }
                    else {
                        cout << "Автомобиль не найден." << endl;
                    }

                    // Установка даты продажи
                    medical_list.setSaleDate(searchResult, "2024-04-23");
                }
            }

            else {
                cout << "Ошибка" << endl;
                return -1;
            }

            // Удаление проданных автомобилей
            medical_list.deleteSoldCars();
            cout << "Список после удаления проданных автомобилей:" << endl;
            medical_list.printListForward();
            break;

        case 9:
            cout << "Завершение программы" << endl;
            return 0;

        default:
            cout << "Ошибка" << endl;
            return 0;
        }
    } while (choice_method != 9);
    return 0;
}