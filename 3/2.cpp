#include <iostream>
#include <random>
#include <vector>
#include <chrono>   
using namespace std;

long long int qsort(vector<int>& arr, int start, int end) {
    long long int operation_counter = 0;
    if (start < end) {
        int i = start; // Начало массива(эказатель)
        int j = end; // Конец массива(эказатель)
        int o_elem = arr[(start + end) / 2]; //Опорный элемент в данном случае - средний элемент в массиве
        while (i <= j) {
            while (arr[i] < o_elem) { // Поиск элемента слева от опорного, который больше текущего опорного
                ++i;
                operation_counter += 2; // Инкремент сравнение
            }
            while (arr[j] > o_elem) { // Поиск элемента справа от опорного, который меньше текущего опорного
                --j;
                operation_counter += 2; // Присвоение условие цикла
            }
            if (i <= j) {
                swap(arr[i], arr[j]);
                ++i;
                --j;
                operation_counter += 3; // Присвоение условие
            }
            operation_counter += 2; // Присвоение условие
        }
        operation_counter += 4; // Присвоение условие
        qsort(arr, start, j); // Рекурсия для леовй части массива
        qsort(arr, i, end); // Рекурсия для правой части массива
    }
    ++operation_counter; // Выход из if
    return operation_counter;
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
        uniform_int_distribution<int> dist(1, 10); // Инструмент, позволяющий генерировать случайное целое число в заданном диапазоне

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
    auto start = chrono::high_resolution_clock::now(); // Начало отсчета время сорировки
    long long int operation_counter = qsort(array, 0, array.size() - 1); // Вызов функции сортировки массива с воращением значения подсчета операций
    auto end = chrono::high_resolution_clock::now(); // Окончание отсчета время сорировки
    cout << "Вывод отсортированного массива" << endl;
    for (auto& it : array) // Вывод массива
        cout << it << " ";
    cout << endl;
    cout << "Количество операций срванения, присоения алгоритма сортировки: " << operation_counter << endl;
    cout << "Время работы алгоритма сортировки: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " наносекунд" << endl;
    return 0;
}