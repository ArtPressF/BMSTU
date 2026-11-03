// Лабораторная работа №2. Вариант 18.
// Структура «компьютер» (поля: тип процессора, тактовая частота, объем оперативной
// памяти, размер жесткого диска, тип видеокарты). Создается массив (вектор) компьютеров
// размерности n. Сохраняется в файле и читается из файла в текстовом или двоичном режимах.
// Режимы работы задаются параметрами командной строки: write или read, затем text или
// binary, затем имя файла. Например:
//   computers write text MyFile.txt    - запись, файл в текстовом режиме
//   computers read binary MyFile.dat   - чтение, файл в двоичном режиме
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
struct COMPUTER // Структура - компьютер
{
string cpu; // Тип процессора
double freq; // Тактовая частота (ГГц)
int ram; // Объем оперативной памяти (ГБ)
int disk; // Размер жесткого диска (ГБ)
string gpu; // Тип видеокарты
};
// Печатаем массив компьютеров
void print_computers(ostream & out, vector<COMPUTER> & Computers)
{
for (auto & pos : Computers)
out << "CPU: " << pos.cpu << ", " << pos.freq << " GHz, RAM " << pos.ram << " GB, disk " << pos.disk << " GB, GPU: " << pos.gpu << endl;
}
// Запись одного компьютера в файл в текстовом режиме
void write_text(ostream & out, COMPUTER & c)
{
out << c.cpu << endl << c.gpu << endl; // Каждая строка с новой строки
out << c.freq << ' ' << c.ram << ' ' << c.disk << endl; // Числа в одну строку через пробелы
}
// Запись одного компьютера в файл в двоичном режиме
void write_binary(ostream & out, COMPUTER & c)
{
out << c.cpu << ends << c.gpu << ends; // После строк вставляем 0, как признак конца
out.write((char *)&c.freq, sizeof(c.freq)); // Числа записываются как есть, по байтам
out.write((char *)&c.ram, sizeof(c.ram));
out.write((char *)&c.disk, sizeof(c.disk));
}
// Чтение одного компьютера из файла в текстовом режиме
void read_text(istream & in, COMPUTER & c)
{
in.ignore(2, '\n'); // Пропускаем символы перехода на новую строку
getline(in, c.cpu);
getline(in, c.gpu);
in >> c.freq >> c.ram >> c.disk;
}
// Чтение одного компьютера из файла в двоичном режиме
void read_binary(istream & in, COMPUTER & c)
{
getline(in, c.cpu, '\0'); // Символ '\0' читается из потока
getline(in, c.gpu, '\0');
in.read((char *)&c.freq, sizeof(c.freq));
in.read((char *)&c.ram, sizeof(c.ram));
in.read((char *)&c.disk, sizeof(c.disk));
}
int main(int argc, const char* argv[]) {
if (argc != 4) {
cerr << "Error: Use three parameters: write|read text|binary file_name\n";
return 5;
}
const string mode(argv[1]); // Режим работы (запись или чтение)
const string open_mode(argv[2]); // Режим открытия файла (текстовый или двоичный)
const string file_name(argv[3]); // Имя файла
int n; // Переменная, задающая число элементов массива
vector<COMPUTER> Computers; // Массив структур
if (mode == "write") { // Запись в файл
// Ввод данных с клавиатуры
cout << "n="; cin >> n; // Ввод числа компьютеров
Computers.resize(n); // Задаем размер массива (вектора)
cin.ignore(); // Пропускаем символ перехода на новую строку после n
for (int i = 0; i < n; i++) // Цикл ввода данных о компьютерах с клавиатуры
{
cout << "Computer N=" << (i + 1) << endl;
cout << "CPU: ";
getline(cin, Computers[i].cpu);
cout << "Frequency (GHz): "; cin >> Computers[i].freq;
cout << "RAM (GB): "; cin >> Computers[i].ram;
cout << "Disk (GB): "; cin >> Computers[i].disk;
cout << "GPU: ";
cin.ignore(); // Пропускаем символ перехода на новую строку после числа
getline(cin, Computers[i].gpu);
}
// Выводим введенные данные для контроля ввода
cout << endl << "Entered data:" << endl;
print_computers(cout, Computers);
if (open_mode == "text")
{
// Работа с файлом в текстовом режиме
ofstream foutt(file_name); // Открываем файл для записи в текстовом режиме
if (!foutt) // Ошибка файл не открыт
{
cerr << "Error, cannot open file" << endl;
return 1;
}
foutt << n << endl; // Записываем n в текстовом режиме, далее переход на новую строку
for (auto & pos : Computers) write_text(foutt, pos);
foutt.close(); // Закрываем файл
}
else
if (open_mode == "binary")
{
// Работа с файлом в двоичном режиме
ofstream foutb(file_name, ios::binary); // Открываем файл для записи в двоичном режиме
if (!foutb) // Ошибка файл не открыт
{
cerr << "Error, cannot open file" << endl;
return 1;
}
foutb.write((char *)&n, sizeof(n)); // Записываем n в двоичном режиме
for (auto & pos : Computers) write_binary(foutb, pos);
foutb.close(); // Закрываем файл
}
else {
cerr << "Error: second parameter must be text or binary\n";
return 5;
}
}
else if (mode == "read") {
// Чтение из файла
if (open_mode == "text")
{
ifstream fint(file_name); // Открываем файл для чтения в текстовом режиме
if (!fint) // Ошибка файл не открыт
{
cout << endl << "Error, file not found" << endl;
return 1;
}
fint >> n; // Читаем n в текстовом режиме
Computers.resize(n); // Задаем размер массива
for (auto & pos : Computers) read_text(fint, pos);
fint.close(); // Закрываем файл
}
else
if (open_mode == "binary")
{
ifstream finb(file_name, ios::binary); // Открываем файл для чтения в двоичном режиме
if (!finb) // Ошибка файл не открыт
{
cout << endl << "Error, file not found" << endl;
return 1;
}
finb.read((char *)&n, sizeof(n)); // Читаем n в двоичном режиме
Computers.resize(n); // Задаем размер массива
for (auto & pos : Computers) read_binary(finb, pos);
finb.close(); // Закрываем файл
}
else {
cerr << "Error: second parameter must be text or binary\n";
return 5;
}
// Печать компьютеров, прочитанных из файла
print_computers(cout, Computers);
}
else {
cerr << "Error: first parameter must be write or read\n";
return 5;
}
return 0;
}
