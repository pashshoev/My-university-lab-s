//Ириска весит X грамм, мандарин – Y грамм, пряник – Z грамм.
//Требуется написать программу, которая определит, сколько различных вариантов подарков весом ровно W грамм может сделать Дед Мороз.
//Входные данные
//      В единственной строке входного файла INPUT.TXT содержится четыре целых числа X, Y, Z и W(1 ≤ X, Y, Z ≤ 100, 1 ≤ W ≤ 1000).
//Выходные данные
//      Выходной файл OUTPUT.TXT должен содержать одно целое число – количество вариантов подарков.
#include<fstream>
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "ru");
    ifstream fin("INPUT.TXT");
    int X, Y, Z ,W, res = 0;

    if (!fin.is_open())
    {
        cout << "Не удалось открыт файл INPUT.TXT";
        return 0;
    }
    fin >> X>> Y >>Z >> W;
    fin.close();

    cout << X << "  " << Y << " " << Z << " " << W;
    int xi_sf;

    for (int xi = 0; xi * X<=W; xi++)
    {
         xi_sf = xi * X;
         for (int yi = 0; xi_sf + yi * Y <= W; yi++)
         {
             if ((W - (xi_sf + yi * Y)) % Z == 0)
             {
                 res++;
             }
         }
    }
    ofstream fout("OUTPUT.TXT");
    fout << res;
    fout.close();
    cout <<endl<<res;
}

