// Лабораторная работа №3, часть 1. Вариант 18.
// Класс Vector (вектор из int). Перегружена операция префиксного декремента --
// (каждый элемент уменьшается на 1, результат - измененный вектор), а также
// операции [], = (копирование и перемещение), << и >>.
// Входные данные читаются из input.txt, результаты выводятся в output.txt.
#include <iostream>
#include <fstream>
using namespace std;
class Vector // Класс- вектор
{
    int *p=nullptr; // Указатель на массив (вектор)
    int n=0; // Размерность вектора (число элементов) массива
public:
    Vector() // Конструктор без параметров, задает "пустой" объект
    {
        p = nullptr; n = 0;
        cout<<"Vector()"<<endl;
    }
    Vector(int *p, int n) // Конструктор на входе массив, задающий вектор
    {
        this->n = n; // Задаем число элементов
        this->p = new int[n]; // Выделяем память
        for (int i = 0; i < n; i++) this->p[i] = p[i]; // Копируем один массив в другой
        cout<<"Vector(int *p, int n)"<<endl;
    }
    Vector(const Vector & V) // Конструктор копирования
    {
        n = V.n;
        p = new int[n];
        for (int i = 0; i < n; i++) p[i] = V.p[i];
        cout<<"Vector(const Vector & V) n="<<n<<endl;
    }
    Vector(Vector&& V) // Конструктор перемещения, параметр - правосторонняя ссылка
    {
        std::swap(p, V.p);
        std::swap(n, V.n);
        cout<<"Vector(Vector&& V)"<<endl;
    }
    ~Vector() // Деструктор
    {
        cout<<"~Vector() n="<<n<<endl;
        if (p!=nullptr) delete[] p; // Освобождаем память
    }
    int& operator[](int index) // Оператор- функция обращения к элементу
    {
        return p[index];
    }
    Vector & operator =(const Vector& v2) // Оператор- функция копирования объекта
    {
        if (this!=&v2) // Запрет копирования вектора самого в себя
        {
            n = v2.n;
            if (p != nullptr) delete[] p; // Освобождаем память старого вектора
            p = new int[n]; // Выделяем память для нового вектора
            for (int i = 0; i < n; i++) p[i] = v2.p[i];
        }
        cout<<"Vector & operator =(const Vector& v2)"<<endl;
        return *this; // Возвращаем ссылку на текущий объект
    }
    Vector & operator =(Vector&& v2) // Оператор- функция перемещения объекта
    {
        if (this!=&v2) // Запрет перемещения вектора самого в себя
        {
            std::swap(p, v2.p);
            std::swap(n, v2.n);
        }
        cout<<"Vector & operator =(Vector&& v2)"<<endl;
        return *this; // Возвращаем ссылку на текущий объект
    }
    Vector & operator --() // Префиксный декремент: все элементы уменьшаются на 1
    {
        for (int i = 0; i < n; i++) p[i]--;
        return *this; // Результат - измененный вектор
    }
    friend ostream& operator <<(ostream& os, const Vector& V); // Дружественные функции,
    friend istream& operator >>(istream& is, Vector& V); // определенные вне класса
};
ostream& operator <<(ostream& os, const Vector& V) // Вставка вектора в поток
{
    os<<"n="<<V.n<<":";
    for (int i = 0; i < V.n; i++) os<<" "<<V.p[i];
    return os;
}
istream& operator >>(istream& is, Vector& V) // Извлечение вектора из потока
{
    int k;
    is>>k; // Сначала число элементов
    if (V.p != nullptr) delete[] V.p; // Освобождаем память старого вектора
    V.n = k;
    V.p = new int[k];
    for (int i = 0; i < k; i++) is>>V.p[i]; // Затем элементы
    return is;
}
int main()
{
    ifstream fin("input.txt"); // Входной файл, из него читаются все исходные данные
    ofstream fout("output.txt"); // Выходной файл, в него выводятся результаты
    int k; // Число элементов обычного массива
    int m[20]; // Обычный массив (в input.txt должно быть не больше 20 элементов)

    Vector V0; // Создаем пустой вектор, вызывается конструктор без параметров
    fout<<"V0 = "<<V0<<endl; // Печатаем вектор в файл с помощью перегруженной операции <<

    Vector V1; // Пустой вектор, в него прочитаем данные из файла
    fin>>V1; // Операция >> : сначала читается число элементов, затем сами элементы
    fout<<"V1 = "<<V1<<endl; // Вывод в файл для контроля ввода

    fin>>k; // Читаем из файла число элементов обычного массива
    for (int i = 0; i < k; i++) fin>>m[i]; // Читаем из файла элементы обычного массива
    Vector V2(m, k); // Создаем вектор на основе обычного массива
    fout<<"V2 = "<<V2<<endl;

    int old = V1[0]; // Операция [] : читаем элемент с индексом 0 (вектор не должен быть пустым)
    fout<<"V1[0] = "<<old<<endl;
    V1[0] = 30; // Операция [] слева от присваивания: записываем элемент
    fout<<"V1 after V1[0]=30: "<<V1<<endl;
    V1[0] = old; // Возвращаем прежнее значение элемента

    --V1; // Префиксный декремент: все элементы V1 уменьшаются на 1
    fout<<"V1 after --V1: "<<V1<<endl;
    Vector V3 = --V2; // Результат операции - измененный вектор, V3 создается копированием
    fout<<"V2 after --V2: "<<V2<<endl;
    fout<<"V3 = --V2:     "<<V3<<endl;

    Vector C1(V1); // Конструктор копирования: V1 не меняется
    fout<<"copy ctor: V1 = "<<V1<<endl;
    fout<<"           C1 = "<<C1<<endl;
    Vector C2(std::move(V1)); // Конструктор перемещения: V1 становится пустым
    fout<<"move ctor: V1 = "<<V1<<endl;
    fout<<"           C2 = "<<C2<<endl;

    Vector A1; // Пустой вектор для присваивания с копированием
    A1 = V3; // Присваивание с копированием: V3 не меняется
    fout<<"copy =:    V3 = "<<V3<<endl;
    fout<<"           A1 = "<<A1<<endl;
    Vector A2; // Пустой вектор для присваивания с перемещением
    A2 = std::move(V3); // Присваивание с перемещением: V3 становится пустым
    fout<<"move =:    V3 = "<<V3<<endl;
    fout<<"           A2 = "<<A2<<endl;
    return 0;
}
