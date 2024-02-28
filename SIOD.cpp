#include <iostream>
#include <random>
using namespace std;


void delFirstMethod(int* x, int& n, int key) {
	int operation_counter = 0; // Счетчик кол-ва операций
	int i = 0;
	++operation_counter; // Присвоение i = 0
	while (i < n) { // Итерирование массива x
		++operation_counter; // i < n
		if (x[i] == key) { // Если элемент массива i-ый равен значению key, то удаляем элемент
			for (int j = i; j < n - 1; ++j) { // Сдвиг элементов x с i-ого влево
				++operation_counter; // j < n - 1
				x[j] = x[j + 1];
				++operation_counter; // Присвоение x[j] = x[j + 1]
			}
			--n;
			++operation_counter; // Дискримент
		}
		else {
			++i;
			++operation_counter; // Икримент
		}
	}
	cout << "Количество операций: " << operation_counter << endl;
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
	delFirstMethod(array, n, key);

	for (int i = 0; i < n; ++i)
		cout << array[i] << " ";
	delete[] array;
	return 0;
}










	//mt19937 gen(random_device{}()); // mt19937 gen - генератор случайных чисел
	//uniform_int_distribution<int> dist(1, 10); // Инструмент, позволяющий генерировать случайное целое число в заданном диапазоне

	//for (int i = 0; i < n; i++)
	//	array[i] = dist(gen); // Заполнение массива случайными значениями от 1 до 10
	//for (int i = 0; i < n; ++i) // Вывод сгенериованного массива
	//	cout << array[i] << " ";