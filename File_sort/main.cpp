#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void write_arr(const string& filename, const int* arr, const int n)
{
    fstream fs;

    fs.open(filename, fstream::out);

    if (fs.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            fs << arr[i] << ' ';
        }
        fs << '\n';

        fs.close();
    }
}

void merging_Sort(string name)
{
    int a1, a2, k, i, j, num;
    fstream fs, fs1, fs2;
    num = 0;

    fs.open(name, fstream::in);

    if (fs.is_open())
    {
        while (!fs.eof())
        {
            fs >> a1;
            num++;
        }
        fs.close();
    }

    k = 1;
    while (k < num)
    {
        fs.open(name, fstream::in);
        fs1.open("msort_1.txt", fstream::out);
        fs2.open("msort_2.txt", fstream::out);

        if (!fs.eof())
        {
            fs >> a1;
        }

        while (!fs.eof())
        {
            for (i = 0; i < k && !fs.eof(); i++)
            {
                fs1 << a1 << ' ';
                fs >> a1;
            }
            for (j = 0; j < k && !fs.eof(); j++)
            {
                fs2 << a1 << ' ';
                fs >> a1;
            }
        }
        fs2.close();
        fs1.close();
        fs.close();

        fs.open(name, fstream::out);
        fs1.open("msort_1.txt", fstream::in);
        fs2.open("msort_2.txt", fstream::in);
        if (!fs1.eof())
        {
            fs1 >> a1;
        }
        if (!fs2.eof())
        {
            fs2 >> a2;
        }

        while (!fs1.eof() && !fs2.eof())
        {
            i = 0;
            j = 0;
            while (i < k && j < k && !fs1.eof() && !fs2.eof())
            {
                if (a1 < a2)
                {
                    fs << a1 << ' ';
                    fs1 >> a1;
                    i++;
                }
                else
                {
                    fs << a2 << ' ';
                    fs2 >> a2;
                    j++;
                }
            }
            while (i < k && !fs1.eof())
            {
                fs << a1 << ' ';
                fs1 >> a1;
                i++;
            }
            while (j < k && !fs2.eof())
            {
                fs << a2 << ' ';
                fs2 >> a2;
                j++;
            }
        }
        while (!fs1.eof())
        {
            fs << a1 << ' ';
            fs1 >> a1;
        }
        while (!fs2.eof())
        {
            fs << a2 << ' ';
            fs2 >> a2;
        }
        fs2.close();
        fs1.close();
        fs.close();
        k *= 2;
    }
    remove("msort_1.txt");
    remove("msort_2.txt");
}

int main()
{
    string filename = "array_data.txt";
    const int size = 500000;
    int* rand_arr = new int[size];

    srand(time(nullptr)); // используем текущее время, чтобы сгенерировать рандомные значения
    int lef_border = 5;
    int range_len = 100; // правая граница = range_len + left_border
    for (int i = 0; i < size; i++)
    {
        rand_arr[i] = lef_border + rand() % range_len; // генерируем число в указанном диапазоне и записываем в массив
    }

    write_arr(filename, rand_arr, size); // записываем массив в файл

    merging_Sort(filename); // запускаем сортировку

    delete[] rand_arr;

    return 0;
}