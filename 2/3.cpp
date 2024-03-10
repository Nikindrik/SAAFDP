#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

long long int insertion_sort(vector<int>& arr) {
    long long int operations_counter = 0;
    for (int i = 0; i < arr.size(); ++i) {
        int tmp = arr[i];
        int j = i;
        while (j > 0 && arr[j - 1] > tmp) {
            arr[j] = arr[j - 1];
            --j;
            operations_counter += 3; // Сравнение в цикле, присвоение в теле цикла, декремент
        }
        arr[j] = tmp;
        operations_counter += 5; // Сравние в цикле при входе, 3 присвоение, 2 из которых вышее цикла while, сравнение в цикле при выходе
    }
    ++operations_counter; // Сравнение при выходе из цикла for
    return operations_counter;
}

int main() { 
    setlocale(LC_ALL, "Rus");
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    vector<int> array;
       
    cout << "Выберите тип заполнения массива" << endl;
    cout << "a - рандом" << endl;
    cout << "b - с одним заданым значением" << endl;
    cout << "c - ручной ввод массива" << endl;
    char ty;
    cin >> ty;
    switch (ty) { //Конструкция switch case default для выбор типа заполения массива
    case 'a': {
        mt19937 gen(random_device{}()); // mt19937 gen - генератор случайных чисел
        uniform_int_distribution<int> dist(0, 10); // Инструмент, позволяющий генерировать случайное целое число в заданном диапазоне

        for (int i = 0; i < n; i++)
            array.push_back(dist(gen));
        for (int i = 0; i < n; i++) // Вывод сгенерированого массива
                cout << array[i] << " ";
        cout << endl;
    }
            break;
    case 'b': {
        cout << "Введите значение: ";
        int x;
        cin >> x;
        for (int i = 0; i < n; i++)
            array.push_back(x);
        for (int i = 0; i < n; i++) // Вывод сгенерированого массива
            cout << array[i] << " ";
        cout << endl;
    }
            break;
    case 'c': {
        // Ручной ввдо массива
        for (int i = 0; i < n; i++) {
            int tmp;
            cin >> tmp;
            array.push_back(tmp);
        }
        for (int i = 0; i < n; i++) // Вывод сгенерированого массива
            cout << array[i] << " ";
        cout << endl;
    }
            break;
    default: {
        cout << "Допущенны ошибки" << endl;
        return -1; // Завершение программы при некоректных данных
    }
    }
    sort(array.begin(), array.end()); // Массив отсортированный не по убыванию
    for (int i = 0; i < n; i++) // Вывод сгенерированого массива
        cout << array[i] << " ";
    cout << endl;
    auto start = chrono::high_resolution_clock::now(); // Начало отсчета время сорировки
    long long int operation_counter = insertion_sort(array); // Вызов функции сортировки массива с воращением значения подсчета операций
    auto end = chrono::high_resolution_clock::now(); // Окончание отсчета время сорировки
    cout << "Вывод отсортированного массива" << endl;
    for (auto& it : array) // Вывод массива
        cout << it << " ";
    cout << endl;
    cout << "Количество операций срванения, присоения алгоритма сортировки: " << operation_counter << endl;
    cout << "Время работы алгоритма сортировки: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " наносекунд" << endl;
    return 0;
}