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

int partition(vector<int>& arr, int low, int high) { // Функция для разделения массива и возврата индекса опорного элемента
    int pivot = arr[high]; // Опорный элемент
    int i = (low - 1); // Индекс меньшего элемента
    for (int j = low; j <= high - 1; j++) {
        // Если текущий элемент меньше или равен опорному
        if (arr[j] <= pivot) {
            i++; // Увеличиваем индекс меньшего элемента
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Основная функция сортировки
void quick_sort(vector<int>& arr, int low, int high) { // Основная функция быстрой сортировки сортировки
    if (low < high) {
        int pi = partition(arr, low, high);  // индекс разделения, arr[p] сейчас на правильной позиции
        // Рекурсивно сортируем элементы до разделения и после
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void Qsort(vector<int>& arr) { // Функция для вызова быстрой сортировки
    int size = arr.size();
    quick_sort(arr, 0, size - 1); // Вызывает сортировку
    reverse(arr.begin(), arr.end()); // Отвечает за реверс массива
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
        //for (int i = 0; i < n; i++) // Вывод сгенерированого массива
        //        cout << array[i] << " ";
        //cout << endl;
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
    
    Qsort(array); // Получаем реверстнутый массив
    cout << "Вывод отсортированного по убыванию массива" << endl;
    for (auto& it : array) // Вывод массива
        cout << it << " ";
    cout << endl;
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