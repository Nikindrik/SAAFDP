#include <iostream>
#include <random>
using namespace std;

int findmax_duplicate(int** matrix, int n, int m) {
    int operation_counter = 0;
    int* countArray = new int[1000000](); // Используем массив для подсчета количества чисел, встречающихся в матрице
    operation_counter++; // Присвоение
    int max_duplicate = -1;
    operation_counter++; // Присвоение
    // Подсчитываем количество встречающихся чисел
    for (int i = 0; i < n; ++i) {
        operation_counter++; //  Сравнение при входе в цикл
        for (int j = 0; j < m; ++j) {
            operation_counter++; //  Сравнение при входе в цикл
            countArray[matrix[i][j]]++;
            operation_counter++; // Инкремент
            if (countArray[matrix[i][j]] > 1 && matrix[i][j] > max_duplicate) {
                max_duplicate = matrix[i][j];
                operation_counter++; // Присвоение
            }
        }
    }

    delete[] countArray; // Освобождаем выделенную память
    cout << "Количество операций " << operation_counter << endl;
    return max_duplicate;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int n, m;
    cout << "Введите размеры матрицы (n m): ";
    cin >> n >> m;

    int** matrix = new int* [n]; // Выделяем память для двумерного динамического массива
    for (int i = 0; i < n; ++i)
        matrix[i] = new int[m];

    cout << "Выберите тип заполнения массива" << endl;
    cout << "a - рандом" << endl;
    cout << "b - с одним заданым значением" << endl;
    cout << "c - заполняем матрицу элементами, где следующий больше предыдущего на 1" << endl;
    cout << "d - ручной ввод матрицы" << endl;
    char ty;
    cin >> ty;
    switch (ty) { //Конструкция switch case default для выбор типа заполения массива
    case 'a': {
        mt19937 gen(random_device{}()); // mt19937 gen - генератор случайных чисел
        uniform_int_distribution<int> dist(1,10); // Инструмент, позволяющий генерировать случайное целое число в заданном диапазоне

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; ++j)
                matrix[i][j] = dist(gen); // Заполнение матрицы случайными значениями от 0 до 10
        for (int i = 0; i < n; i++) { // Вывод сгенерированной матрицы
            for (int j = 0; j < m; ++j)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }
            break;
    case 'b': {
        cout << "Введите значение" << endl;
        int x;
        cin >> x;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; ++j)
                matrix[i][j] = x;
        for (int i = 0; i < n; i++) { // Вывод сгенерированной матрицы
            for (int j = 0; j < m; ++j)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }
            break;
    case 'c': {
        int c = 0; // Заполняем матрицу элементами, где следующий больше предыдущего на 1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = c;
                c += 1;
            }
        }
        for (int i = 0; i < n; i++) { // Вывод сгенерированной матрицы
            for (int j = 0; j < m; ++j)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }
            break;
    case 'd': {
        // Ручной ввдо матрицы
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; ++j) {
                cin >> matrix[i][j];
            }
        }
    }
            break;
    default: {
        cout << "Допущенны ошибки" << endl;
        return -1; // Завершение программы при некоректных данных
    }
    }
    int max_duplicate = findmax_duplicate(matrix, n, m);
    if (max_duplicate != -1)
        cout << "Максимальное число, встретившееся более одного раза: " << max_duplicate << endl;
    else
        cout << "В матрице нет чисел, встречающихся более одного раза." << endl;

    // Освобождаем память, выделенную для двумерного динамического массива
    for (int i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;
    return 0;
}