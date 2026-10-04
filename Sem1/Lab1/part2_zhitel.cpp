// Лабораторная работа №1, часть 2. Вариант 18.
// Структура «Житель»: ФИО, адрес (улица, номер дома, номер квартиры), пол, возраст.
// Задача: определить, сколько детей от 1 года до 5 лет проживают в заданном доме.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Adres // Структура «адрес»
{
    string ulica; // Улица
    int dom;      // Номер дома
    int kv;       // Номер квартиры
};

struct Zhitel // Структура «житель»
{
    string fio;  // ФИО
    Adres adres; // Адрес
    string pol;  // Пол
    int vozrast; // Возраст
};

// Ввод одного жителя с клавиатуры
void inputZhitel(Zhitel& z)
{
    cout << "ФИО: ";
    getline(cin, z.fio);
    cout << "Улица: ";
    getline(cin, z.adres.ulica);
    cout << "Номер дома: ";
    cin >> z.adres.dom;
    cout << "Номер квартиры: ";
    cin >> z.adres.kv;
    cout << "Пол (м/ж): ";
    cin >> z.pol;
    cout << "Возраст: ";
    cin >> z.vozrast;
    cin.ignore(); // После ввода числа в буфере остается символ '\n', его игнорируем
}

// Вывод одного жителя на консоль
void printZhitel(const Zhitel& z)
{
    cout << z.fio << ", ул. " << z.adres.ulica << ", д. " << z.adres.dom
         << ", кв. " << z.adres.kv << ", пол: " << z.pol
         << ", возраст: " << z.vozrast << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian"); // Чтобы в консоли выводились русские буквы
    int n; // Число жителей в базе
    cout << "n = ";
    cin >> n;
    cin.ignore();

    vector<Zhitel> baza(n); // Массив жителей, размер известен только во время работы
    for (int i = 0; i < n; i++)
    {
        cout << endl << "Житель №" << i + 1 << endl;
        inputZhitel(baza[i]);
    }

    cout << endl << "Введенные данные:" << endl; // Вывод для контроля ввода
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ". ";
        printZhitel(baza[i]);
    }

    int dom;
    cout << endl << "Номер дома: ";
    cin >> dom;

    int k = 0; // Число детей от 1 года до 5 лет в заданном доме
    for (const Zhitel& z : baza)
        if (z.adres.dom == dom && z.vozrast >= 1 && z.vozrast <= 5)
            k++;

    cout << "Детей от 1 года до 5 лет в доме " << dom << ": " << k << endl;
    return 0;
}
