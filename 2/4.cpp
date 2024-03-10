#include <iostream>
#include <random>
#include <vector>
#include <chrono>
using namespace std;

long long int selection_sort(vector<int>& arr) {
    long long int operations_counter = 0;
    for (int i = 0; i < arr.size(); ++i) {
        int min_ind = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[min_ind]) {
                min_ind = j; //  Теперь минимальный индекс равен текущему j-ому
                ++operations_counter; // Присвоение
            }
            ++operations_counter; // Сравнение
        }
        swap(arr[i], arr[min_ind]);
        operations_counter += 4; // Присвоение сравнение при входе и выходе из цикла
    }
    ++operations_counter; // Выход из цикла
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
    long long int operation_counter = selection_sort(array); // Вызов функции сортировки массива с воращением значения подсчета операций
    auto end = chrono::high_resolution_clock::now(); // Окончание отсчета время сорировки
    cout << "Вывод отсортированного массива" << endl;
    for (auto& it : array) // Вывод массива
        cout << it << " ";
    cout << endl;
    cout << "Количество операций срванения, присоения алгоритма сортировки: " << operation_counter << endl;
    cout << "Время работы алгоритма сортировки: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " наносекунд" << endl;
    return 0;
}