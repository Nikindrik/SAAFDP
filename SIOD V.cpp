#include <iostream>
#include <random>
using namespace std;

void delSecondMethod(int* array, int& n, int key) {
    int operation_counter = 0;
    int j = 0;
    operation_counter++; // Присвоение
    for (int i = 0; i < n; ++i) {
        operation_counter++; // i < n
        array[j] = array[i]; // Сдвиг элемента на j-ый
        operation_counter++; //Присвоение
        if (array[i] != key) { // Если не нужно удалять
            ++j;
            operation_counter++; // Инкремент
        }
		operation_counter++; // Присвоение
    }
    operation_counter++; // Сравнение при выходе из цикла
    n = j;
    operation_counter++; // Присвоение
    cout << "Количество операций " << operation_counter << endl;
}

int main() {
    setlocale(LC_ALL, "Rus");
	int n, key;
	cin >> n >> key;
	int* array = new int[n]; // Массив
	cout << "Выберите тип заполнения массива" << endl;
	cout << "a - рандом" << endl;
	cout << "b - с одним заданым значением" << endl;
	char ty;
	cin >> ty;
	switch (ty) { //Конструкция switch case default для выбор типа заполения массива
	case 'a':
	{
		mt19937 gen(random_device{}()); // mt19937 gen - генератор случайных чисел
		uniform_int_distribution<int> dist(1, 10); // Инструмент, позволяющий генерировать случайное целое число в заданном диапазоне

		for (int i = 0; i < n; i++)
			array[i] = dist(gen); // Заполнение массива случайными значениями от 1 до 10
		for (int i = 0; i < n; ++i) // Вывод сгенериованного массива
			cout << array[i] << " ";
		cout << endl;
	}
	break;
	case 'b':
	{
		cout << "Введите значение" << endl;
		int x;
		cin >> x;
		for (int i = 0; i < n; i++)
			array[i] = x; // Заполнение массива значением x
		for (int i = 0; i < n; ++i) // Вывод сгенериованного массива
			cout << array[i] << " ";
		cout << endl;
	}
	break;
	default:
	{
		cout << "Допущенны ошибки" << endl;
		return -1; // Завершение программы при некоректных данных
	}
	}
	delSecondMethod(array, n, key);

	for (int i = 0; i < n; ++i)
		cout << array[i] << " ";
	delete[] array;
    return 0;
}