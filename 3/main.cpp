#include <iostream>
#include <random>
#include <vector>
#include <chrono>   
using namespace std;

long long int shell_sort(vector<int>& arr) {
    long long int operation_counter = 0;
    int n = arr.size();
    // Генерация последовательности смещений Кнута
    int h = 1;
    operation_counter += 2; // Присвоения
    while (h < n / 3) {
        h = 3 * h + 1;
        operation_counter += 2; // Присовение и сравнение с условием
    }

    while (h >= 1) { // Начало сортировки
        for (int i = h; i < n; i++) { // Вставочная сортировка для каждого смещения
            // Вставка arr[i] среди arr[i-h], arr[i-2*h], arr[i-3*h]...
            int key = arr[i]; // Ключ i-ого
            int j = i;
            while (j >= h && arr[j - h] > key) {
                arr[j] = arr[j - h];
                j -= h;
                operation_counter += 2; // Присвоения
            }
            arr[j] = key;
            operation_counter += 3; // Присвоения
        }
        h /= 3; // Уменьшение смещения
        ++operation_counter; // Присвоение
    }
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
    long long int operation_counter = shell_sort(array); // Вызов функции сортировки массива с воращением значения подсчета операций
    auto end = chrono::high_resolution_clock::now(); // Окончание отсчета время сорировки
    cout << "Вывод отсортированного массива" << endl;
    for (auto& it : array) // Вывод массива
        cout << it << " ";
    cout << endl;
    cout << "Количество операций срванения, присоения алгоритма сортировки: " << operation_counter << endl;
    cout << "Время работы алгоритма сортировки: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    return 0;
}