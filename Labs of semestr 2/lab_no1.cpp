#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

void writing(int* arr, int size, string file)
{
    //Открытие файла для записи
    ofstream fout;
    fout.open("myArray.txt");
    if (fout.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            if (i)
                fout << " ";
            fout << arr[i];

        }
        cout << "Массив  успешно записан в файл " << file << endl;
    }
    else
    {
        cout << "Не удалось открыт файл\n";
    }
    fout.close();
    //Закрытие файла 
}
void reading(int* arr, int size,string file)
{
    ifstream fin;
    fin.open(file);
    if (fin.is_open())
    {
        int  num, i = 0;
        while (!fin.eof())
        {
            num = 0;
            fin >> num;
            sizeof(num);
            arr[i] = num;
            i++;
        }
        cout << "Данные успешно прочитаны из файла и записаны в массив " << endl;
    }
    else
    {
        cout << "Не удалось открыть файл\n";
    }
    fin.close();
}
void find_couple(int* arr, int size)
{   
    ofstream fout;
    fout.open("myRes.txt");
    if (fout.is_open() && size%2==0)
    {
        int k;
        for (int i = 0; i < size; i += 2)
        {
            k = i + 2;
            for (; k < size; k += 2)
            {
                if (arr[i] == -arr[k] )//тут можно было " обьединить if-ы", но я сделал двойной if чтобы каждый раз не сравниват 4 элемента
                {
                   if  (arr[i + 1] == arr[k + 1])
                    {
                        cout << " (" << arr[i] << "," << arr[i + 1] << ")" << "(" << arr[k] << "," << arr[k + 1] << ")  ";
                        fout << arr[i] << " " << arr[i + 1] << " " << arr[k] << " " << arr[k + 1] << " ";
                    }
                }
            }
        }
        cout << "\nДанные пары записаны в файл myRes.txt\n";
    }
    else
    {
        cout << " Error !\n";
    }
    fout.close();
}

int main(){
    setlocale(LC_ALL, "rus");
    system("color 2");

    int const size = 24;
    int arr_for_writing[size] = { 1,2, -1,2 ,3,3, -5,4, 5,-4, 0,0, 1,5, -1,5, 6,1, -6,1 ,1,-1,-1,-1};

    int* mass = new int[size];
    string name = "myArray.txt";

    writing(arr_for_writing, size,name);
    
    reading(mass, size, name);

//////////////////////////////////////////////////////

    
    cout << "Исходный массив \n";
    for (int i = 0; i < size; i++)
    {
        cout << mass[i] << " ";
    }
    cout << " \nСимметричные пары относительно оси OY\n";
    find_couple(mass, size);
    cout << "\n\n\n";

    delete[] mass;
    mass = nullptr;
}

