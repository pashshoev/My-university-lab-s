#include <iostream>
#include <fstream>
using namespace std;
unsigned long long int func( unsigned long long N,unsigned long long min=1000, unsigned long long int count = 0)
{
    if (count >=min)
        return 0;
    if ( N == 1)
        return count;
    else if (N % 2==0)
    {
        count++;
        return func(N / 2,min,count);
    }
    else
    {
        count++;
        return func(N * 3 + 1, min,count);
    }
}
int main()
{
    setlocale(LC_ALL, "ru");
    unsigned long long int N , M ;
    ifstream fin("INPUT.TXT");
    if (fin.is_open())
    {
        cout<<"File opened succesfuly\n";
        fin >> N;
        fin >> M;
    }
    else
    {
        cout << "Error! File INPUT.TXT not found";
        return 0;
    }
    fin.close();

    unsigned long long int  step_N = func(N); 
    unsigned long long int  min_step=step_N;
    unsigned long long int numK=N,step_k;
    unsigned long long int min = step_N;

    cout << "N=" << N << ", M=" << M << " Следовательно число К будем искать в диапазоне [" << N + 1 << "..." << N + M << "]\n";
    cout << "Число N" << ",  шаг=" << step_N << endl;

    for (unsigned long long int k = N+1; k <=N + M;k++)
    {
        step_k = func(k,min_step);
        if (step_k!=0)
            cout <<"Число "<<k<<" , шаг= "<<step_k <<endl;
        else 
            cout << "Число " << k << " , шаг > " << min_step << endl;
        if (step_k!=0)
        {
            numK = k;
            min_step = step_k;
        }
    }

    ofstream  fout("OUTPUT.TXT");
    if (fout.is_open())
    {
        if (min_step != step_N)
        {
            cout << "Число с минимальным  количеством шагов " << numK;
            fout << numK;
        }
        else
        {
            cout << "Такого числа нет\n";
            fout << "NO";
        }
    }
    else
    {
        cout << "Error while opening file to write";
        return 0;
    }
    fout.close();
    return 0;
}

