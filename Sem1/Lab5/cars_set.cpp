// Лабораторная работа №5. Вариант 18.
// Класс «автомобиль» из лабораторной работы №4 (поля: название модели, массив расходов
// топлива из 3-х элементов, максимальная скорость, мощность).
// Объекты добавляются в контейнер set (сортировка по названию модели, как в ЛР4)
// и в контейнер unordered_set. Исходные данные читаются из input.txt (как в ЛР4),
// объекты контейнеров выводятся в output.txt для контроля.
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>
using namespace std;

class Car // Класс - автомобиль
{
    string name;    // Название модели
    double fuel[3]; // Расход топлива: на трассе, в городе, смешанный
    int speed;      // Максимальная скорость
    int power;      // Мощность
public:
    Car() // Конструктор без параметров
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
    // в классе нет указателей и динамической памяти, поэтому подходят стандартные, которые
    // создает компилятор.
    string getName() const // Название модели (нужно для хеш-функции)
    {
        return name;
    }
    bool operator <(const Car & c) const // Для set: порядок по названию модели
    {
        return name < c.name;
    }
    bool operator ==(const Car & c) const // Для unordered_set: автомобили равны, если равны названия
    {
        return name == c.name;
    }
    friend ostream & operator <<(ostream & out, const Car & c); // Дружественная функция вставки в поток
};
ostream & operator <<(ostream & out, const Car & c) // Вставка объекта в поток
{
    out << c.name << ", fuel " << c.fuel[0] << "/" << c.fuel[1] << "/" << c.fuel[2]
        << " l/100km, max speed " << c.speed << " km/h, power " << c.power << " hp";
    return out;
}
struct CarHash // Хеш-функция для unordered_set: хеш от названия модели
{
    size_t operator()(const Car & c) const
    {
        return hash<string>()(c.getName());
    }
};

int main()
{
    ifstream fin("input.txt"); // Входной файл
    ofstream fout("output.txt"); // Выходной файл
    if (!fin) // Ошибка файл не открыт
    {
        cerr << "Error, input.txt not found" << endl;
        return 1;
    }
    int n; // Число автомобилей в файле
    fin >> n;
    fin.ignore(2, '\n'); // Пропускаем символы перехода на новую строку
    set<Car> s; // Упорядоченный контейнер
    unordered_set<Car, CarHash> u; // Неупорядоченный контейнер
    for (int i = 0; i < n; i++) // Читаем автомобили из файла и добавляем в оба контейнера
    {
        string name;
        double f1, f2, f3;
        int speed, power;
        getline(fin, name);
        fin >> f1 >> f2 >> f3 >> speed >> power;
        fin.ignore(2, '\n');
        Car c(name, f1, f2, f3, speed, power);
        s.insert(c); // Если автомобиль с таким названием уже есть, второй раз не добавляется
        u.insert(c);
    }
    fout << "Read from file: " << n << " cars" << endl << endl;
    fout << "set (sorted by model name), " << s.size() << " cars:" << endl;
    for (const Car & c : s) fout << c << endl; // Используем перегруженную операцию <<
    fout << endl << "unordered_set (order is not defined), " << u.size() << " cars:" << endl;
    for (const Car & c : u) fout << c << endl;
    return 0;
}
