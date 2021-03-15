// LabNo4_sem3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<vector>
#include<cmath>
using namespace std;
#pragma comment(linker,"/STACK:5000000")
int main()
{
    setlocale(LC_ALL, "");
    const int N=10, M=10;
    vector<vector<int>> Gray(N, vector<int>(M));
    vector<vector<vector<int>>> img(3, vector<vector<int>>(N, vector<int>(M)));
    for (int j = 0; j < N; j++)
    {
        for (int k = 0; k < M; k++)
        {
            img[0][j][k] = rand() % 256;
            img[1][j][k] = rand() % 256;
            img[2][j][k] = rand() % 256;
        }
    }
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < M; k++)
            {
                cout << img[i][j][k]<<" ";
            }
            cout << endl;
        }
        cout << "\n\n";
    }


    ///// Конвертируем в Чернобелое
    for (int j = 0; j < N; j++)
    {
        for (int k = 0; k < M; k++)
        {
            Gray[j][k] = 0.3 * img[0][j][k] + 0.5 * img[1][j][k] + 0.11 * img[2][j][k];
        }
        cout << endl;
    }



    // Задание 4.1. Свертка
    const int f_size = 3;
    int Filter[f_size][f_size] = { {1,0,0},{0,0,0},{0,0,-1} };
    const int n1 = N - f_size + 1, m1 = M - f_size + 1;

    vector<vector<int>> Filtred(n1, vector<int>(m1));
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            int sum=0;
            for (int g1 = i,f1=0;  g1 < i + f_size;  g1++,f1++)
            {
                for (int g2 = j,f2=0;  g2 < j + f_size;  g2++,f2++)
                {
                    sum += Filter[f1][f2] * Gray[g1][g2];
                }        
            }
            Filtred[i][j] = sum;
        }
    }
    cout << "\n\nПосле свертки \n\n";
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            cout << Filtred[i][j] << " ";
        }
        cout << endl;
    }

    //Задание 4.2. Активация Soft PLus , y=ln(1+e^x)

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            Filtred[i][j] = log(1 + exp(Filtred[i][j]));
        }
    }

    cout << "\n\nПосле функции активации Soft Plus y=ln(1+e^x)\n\n";

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            cout << Filtred[i][j] << " ";
        }
        cout << endl;
    }


    //// Задание 4.3.Пулинг    size=(n+2p-f)/s+1
    const int p_size = 2,stride=2;
    const int n2 = (n1 - p_size) / stride + 1;
    const int m2 = (m1 - p_size) / stride + 1;
    vector<vector<int>> Pooled(n2, vector<int>(m2));
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            double sum = 0;
            for (int g1 = i*stride; g1 < i*stride + p_size; g1++)
            {
                for (int g2 = j*stride; g2 < j* stride + p_size; g2++)
                {
                    sum += Filtred[g1][g2];
                }            
            }
            Pooled[i][j] = sum / (p_size * p_size);
        }
    }
    cout << "\n\nПосле average pooling 2x2 \n\n";
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            cout << Pooled[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n\nEND\n\n";
}
