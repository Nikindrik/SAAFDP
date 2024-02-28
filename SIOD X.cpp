#include <iostream>
using namespace std;

int findMaxDuplicate(int** matrix, int n, int m) {
    int* countArray = new int[1000000](); // Используем массив для подсчета количества чисел, встречающихся в матрице
    int maxDuplicate = -1;

    // Подсчитываем количество встречающихся чисел
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            countArray[matrix[i][j]]++;
            if (countArray[matrix[i][j]] > 1 && matrix[i][j] > maxDuplicate)
                maxDuplicate = matrix[i][j];
        }
    }

    delete[] countArray; // Освобождаем выделенную память

    return maxDuplicate;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int n, m;
    cout << "Введите размеры матрицы (n m): ";
    cin >> n >> m;

    int** matrix = new int* [n]; // Выделяем память для двумерного динамического массива
    for (int i = 0; i < n; ++i)
        matrix[i] = new int[m];

    cout << "Введите элементы матрицы:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> matrix[i][j];

    int maxDuplicate = findMaxDuplicate(matrix, n, m);
    if (maxDuplicate != -1)
        cout << "Максимальное число, встретившееся более одного раза: " << maxDuplicate << endl;
    else
        cout << "В матрице нет чисел, встречающихся более одного раза." << endl;

    // Освобождаем память, выделенную для двумерного динамического массива
    for (int i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;
    return 0;
}