// Лабораторная работа №4. Вариант 18.
// Объект - автомобиль (поля: название модели, массив расходов топлива из 3-х элементов
// (на трассе, в городе, смешанный), максимальная скорость, мощность).
// Исходный контейнер list, копируем в vector. Сортировка по названию модели.
// Элементы контейнеров - объекты класса, а не указатели.
// Исходные данные читаются из input.txt, результаты выводятся в output.txt.
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm> // copy
using namespace std;

class Car // Класс - автомобиль
{
    string name;    // Название модели
    double fuel[3]; // Расход топлива: на трассе, в городе, смешанный
    int speed;      // Максимальная скорость
    int power;      // Мощность
public:
    Car() // Конструктор без параметров (нужен для vector, который создается заранее нужного размера)
    {
        name = "";
        fuel[0] = fuel[1] = fuel[2] = 0;
        speed = 0; power = 0;
    }
    Car(string name, double f1, double f2, double f3, int speed, int power) // Конструктор для инициализации полей
    {
        this->name = name;
        fuel[0] = f1; fuel[1] = f2; fuel[2] = f3;
        this->speed = speed; this->power = power;
    }
    // Конструктор копирования, конструктор перемещения и операции присваивания не нужны:
    // в классе нет указателей и динамической памяти, string и массив из 3 чисел копируются
    // и перемещаются корректно стандартными средствами, которые создает компилятор.
    bool operator <(const Car & c) const // Сравнение по названию модели (для сортировки list::sort)
    {
        return name < c.name;
    }
    friend ostream & operator <<(ostream & out, const Car & c); // Дружественная функция вставки в поток
};
ostream & operator <<(ostream & out, const Car & c) // Вставка объекта в поток
{
    out << c.name << ", fuel " << c.fuel[0] << "/" << c.fuel[1] << "/" << c.fuel[2]
        << " l/100km, max speed " << c.speed << " km/h, power " << c.power << " hp";
    return out;
}

int main()
{
    ifstream fin("input.txt"); // Входной файл
    ofstream fout("output.txt"); // Выходной файл
    if (!fin) // Ошибка файл не открыт
    {
        cerr << "Error, input.txt not found" << endl;
        return 1;
    }
    int n; // Число автомобилей
    fin >> n;
    fin.ignore(2, '\n'); // Пропускаем символы перехода на новую строку
    list<Car> cars; // Исходный контейнер list
    for (int i = 0; i < n; i++) // Читаем автомобили из файла
    {
        string name;
        double f1, f2, f3;
        int speed, power;
        getline(fin, name); // Название модели - строка, может содержать пробелы
        fin >> f1 >> f2 >> f3 >> speed >> power; // Остальные поля в одной строке
        fin.ignore(2, '\n');
        cars.push_back(Car(name, f1, f2, f3, speed, power));
    }

    // Копируем исходный контейнер list в vector алгоритмом copy (до сортировки)
    vector<Car> copy_cars(cars.size()); // Нужный размер вектора задаем заранее
    copy(cars.begin(), cars.end(), copy_cars.begin());

    fout << "Source container (list):" << endl;
    for (const Car & c : cars) fout << c << endl; // Используем перегруженную операцию <<

    cars.sort(); // Сортировка list методом sort без параметров (по названию модели)
    fout << endl << "Container after sorting (list::sort by model name):" << endl;
    for (const Car & c : cars) fout << c << endl;

    fout << endl << "Copy of the source container (vector, algorithm copy):" << endl;
    for (const Car & c : copy_cars) fout << c << endl;

    if (n > 0) // Демонстрация копирования объекта (стандартные конструктор копирования и присваивание)
    {
        Car first = cars.front(); // Конструктор копирования
        Car other;
        other = first; // Присваивание с копированием
        fout << endl << "Copy constructor: " << first << endl;
        fout << "Assignment:       " << other << endl;
    }
    return 0;
}
